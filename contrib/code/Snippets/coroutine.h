/* $MirOS: contrib/code/Snippets/coroutine.h,v 1.15 2008/11/19 01:53:56 tg Exp $ */

/*-
 * $Id$ is
 * Copyright (c) 2008
 *	Felix Fietkau <nbd@openwrt.org>
 *	Thorsten Glaser <tg@mirbsd.org>
 *
 * Provided that these terms and disclaimer and all copyright notices
 * are retained or reproduced in an accompanying document, permission
 * is granted to deal in this work without restriction, including un-
 * limited rights to use, publicly perform, distribute, sell, modify,
 * merge, give away, or sublicence.
 *
 * This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
 * the utmost extent permitted by applicable law, neither express nor
 * implied; without malicious intent or gross negligence. In no event
 * may a licensor, author or contributor be held liable for indirect,
 * direct, other damage, loss, or other issues arising in any way out
 * of dealing in the work, even if advised of the possibility of such
 * damage or existence of a defect, except proven that it results out
 * of said person's immediate fault when using the work as intended.
 *-
 * Thanks to Simon Tatham for the idea and a reference for the
 * implementation.  For more information about this, refer to:
 * http://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 */

/**
 * Information on how to use this header file:
 *
 * You will need to include <stdlib.h> for malloc/free, abort, NULL.
 * To create a coroutine, use this:

 * once per <typename>, in a header file:
__coroutine_decl(<typename>, <return type>, <arguments>);
__coroutine_decl_na(<typename>, <return type>);

 * once per function <name>, in a header file:
__coroutine_proto(<typename>, <name>, <return type>, <arguments>);
__coroutine_proto_na(<typename>, <name>, <return type>);

 * once per <typename>, in a source file, with no trailing semicolon:
__coroutine_impl(<typename>)

 * once per function <name>, in a source (*.c) file:
__coroutine_defn(<typename>, <name>, <return type>, <arguments>)
__coroutine_defn_na(<typename>, <name>, <return type>)
{
	<local variables>
	__cr_begin(<name>);
	< your code goes here >
	__cr_end(<name>);
	return (<value>);
}

 * A coroutine can yield by using __cr_return(<value>); and pass execu-
 * tion to another function with the same <typename> with __cr_pass (or
 * __cr_passv if the function return type is "void") or __cr_pass_na or
 * __cr_passv_na, respectively, for functions taking no arguments.
 * Local variables can be accessed in a coroutine with __cr_var(<name>)
 *
 * To access a coroutine, first create a pointer to a state variable
 * of its <typename> and initialise it with something like
 *	__cr_init(<typename>, <pointervar>, <name>);
 * and call the coroutine using __cr_call(<pointervar>, <arguments>) or
 * __cr_call_na(<pointervar>).
 *
 * Example:

#include <stdlib.h>
#include <stdio.h>
#include "coroutine.h"

static const char rcsid[] = "$MirOS: contrib/code/Snippets/coroutine.h,v 1.15 2008/11/19 01:53:56 tg Exp $";

__coroutine_decl(footype, int, int);
__coroutine_decl(foovtype, void, int);
__coroutine_decl_na(foontype, int);
__coroutine_decl_na(foovntype, void);

__coroutine_proto(footype, foo, int, int);
__coroutine_proto(footype, bar, int, int);
__coroutine_proto(foovtype, foov, void, int);
__coroutine_proto(foovtype, barv, void, int);
__coroutine_proto_na(foontype, foon, int);
__coroutine_proto_na(foontype, barn, int);
__coroutine_proto_na(foovntype, foovn, void);
__coroutine_proto_na(foovntype, barvn, void);

__coroutine_impl(footype)
__coroutine_impl(foovtype)
__coroutine_impl(foontype)
__coroutine_impl(foovntype)

int global_state;

__coroutine_defn(footype,
foo, int, int arg)
{
	int a;

	__cr_begin(foo);
	__cr_var(a) = 0;
	while (__cr_var(a) < 1000000) {
		if (arg > 3)
			__cr_pass(footype, bar, arg);
		__cr_var(a) += arg;
		__cr_return(__cr_var(a));
	}
	__cr_end(foo);
	return (0);
}

__coroutine_defn(footype,
bar, int, int arg)
{
	unsigned short k;

	__cr_begin(bar);
	__cr_var(k) = 0;
	while (__cr_var(k) < 10000) {
		__cr_var(k) += arg;
		__cr_return(1000 + __cr_var(k));
	}
	__cr_end(bar);
	return (0);
}

__coroutine_defn(foovtype,
foov, void, int arg)
{
	int a;

	__cr_begin(foov);
	__cr_var(a) = 0;
	while (__cr_var(a) < 1000000) {
		if (arg > 3)
			__cr_passv(foovtype, barv, arg);
		__cr_var(a) += arg;
		global_state = __cr_var(a);
		__cr_return();
	}
	__cr_end(foov);
	return;
}

__coroutine_defn(foovtype,
barv, void, int arg)
{
	unsigned short k;

	__cr_begin(barv);
	__cr_var(k) = 0;
	while (__cr_var(k) < 10000) {
		__cr_var(k) += arg;
		global_state = 1000 + __cr_var(k);
		__cr_return();
	}
	__cr_end(barv);
	return;
}

__coroutine_defn_na(foontype,
foon, int)
{
	int a;

	__cr_begin(foon);
	__cr_var(a) = 0;
	while (__cr_var(a) < 1000000) {
		if (__cr_var(a) > 3)
			__cr_pass_na(foontype, barn);
		__cr_var(a) += 1;
		__cr_return(__cr_var(a));
	}
	__cr_end(foon);
	return (0);
}

__coroutine_defn_na(foontype,
barn, int)
{
	unsigned short k;

	__cr_begin(barn);
	__cr_var(k) = 0;
	while (__cr_var(k) < 10000) {
		__cr_var(k) += 1;
		__cr_return(1000 + __cr_var(k));
	}
	__cr_end(barn);
	return (0);
}

__coroutine_defn_na(foovntype,
foovn, void)
{
	int a;

	__cr_begin(foovn);
	__cr_var(a) = 0;
	while (__cr_var(a) < 1000000) {
		if (__cr_var(a) > 3)
			__cr_passv_na(foovntype, barvn);
		__cr_var(a) += 1;
		global_state = __cr_var(a);
		__cr_return();
	}
	__cr_end(foovn);
	return;
}

__coroutine_defn_na(foovntype,
barvn, void)
{
	unsigned short k;

	__cr_begin(barvn);
	__cr_var(k) = 0;
	while (__cr_var(k) < 10000) {
		__cr_var(k) += 1;
		global_state = 1000 + __cr_var(k);
		__cr_return();
	}
	__cr_end(barvn);
	return;
}

int
main(int argc, char *argv[])
{
	__cr_init(footype, c, foo);
	__cr_init(foovtype, cv, foov);
	__cr_init(foontype, cn, foon);
	__cr_init(foovntype, cvn, foovn);
	int i;

	printf("%s\n", rcsid);

	global_state = 0;
	for (i = 1; i <= 6; ++i)
		printf("#%d: ret = %d\n", i, __cr_call(c, i));
	for (i = 1; i <= 6; ++i) {
		__cr_call(cv, i);
		printf("#%d: ret = %d\n", i, global_state);
	}
	global_state = 0;
	for (i = 1; i <= 6; ++i)
		printf("#%d: ret = %d\n", i, __cr_call_na(cn));
	for (i = 1; i <= 6; ++i) {
		__cr_call_na(cvn);
		printf("#%d: ret = %d\n", i, global_state);
	}

	printf("%s[%d]: ret = %d\n", argv[0], argc, __cr_call(c, argc));

	return (0);
}

 */

#ifndef __COROUTINE_H
#define __COROUTINE_H

/* configuration: malloc/free functions to use */
#ifndef __coroutine_malloc
#define __coroutine_malloc	malloc
#endif

#ifndef __coroutine_free
#define __coroutine_free	free
#endif

/* configuration: implementation style to use */
#if !defined(__COROUTINE_DUFF)
#ifdef __GNUC__
#define __COROUTINE_DUFF	0	/* use address of local label */
#else
#define __COROUTINE_DUFF	1	/* use Duff's Device (ANSI C) */
#endif
#endif


/* concatenation macro, used internally */
#define __CR(x, y)		__coroutine_ ## x ## _ ## y


#if __COROUTINE_DUFF
#define __coroutine_content	unsigned long lno
#else
#define __coroutine_content	void *ptr
#endif

/* declare a <typename>, its structures, and initialiser function */
#define __coroutine_decl(_typename, _rettype, ...)			\
	struct __CR(struct, _typename);					\
	typedef _rettype (*__CR(ptr, _typename))(struct			\
	    __CR(struct, _typename) **, __VA_ARGS__);			\
	typedef struct __CR(struct, _typename) {			\
		__CR(ptr, _typename) __fptr;				\
		__coroutine_content;					\
	} _typename;							\
	_typename *__CR(init, _typename)(void (*)(_typename **))

#define __coroutine_decl_na(_typename, _rettype)			\
	struct __CR(struct, _typename);					\
	typedef _rettype (*__CR(ptr, _typename))(struct			\
	    __CR(struct, _typename) **);				\
	typedef struct __CR(struct, _typename) {			\
		__CR(ptr, _typename) __fptr;				\
		__coroutine_content;					\
	} _typename;							\
	_typename *__CR(init, _typename)(void (*)(_typename **))

/* implement a <typename>'s initialiser function */
#define __coroutine_impl(_typename)					\
	_typename *							\
	__CR(init, _typename)(void (*__cr_ptr)(_typename **))		\
	{								\
		_typename *__cr_tmp1 = NULL;				\
		(*__cr_ptr)(&__cr_tmp1);				\
		return (__cr_tmp1);					\
	}

/* declare and initialise a context pointer variable */
#define __coroutine_init(_typename, _ptrvar, _name)			\
	_typename *_ptrvar =						\
	    __CR(init, _typename)((void (*)(_typename **))&(_name))

/* pass execution to another coroutine of the same <typename> ret. non-void */
#define __coroutine_pass(_typename, _name, ...) do {			\
	__coroutine_free(*__cr_ectx);					\
	*__cr_ectx =							\
	    __CR(init, _typename)((void (*)(_typename **))&(_name));	\
	return ((*__cr_ectx)->__fptr(__cr_ectx, __VA_ARGS__));		\
} while (/* CONSTCOND */ 0)

#define __coroutine_pass_na(_typename, _name) do {			\
	__coroutine_free(*__cr_ectx);					\
	*__cr_ectx =							\
	    __CR(init, _typename)((void (*)(_typename **))&(_name));	\
	return ((*__cr_ectx)->__fptr(__cr_ectx));			\
} while (/* CONSTCOND */ 0)

/* pass execution to another coroutine of the same <typename> returning void */
#define __coroutine_passv(_typename, _name, ...) do {			\
	__coroutine_free(*__cr_ectx);					\
	*__cr_ectx =							\
	    __CR(init, _typename)((void (*)(_typename **))&(_name));	\
	(*__cr_ectx)->__fptr(__cr_ectx, __VA_ARGS__);			\
	return;								\
} while (/* CONSTCOND */ 0)

#define __coroutine_passv_na(_typename, _name) do {			\
	__coroutine_free(*__cr_ectx);					\
	*__cr_ectx =							\
	    __CR(init, _typename)((void (*)(_typename **))&(_name));	\
	(*__cr_ectx)->__fptr(__cr_ectx);				\
	return;								\
} while (/* CONSTCOND */ 0)

/* declare a coroutine function prototype */
#define __coroutine_proto(_typename, _name, _rettype, ...)		\
	_rettype _name(_typename **, __VA_ARGS__)

#define __coroutine_proto_na(_typename, _name, _rettype)		\
	_rettype _name(_typename **)

/* define a coroutine function */
#define __coroutine_defn(_typename, _name, _rettype, ...)		\
	_rettype							\
	_name(_typename **__cr_ectx, __VA_ARGS__)			\
	{								\
		struct __CR(internal, _name) {				\
			/* __cr_internal must be first */		\
			_typename __cr_internal;			\
			struct	/* ... yes, here the macro ends */

#define __coroutine_defn_na(_typename, _name, _rettype)			\
	_rettype							\
	_name(_typename **__cr_ectx)					\
	{								\
		struct __CR(internal, _name) {				\
			/* __cr_internal must be first */		\
			_typename __cr_internal;			\
			struct	/* ... yes, here the macro ends */


#if __COROUTINE_DUFF

/* begin execution of a coroutine function */
#define __coroutine_begin(_name)					\
			} __cr_data;					\
		} *__cr_ictx;						\
									\
	if (*__cr_ectx == NULL) {					\
		__coroutine_initctx(_name);				\
		(*__cr_ectx)->lno = 0;					\
		goto __CR(endlbl, _name);				\
	} else								\
		__coroutine_checkctx(_name);				\
	switch ((*__cr_ectx)->lno) {					\
	case 0:

/* yield from a coroutine to its caller */
#define __coroutine_return(x) do {					\
	/* the following must all be on the same line */		\
	(*__cr_ectx)->lno = __LINE__; return x; case __LINE__: ;	\
} while (/* CONSTCOND */ 0)

/* finish execution of a coroutine function */
#define __coroutine_end(_name)						\
		if (*__cr_ectx != NULL) {				\
			__coroutine_free(*__cr_ectx);			\
			*__cr_ectx = NULL;				\
		}							\
	}								\
	__CR(endlbl, _name):

#else /* !__COROUTINE_DUFF */

/* begin execution of a coroutine function */
#define __coroutine_begin(_name)					\
			} __cr_data;					\
		} *__cr_ictx;						\
									\
	if (*__cr_ectx == NULL) {					\
		__coroutine_initctx(_name);				\
		(*__cr_ectx)->ptr = NULL;				\
		goto __CR(endlbl, _name);				\
	} else								\
		__coroutine_checkctx(_name);				\
	if ((*__cr_ectx)->ptr != NULL)					\
		__extension__({ goto *((*__cr_ectx)->ptr); })

/* yield from a coroutine to its caller */
#define __coroutine_return(value) __extension__({			\
	__label__ __cr_tmplbl;						\
									\
	(*__cr_ectx)->ptr = &&__cr_tmplbl;				\
	return value;	/* no parens: void function support */		\
 __cr_tmplbl:								\
	;								\
})

/* finish execution of a coroutine function */
#define __coroutine_end(_name)						\
	if (*__cr_ectx != NULL) {					\
		__coroutine_free(*__cr_ectx);				\
		*__cr_ectx = NULL;					\
	}								\
	__CR(endlbl, _name):

#endif /* !__COROUTINE_DUFF */


/* internal: fill in a context pointer and local variables variable */
#define __coroutine_initctx(_name) do {					\
	*__cr_ectx = __coroutine_malloc(sizeof (*__cr_ictx));		\
	(*__cr_ectx)->__fptr = &(_name);				\
} while (/* CONSTCOND */ 0)

/* internal: check a context pointer for validity and load it */
#define __coroutine_checkctx(_name) do {				\
	/* check if the struct passed matches */			\
	if ((*__cr_ectx)->__fptr != &(_name))				\
		abort();						\
	__cr_ictx = (struct __CR(internal, _name) *)(*__cr_ectx);	\
} while (/* CONSTCOND */ 0)


/* API exported to the user */
#define __cr_init		__coroutine_init
#define __cr_free		__coroutine_free
#define __cr_begin		__coroutine_begin
#define __cr_end		__coroutine_end
#define __cr_call(_ctx, ...)	((_ctx)->__fptr(&(_ctx), __VA_ARGS__))
#define __cr_call_na(_ctx)	((_ctx)->__fptr(&(_ctx)))
#define __cr_pass		__coroutine_pass
#define __cr_pass_na		__coroutine_pass_na
#define __cr_passv		__coroutine_passv
#define __cr_passv_na		__coroutine_passv_na
#define __cr_return(v)		__coroutine_return(v)
#define __cr_var(_name)		((__cr_ictx->__cr_data)._name)

#endif /* __COROUTINE_H */
