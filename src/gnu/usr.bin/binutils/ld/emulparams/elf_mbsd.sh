# $MirOS: src/gnu/usr.bin/binutils/ld/emulparams/elf_mbsd.sh,v 1.1.7.1 2005/03/06 16:58:49 tg Exp $

. ${srcdir}/emulparams/elf_obsd.sh

# Not. That's the BFD output format. MirOS BSD uses pretty
# standard ELF, so no need to do that.
#OUTPUT_FORMAT="${OUTPUT_FORMAT}-mirbsd"

INITIAL_NOTE_SECTIONS='.note.miros.ident'
