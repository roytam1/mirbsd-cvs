/*
 *    Written 3/1/94, Robert Sanders <Robert.Sanders@linux.org>
 *
 * based upon the file "dl.c", which is
 *    Copyright (c) 1994, Larry Wall
 *
 *    You may distribute under the terms of either the GNU General Public
 *    License or the Artistic License, as specified in the README file.
 *
 * $Date$
 * $Source$
 * $Revision$
 * $State$
 *
 * $Log$
 * Revision 1.7  2003/12/03 03:02:28  millert
 * Resolve conflicts for perl 5.8.2, remove old files, and add OpenBSD-specific scaffolding
 *
 * Removed implicit link against libc.  1994/09/14 William Setzer.
 *
 * Integrated other DynaLoader changes. 1994/06/08 Tim Bunce.
 *
 * rewrote dl_load_file, misc updates.  1994/09/03 William Setzer.
 *
 * Revision 1.4  1994/03/07  00:21:43  rsanders
 * added min symbol count for load_libs and switched order so system libs
 * are loaded after app-specified libs.
 *
 * Revision 1.3  1994/03/05  01:17:26  rsanders
 * added path searching.
 *
 * Revision 1.2  1994/03/05  00:52:39  rsanders
 * added package-specified libraries.
 *
 * Revision 1.1  1994/03/05  00:33:40  rsanders
 * Initial revision
 *
 *
 */

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <dld.h>	/* GNU DLD header file */
#include <unistd.h>

typedef struct {
    AV *	x_resolve_using;
    AV *	x_require_symbols;
} my_cxtx_t;		/* this *must* be named my_cxtx_t */

#define DL_CXT_EXTRA	/* ask for dl_cxtx to be defined in dlutils.c */
#include "dlutils.c"	/* for SaveError() etc */

#define dl_resolve_using	(dl_cxtx.x_resolve_using)
#define dl_require_symbols	(dl_cxtx.x_require_symbols)

static void
dl_private_init(pTHX)
{
    dl_generic_private_init(aTHX);
    {
	int dlderr;
	dMY_CXT;

	dl_resolve_using   = get_av("DynaLoader::dl_resolve_using", GV_ADDMULTI);
	dl_require_symbols = get_av("DynaLoader::dl_require_symbols", GV_ADDMULTI);
#ifdef __linux__
	dlderr = dld_init("/proc/self/exe");
	if (dlderr) {
#endif
	    dlderr = dld_init(dld_find_executable(PL_origargv[0]));
	    if (dlderr) {
		char *msg = dld_strerror(dlderr);
		SaveError(aTHX_ "dld_init(%s) failed: %s", PL_origargv[0], msg);
		DLDEBUG(1,PerlIO_printf(Perl_debug_log, "%s", dl_last_error));
	    }
#ifdef __linux__
	}
#endif
    }
}


MODULE = DynaLoader     PACKAGE = DynaLoader

BOOT:
    (void)dl_private_init();


char *
dl_load_file(filename, flags=0)
    char *	filename
    int		flags
    PREINIT:
    int dlderr,x,max;
    GV *gv;
    dMY_CXT;
    CODE:
    RETVAL = filename;
    DLDEBUG(1,PerlIO_printf(Perl_debug_log, "dl_load_file(%s,%x):\n", filename,flags));
    if (flags & 0x01)
	Perl_croak(aTHX_ "Can't make loaded symbols global on this platform while loading %s",filename);
    max = AvFILL(dl_require_symbols);
    for (x = 0; x <= max; x++) {
	char *sym = SvPVX(*av_fetch(dl_require_symbols, x, 0));
	DLDEBUG(1,PerlIO_printf(Perl_debug_log, "dld_create_ref(%s)\n", sym));
	if (dlderr = dld_create_reference(sym)) {
	    SaveError(aTHX_ "dld_create_reference(%s): %s", sym,
		      dld_strerror(dlderr));
	    goto haverror;
	}
    }

    DLDEBUG(1,PerlIO_printf(Perl_debug_log, "dld_link(%s)\n", filename));
    if (dlderr = dld_link(filename)) {
	SaveError(aTHX_ "dld_link(%s): %s", filename, dld_strerror(dlderr));
	goto haverror;
    }

    max = AvFILL(dl_resolve_using);
    for (x = 0; x <= max; x++) {
	char *sym = SvPVX(*av_fetch(dl_resolve_using, x, 0));
	DLDEBUG(1,PerlIO_printf(Perl_debug_log, "dld_link(%s)\n", sym));
	if (dlderr = dld_link(sym)) {
	    SaveError(aTHX_ "dld_link(%s): %s", sym, dld_strerror(dlderr));
	    goto haverror;
	}
    }
    DLDEBUG(2,PerlIO_printf(Perl_debug_log, "libref=%s\n", RETVAL));
haverror:
    ST(0) = sv_newmortal() ;
    if (dlderr == 0)
	sv_setiv(ST(0), PTR2IV(RETVAL));


void *
dl_find_symbol(libhandle, symbolname)
    void *	libhandle
    char *	symbolname
    CODE:
    DLDEBUG(2,PerlIO_printf(Perl_debug_log, "dl_find_symbol(handle=%x, symbol=%s)\n",
	    libhandle, symbolname));
    RETVAL = (void *)dld_get_func(symbolname);
    /* if RETVAL==NULL we should try looking for a non-function symbol */
    DLDEBUG(2,PerlIO_printf(Perl_debug_log, "  symbolref = %x\n", RETVAL));
    ST(0) = sv_newmortal() ;
    if (RETVAL == NULL)
	SaveError(aTHX_ "dl_find_symbol: Unable to find '%s' symbol", symbolname) ;
    else
	sv_setiv(ST(0), PTR2IV(RETVAL));


void
dl_undef_symbols()
    PPCODE:
    if (dld_undefined_sym_count) {
	int x;
	char **undef_syms = dld_list_undefined_sym();
	EXTEND(SP, dld_undefined_sym_count);
	for (x=0; x < dld_undefined_sym_count; x++)
	    PUSHs(sv_2mortal(newSVpv(undef_syms[x]+1, 0)));
	free(undef_syms);
    }



# These functions should not need changing on any platform:

void
dl_install_xsub(perl_name, symref, filename="$Package")
    char *	perl_name
    void *	symref 
    char *	filename
    CODE:
    DLDEBUG(2,PerlIO_printf(Perl_debug_log, "dl_install_xsub(name=%s, symref=%x)\n",
	    perl_name, symref));
    ST(0) = sv_2mortal(newRV((SV*)newXS(perl_name,
					(void(*)(pTHX_ CV *))symref,
					filename)));


char *
dl_error()
    PREINIT:
    dMY_CXT;
    CODE:
    RETVAL = dl_last_error ;
    OUTPUT:
    RETVAL

# end.
