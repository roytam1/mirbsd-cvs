/* $MirOS: src/sys/lib/libsa/fat.h,v 1.2 2005/12/17 05:46:26 tg Exp $ */

#ifndef _SYS_LIB_LIBSA_USTAR_H
#define _SYS_LIB_LIBSA_USTAR_H

typedef struct {
	char name[100];			/* ASCII filename, NUL or #100 ends */
	char mode[8];			/* OCT mode (UNIX permissions) */
	char uid[8];			/* OCT numerical uid */
	char gid[8];			/* OCT numerical gid */
	char size[12];			/* OCT file size (up to 8 GiB) */
	char mtime[12];			/* OCT file mtime (time_t) */
	char chksum[8];			/* OCT header additive checksum */
	char typeflag;			/* see below */
	char linkname[100];		/* ASCII linkdest, NUL or #100 ends */
	char magic[6];			/* ASCIZ "ustar" */
	char version[2];		/* ASCII "00" */
	char uname[32];			/* ASCIZ alpha uid */
	char gname[32];			/* ASCIZ alpha gid */
	char devmajor[8];
	char devminor[8];
	char prefix[155];		/* ASCII pathpart, NUL or #155 ends */
	char _padding[12];		/* pad up to 512 octets */
} ustar_hdr_t;

/**
 * Possible typeflags:
 * + with data blocks stored ((size+511)/512):
 *   - '0' or '\0' or '7' = regular file
 * + without data blocks stored:
 *   - '1' = hardlink (target is in linkname, prev. archived)
 *   - '2' = symlink (target is in linkname)
 *   - '3' = character device
 *   - '4' = block device
 *   - '5' = directory
 *   - '6' = FIFO
 * + everything else is invalid and will initiate header search
 */

extern const char ustar_magic_version[8];

#endif
