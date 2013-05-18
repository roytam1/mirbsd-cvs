/**	$MirOS: src/lib/libc/gen/fnlist.c,v 1.8 2006/01/24 21:01:03 tg Exp $ */
/*	$OpenBSD: nlist.c,v 1.51 2005/08/08 08:05:34 espie Exp $ */
/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <a.out.h>		/* pulls in nlist.h */

__RCSID("$MirOS: src/lib/libc/gen/fnlist.c,v 1.8 2006/01/24 21:01:03 tg Exp $");

#ifdef _NLIST_DO_ELF
#include <elf_abi.h>
#include <olf_abi.h>
#endif

int	__fnlist(FILE *, struct nlist *);
int	__aout_fnlist(FILE *, struct nlist *);
int	__elf_fnlist(FILE *, struct nlist *);
#ifdef _NLIST_DO_ELF
int	__elf_is_okay__(Elf_Ehdr *ehdr);
#endif

#define	ISLAST(p)	(p->n_un.n_name == 0 || p->n_un.n_name[0] == 0)

#ifdef correct_fpseek_not_a_speed_hack
static ssize_t
__fpread(FILE *f, void *buf, size_t nbytes, off_t offset)
{
	off_t oldofs;
	ssize_t rv;

	if ((oldofs = ftello(f)) == -1)
		return (-1);
	if ((oldofs != offset) && (fseeko(f, offset, SEEK_SET)))
		return (-1);
	if ((rv = fread(buf, 1, nbytes, f)) == 0) {
		if (ferror(f))
			return (-1);
	}
	if (fseeko(f, oldofs, SEEK_SET))
		return (-1);

	return (rv);
}
#else
static ssize_t
__fpread(FILE *f, void *buf, size_t nbytes, off_t offset)
{
	ssize_t rv;

	if ((ftello(f) != offset) && (fseeko(f, offset, SEEK_SET)))
		return (-1);
	if ((rv = fread(buf, 1, nbytes, f)) == 0) {
		if (ferror(f))
			return (-1);
	}

	return (rv);
}
#endif

#define fpread __fpread

#ifdef _NLIST_DO_AOUT
int
__aout_fnlist(FILE *f, struct nlist *list)
{
	struct nlist *p, *s;
	char *strtab;
	off_t symoff, stroff;
	u_long symsize;
	int nent, cc;
	int strsize;
	struct nlist nbuf[1024];
	struct exec exec;

	if (fpread(f, &exec, sizeof(exec), (off_t)0) != sizeof(exec) ||
	    N_BADMAG(exec) || exec.a_syms == (u_int32_t)NULL)
		return (-1);

	stroff = N_STROFF(exec);
	symoff = N_SYMOFF(exec);
	symsize = exec.a_syms;

	/* Read in the size of the string table. */
	if (fpread(f, (void *)&strsize, sizeof(strsize), stroff) !=
	    sizeof(strsize))
		return (-1);
	else
		stroff += sizeof(strsize);

	/*
	 * Read in the string table.  We don't try mmap, that will fail
	 * for zlib streams so use on malloc.  Since OpenBSD's malloc(3)
	 * returns memory to the system on free this does not cause bloat.
	 */
	strsize -= sizeof(strsize);
	if ((strtab = (char *)malloc(strsize)) == NULL)
		return (-1);
	errno = EIO;
	if (fpread(f, strtab, strsize, stroff) != strsize) {
		nent = -1;
		goto aout_done;
	}

	/*
	 * clean out any left-over information for all valid entries.
	 * Type and value defined to be 0 if not found; historical
	 * versions cleared other and desc as well.  Also figure out
	 * the largest string length so don't read any more of the
	 * string table than we have to.
	 *
	 * XXX clearing anything other than n_type and n_value violates
	 * the semantics given in the man page.
	 */
	nent = 0;
	for (p = list; !ISLAST(p); ++p) {
		p->n_type = 0;
		p->n_other = 0;
		p->n_desc = 0;
		p->n_value = 0;
		++nent;
	}

	while (symsize > 0) {
		cc = MIN(symsize, sizeof(nbuf));
		if (fpread(f, nbuf, cc, symoff) != cc)
			break;
		symsize -= cc;
		symoff += cc;
		for (s = nbuf; cc > 0; ++s, cc -= sizeof(*s)) {
			char *sname = strtab + s->n_un.n_strx - sizeof(int);

			if (s->n_un.n_strx == 0 || (s->n_type & N_STAB) != 0)
				continue;
			for (p = list; !ISLAST(p); p++) {
				char *pname = p->n_un.n_name;

				if (*sname != '_' && *pname == '_')
					pname++;
				if (!strcmp(sname, pname)) {
					p->n_value = s->n_value;
					p->n_type = s->n_type;
					p->n_desc = s->n_desc;
					p->n_other = s->n_other;
					if (--nent <= 0)
						break;
				}
			}
		}
	}
aout_done:
	free(strtab);
	return (nent);
}
#endif /* _NLIST_DO_AOUT */

#ifdef _NLIST_DO_ELF
int
__elf_fnlist(FILE *f, struct nlist *list)
{
	struct nlist *p;
	caddr_t strtab;
	Elf_Off symoff = 0, symstroff = 0;
	Elf_Word symsize = 0, symstrsize = 0;
	Elf_Sword nent, cc, i;
	Elf_Sym sbuf[1024];
	Elf_Sym *s;
	Elf_Ehdr ehdr;
	Elf_Shdr *shdr = NULL;
	Elf_Word shdr_size;
	struct stat st;

	/* Make sure obj is OK */
	if (fpread(f, &ehdr, sizeof(Elf_Ehdr), (off_t)0) != sizeof(Elf_Ehdr) ||
	    !__elf_is_okay__(&ehdr) || fstat(fileno(f), &st) < 0)
		return (-1);

	/* calculate section header table size */
	shdr_size = ehdr.e_shentsize * ehdr.e_shnum;

	if ((shdr = malloc(shdr_size)) == NULL)
		return (-1);

	if (fpread(f, shdr, shdr_size, ehdr.e_shoff) != shdr_size) {
		free(shdr);
		return (-1);
	}

	/*
	 * Find the symbol table entry and it's corresponding
	 * string table entry.	Version 1.1 of the ABI states
	 * that there is only one symbol table but that this
	 * could change in the future.
	 */
	for (i = 0; i < ehdr.e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			symoff = shdr[i].sh_offset;
			symsize = shdr[i].sh_size;
			symstroff = shdr[shdr[i].sh_link].sh_offset;
			symstrsize = shdr[shdr[i].sh_link].sh_size;
			break;
		}
	}

	/* Flush the section header table */
	free(shdr);

	/*
	 * Read string table into our address space.
	 */
	if ((strtab = malloc(symstrsize)) == NULL)
		return (-1);
	if (fpread(f, strtab, symstrsize, symstroff) != symstrsize) {
		free(strtab);
		return (-1);
	}
	/*
	 * clean out any left-over information for all valid entries.
	 * Type and value defined to be 0 if not found; historical
	 * versions cleared other and desc as well.  Also figure out
	 * the largest string length so don't read any more of the
	 * string table than we have to.
	 *
	 * XXX clearing anything other than n_type and n_value violates
	 * the semantics given in the man page.
	 */
	nent = 0;
	for (p = list; !ISLAST(p); ++p) {
		p->n_type = 0;
		p->n_other = 0;
		p->n_desc = 0;
		p->n_value = 0;
		++nent;
	}

	/* Don't process any further if object is stripped. */
	/* ELFism - dunno if stripped by looking at header */
	if (symoff == 0)
		goto elf_done;

	while (symsize > 0) {
		cc = MIN(symsize, sizeof(sbuf));
		if (fpread(f, sbuf, cc, symoff) != cc)
			break;
		symsize -= cc;
		symoff += cc;
		for (s = sbuf; cc > 0; ++s, cc -= sizeof(*s)) {
			int soff = s->st_name;

			if (soff == 0)
				continue;
			for (p = list; !ISLAST(p); p++) {
				char *sym;

				/*
				 * First we check for the symbol as it was
				 * provided by the user. If that fails
				 * and the first char is an '_', skip over
				 * the '_' and try again.
				 * XXX - What do we do when the user really
				 *       wants '_foo' and the are symbols
				 *       for both 'foo' and '_foo' in the
				 *	 table and 'foo' is first?
				 */
				sym = p->n_un.n_name;
				if (strcmp(&strtab[soff], sym) != 0 &&
				    (sym[0] != '_' ||
				     strcmp(&strtab[soff], sym + 1) != 0))
					continue;

				p->n_value = s->st_value;

				/* XXX - type conversion */
				/*	 is pretty rude. */
				switch(ELF_ST_TYPE(s->st_info)) {
				case STT_NOTYPE:
					switch (s->st_shndx) {
					case SHN_UNDEF:
						p->n_type = N_UNDF;
						break;
					case SHN_ABS:
						p->n_type = N_ABS;
						break;
					case SHN_COMMON:
						p->n_type = N_COMM;
						break;
					default:
						p->n_type = N_COMM | N_EXT;
						break;
					}
					break;
				case STT_OBJECT:
					p->n_type = N_DATA;
					break;
				case STT_FUNC:
					p->n_type = N_TEXT;
					break;
				case STT_FILE:
					p->n_type = N_FN;
					break;
				}
				if (ELF_ST_BIND(s->st_info) ==
				    STB_LOCAL)
					p->n_type = N_EXT;
				p->n_desc = 0;
				p->n_other = 0;
				if (--nent <= 0)
					break;
			}
		}
	}
elf_done:
	free(strtab);
	return (nent);
}
#endif /* _NLIST_DO_ELF */


static struct nlist_handlers {
	int	(*fn)(FILE *f, struct nlist *list);
} nlist_fn[] = {
#ifdef _NLIST_DO_AOUT
	{ __aout_fnlist },
#endif
#ifdef _NLIST_DO_ELF
	{ __elf_fnlist },
#endif
};

int
__fnlist(FILE *f, struct nlist *list)
{
	int n = -1, i;

	for (i = 0; i < sizeof(nlist_fn)/sizeof(nlist_fn[0]); i++) {
		n = (nlist_fn[i].fn)(f, list);
		if (n != -1)
			break;
	}
	return (n);
}
