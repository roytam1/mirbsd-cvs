/* $MirOS: contrib/code/Snippets/coroutine.h,v 1.4 2008/06/20 15:41:26 tg Exp $ */

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
 * To create a coroutine, use this:

__coroutine_decl(<typename>, <return type> [, <arguments>]);

__coroutine_proto(<typename>, <name>, <return type> [, <arguments>]);

__coroutine_defn(<typename>, <name>, <return type> [, <arguments>])
{
	<local variables>
	__cr_begin(<name>);
	< your code goes here >
	__cr_end(<name>);
	return (<value>);
}

 * A coroutine can yield by using __cr_return(<value>); and pass execu-
 * tion to another function with the same <typename> with __cr_pass.
 * Local variables can be accessed in a coroutine with __cr_var(<name>)
 *
 * To access a coroutine, first create a pointer to a state variable
 * of its <typename>, initialise it with something like
 *	__cr_new(<pointervar>, <typename>, <name>);
 * and call the coroutine using __cr_call(<pointervar> [, <arguments>]).
 *
 * Example:

#include <stdlib.h>
#include <stdio.h>
#include "coroutine.h"

__coroutine_decl(footype, int, int);

__coroutine_proto(footype, foo, int, int);
__coroutine_proto(footype, bar, int, int);

__coroutine_defn(footype, foo, int, int arg)
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

__coroutine_defn(footype, bar, int, int arg)
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

int
main(void)
{
	footype *c;
	int i;

	__cr_new(c, footype, foo);
	for (i = 1; i <= 6; ++i)
		printf("#%d: ret = %d\n", i, __cr_call(c, i));

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

#define __coroutine_decl(_typename, _rettype, ...)			\
	struct __CR(struct, _typename);					\
	typedef _rettype (*__CR(ptr, _typename))(			\
	    struct __CR(struct, _typename) **, ##__VA_ARGS__);		\
	typedef struct __CR(struct, _typename) {			\
		__CR(ptr, _typename) __fptr;				\
		__coroutine_content;					\
	} _typename

#define __coroutine_initctx(_name) do {					\
	*__cr_ectx = __coroutine_malloc(sizeof (*__cr_ictx));		\
	(*__cr_ectx)->__fptr = &_name;					\
} while (/* CONSTCOND */ 0)

#define __coroutine_checkctx(_name) do {				\
	/* check if the struct passed matches */			\
	if ((*__cr_ectx)->__fptr != &_name)				\
		abort();						\
	__cr_ictx = (struct __CR(internal, _name) *)(*__cr_ectx);	\
} while (/* CONSTCOND */ 0)

#define __coroutine_pass(_typename, _name, ...) do {			\
	__coroutine_free(*__cr_ectx);					\
	__coroutine_new(*__cr_ectx, _typename, _name);			\
	return ((*__cr_ectx)->__fptr(__cr_ectx, ##__VA_ARGS__));	\
} while (/* CONSTCOND */ 0)

#define __coroutine_proto(_typename, _name, _rettype, ...)		\
	_rettype _name(_typename **, ##__VA_ARGS__)

#define __coroutine_defn(_typename, _name, _rettype, ...)		\
	_rettype _name(_typename **__cr_ectx, ##__VA_ARGS__)		\
	{								\
		struct __CR(internal, _name) {				\
			/* __cr_internal must be first */		\
			_typename __cr_internal;			\
			struct	/* ... yes, here the macro ends */

#if __COROUTINE_DUFF

#ifndef __extension__
#define __extension__		/* nothing */
#endif

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

#define __coroutine_return(x) do {					\
	/* the following must all be on the same line */		\
	(*__cr_ectx)->lno = __LINE__; return x; case __LINE__: ;	\
} while (/* CONSTCOND */ 0)

#define __coroutine_end(_name)						\
		if (*__cr_ectx != NULL) {				\
			__coroutine_free(*__cr_ectx);			\
			*__cr_ectx = NULL;				\
		}							\
	}								\
	__CR(endlbl, _name):

#else /* !__COROUTINE_DUFF */

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

#define __coroutine_return(value) __extension__({			\
	__label__ __cr_tmplbl;						\
									\
	(*__cr_ectx)->ptr = &&__cr_tmplbl;				\
	return value;	/* no parens: void function support */		\
 __cr_tmplbl:								\
	;								\
})

#define __coroutine_end(_name)						\
	if (*__cr_ectx != NULL) {					\
		__coroutine_free(*__cr_ectx);				\
		*__cr_ectx = NULL;					\
	}								\
	__CR(endlbl, _name):

#endif /* !__COROUTINE_DUFF */

#define __coroutine_new(_ptrvar, _typename, _name) do {			\
	_typename *__cr_tmp1 = NULL;					\
	void (*__cr_tmp2)(_typename **) =				\
	    (void (*)(_typename **))&_name;				\
	(*__cr_tmp2)(&__cr_tmp1);					\
	_ptrvar = __cr_tmp1;						\
} while (/* CONSTCOND */ 0)

#define __cr_new		__coroutine_new
#define __cr_free		__coroutine_free
#define __cr_begin		__coroutine_begin
#define __cr_end		__coroutine_end
#define __cr_call(_ctx, ...)	((_ctx)->__fptr(&(_ctx), ##__VA_ARGS__))
#define __cr_pass		__coroutine_pass
#define __cr_return(v)		__coroutine_return(v)
#define __cr_var(_name)		(__cr_ictx->__cr_data._name)

#endif /* __COROUTINE_H */
