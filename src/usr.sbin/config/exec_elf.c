/*	$OpenBSD: exec_elf.c,v 1.10 2004/01/04 18:30:05 deraadt Exp $ */

/*
 * Copyright (c) 1999 Mats O Jansson.  All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <nlist.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/exec.h>
#include <sys/exec_elf.h>
#include <sys/types.h>

#include "ukc.h"
#include "config.h"

__RCSID("$MirOS$");

caddr_t		ptr, rest, pre;
Elf_Ehdr	elf_ex;
Elf_Phdr	*elf_phdr;
Elf_Shdr	*elf_shdr;
char		*elf_total;
char		*elf_shstrtab;
off_t		elf_size;

caddr_t		elf_adjust(caddr_t);
caddr_t		elf_readjust(caddr_t);
int		elf_check(char *);
void		elf_loadkernel(char *);
void		elf_savekernel(char *);

caddr_t
elf_adjust(caddr_t x)
{
	int i;
	Elf_Shdr *s;
	unsigned long y = 0;

	s = elf_shdr;

	for (i = 0; i < elf_ex.e_shnum; i++) {
		if (s[i].sh_addr == 0)
			continue;
		if (((unsigned long)x >= s[i].sh_addr) &&
		    ((unsigned long)x < (s[i].sh_addr+s[i].sh_size))) {
			y = (unsigned long)&elf_total[(unsigned long)x -
			    s[i].sh_addr + s[i].sh_offset];
			break;
		}
	}

	return((caddr_t)y);
}

caddr_t
elf_readjust(caddr_t x)
{
	int i;
	Elf_Shdr *s;
	unsigned long y = 0;

	s = elf_shdr;

	for (i = 0; i < elf_ex.e_shnum; i++) {
		if (s[i].sh_addr == 0)
			continue;
		if (((x - elf_total) >= s[i].sh_offset) &&
		    ((x - elf_total) <= (s[i].sh_offset + s[i].sh_size)))
			y = (unsigned long)x - (unsigned long)elf_total +
			    (unsigned long)s[i].sh_addr - s[i].sh_offset;
	}

	return((caddr_t)y);
}

int
elf_check(char *file)
{
	int fd, ret = 1;

	if ((fd = open(file, O_RDONLY | O_EXLOCK, 0)) < 0)
		return (0);

	if (read(fd, (char *)&elf_ex, sizeof(elf_ex)) != sizeof(elf_ex))
		ret = 0;

	if (ret) {
		if (!IS_ELF(elf_ex))
			ret = 0;
	}

	close(fd);
	return (ret);
}

void
elf_loadkernel(char *file)
{
	int fd;

	if ((fd = open(file, O_RDONLY | O_EXLOCK, 0)) < 0)
		err(1, "%s", file);

	if (read(fd, (char *)&elf_ex, sizeof(elf_ex)) != sizeof(elf_ex))
		errx(1, "can't read elf header");

	if (!IS_ELF(elf_ex))
		errx(1, "bad elf magic");

	elf_size = lseek(fd, (off_t)0, SEEK_END);
	(void)lseek(fd, (off_t)0, SEEK_SET);
	elf_total = emalloc((size_t)elf_size);

	if (read(fd, elf_total, (size_t)elf_size) != elf_size)
		errx(1, "can't read elf kernel");

	elf_phdr = (Elf_Phdr *)&elf_total[elf_ex.e_phoff];
	elf_shdr = (Elf_Shdr *)&elf_total[elf_ex.e_shoff];

	elf_shstrtab = &elf_total[elf_shdr[elf_ex.e_shstrndx].sh_offset];

	close(fd);
}

void
elf_savekernel(char *outfile)
{
	int fd;

	if ((fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0755)) < 0)
		err(1, "%s", outfile);

	if (write(fd, elf_total, (size_t)elf_size) != elf_size)
		errx(1, "can't write file %s", outfile);

	close(fd);
}
