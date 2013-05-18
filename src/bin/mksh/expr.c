/*	$OpenBSD: expr.c,v 1.19 2006/04/10 14:38:59 jaredy Exp $	*/

#include "sh.h"

__RCSID("$MirOS: src/bin/mksh/expr.c,v 1.24 2009/04/07 18:41:35 tg Exp $");

/* The order of these enums is constrained by the order of opinfo[] */
enum token {
	/* some (long) unary operators */
	O_PLUSPLUS = 0, O_MINUSMINUS,
	/* binary operators */
	O_EQ, O_NE,
	/* assignments are assumed to be in range O_ASN .. O_BORASN */
	O_ASN, O_TIMESASN, O_DIVASN, O_MODASN, O_PLUSASN, O_MINUSASN,
	O_LSHIFTASN, O_RSHIFTASN, O_BANDASN, O_BXORASN, O_BORASN,
	O_LSHIFT, O_RSHIFT,
	O_LE, O_GE, O_LT, O_GT,
	O_LAND,
	O_LOR,
	O_TIMES, O_DIV, O_MOD,
	O_PLUS, O_MINUS,
	O_BAND,
	O_BXOR,
	O_BOR,
	O_TERN,
	O_COMMA,
	/* things after this aren't used as binary operators */
	/* unary that are not also binaries */
	O_BNOT, O_LNOT,
	/* misc */
	OPEN_PAREN, CLOSE_PAREN, CTERN,
	/* things that don't appear in the opinfo[] table */
	VAR, LIT, END, BAD
};
#define IS_BINOP(op) (((int)op) >= (int)O_EQ && ((int)op) <= (int)O_COMMA)
#define IS_ASSIGNOP(op)	((int)(op) >= (int)O_ASN && (int)(op) <= (int)O_BORASN)

/* precisions; used to be enum prec but we do arithmetics on it */
#define P_PRIMARY	0	/* VAR, LIT, (), ~ ! - + */
#define P_MULT		1	/* * / % */
#define P_ADD		2	/* + - */
#define P_SHIFT		3	/* << >> */
#define P_RELATION	4	/* < <= > >= */
#define P_EQUALITY	5	/* == != */
#define P_BAND		6	/* & */
#define P_BXOR		7	/* ^ */
#define P_BOR		8	/* | */
#define P_LAND		9	/* && */
#define P_LOR		10	/* || */
#define P_TERN		11	/* ?: */
#define P_ASSIGN	12	/* = *= /= %= += -= <<= >>= &= ^= |= */
#define P_COMMA		13	/* , */
#define MAX_PREC	P_COMMA

struct opinfo {
	char		name[4];
	int		len;	/* name length */
	int		prec;	/* precedence: lower is higher */
};

/* Tokens in this table must be ordered so the longest are first
 * (eg, += before +).  If you change something, change the order
 * of enum token too.
 */
static const struct opinfo opinfo[] = {
	{ "++",	 2, P_PRIMARY },	/* before + */
	{ "--",	 2, P_PRIMARY },	/* before - */
	{ "==",	 2, P_EQUALITY },	/* before = */
	{ "!=",	 2, P_EQUALITY },	/* before ! */
	{ "=",	 1, P_ASSIGN },		/* keep assigns in a block */
	{ "*=",	 2, P_ASSIGN },
	{ "/=",	 2, P_ASSIGN },
	{ "%=",	 2, P_ASSIGN },
	{ "+=",	 2, P_ASSIGN },
	{ "-=",	 2, P_ASSIGN },
	{ "<<=", 3, P_ASSIGN },
	{ ">>=", 3, P_ASSIGN },
	{ "&=",	 2, P_ASSIGN },
	{ "^=",	 2, P_ASSIGN },
	{ "|=",	 2, P_ASSIGN },
	{ "<<",	 2, P_SHIFT },
	{ ">>",	 2, P_SHIFT },
	{ "<=",	 2, P_RELATION },
	{ ">=",	 2, P_RELATION },
	{ "<",	 1, P_RELATION },
	{ ">",	 1, P_RELATION },
	{ "&&",	 2, P_LAND },
	{ "||",	 2, P_LOR },
	{ "*",	 1, P_MULT },
	{ "/",	 1, P_MULT },
	{ "%",	 1, P_MULT },
	{ "+",	 1, P_ADD },
	{ "-",	 1, P_ADD },
	{ "&",	 1, P_BAND },
	{ "^",	 1, P_BXOR },
	{ "|",	 1, P_BOR },
	{ "?",	 1, P_TERN },
	{ ",",	 1, P_COMMA },
	{ "~",	 1, P_PRIMARY },
	{ "!",	 1, P_PRIMARY },
	{ "(",	 1, P_PRIMARY },
	{ ")",	 1, P_PRIMARY },
	{ ":",	 1, P_PRIMARY },
	{ "",	 0, P_PRIMARY }
};

typedef struct expr_state Expr_state;
struct expr_state {
	const char *expression;		/* expression being evaluated */
	const char *tokp;		/* lexical position */
	struct tbl *val;		/* value from token() */
	struct tbl *evaling;		/* variable that is being recursively
					 * expanded (EXPRINEVAL flag set) */
	int noassign;			/* don't do assigns (for ?:,&&,||) */
	enum token tok;			/* token from token() */
	bool arith;			/* evaluating an $(()) expression? */
	bool natural;			/* unsigned arithmetic calculation */
};

#define bivui(x, op, y)	(es->natural ?			\
	    (mksh_ari_t)((x)->val.u op (y)->val.u) :	\
	    (mksh_ari_t)((x)->val.i op (y)->val.i)	\
	)
#define chvui(x, op)	do {			\
	if (es->natural)			\
		(x)->val.u = op (x)->val.u;	\
	else					\
		(x)->val.i = op (x)->val.i;	\
} while (/* CONSTCOND */ 0)
#define stvui(x, n)	do {			\
	if (es->natural)			\
		(x)->val.u = (n);		\
	else					\
		(x)->val.i = (n);		\
} while (/* CONSTCOND */ 0)

enum error_type {
	ET_UNEXPECTED, ET_BADLIT, ET_RECURSIVE,
	ET_LVALUE, ET_RDONLY, ET_STR
};

static void evalerr(Expr_state *, enum error_type, const char *)
    __attribute__((noreturn));
static struct tbl *evalexpr(Expr_state *, int);
static void exprtoken(Expr_state *);
static struct tbl *do_ppmm(Expr_state *, enum token, struct tbl *, bool);
static void assign_check(Expr_state *, enum token, struct tbl *);
static struct tbl *tempvar(void);
static struct tbl *intvar(Expr_state *, struct tbl *);

/*
 * parse and evaluate expression
 */
int
evaluate(const char *expr, mksh_ari_t *rval, int error_ok, bool arith)
{
	struct tbl v;
	int ret;

	v.flag = DEFINED|INTEGER;
	v.type = 0;
	ret = v_evaluate(&v, expr, error_ok, arith);
	*rval = v.val.i;
	return (ret);
}

/*
 * parse and evaluate expression, storing result in vp.
 */
int
v_evaluate(struct tbl *vp, const char *expr, volatile int error_ok,
    bool arith)
{
	struct tbl *v;
	Expr_state curstate;
	Expr_state * const es = &curstate;
	int i;

	/* save state to allow recursive calls */
	curstate.expression = curstate.tokp = expr;
	curstate.noassign = 0;
	curstate.arith = arith;
	curstate.evaling = NULL;
	curstate.natural = false;

	newenv(E_ERRH);
	i = sigsetjmp(e->jbuf, 0);
	if (i) {
		/* Clear EXPRINEVAL in of any variables we were playing with */
		if (curstate.evaling)
			curstate.evaling->flag &= ~EXPRINEVAL;
		quitenv(NULL);
		if (i == LAEXPR) {
			if (error_ok == KSH_RETURN_ERROR)
				return (0);
			errorfz();
		}
		unwind(i);
		/* NOTREACHED */
	}

	exprtoken(es);
	if (es->tok == END) {
		es->tok = LIT;
		es->val = tempvar();
	}
	v = intvar(es, evalexpr(es, MAX_PREC));

	if (es->tok != END)
		evalerr(es, ET_UNEXPECTED, NULL);

	if (es->arith && es->natural)
		vp->flag |= INT_U;
	if (vp->flag & INTEGER)
		setint_v(vp, v, es->arith);
	else
		/* can fail if readonly */
		setstr(vp, str_val(v), error_ok);

	quitenv(NULL);

	return (1);
}

static void
evalerr(Expr_state *es, enum error_type type, const char *str)
{
	char tbuf[2];
	const char *s;

	es->arith = false;
	switch (type) {
	case ET_UNEXPECTED:
		switch (es->tok) {
		case VAR:
			s = es->val->name;
			break;
		case LIT:
			s = str_val(es->val);
			break;
		case END:
			s = "end of expression";
			break;
		case BAD:
			tbuf[0] = *es->tokp;
			tbuf[1] = '\0';
			s = tbuf;
			break;
		default:
			s = opinfo[(int)es->tok].name;
		}
		warningf(true, "%s: unexpected '%s'", es->expression, s);
		break;

	case ET_BADLIT:
		warningf(true, "%s: bad number '%s'", es->expression, str);
		break;

	case ET_RECURSIVE:
		warningf(true, "%s: expression recurses on parameter '%s'",
		    es->expression, str);
		break;

	case ET_LVALUE:
		warningf(true, "%s: %s requires lvalue",
		    es->expression, str);
		break;

	case ET_RDONLY:
		warningf(true, "%s: %s applied to read only variable",
		    es->expression, str);
		break;

	default: /* keep gcc happy */
	case ET_STR:
		warningf(true, "%s: %s", es->expression, str);
		break;
	}
	unwind(LAEXPR);
}

static struct tbl *
evalexpr(Expr_state *es, int prec)
{
	struct tbl *vl, *vr = NULL, *vasn;
	enum token op;
	mksh_ari_t res = 0;

	if (prec == P_PRIMARY) {
		op = es->tok;
		if (op == O_BNOT || op == O_LNOT || op == O_MINUS ||
		    op == O_PLUS) {
			exprtoken(es);
			vl = intvar(es, evalexpr(es, P_PRIMARY));
			if (op == O_BNOT)
				chvui(vl, ~);
			else if (op == O_LNOT)
				chvui(vl, !);
			else if (op == O_MINUS)
				chvui(vl, -);
			/* op == O_PLUS is a no-op */
		} else if (op == OPEN_PAREN) {
			exprtoken(es);
			vl = evalexpr(es, MAX_PREC);
			if (es->tok != CLOSE_PAREN)
				evalerr(es, ET_STR, "missing )");
			exprtoken(es);
		} else if (op == O_PLUSPLUS || op == O_MINUSMINUS) {
			exprtoken(es);
			vl = do_ppmm(es, op, es->val, true);
			exprtoken(es);
		} else if (op == VAR || op == LIT) {
			vl = es->val;
			exprtoken(es);
		} else {
			evalerr(es, ET_UNEXPECTED, NULL);
			/* NOTREACHED */
		}
		if (es->tok == O_PLUSPLUS || es->tok == O_MINUSMINUS) {
			vl = do_ppmm(es, es->tok, vl, false);
			exprtoken(es);
		}
		return (vl);
	}
	vl = evalexpr(es, prec - 1);
	for (op = es->tok; IS_BINOP(op) && opinfo[(int)op].prec == prec;
	    op = es->tok) {
		exprtoken(es);
		vasn = vl;
		if (op != O_ASN) /* vl may not have a value yet */
			vl = intvar(es, vl);
		if (IS_ASSIGNOP(op)) {
			assign_check(es, op, vasn);
			vr = intvar(es, evalexpr(es, P_ASSIGN));
		} else if (op != O_TERN && op != O_LAND && op != O_LOR)
			vr = intvar(es, evalexpr(es, prec - 1));
		if ((op == O_DIV || op == O_MOD || op == O_DIVASN ||
		    op == O_MODASN) && vr->val.i == 0) {
			if (es->noassign)
				vr->val.i = 1;
			else
				evalerr(es, ET_STR, "zero divisor");
		}
		switch ((int)op) {
		case O_TIMES:
		case O_TIMESASN:
			res = bivui(vl, *, vr);
			break;
		case O_DIV:
		case O_DIVASN:
			res = bivui(vl, /, vr);
			break;
		case O_MOD:
		case O_MODASN:
			res = bivui(vl, %, vr);
			break;
		case O_PLUS:
		case O_PLUSASN:
			res = bivui(vl, +, vr);
			break;
		case O_MINUS:
		case O_MINUSASN:
			res = bivui(vl, -, vr);
			break;
		case O_LSHIFT:
		case O_LSHIFTASN:
			res = bivui(vl, <<, vr);
			break;
		case O_RSHIFT:
		case O_RSHIFTASN:
			res = bivui(vl, >>, vr);
			break;
		case O_LT:
			res = bivui(vl, <, vr);
			break;
		case O_LE:
			res = bivui(vl, <=, vr);
			break;
		case O_GT:
			res = bivui(vl, >, vr);
			break;
		case O_GE:
			res = bivui(vl, >=, vr);
			break;
		case O_EQ:
			res = bivui(vl, ==, vr);
			break;
		case O_NE:
			res = bivui(vl, !=, vr);
			break;
		case O_BAND:
		case O_BANDASN:
			res = bivui(vl, &, vr);
			break;
		case O_BXOR:
		case O_BXORASN:
			res = bivui(vl, ^, vr);
			break;
		case O_BOR:
		case O_BORASN:
			res = bivui(vl, |, vr);
			break;
		case O_LAND:
			if (!vl->val.i)
				es->noassign++;
			vr = intvar(es, evalexpr(es, prec - 1));
			res = bivui(vl, &&, vr);
			if (!vl->val.i)
				es->noassign--;
			break;
		case O_LOR:
			if (vl->val.i)
				es->noassign++;
			vr = intvar(es, evalexpr(es, prec - 1));
			res = bivui(vl, ||, vr);
			if (vl->val.i)
				es->noassign--;
			break;
		case O_TERN:
			{
				bool ev = vl->val.i != 0;

				if (!ev)
					es->noassign++;
				vl = evalexpr(es, MAX_PREC);
				if (!ev)
					es->noassign--;
				if (es->tok != CTERN)
					evalerr(es, ET_STR, "missing :");
				exprtoken(es);
				if (ev)
					es->noassign++;
				vr = evalexpr(es, P_TERN);
				if (ev)
					es->noassign--;
				vl = ev ? vl : vr;
			}
			break;
		case O_ASN:
			res = vr->val.i;
			break;
		case O_COMMA:
			res = vr->val.i;
			break;
		}
		if (IS_ASSIGNOP(op)) {
			stvui(vr, res);
			if (vasn->flag & INTEGER)
				setint_v(vasn, vr, es->arith);
			else
				setint(vasn, res);
			vl = vr;
		} else if (op != O_TERN)
			stvui(vl, res);
	}
	return (vl);
}

static void
exprtoken(Expr_state *es)
{
	const char *cp = es->tokp;
	int c;
	char *tvar;

	/* skip white space */
 skip_spaces:
	while ((c = *cp), ksh_isspace(c))
		++cp;
	if (es->tokp == es->expression && c == '#') {
		/* expression begins with # */
		es->natural = true;	/* switch to unsigned */
		++cp;
		goto skip_spaces;
	}
	es->tokp = cp;

	if (c == '\0')
		es->tok = END;
	else if (ksh_isalphx(c)) {
		for (; ksh_isalnux(c); c = *cp)
			cp++;
		if (c == '[') {
			int len;

			len = array_ref_len(cp);
			if (len == 0)
				evalerr(es, ET_STR, "missing ]");
			cp += len;
		} else if (c == '(' /*)*/ ) {
			/* todo: add math functions (all take single argument):
			 * abs acos asin atan cos cosh exp int log sin sinh sqrt
			 * tan tanh
			 */
			;
		}
		if (es->noassign) {
			es->val = tempvar();
			es->val->flag |= EXPRLVALUE;
		} else {
			strndupx(tvar, es->tokp, cp - es->tokp, ATEMP);
			es->val = global(tvar);
			afree(tvar, ATEMP);
		}
		es->tok = VAR;
	} else if (c == '1' && cp[1] == '#') {
		cp += 2;
		cp += utf_ptradj(cp);
		strndupx(tvar, es->tokp, cp - es->tokp, ATEMP);
		goto process_tvar;
	} else if (ksh_isdigit(c)) {
		while (c != '_' && (ksh_isalnux(c) || c == '#'))
			c = *cp++;
		strndupx(tvar, es->tokp, --cp - es->tokp, ATEMP);
 process_tvar:
		es->val = tempvar();
		es->val->flag &= ~INTEGER;
		es->val->type = 0;
		es->val->val.s = tvar;
		if (setint_v(es->val, es->val, es->arith) == NULL)
			evalerr(es, ET_BADLIT, tvar);
		afree(tvar, ATEMP);
		es->tok = LIT;
	} else {
		int i, n0;

		for (i = 0; (n0 = opinfo[i].name[0]); i++)
			if (c == n0 &&
			    strncmp(cp, opinfo[i].name, opinfo[i].len) == 0) {
				es->tok = (enum token)i;
				cp += opinfo[i].len;
				break;
			}
		if (!n0)
			es->tok = BAD;
	}
	es->tokp = cp;
}

/* Do a ++ or -- operation */
static struct tbl *
do_ppmm(Expr_state *es, enum token op, struct tbl *vasn, bool is_prefix)
{
	struct tbl *vl;
	mksh_ari_t oval;

	assign_check(es, op, vasn);

	vl = intvar(es, vasn);
	oval = vl->val.i;
	if (op == O_PLUSPLUS) {
		if (es->natural)
			++vl->val.u;
		else
			++vl->val.i;
	} else {
		if (es->natural)
			--vl->val.u;
		else
			--vl->val.i;
	}
	if (vasn->flag & INTEGER)
		setint_v(vasn, vl, es->arith);
	else
		setint(vasn, vl->val.i);
	if (!is_prefix)		/* undo the inc/dec */
		vl->val.i = oval;

	return (vl);
}

static void
assign_check(Expr_state *es, enum token op, struct tbl *vasn)
{
	if (vasn->name[0] == '\0' && !(vasn->flag & EXPRLVALUE))
		evalerr(es, ET_LVALUE, opinfo[(int)op].name);
	else if (vasn->flag & RDONLY)
		evalerr(es, ET_RDONLY, opinfo[(int)op].name);
}

static struct tbl *
tempvar(void)
{
	struct tbl *vp;

	vp = alloc(sizeof (struct tbl), ATEMP);
	vp->flag = ISSET|INTEGER;
	vp->type = 0;
	vp->areap = ATEMP;
	vp->val.i = 0;
	vp->name[0] = '\0';
	return (vp);
}

/* cast (string) variable to temporary integer variable */
static struct tbl *
intvar(Expr_state *es, struct tbl *vp)
{
	struct tbl *vq;

	/* try to avoid replacing a temp var with another temp var */
	if (vp->name[0] == '\0' &&
	    (vp->flag & (ISSET|INTEGER|EXPRLVALUE)) == (ISSET|INTEGER))
		return (vp);

	vq = tempvar();
	if (setint_v(vq, vp, es->arith) == NULL) {
		if (vp->flag & EXPRINEVAL)
			evalerr(es, ET_RECURSIVE, vp->name);
		es->evaling = vp;
		vp->flag |= EXPRINEVAL;
		v_evaluate(vq, str_val(vp), KSH_UNWIND_ERROR, es->arith);
		vp->flag &= ~EXPRINEVAL;
		es->evaling = NULL;
	}
	return (vq);
}
