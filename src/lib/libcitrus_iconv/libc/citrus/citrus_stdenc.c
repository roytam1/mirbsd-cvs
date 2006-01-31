/*	$NetBSD: citrus_stdenc.c,v 1.3 2005/10/29 18:02:04 tshiozak Exp $	*/

/*-
 * Copyright (c)2003 Citrus Project,
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
__RCSID("$NetBSD: citrus_stdenc.c,v 1.3 2005/10/29 18:02:04 tshiozak Exp $");
#endif /* LIBC_SCCS and not lint */

#include "namespace.h"
#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "citrus_namespace.h"
#include "citrus_types.h"
#include "citrus_module.h"
#include "citrus_stdenc.h"
#include "citrus_none.h"

struct _citrus_stdenc _citrus_stdenc_default = {
	&_citrus_NONE_stdenc_ops,	/* ce_ops */
	NULL,				/* ce_closure */
	NULL,				/* ce_module */
	&_citrus_NONE_stdenc_traits,	/* ce_traits */
};

#ifdef _I18N_DYNAMIC

static int
/*ARGSUSED*/
get_state_desc_default(struct _citrus_stdenc * __restrict ce,
		       void * __restrict ps,
		       int id,
		       struct _citrus_stdenc_state_desc * __restrict d)
{
	return EOPNOTSUPP;
}

int
_citrus_stdenc_open(struct _citrus_stdenc * __restrict * __restrict rce,
		    char const * __restrict encname,
		    const void * __restrict variable, size_t lenvar)
{
	int ret;
	_citrus_module_t handle;
	struct _citrus_stdenc *ce;
	_citrus_stdenc_getops_t getops;

	_DIAGASSERT(encname != NULL);
	_DIAGASSERT(!lenvar || variable!=NULL);
	_DIAGASSERT(rce != NULL);

	if (!strcmp(encname, _CITRUS_DEFAULT_STDENC_NAME)) {
		*rce = &_citrus_stdenc_default;
		return (0);
	}
	ce = malloc(sizeof(*ce));
	if (ce==NULL) {
		ret = errno;
		goto bad;
	}
	ce->ce_ops = NULL;
	ce->ce_closure = NULL;
	ce->ce_module = NULL;
	ce->ce_traits = NULL;

	ret = _citrus_load_module(&handle, encname);
	if (ret)
		goto bad;

	ce->ce_module = handle;

	getops =
	    (_citrus_stdenc_getops_t)_citrus_find_getops(ce->ce_module,
							 encname, "stdenc");
	if (getops == NULL) {
		ret = EINVAL;
		goto bad;
	}

	ce->ce_ops = (struct _citrus_stdenc_ops *)malloc(sizeof(*ce->ce_ops));
	if (ce->ce_ops == NULL) {
		ret = errno;
		goto bad;
	}

	ret = (*getops)(ce->ce_ops, sizeof(*ce->ce_ops),
			_CITRUS_STDENC_ABI_VERSION);
	if (ret)
		goto bad;

	/* If return ABI version is not expected, should fixup it */
	if (ce->ce_ops->eo_abi_version < 0x00000002) {
		ce->ce_ops->eo_get_state_desc = &get_state_desc_default;
	}

	/* validation check */
	if (ce->ce_ops->eo_init == NULL ||
	    ce->ce_ops->eo_uninit == NULL ||
	    ce->ce_ops->eo_init_state == NULL ||
	    ce->ce_ops->eo_mbtocs == NULL ||
	    ce->ce_ops->eo_cstomb == NULL ||
	    ce->ce_ops->eo_mbtowc == NULL ||
	    ce->ce_ops->eo_wctomb == NULL ||
	    ce->ce_ops->eo_get_state_desc == NULL)
		goto bad;

	/* allocate traits */
	ce->ce_traits = malloc(sizeof(*ce->ce_traits));
	if (ce->ce_traits == NULL) {
		ret = errno;
		goto bad;
	}
	/* init and get closure */
	ret = (*ce->ce_ops->eo_init)(ce, variable, lenvar, ce->ce_traits);
	if (ret)
		goto bad;

	*rce = ce;

	return (0);

bad:
	_citrus_stdenc_close(ce);
	return (ret);
}

void
_citrus_stdenc_close(struct _citrus_stdenc *ce)
{

	_DIAGASSERT(ce != NULL);

	if (ce == &_citrus_stdenc_default)
		return;

	if (ce->ce_module) {
		if (ce->ce_ops) {
			if (ce->ce_closure && ce->ce_ops->eo_uninit)
				(*ce->ce_ops->eo_uninit)(ce);
			free(ce->ce_ops);
		}
		free(ce->ce_traits);
		_citrus_unload_module(ce->ce_module);
	}
	free(ce);
}

#else
/* !_I18N_DYNAMIC */

int
/*ARGSUSED*/
_citrus_stdenc_open(struct _citrus_stdenc * __restrict * __restrict rce,
		    char const * __restrict encname,
		    const void * __restrict variable, size_t lenvar)
{
	if (!strcmp(encname, _CITRUS_DEFAULT_STDENC_NAME)) {
		*rce = &_citrus_stdenc_default;
		return (0);
	}
	return (EINVAL);
}

void
/*ARGSUSED*/
_citrus_stdenc_close(struct _citrus_stdenc *ce)
{
}

#endif
