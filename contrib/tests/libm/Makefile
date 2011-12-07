# $NetBSD: Makefile,v 1.17 2011/10/16 13:43:26 jruoho Exp $


TESTSDIR=	${TESTSBASE}/lib/libm

TESTS_C+=	t_acos
TESTS_C+=	t_asin
TESTS_C+=	t_atan
TESTS_C+=	t_cbrt
TESTS_C+=	t_ceil
TESTS_C+=	t_cos
TESTS_C+=	t_cosh
TESTS_C+=	t_erf
TESTS_C+=	t_exp
TESTS_C+=	t_infinity
TESTS_C+=	t_ldexp
TESTS_C+=	t_log
TESTS_C+=	t_pow
TESTS_C+=	t_round
TESTS_C+=	t_scalbn
TESTS_C+=	t_sin
TESTS_C+=	t_sinh
TESTS_C+=	t_sqrt
TESTS_C+=	t_tan
TESTS_C+=	t_tanh

LDADD+=		-lm

CFLAGS!=	pkg-config --cflags atf-c
LDFLAGS!=	pkg-config --libs-only-L --libs-only-other atf-c
LIBS!=		pkg-config --libs-only-l atf-c

all: $(TESTS_C)

.c:
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $< ${LIBS} ${LDADD}
