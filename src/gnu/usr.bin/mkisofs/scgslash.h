
/* @(#)scsicdb.h	2.18 03/04/20 Copyright 1986 J. Schilling */
/*
 *	Definitions for the SCSI Command Descriptor Block
 *
 *	Copyright (c) 1986 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef	_SCG_SCSICDB_H
#define	_SCG_SCSICDB_H

#ifndef  _UTYPES_H
#include <utypes.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif
/*
 * SCSI Operation codes. 
 */
#define SC_TEST_UNIT_READY	0x00
#define SC_REZERO_UNIT		0x01
#define SC_REQUEST_SENSE	0x03
#define SC_FORMAT		0x04
#define SC_FORMAT_TRACK		0x06
#define SC_REASSIGN_BLOCK	0x07		/* CCS only */
#define SC_SEEK			0x0b
#define SC_TRANSLATE		0x0f		/* ACB4000 only */
#define SC_INQUIRY		0x12		/* CCS only */
#define SC_MODE_SELECT		0x15
#define SC_RESERVE		0x16
#define SC_RELEASE		0x17
#define SC_MODE_SENSE		0x1a
#define SC_START		0x1b
#define SC_READ_DEFECT_LIST	0x37		/* CCS only, group 1 */
#define SC_READ_BUFFER          0x3c            /* CCS only, group 1 */
	/*
	 * Note, these two commands use identical command blocks for all
 	 * controllers except the Adaptec ACB 4000 which sets bit 1 of byte 1.
	 */
#define SC_READ			0x08
#define SC_WRITE		0x0a
#define SC_EREAD		0x28		/* 10 byte read */
#define SC_EWRITE		0x2a		/* 10 byte write */
#define SC_WRITE_VERIFY		0x2e            /* 10 byte write+verify */
#define SC_WRITE_FILE_MARK	0x10
#define SC_UNKNOWN		0xff		/* cmd list terminator */


/*
 * Standard SCSI control blocks.
 * These go in or out over the SCSI bus.
 */

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_g0cdb {		/* scsi group 0 command description block */
	Uchar	cmd;		/* command code */
	Ucbit	high_addr : 5;	/* high part of block address */
	Ucbit	lun	  : 3;	/* logical unit number */
	Uchar	mid_addr;	/* middle part of block address */
	Uchar	low_addr;	/* low part of block address */
	Uchar	count;		/* transfer length */
	Ucbit	link	  : 1;	/* link (another command follows) */
	Ucbit	fr	  : 1;	/* flag request (interrupt at completion) */
	Ucbit	naca	  : 1;	/* Normal ACA (Auto Contingent Allegiance) */
	Ucbit	rsvd	  : 3;	/* reserved */
	Ucbit	vu_56	  : 1;	/* vendor unique (byte 5 bit 6) */
	Ucbit	vu_57	  : 1;	/* vendor unique (byte 5 bit 7) */
};

#else	/* Motorola byteorder */

struct	scsi_g0cdb {		/* scsi group 0 command description block */
	Uchar	cmd;		/* command code */
	Ucbit	lun	  : 3;	/* logical unit number */
	Ucbit	high_addr : 5;	/* high part of block address */
	Uchar	mid_addr;	/* middle part of block address */
	Uchar	low_addr;	/* low part of block address */
	Uchar	count;		/* transfer length */
	Ucbit	vu_57	  : 1;	/* vendor unique (byte 5 bit 7) */
	Ucbit	vu_56	  : 1;	/* vendor unique (byte 5 bit 6) */
	Ucbit	rsvd	  : 3;	/* reserved */
	Ucbit	naca	  : 1;	/* Normal ACA (Auto Contingent Allegiance) */
	Ucbit	fr	  : 1;	/* flag request (interrupt at completion) */
	Ucbit	link	  : 1;	/* link (another command follows) */
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_g1cdb {		/* scsi group 1 command description block */
	Uchar	cmd;		/* command code */
	Ucbit	reladr	  : 1;	/* address is relative */
	Ucbit	res	  : 4;	/* reserved bits 1-4 of byte 1 */
	Ucbit	lun	  : 3;	/* logical unit number */
	Uchar	addr[4];	/* logical block address */
	Uchar	res6;		/* reserved byte 6 */
	Uchar	count[2];	/* transfer length */
	Ucbit	link	  : 1;	/* link (another command follows) */
	Ucbit	fr	  : 1;	/* flag request (interrupt at completion) */
	Ucbit	naca	  : 1;	/* Normal ACA (Auto Contingent Allegiance) */
	Ucbit	rsvd	  : 3;	/* reserved */
	Ucbit	vu_96	  : 1;	/* vendor unique (byte 5 bit 6) */
	Ucbit	vu_97	  : 1;	/* vendor unique (byte 5 bit 7) */
};

#else	/* Motorola byteorder */

struct	scsi_g1cdb {		/* scsi group 1 command description block */
	Uchar	cmd;		/* command code */
	Ucbit	lun	  : 3;	/* logical unit number */
	Ucbit	res	  : 4;	/* reserved bits 1-4 of byte 1 */
	Ucbit	reladr	  : 1;	/* address is relative */
	Uchar	addr[4];	/* logical block address */
	Uchar	res6;		/* reserved byte 6 */
	Uchar	count[2];	/* transfer length */
	Ucbit	vu_97	  : 1;	/* vendor unique (byte 5 bit 7) */
	Ucbit	vu_96	  : 1;	/* vendor unique (byte 5 bit 6) */
	Ucbit	rsvd	  : 3;	/* reserved */
	Ucbit	naca	  : 1;	/* Normal ACA (Auto Contingent Allegiance) */
	Ucbit	fr	  : 1;	/* flag request (interrupt at completion) */
	Ucbit	link	  : 1;	/* link (another command follows) */
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_g5cdb {		/* scsi group 5 command description block */
	Uchar	cmd;		/* command code */
	Ucbit	reladr	  : 1;	/* address is relative */
	Ucbit	res	  : 4;	/* reserved bits 1-4 of byte 1 */
	Ucbit	lun	  : 3;	/* logical unit number */
	Uchar	addr[4];	/* logical block address */
	Uchar	count[4];	/* transfer length */
	Uchar	res10;		/* reserved byte 10 */
	Ucbit	link	  : 1;	/* link (another command follows) */
	Ucbit	fr	  : 1;	/* flag request (interrupt at completion) */
	Ucbit	naca	  : 1;	/* Normal ACA (Auto Contingent Allegiance) */
	Ucbit	rsvd	  : 3;	/* reserved */
	Ucbit	vu_B6	  : 1;	/* vendor unique (byte B bit 6) */
	Ucbit	vu_B7	  : 1;	/* vendor unique (byte B bit 7) */
};

#else	/* Motorola byteorder */

struct	scsi_g5cdb {		/* scsi group 5 command description block */
	Uchar	cmd;		/* command code */
	Ucbit	lun	  : 3;	/* logical unit number */
	Ucbit	res	  : 4;	/* reserved bits 1-4 of byte 1 */
	Ucbit	reladr	  : 1;	/* address is relative */
	Uchar	addr[4];	/* logical block address */
	Uchar	count[4];	/* transfer length */
	Uchar	res10;		/* reserved byte 10 */
	Ucbit	vu_B7	  : 1;	/* vendor unique (byte B bit 7) */
	Ucbit	vu_B6	  : 1;	/* vendor unique (byte B bit 6) */
	Ucbit	rsvd	  : 3;	/* reserved */
	Ucbit	naca	  : 1;	/* Normal ACA (Auto Contingent Allegiance) */
	Ucbit	fr	  : 1;	/* flag request (interrupt at completion) */
	Ucbit	link	  : 1;	/* link (another command follows) */
};
#endif

#define	g0_cdbaddr(cdb, a)	((cdb)->high_addr = (a) >> 16,\
				 (cdb)->mid_addr = ((a) >> 8) & 0xFF,\
				 (cdb)->low_addr = (a) & 0xFF)

#define	g1_cdbaddr(cdb, a)	((cdb)->addr[0] = (a) >> 24,\
				 (cdb)->addr[1] = ((a) >> 16)& 0xFF,\
				 (cdb)->addr[2] = ((a) >> 8) & 0xFF,\
				 (cdb)->addr[3] = (a) & 0xFF)

#define g5_cdbaddr(cdb, a)	g1_cdbaddr(cdb, a)


#define	g0_cdblen(cdb, len)	((cdb)->count = (len))

#define	g1_cdblen(cdb, len)	((cdb)->count[0] = ((len) >> 8) & 0xFF,\
				 (cdb)->count[1] = (len) & 0xFF)

#define g5_cdblen(cdb, len)	((cdb)->count[0] = (len) >> 24L,\
				 (cdb)->count[1] = ((len) >> 16L)& 0xFF,\
				 (cdb)->count[2] = ((len) >> 8L) & 0xFF,\
				 (cdb)->count[3] = (len) & 0xFF)

/*#define	XXXXX*/
#ifdef	XXXXX
#define	i_to_long(a, i)		(((Uchar *)(a))[0] = ((i) >> 24)& 0xFF,\
				 ((Uchar *)(a))[1] = ((i) >> 16)& 0xFF,\
				 ((Uchar *)(a))[2] = ((i) >> 8) & 0xFF,\
				 ((Uchar *)(a))[3] = (i) & 0xFF)

#define	i_to_3_byte(a, i)	(((Uchar *)(a))[0] = ((i) >> 16)& 0xFF,\
				 ((Uchar *)(a))[1] = ((i) >> 8) & 0xFF,\
				 ((Uchar *)(a))[2] = (i) & 0xFF)

#define	i_to_4_byte(a, i)	(((Uchar *)(a))[0] = ((i) >> 24)& 0xFF,\
				 ((Uchar *)(a))[1] = ((i) >> 16)& 0xFF,\
				 ((Uchar *)(a))[2] = ((i) >> 8) & 0xFF,\
				 ((Uchar *)(a))[3] = (i) & 0xFF)

#define	i_to_short(a, i)	(((Uchar *)(a))[0] = ((i) >> 8) & 0xFF,\
				 ((Uchar *)(a))[1] = (i) & 0xFF)

#define	a_to_u_short(a)	((unsigned short) \
			((((Uchar*) a)[1]       & 0xFF) | \
			 (((Uchar*) a)[0] << 8  & 0xFF00)))

#define	a_to_3_byte(a)	((Ulong) \
			((((Uchar*) a)[2]       & 0xFF) | \
			 (((Uchar*) a)[1] << 8  & 0xFF00) | \
			 (((Uchar*) a)[0] << 16 & 0xFF0000)))

#ifdef	__STDC__
#define	a_to_u_long(a)	((Ulong) \
			((((Uchar*) a)[3]       & 0xFF) | \
			 (((Uchar*) a)[2] << 8  & 0xFF00) | \
			 (((Uchar*) a)[1] << 16 & 0xFF0000) | \
			 (((Uchar*) a)[0] << 24 & 0xFF000000UL)))
#else
#define	a_to_u_long(a)	((Ulong) \
			((((Uchar*) a)[3]       & 0xFF) | \
			 (((Uchar*) a)[2] << 8  & 0xFF00) | \
			 (((Uchar*) a)[1] << 16 & 0xFF0000) | \
			 (((Uchar*) a)[0] << 24 & 0xFF000000)))
#endif
#endif	/* XXXX */


#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCSICDB_H */
/* @(#)scsisense.h	2.17 00/11/07 Copyright 1986 J. Schilling */
/*
 *	Definitions for the SCSI status code and sense structure
 *
 *	Copyright (c) 1986 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_SCG_SCSISENSE_H
#define	_SCG_SCSISENSE_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * SCSI status completion block.
 */
#define	SCSI_EXTENDED_STATUS

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_status {
	Ucbit	vu_00	: 1;	/* vendor unique */
	Ucbit	chk	: 1;	/* check condition: sense data available */
	Ucbit	cm	: 1;	/* condition met */
	Ucbit	busy	: 1;	/* device busy or reserved */
	Ucbit	is	: 1;	/* intermediate status sent */
	Ucbit	vu_05	: 1;	/* vendor unique */
#define st_scsi2	vu_05	/* SCSI-2 modifier bit */
	Ucbit	vu_06	: 1;	/* vendor unique */
	Ucbit	st_rsvd	: 1;	/* reserved */

#ifdef	SCSI_EXTENDED_STATUS
#define	ext_st1	st_rsvd		/* extended status (next byte valid) */
	/* byte 1 */
	Ucbit	ha_er	: 1;	/* host adapter detected error */
	Ucbit	reserved: 6;	/* reserved */
	Ucbit	ext_st2	: 1;	/* extended status (next byte valid) */
	/* byte 2 */
	Uchar	byte2;		/* third byte */
#endif	/* SCSI_EXTENDED_STATUS */
};

#else	/* Motorola byteorder */

struct	scsi_status {
	Ucbit	st_rsvd	: 1;	/* reserved */
	Ucbit	vu_06	: 1;	/* vendor unique */
	Ucbit	vu_05	: 1;	/* vendor unique */
#define st_scsi2	vu_05	/* SCSI-2 modifier bit */
	Ucbit	is	: 1;	/* intermediate status sent */
	Ucbit	busy	: 1;	/* device busy or reserved */
	Ucbit	cm	: 1;	/* condition met */
	Ucbit	chk	: 1;	/* check condition: sense data available */
	Ucbit	vu_00	: 1;	/* vendor unique */
#ifdef	SCSI_EXTENDED_STATUS
#define	ext_st1	st_rsvd		/* extended status (next byte valid) */
	/* byte 1 */
	Ucbit	ext_st2	: 1;	/* extended status (next byte valid) */
	Ucbit	reserved: 6;	/* reserved */
	Ucbit	ha_er	: 1;	/* host adapter detected error */
	/* byte 2 */
	Uchar	byte2;		/* third byte */
#endif	/* SCSI_EXTENDED_STATUS */
};
#endif

/*
 * OLD Standard (Non Extended) SCSI Sense. Used mainly by the
 * Adaptec ACB 4000 which is the only controller that
 * does not support the Extended sense format.
 */
#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_sense {		/* scsi sense for error classes 0-6 */
	Ucbit	code	: 7;	/* error class/code */
	Ucbit	adr_val	: 1;	/* sense data is valid */
#ifdef	comment
	Ucbit	high_addr:5;	/* high byte of block addr */
	Ucbit	rsvd	: 3;
#else
	Uchar	high_addr;	/* high byte of block addr */
#endif
	Uchar	mid_addr;	/* middle byte of block addr */
	Uchar	low_addr;	/* low byte of block addr */
};

#else	/* Motorola byteorder */

struct	scsi_sense {		/* scsi sense for error classes 0-6 */
	Ucbit	adr_val	: 1;	/* sense data is valid */
	Ucbit	code	: 7;	/* error class/code */
#ifdef	comment
	Ucbit	rsvd	: 3;
	Ucbit	high_addr:5;	/* high byte of block addr */
#else
	Uchar	high_addr;	/* high byte of block addr */
#endif
	Uchar	mid_addr;	/* middle byte of block addr */
	Uchar	low_addr;	/* low byte of block addr */
};
#endif

/*
 * SCSI extended sense parameter block.
 */
#ifdef	comment
#define SC_CLASS_EXTENDED_SENSE 0x7     /* indicates extended sense */
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_ext_sense {	/* scsi extended sense for error class 7 */
	/* byte 0 */
	Ucbit	type	: 7;	/* fixed at 0x70 */
	Ucbit	adr_val	: 1;	/* sense data is valid */
	/* byte 1 */
	Uchar	seg_num;	/* segment number, applies to copy cmd only */
	/* byte 2 */
	Ucbit	key	: 4;	/* sense key, see below */
	Ucbit		: 1;	/* reserved */
	Ucbit	ili	: 1;	/* incorrect length indicator */
	Ucbit	eom	: 1;	/* end of media */
	Ucbit	fil_mk	: 1;	/* file mark on device */
	/* bytes 3 through 7 */
	Uchar	info_1;		/* information byte 1 */
	Uchar	info_2;		/* information byte 2 */
	Uchar	info_3;		/* information byte 3 */
	Uchar	info_4;		/* information byte 4 */
	Uchar	add_len;	/* number of additional bytes */
	/* bytes 8 through 13, CCS additions */
	Uchar	optional_8;	/* CCS search and copy only */
	Uchar	optional_9;	/* CCS search and copy only */
	Uchar	optional_10;	/* CCS search and copy only */
	Uchar	optional_11;	/* CCS search and copy only */
	Uchar 	sense_code;	/* sense code */
	Uchar	qual_code;	/* sense code qualifier */
	Uchar	fru_code;	/* Field replacable unit code */
	Ucbit	bptr	: 3;	/* bit pointer for failure (if bpv) */
	Ucbit	bpv	: 1;	/* bit pointer is valid */
	Ucbit		: 2;
	Ucbit	cd	: 1;	/* pointers refer to command not data */
	Ucbit	sksv	: 1;	/* sense key specific valid */
	Uchar	field_ptr[2];	/* field pointer for failure */
	Uchar	add_info[2];	/* round up to 20 bytes */
};

#else	/* Motorola byteorder */

struct	scsi_ext_sense {	/* scsi extended sense for error class 7 */
	/* byte 0 */
	Ucbit	adr_val	: 1;	/* sense data is valid */
	Ucbit	type	: 7;	/* fixed at 0x70 */
	/* byte 1 */
	Uchar	seg_num;	/* segment number, applies to copy cmd only */
	/* byte 2 */
	Ucbit	fil_mk	: 1;	/* file mark on device */
	Ucbit	eom	: 1;	/* end of media */
	Ucbit	ili	: 1;	/* incorrect length indicator */
	Ucbit		: 1;	/* reserved */
	Ucbit	key	: 4;	/* sense key, see below */
	/* bytes 3 through 7 */
	Uchar	info_1;		/* information byte 1 */
	Uchar	info_2;		/* information byte 2 */
	Uchar	info_3;		/* information byte 3 */
	Uchar	info_4;		/* information byte 4 */
	Uchar	add_len;	/* number of additional bytes */
	/* bytes 8 through 13, CCS additions */
	Uchar	optional_8;	/* CCS search and copy only */
	Uchar	optional_9;	/* CCS search and copy only */
	Uchar	optional_10;	/* CCS search and copy only */
	Uchar	optional_11;	/* CCS search and copy only */
	Uchar 	sense_code;	/* sense code */
	Uchar	qual_code;	/* sense code qualifier */
	Uchar	fru_code;	/* Field replacable unit code */
	Ucbit	sksv	: 1;	/* sense key specific valid */
	Ucbit	cd	: 1;	/* pointers refer to command not data */
	Ucbit		: 2;
	Ucbit	bpv	: 1;	/* bit pointer is valid */
	Ucbit	bptr	: 3;	/* bit pointer for failure (if bpv) */
	Uchar	field_ptr[2];	/* field pointer for failure */
	Uchar	add_info[2];	/* round up to 20 bytes */
};
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCSISENSE_H */
/* @(#)scgcmd.h	2.21 02/08/08 Copyright 1986 J. Schilling */
/*
 *	Definitions for the SCSI 'scg_cmd' structure that has been created
 *	for the SCSI general driver 'scg' for SunOS and Solaris but
 *	now is used for wrapping general libscg SCSI transport requests.
 *
 *	Copyright (c) 1986 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_SCG_SCGCMD_H
#define	_SCG_SCGCMD_H

#include <utypes.h>
#include <btorder.h>

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */
#else
# if	defined(_BIT_FIELDS_HTOL)	/* Motorola byteorder */
# else 
/*
 * #error will not work for all compilers (e.g. sunos4)
 * The following line will abort compilation on all compilers
 * if none of the above is defines. And that's  what we want.
 */
error  One of _BIT_FIELDS_LTOH or _BIT_FIELDS_HTOL must be defined
# endif
#endif

#include <intcvt.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Leave these definitions here if possible to avoid the need to
 * include scsireg.h which makes problems on some OS because these
 * OS define the same types as in scsireg.h
 */

/* 
 * SCSI status bits.
 */
#define	ST_VU_00	0x01	/* Vendor unique		*/
#define	ST_CHK_COND	0x02	/* Check condition		*/
#define	ST_COND_MET	0x04	/* Condition met		*/
#define	ST_BUSY		0x08	/* Busy				*/
#define	ST_IS_SEND	0x10	/* Intermediate status send	*/
#define	ST_VU_05	0x20	/* Vendor unique		*/
#define	ST_VU_06	0x40	/* Vendor unique		*/
#define	ST_RSVD_07	0x80	/* Reserved	 		*/

/* 
 * Sense key values for extended sense.
 */
#define SC_NO_SENSE		0x00
#define SC_RECOVERABLE_ERROR	0x01
#define SC_NOT_READY		0x02
#define SC_MEDIUM_ERROR		0x03
#define SC_HARDWARE_ERROR	0x04
#define SC_ILLEGAL_REQUEST	0x05
#define SC_UNIT_ATTENTION	0x06
#define SC_WRITE_PROTECT	0x07
#define SC_BLANK_CHECK		0x08
#define SC_VENDOR_UNIQUE	0x09
#define SC_COPY_ABORTED		0x0A
#define SC_ABORTED_COMMAND	0x0B
#define SC_EQUAL		0x0C
#define SC_VOLUME_OVERFLOW	0x0D
#define SC_MISCOMPARE		0x0E
#define SC_RESERVED		0x0F

/*
 * Messages that SCSI can send.
 */
#define SC_COMMAND_COMPLETE	0x00
#define SC_SYNCHRONOUS		0x01
#define SC_SAVE_DATA_PTR	0x02
#define SC_RESTORE_PTRS		0x03
#define SC_DISCONNECT		0x04
#define SC_ABORT		0x06
#define SC_MSG_REJECT		0x07
#define SC_NO_OP		0x08
#define SC_PARITY		0x09
#define SC_IDENTIFY		0x80
#define SC_DR_IDENTIFY		0xc0
#define SC_DEVICE_RESET		0x0c

#define	SC_G0_CDBLEN	6	/* Len of Group 0 commands */
#define	SC_G1_CDBLEN	10	/* Len of Group 1 commands */
#define	SC_G5_CDBLEN	12	/* Len of Group 5 commands */

#define	SCG_MAX_CMD	24	/* 24 bytes max. size is supported */
#define	SCG_MAX_STATUS	3	/* XXX (sollte 4 allign.) Mamimum Status Len */
#define	SCG_MAX_SENSE	32	/* Mamimum Sense Len for auto Req. Sense */

#define	DEF_SENSE_LEN	16	/* Default Sense Len */
#define	CCS_SENSE_LEN	18	/* Sense Len for CCS compatible devices */

struct	scg_cmd {
	caddr_t	addr;			/* Address of data in user space */
	int	size;			/* DMA count for data transfer */
	int	flags;			/* see below for definition */
	int	cdb_len;		/* Size of SCSI command in bytes */
					/* NOTE: rel 4 uses this field only */
					/* with commands not in group 1 or 2*/
	int	sense_len;		/* for intr() if -1 don't get sense */
	int	timeout;		/* timeout in seconds */
					/* NOTE: actual resolution depends */
					/* on driver implementation */
	int	kdebug;			/* driver kernel debug level */
	int	resid;			/* Bytes not transfered */
	int	error;			/* Error code from scgintr() */
	int	ux_errno;		/* UNIX error code */
#ifdef	comment
XXX	struct	scsi_status scb; ???	/* Status returnd by command */
#endif
	union {
		struct	scsi_status Scb;/* Status returnd by command */
		Uchar	cmd_scb[SCG_MAX_STATUS];
	} u_scb;
#define	scb	u_scb.Scb
#ifdef	comment
XXX	struct	scsi_sense sense; ???	/* Sense bytes from command */
#endif
	union {
		struct	scsi_sense Sense;/* Sense bytes from command */
		Uchar	cmd_sense[SCG_MAX_SENSE];
	} u_sense;
#define	sense	u_sense.Sense
	int	sense_count;		/* Number of bytes valid in sense */
	int	target;			/* SCSI target id */
					/* NOTE: The SCSI target id field    */
					/* does not need to be filled unless */
					/* the low level transport is a real */
					/* scg driver. In this case the low  */
					/* level transport routine of libscg */
					/* will fill in the needed value     */
	union {				/* SCSI command descriptor block */
		struct	scsi_g0cdb g0_cdb;
		struct	scsi_g1cdb g1_cdb;
		struct	scsi_g5cdb g5_cdb;
		Uchar	cmd_cdb[SCG_MAX_CMD];
	} cdb;				/* 24 bytes max. size is supported */
};

#define	dma_read	flags		/* 1 if DMA to Sun, 0 otherwise */

/*
 * definition for flags field in scg_cmd struct
 */
#define	SCG_RECV_DATA	0x0001		/* DMA direction to Sun */
#define	SCG_DISRE_ENA	0x0002		/* enable disconnect/reconnect */
#define	SCG_SILENT	0x0004		/* be silent on errors */
#define	SCG_CMD_RETRY	0x0008		/* enable retries */
#define	SCG_NOPARITY	0x0010		/* disable parity for this command */

/*
 * definition for error field in scg_cmd struct
 *
 * The codes refer to SCSI general errors, not to device
 * specific errors.  Device specific errors are discovered
 * by checking the sense data.
 * The distinction between retryable and fatal is somewhat ad hoc.
 */
#define SCG_NO_ERROR	0		/* cdb transported without error     */
					/* SCG_NO_ERROR incudes all commands */
					/* where the SCSI status is valid    */

#define SCG_RETRYABLE	1		/* any other case e.g. SCSI bus busy */
					/* SCSI cdb could not be send,	     */
					/* includes DMA errors other than    */
					/* DMA underrun			     */

#define SCG_FATAL	2		/* could not select target	     */
#define SCG_TIMEOUT	3		/* driver timed out		     */


#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCGCMD_H */
/* @(#)scgio.h	2.16 00/11/07 Copyright 1986 J. Schilling */
/*
 *	Definitions for the SCSI general driver 'scg'
 *
 *	Copyright (c) 1986 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_SCG_SCGIO_H
#define	_SCG_SCGIO_H

#if	defined(SVR4)
#include <sys/ioccom.h>
#endif

#ifdef	__cplusplus
extern "C" {
#endif

#if	defined(__STDC__) || defined(SVR4)
#define	SCGIOCMD	_IOWR('G', 1, struct scg_cmd)	/* do a SCSI cmd   */
#define	SCGIORESET	_IO('G', 2)			/* reset SCSI bus  */
#define	SCGIOGDISRE	_IOR('G', 4, int)		/* get sc disre Val*/
#define	SCGIOSDISRE	_IOW('G', 5, int)		/* set sc disre Val*/
#define	SCGIOIDBG	_IO('G', 100)			/* Inc Debug Val   */
#define	SCGIODDBG	_IO('G', 101)			/* Dec Debug Val   */
#define	SCGIOGDBG	_IOR('G', 102, int)		/* get Debug Val   */
#define	SCGIOSDBG	_IOW('G', 103, int)		/* set Debug Val   */
#define	SCIOGDBG	_IOR('G', 104, int)		/* get sc Debug Val*/
#define	SCIOSDBG	_IOW('G', 105, int)		/* set sc Debug Val*/
#else
#define	SCGIOCMD	_IOWR(G, 1, struct scg_cmd)	/* do a SCSI cmd   */
#define	SCGIORESET	_IO(G, 2)			/* reset SCSI bus  */
#define	SCGIOGDISRE	_IOR(G, 4, int)			/* get sc disre Val*/
#define	SCGIOSDISRE	_IOW(G, 5, int)			/* set sc disre Val*/
#define	SCGIOIDBG	_IO(G, 100)			/* Inc Debug Val   */
#define	SCGIODDBG	_IO(G, 101)			/* Dec Debug Val   */
#define	SCGIOGDBG	_IOR(G, 102, int)		/* get Debug Val   */
#define	SCGIOSDBG	_IOW(G, 103, int)		/* set Debug Val   */
#define	SCIOGDBG	_IOR(G, 104, int)		/* get sc Debug Val*/
#define	SCIOSDBG	_IOW(G, 105, int)		/* set sc Debug Val*/
#endif

#define	SCGIO_CMD	SCGIOCMD	/* backward ccompatibility */

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCGIO_H */
/* @(#)scsidefs.h	1.27 01/09/27 Copyright 1988 J. Schilling */
/*
 *	Definitions for SCSI devices i.e. for error strings in scsierrs.c
 *
 *	Copyright (c) 1988 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_SCG_SCSIDEFS_H
#define	_SCG_SCSIDEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Disks
 */
#ifdef	DEV_UNKNOWN
/*
 * True64 defines DEV_UNKNOWN in /usr/include/sys/devio.h as "UNKNOWN"
 */
#undef	DEV_UNKNOWN
#endif
#define	DEV_UNKNOWN		0
#define	DEV_ACB40X0		1
#define	DEV_ACB4000		2
#define	DEV_ACB4010		3
#define	DEV_ACB4070		4
#define	DEV_ACB5500		5
#define	DEV_ACB4520A		6
#define	DEV_ACB4525		7
#define	DEV_MD21		8
#define	DEV_MD23		9
#define	DEV_NON_CCS_DSK		10
#define	DEV_CCS_GENDISK		11

/*
 * Tapes
 */
#define	DEV_MT02		100
#define	DEV_SC4000		101

/*
 * Printer
 */
#define	DEV_PRT			200

/*
 * Processors
 */
#define	DEV_PROC		300

/*
 * Worm
 */
#define	DEV_WORM		400
#define	DEV_RXT800S		401

/*
 * CD-ROM
 */
#define	DEV_CDROM		500
#define	DEV_MMC_CDROM		501
#define	DEV_MMC_CDR		502
#define	DEV_MMC_CDRW		503
#define	DEV_MMC_DVD		504
#define	DEV_MMC_DVD_WR		505

#define	DEV_CDD_521_OLD		510
#define	DEV_CDD_521		511
#define	DEV_CDD_522		512
#define	DEV_PCD_600		513
#define	DEV_CDD_2000		514
#define	DEV_CDD_2600		515
#define	DEV_TYUDEN_EW50		516
#define	DEV_YAMAHA_CDR_100	520
#define	DEV_YAMAHA_CDR_400	521
#define	DEV_PLASMON_RF_4100	530
#define	DEV_SONY_CDU_924	540
#define	DEV_RICOH_RO_1420C	550
#define	DEV_RICOH_RO_1060C	551
#define	DEV_TEAC_CD_R50S	560
#define	DEV_MATSUSHITA_7501	570
#define	DEV_MATSUSHITA_7502	571
#define	DEV_PIONEER_DW_S114X	580
#define	DEV_PIONEER_DVDR_S101	581

/*
 * Scanners
 */
#define	DEV_HRSCAN		600
#define	DEV_MS300A		601

/*
 * Optical memory
 */
#define DEV_SONY_SMO		700


#define	old_acb(d)	(((d) == DEV_ACB40X0) || \
			 ((d) == DEV_ACB4000) || ((d) == DEV_ACB4010) || \
			 ((d) == DEV_ACB4070) || ((d) == DEV_ACB5500))

#define	is_ccs(d)	(!old_acb(d))

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCSIDEFS_H */
/* @(#)scsireg.h	1.29 03/04/20 Copyright 1987 J. Schilling */
/*
 *	usefull definitions for dealing with CCS SCSI - devices
 *
 *	Copyright (c) 1987 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef	_SCG_SCSIREG_H
#define	_SCG_SCSIREG_H

#include <utypes.h>
#include <btorder.h>

#ifdef	__cplusplus
extern "C" {
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_inquiry {
	Ucbit	type		: 5;	/*  0 */
	Ucbit	qualifier	: 3;	/*  0 */

	Ucbit	type_modifier	: 7;	/*  1 */
	Ucbit	removable	: 1;	/*  1 */

	Ucbit	ansi_version	: 3;	/*  2 */
	Ucbit	ecma_version	: 3;	/*  2 */
	Ucbit	iso_version	: 2;	/*  2 */

	Ucbit	data_format	: 4;	/*  3 */
	Ucbit	res3_54		: 2;	/*  3 */
	Ucbit	termiop		: 1;	/*  3 */
	Ucbit	aenc		: 1;	/*  3 */

	Ucbit	add_len		: 8;	/*  4 */
	Ucbit	sense_len	: 8;	/*  5 */ /* only Emulex ??? */
	Ucbit	res2		: 8;	/*  6 */

	Ucbit	softreset	: 1;	/*  7 */
	Ucbit	cmdque		: 1;
	Ucbit	res7_2		: 1;
	Ucbit	linked		: 1;
	Ucbit	sync		: 1;
	Ucbit	wbus16		: 1;
	Ucbit	wbus32		: 1;
	Ucbit	reladr		: 1;	/*  7 */

	char	vendor_info[8];		/*  8 */
	char	prod_ident[16];		/* 16 */
	char	prod_revision[4];	/* 32 */
#ifdef	comment
	char	vendor_uniq[20];	/* 36 */
	char	reserved[40];		/* 56 */
#endif
};					/* 96 */

#else					/* Motorola byteorder */

struct	scsi_inquiry {
	Ucbit	qualifier	: 3;	/*  0 */
	Ucbit	type		: 5;	/*  0 */

	Ucbit	removable	: 1;	/*  1 */
	Ucbit	type_modifier	: 7;	/*  1 */

	Ucbit	iso_version	: 2;	/*  2 */
	Ucbit	ecma_version	: 3;
	Ucbit	ansi_version	: 3;	/*  2 */

	Ucbit	aenc		: 1;	/*  3 */
	Ucbit	termiop		: 1;
	Ucbit	res3_54		: 2;
	Ucbit	data_format	: 4;	/*  3 */

	Ucbit	add_len		: 8;	/*  4 */
	Ucbit	sense_len	: 8;	/*  5 */ /* only Emulex ??? */
	Ucbit	res2		: 8;	/*  6 */
	Ucbit	reladr		: 1;	/*  7 */
	Ucbit	wbus32		: 1;
	Ucbit	wbus16		: 1;
	Ucbit	sync		: 1;
	Ucbit	linked		: 1;
	Ucbit	res7_2		: 1;
	Ucbit	cmdque		: 1;
	Ucbit	softreset	: 1;
	char	vendor_info[8];		/*  8 */
	char	prod_ident[16];		/* 16 */
	char	prod_revision[4];	/* 32 */
#ifdef	comment
	char	vendor_uniq[20];	/* 36 */
	char	reserved[40];		/* 56 */
#endif
};					/* 96 */
#endif

#define	info		vendor_info
#define	ident		prod_ident
#define	revision	prod_revision

/* Peripheral Device Qualifier */

#define	INQ_DEV_PRESENT	0x00		/* Physical device present */
#define	INQ_DEV_NOTPR	0x01		/* Physical device not present */
#define	INQ_DEV_RES	0x02		/* Reserved */
#define	INQ_DEV_NOTSUP	0x03		/* Logical unit not supported */

/* Peripheral Device Type */

#define	INQ_DASD	0x00		/* Direct-access device (disk) */
#define	INQ_SEQD	0x01		/* Sequential-access device (tape) */
#define	INQ_PRTD	0x02 		/* Printer device */
#define	INQ_PROCD	0x03 		/* Processor device */
#define	INQ_OPTD	0x04		/* Write once device (optical disk) */
#define	INQ_WORM	0x04		/* Write once device (optical disk) */
#define	INQ_ROMD	0x05		/* CD-ROM device */
#define	INQ_SCAN	0x06		/* Scanner device */
#define	INQ_OMEM	0x07		/* Optical Memory device */
#define	INQ_JUKE	0x08		/* Medium Changer device (jukebox) */
#define	INQ_COMM	0x09		/* Communications device */
#define	INQ_IT8_1	0x0A		/* IT8 */
#define	INQ_IT8_2	0x0B		/* IT8 */
#define	INQ_STARR	0x0C		/* Storage array device */
#define	INQ_ENCL	0x0D		/* Enclosure services device */
#define	INQ_SDAD	0x0E		/* Simplyfied direct-access device */
#define	INQ_OCRW	0x0F		/* Optical card reader/writer device */
#define	INQ_BRIDGE	0x10		/* Bridging expander device */
#define	INQ_OSD		0x11		/* Object based storage device */
#define	INQ_ADC		0x12		/* Automation/Drive interface */
#define	INQ_WELLKNOWN	0x1E		/* Well known logical unit */
#define	INQ_NODEV	0x1F		/* Unknown or no device */
#define	INQ_NOTPR	0x1F		/* Logical unit not present (SCSI-1) */

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_header {
	Ucbit	sense_data_len	: 8;
	Uchar	medium_type;
	Ucbit	res2		: 4;
	Ucbit	cache		: 1;
	Ucbit	res		: 2;
	Ucbit	write_prot	: 1;
	Uchar	blockdesc_len;
};

#else					/* Motorola byteorder */

struct scsi_mode_header {
	Ucbit	sense_data_len	: 8;
	Uchar	medium_type;
	Ucbit	write_prot	: 1;
	Ucbit	res		: 2;
	Ucbit	cache		: 1;
	Ucbit	res2		: 4;
	Uchar	blockdesc_len;
};
#endif

struct scsi_modesel_header {
	Ucbit	sense_data_len	: 8;
	Uchar	medium_type;
	Ucbit	res2		: 8;
	Uchar	blockdesc_len;
};

struct scsi_mode_blockdesc {
	Uchar	density;
	Uchar	nlblock[3];
	Ucbit	res		: 8;
	Uchar	lblen[3];
};

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct acb_mode_data {
	Uchar	listformat;
	Uchar	ncyl[2];
	Uchar	nhead;
	Uchar	start_red_wcurrent[2];
	Uchar	start_precomp[2];
	Uchar	landing_zone;
	Uchar	step_rate;
	Ucbit			: 2;
	Ucbit	hard_sec	: 1;
	Ucbit	fixed_media	: 1;
	Ucbit			: 4;
	Uchar	sect_per_trk;
};

#else					/* Motorola byteorder */

struct acb_mode_data {
	Uchar	listformat;
	Uchar	ncyl[2];
	Uchar	nhead;
	Uchar	start_red_wcurrent[2];
	Uchar	start_precomp[2];
	Uchar	landing_zone;
	Uchar	step_rate;
	Ucbit			: 4;
	Ucbit	fixed_media	: 1;
	Ucbit	hard_sec	: 1;
	Ucbit			: 2;
	Uchar	sect_per_trk;
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_header {
	Ucbit	p_code		: 6;
	Ucbit	res		: 1;
	Ucbit	parsave		: 1;
	Uchar	p_len;
};

/*
 * This is a hack that allows mode pages without
 * any further bitfileds to be defined bitorder independent.
 */
#define	MP_P_CODE			\
	Ucbit	p_code		: 6;	\
	Ucbit	p_res		: 1;	\
	Ucbit	parsave		: 1

#else					/* Motorola byteorder */

struct scsi_mode_page_header {
	Ucbit	parsave		: 1;
	Ucbit	res		: 1;
	Ucbit	p_code		: 6;
	Uchar	p_len;
};

/*
 * This is a hack that allows mode pages without
 * any further bitfileds to be defined bitorder independent.
 */
#define	MP_P_CODE			\
	Ucbit	parsave		: 1;	\
	Ucbit	p_res		: 1;	\
	Ucbit	p_code		: 6

#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_01 {		/* Error recovery Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Ucbit	term_on_rec_err	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	en_early_corr	: 1;
	Ucbit	read_continuous	: 1;
	Ucbit	tranfer_block	: 1;
	Ucbit	en_auto_reall_r	: 1;
	Ucbit	en_auto_reall_w	: 1;	/* Byte 2 */
	Uchar	rd_retry_count;		/* Byte 3 */
	Uchar	correction_span;
	char	head_offset_count;
	char	data_strobe_offset;
	Uchar	res;
	Uchar	wr_retry_count;
	Uchar	res_tape[2];
	Uchar	recov_timelim[2];
};

#else					/* Motorola byteorder */

struct scsi_mode_page_01 {		/* Error recovery Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	en_auto_reall_w	: 1;	/* Byte 2 */
	Ucbit	en_auto_reall_r	: 1;
	Ucbit	tranfer_block	: 1;
	Ucbit	read_continuous	: 1;
	Ucbit	en_early_corr	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	term_on_rec_err	: 1;
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Uchar	rd_retry_count;		/* Byte 3 */
	Uchar	correction_span;
	char	head_offset_count;
	char	data_strobe_offset;
	Uchar	res;
	Uchar	wr_retry_count;
	Uchar	res_tape[2];
	Uchar	recov_timelim[2];
};
#endif


#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_02 {		/* Device dis/re connect Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 16 Bytes */
	Uchar	buf_full_ratio;
	Uchar	buf_empt_ratio;
	Uchar	bus_inact_limit[2];
	Uchar	disc_time_limit[2];
	Uchar	conn_time_limit[2];
	Uchar	max_burst_size[2];	/* Start SCSI-2 */
	Ucbit	data_tr_dis_ctl	: 2;
	Ucbit			: 6;
	Uchar	res[3];
};

#else					/* Motorola byteorder */

struct scsi_mode_page_02 {		/* Device dis/re connect Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 16 Bytes */
	Uchar	buf_full_ratio;
	Uchar	buf_empt_ratio;
	Uchar	bus_inact_limit[2];
	Uchar	disc_time_limit[2];
	Uchar	conn_time_limit[2];
	Uchar	max_burst_size[2];	/* Start SCSI-2 */
	Ucbit			: 6;
	Ucbit	data_tr_dis_ctl	: 2;
	Uchar	res[3];
};
#endif

#define	DTDC_DATADONE	0x01		/*
					 * Target may not disconnect once
					 * data transfer is started until
					 * all data successfully transferred.
					 */

#define	DTDC_CMDDONE	0x03		/*
					 * Target may not disconnect once
					 * data transfer is started until
					 * command completed.
					 */


#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_03 {		/* Direct access format Paramters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	trk_per_zone[2];
	Uchar	alt_sec_per_zone[2];
	Uchar	alt_trk_per_zone[2];
	Uchar	alt_trk_per_vol[2];
	Uchar	sect_per_trk[2];
	Uchar	bytes_per_phys_sect[2];
	Uchar	interleave[2];
	Uchar	trk_skew[2];
	Uchar	cyl_skew[2];
	Ucbit			: 3;
	Ucbit	inhibit_save	: 1;
	Ucbit	fmt_by_surface	: 1;
	Ucbit	removable	: 1;
	Ucbit	hard_sec	: 1;
	Ucbit	soft_sec	: 1;
	Uchar	res[3];
};

#else					/* Motorola byteorder */

struct scsi_mode_page_03 {		/* Direct access format Paramters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	trk_per_zone[2];
	Uchar	alt_sec_per_zone[2];
	Uchar	alt_trk_per_zone[2];
	Uchar	alt_trk_per_vol[2];
	Uchar	sect_per_trk[2];
	Uchar	bytes_per_phys_sect[2];
	Uchar	interleave[2];
	Uchar	trk_skew[2];
	Uchar	cyl_skew[2];
	Ucbit	soft_sec	: 1;
	Ucbit	hard_sec	: 1;
	Ucbit	removable	: 1;
	Ucbit	fmt_by_surface	: 1;
	Ucbit	inhibit_save	: 1;
	Ucbit			: 3;
	Uchar	res[3];
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_04 {		/* Rigid disk Geometry Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	ncyl[3];
	Uchar	nhead;
	Uchar	start_precomp[3];
	Uchar	start_red_wcurrent[3];
	Uchar	step_rate[2];
	Uchar	landing_zone[3];
	Ucbit	rot_pos_locking	: 2;	/* Start SCSI-2 */
	Ucbit			: 6;	/* Start SCSI-2 */
	Uchar	rotational_off;
	Uchar	res1;
	Uchar	rotation_rate[2];
	Uchar	res2[2];
};

#else					/* Motorola byteorder */

struct scsi_mode_page_04 {		/* Rigid disk Geometry Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Uchar	ncyl[3];
	Uchar	nhead;
	Uchar	start_precomp[3];
	Uchar	start_red_wcurrent[3];
	Uchar	step_rate[2];
	Uchar	landing_zone[3];
	Ucbit			: 6;	/* Start SCSI-2 */
	Ucbit	rot_pos_locking	: 2;	/* Start SCSI-2 */
	Uchar	rotational_off;
	Uchar	res1;
	Uchar	rotation_rate[2];
	Uchar	res2[2];
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_05 {		/* Flexible disk Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x1E = 32 Bytes */
	Uchar	transfer_rate[2];
	Uchar	nhead;
	Uchar	sect_per_trk;
	Uchar	bytes_per_phys_sect[2];
	Uchar	ncyl[2];
	Uchar	start_precomp[2];
	Uchar	start_red_wcurrent[2];
	Uchar	step_rate[2];
	Uchar	step_pulse_width;
	Uchar	head_settle_delay[2];
	Uchar	motor_on_delay;
	Uchar	motor_off_delay;
	Ucbit	spc		: 4;
	Ucbit			: 4;
	Ucbit			: 5;
	Ucbit	mo		: 1;
	Ucbit	ssn		: 1;
	Ucbit	trdy		: 1;
	Uchar	write_compensation;
	Uchar	head_load_delay;
	Uchar	head_unload_delay;
	Ucbit	pin_2_use	: 4;
	Ucbit	pin_34_use	: 4;
	Ucbit	pin_1_use	: 4;
	Ucbit	pin_4_use	: 4;
	Uchar	rotation_rate[2];
	Uchar	res[2];
};

#else					/* Motorola byteorder */

struct scsi_mode_page_05 {		/* Flexible disk Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x1E = 32 Bytes */
	Uchar	transfer_rate[2];
	Uchar	nhead;
	Uchar	sect_per_trk;
	Uchar	bytes_per_phys_sect[2];
	Uchar	ncyl[2];
	Uchar	start_precomp[2];
	Uchar	start_red_wcurrent[2];
	Uchar	step_rate[2];
	Uchar	step_pulse_width;
	Uchar	head_settle_delay[2];
	Uchar	motor_on_delay;
	Uchar	motor_off_delay;
	Ucbit	trdy		: 1;
	Ucbit	ssn		: 1;
	Ucbit	mo		: 1;
	Ucbit			: 5;
	Ucbit			: 4;
	Ucbit	spc		: 4;
	Uchar	write_compensation;
	Uchar	head_load_delay;
	Uchar	head_unload_delay;
	Ucbit	pin_34_use	: 4;
	Ucbit	pin_2_use	: 4;
	Ucbit	pin_4_use	: 4;
	Ucbit	pin_1_use	: 4;
	Uchar	rotation_rate[2];
	Uchar	res[2];
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_07 {		/* Verify Error recovery */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Ucbit	term_on_rec_err	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	en_early_corr	: 1;
	Ucbit	res		: 4;	/* Byte 2 */
	Uchar	ve_retry_count;		/* Byte 3 */
	Uchar	ve_correction_span;
	char	res2[5];		/* Byte 5 */
	Uchar	ve_recov_timelim[2];	/* Byte 10 */
};

#else					/* Motorola byteorder */

struct scsi_mode_page_07 {		/* Verify Error recovery */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	res		: 4;	/* Byte 2 */
	Ucbit	en_early_corr	: 1;
	Ucbit	report_rec_err	: 1;
	Ucbit	term_on_rec_err	: 1;
	Ucbit	disa_correction	: 1;	/* Byte 2 */
	Uchar	ve_retry_count;		/* Byte 3 */
	Uchar	ve_correction_span;
	char	res2[5];		/* Byte 5 */
	Uchar	ve_recov_timelim[2];	/* Byte 10 */
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_08 {		/* Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	disa_rd_cache	: 1;	/* Byte 2 */
	Ucbit	muliple_fact	: 1;
	Ucbit	en_wt_cache	: 1;
	Ucbit	res		: 5;	/* Byte 2 */
	Ucbit	wt_ret_pri	: 4;	/* Byte 3 */
	Ucbit	demand_rd_ret_pri: 4;	/* Byte 3 */
	Uchar	disa_pref_tr_len[2];	/* Byte 4 */
	Uchar	min_pref[2];		/* Byte 6 */
	Uchar	max_pref[2];		/* Byte 8 */
	Uchar	max_pref_ceiling[2];	/* Byte 10 */
};

#else					/* Motorola byteorder */

struct scsi_mode_page_08 {		/* Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Ucbit	res		: 5;	/* Byte 2 */
	Ucbit	en_wt_cache	: 1;
	Ucbit	muliple_fact	: 1;
	Ucbit	disa_rd_cache	: 1;	/* Byte 2 */
	Ucbit	demand_rd_ret_pri: 4;	/* Byte 3 */
	Ucbit	wt_ret_pri	: 4;
	Uchar	disa_pref_tr_len[2];	/* Byte 4 */
	Uchar	min_pref[2];		/* Byte 6 */
	Uchar	max_pref[2];		/* Byte 8 */
	Uchar	max_pref_ceiling[2];	/* Byte 10 */
};
#endif

struct scsi_mode_page_09 {		/* Peripheral device Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* >= 0x06 = 8 Bytes */
	Uchar	interface_id[2];	/* Byte 2 */
	Uchar	res[4];			/* Byte 4 */
	Uchar	vendor_specific[1];	/* Byte 8 */
};

#define	PDEV_SCSI	0x0000		/* scsi interface */
#define	PDEV_SMD	0x0001		/* SMD interface */
#define	PDEV_ESDI	0x0002		/* ESDI interface */
#define	PDEV_IPI2	0x0003		/* IPI-2 interface */
#define	PDEV_IPI3	0x0004		/* IPI-3 interface */

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_0A {		/* Common device Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Ucbit	rep_log_exeption: 1;	/* Byte 2 */
	Ucbit	res		: 7;	/* Byte 2 */
	Ucbit	dis_queuing	: 1;	/* Byte 3 */
	Ucbit	queuing_err_man	: 1;
	Ucbit	res2		: 2;
	Ucbit	queue_alg_mod	: 4;	/* Byte 3 */
	Ucbit	EAENP		: 1;	/* Byte 4 */
	Ucbit	UAENP		: 1;
	Ucbit	RAENP		: 1;
	Ucbit	res3		: 4;
	Ucbit	en_ext_cont_all	: 1;	/* Byte 4 */
	Ucbit	res4		: 8;
	Uchar	ready_aen_hold_per[2];	/* Byte 6 */
};

#else					/* Motorola byteorder */

struct scsi_mode_page_0A {		/* Common device Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Ucbit	res		: 7;	/* Byte 2 */
	Ucbit	rep_log_exeption: 1;	/* Byte 2 */
	Ucbit	queue_alg_mod	: 4;	/* Byte 3 */
	Ucbit	res2		: 2;
	Ucbit	queuing_err_man	: 1;
	Ucbit	dis_queuing	: 1;	/* Byte 3 */
	Ucbit	en_ext_cont_all	: 1;	/* Byte 4 */
	Ucbit	res3		: 4;
	Ucbit	RAENP		: 1;
	Ucbit	UAENP		: 1;
	Ucbit	EAENP		: 1;	/* Byte 4 */
	Ucbit	res4		: 8;
	Uchar	ready_aen_hold_per[2];	/* Byte 6 */
};
#endif

#define	CTRL_QMOD_RESTRICT	0x0
#define	CTRL_QMOD_UNRESTRICT	0x1


struct scsi_mode_page_0B {		/* Medium Types Supported Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Uchar	res[2];			/* Byte 2 */
	Uchar	medium_one_supp;	/* Byte 4 */
	Uchar	medium_two_supp;	/* Byte 5 */
	Uchar	medium_three_supp;	/* Byte 6 */
	Uchar	medium_four_supp;	/* Byte 7 */
};

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_0C {		/* Notch & Partition Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Ucbit	res		: 6;	/* Byte 2 */
	Ucbit	logical_notch	: 1;
	Ucbit	notched_drive	: 1;	/* Byte 2 */
	Uchar	res2;			/* Byte 3 */
	Uchar	max_notches[2];		/* Byte 4  */
	Uchar	active_notch[2];	/* Byte 6  */
	Uchar	starting_boundary[4];	/* Byte 8  */
	Uchar	ending_boundary[4];	/* Byte 12 */
	Uchar	pages_notched[8];	/* Byte 16 */
};

#else					/* Motorola byteorder */

struct scsi_mode_page_0C {		/* Notch & Partition Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x16 = 24 Bytes */
	Ucbit	notched_drive	: 1;	/* Byte 2 */
	Ucbit	logical_notch	: 1;
	Ucbit	res		: 6;	/* Byte 2 */
	Uchar	res2;			/* Byte 3 */
	Uchar	max_notches[2];		/* Byte 4  */
	Uchar	active_notch[2];	/* Byte 6  */
	Uchar	starting_boundary[4];	/* Byte 8  */
	Uchar	ending_boundary[4];	/* Byte 12 */
	Uchar	pages_notched[8];	/* Byte 16 */
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_mode_page_0D {		/* CD-ROM Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Uchar	res;			/* Byte 2 */
	Ucbit	inact_timer_mult: 4;	/* Byte 3 */
	Ucbit	res2		: 4;	/* Byte 3 */
	Uchar	s_un_per_m_un[2];	/* Byte 4  */
	Uchar	f_un_per_s_un[2];	/* Byte 6  */
};

#else					/* Motorola byteorder */

struct scsi_mode_page_0D {		/* CD-ROM Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x06 = 8 Bytes */
	Uchar	res;			/* Byte 2 */
	Ucbit	res2		: 4;	/* Byte 3 */
	Ucbit	inact_timer_mult: 4;	/* Byte 3 */
	Uchar	s_un_per_m_un[2];	/* Byte 4  */
	Uchar	f_un_per_s_un[2];	/* Byte 6  */
};
#endif

struct sony_mode_page_20 {		/* Sony Format Mode Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0A = 12 Bytes */
	Uchar	format_mode;
	Uchar	format_type;
#define	num_bands	user_band_size	/* Gilt bei Type 1 */
	Uchar	user_band_size[4];	/* Gilt bei Type 0 */
	Uchar	spare_band_size[2];
	Uchar	res[2];
};

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct toshiba_mode_page_20 {		/* Toshiba Speed Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x01 = 3 Bytes */
	Ucbit	speed		: 1;
	Ucbit	res		: 7;
};

#else					/* Motorola byteorder */

struct toshiba_mode_page_20 {		/* Toshiba Speed Control Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x01 = 3 Bytes */
	Ucbit	res		: 7;
	Ucbit	speed		: 1;
};
#endif

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct ccs_mode_page_38 {		/* CCS Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 14 Bytes */

	Ucbit	cache_table_size: 4;	/* Byte 3 */
	Ucbit	cache_en	: 1;
	Ucbit	res2		: 1;
	Ucbit	wr_index_en	: 1;
	Ucbit	res		: 1;	/* Byte 3 */
	Uchar	threshold;		/* Byte 4 Prefetch threshold */
	Uchar	max_prefetch;		/* Byte 5 Max. prefetch */
	Uchar	max_multiplier;		/* Byte 6 Max. prefetch multiplier */
	Uchar	min_prefetch;		/* Byte 7 Min. prefetch */
	Uchar	min_multiplier;		/* Byte 8 Min. prefetch multiplier */
	Uchar	res3[8];		/* Byte 9 */
};

#else					/* Motorola byteorder */

struct ccs_mode_page_38 {		/* CCS Caching Parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x0E = 14 Bytes */

	Ucbit	res		: 1;	/* Byte 3 */
	Ucbit	wr_index_en	: 1;
	Ucbit	res2		: 1;
	Ucbit	cache_en	: 1;
	Ucbit	cache_table_size: 4;	/* Byte 3 */
	Uchar	threshold;		/* Byte 4 Prefetch threshold */
	Uchar	max_prefetch;		/* Byte 5 Max. prefetch */
	Uchar	max_multiplier;		/* Byte 6 Max. prefetch multiplier */
	Uchar	min_prefetch;		/* Byte 7 Min. prefetch */
	Uchar	min_multiplier;		/* Byte 8 Min. prefetch multiplier */
	Uchar	res3[8];		/* Byte 9 */
};
#endif

#if defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct cd_mode_page_05 {		/* write parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x32 = 50 Bytes */
	Ucbit	write_type	: 4;	/* Session write type (PACKET/TAO...)*/
	Ucbit	test_write	: 1;	/* Do not actually write data	     */
	Ucbit	LS_V		: 1;	/* Link size valid		     */
	Ucbit	BUFE		: 1;	/* Enable Bufunderrun free rec.	     */
	Ucbit	res_2_7		: 1;
	Ucbit	track_mode	: 4;	/* Track mode (Q-sub control nibble) */
	Ucbit	copy		: 1;	/* 1st higher gen of copy prot track ~*/
	Ucbit	fp		: 1;	/* Fixed packed (if in packet mode)  */
	Ucbit	multi_session	: 2;	/* Multi session write type	     */
	Ucbit	dbtype		: 4;	/* Data block type		     */
	Ucbit	res_4		: 4;	/* Reserved			     */
	Uchar	link_size;		/* Link Size (default is 7)	     */
	Uchar	res_6;			/* Reserved			     */
	Ucbit	host_appl_code	: 6;	/* Host application code of disk     */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Uchar	session_format;		/* Session format (DA/CDI/XA)	     */
	Uchar	res_9;			/* Reserved			     */
	Uchar	packet_size[4];		/* # of user datablocks/fixed packet */
	Uchar	audio_pause_len[2];	/* # of blocks where index is zero   */
	Uchar	media_cat_number[16];	/* Media catalog Number (MCN)	     */
	Uchar	ISRC[14];		/* ISRC for this track		     */
	Uchar	sub_header[4];
	Uchar	vendor_uniq[4];
};

#else				/* Motorola byteorder */

struct cd_mode_page_05 {		/* write parameters */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x32 = 50 Bytes */
	Ucbit	res_2_7		: 1;
	Ucbit	BUFE		: 1;	/* Enable Bufunderrun free rec.	     */
	Ucbit	LS_V		: 1;	/* Link size valid		     */
	Ucbit	test_write	: 1;	/* Do not actually write data	     */
	Ucbit	write_type	: 4;	/* Session write type (PACKET/TAO...)*/
	Ucbit	multi_session	: 2;	/* Multi session write type	     */
	Ucbit	fp		: 1;	/* Fixed packed (if in packet mode)  */
	Ucbit	copy		: 1;	/* 1st higher gen of copy prot track */
	Ucbit	track_mode	: 4;	/* Track mode (Q-sub control nibble) */
	Ucbit	res_4		: 4;	/* Reserved			     */
	Ucbit	dbtype		: 4;	/* Data block type		     */
	Uchar	link_size;		/* Link Size (default is 7)	     */
	Uchar	res_6;			/* Reserved			     */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Ucbit	host_appl_code	: 6;	/* Host application code of disk     */
	Uchar	session_format;		/* Session format (DA/CDI/XA)	     */
	Uchar	res_9;			/* Reserved			     */
	Uchar	packet_size[4];		/* # of user datablocks/fixed packet */
	Uchar	audio_pause_len[2];	/* # of blocks where index is zero   */
	Uchar	media_cat_number[16];	/* Media catalog Number (MCN)	     */
	Uchar	ISRC[14];		/* ISRC for this track		     */
	Uchar	sub_header[4];
	Uchar	vendor_uniq[4];
};

#endif

#if defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct cd_wr_speed_performance {
	Uchar	res0;			/* Reserved			     */
	Ucbit	rot_ctl_sel	: 2;	/* Rotational control selected	     */
	Ucbit	res_1_27	: 6;	/* Reserved			     */
	Uchar	wr_speed_supp[2];	/* Supported write speed	     */
};

struct cd_mode_page_2A {		/* CD Cap / mech status */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x14 = 20 Bytes (MMC) */
					/* 0x18 = 24 Bytes (MMC-2) */
					/* 0x1C >= 28 Bytes (MMC-3) */
	Ucbit	cd_r_read	: 1;	/* Reads CD-R  media		     */
	Ucbit	cd_rw_read	: 1;	/* Reads CD-RW media		     */
	Ucbit	method2		: 1;	/* Reads fixed packet method2 media  */
	Ucbit	dvd_rom_read	: 1;	/* Reads DVD ROM media		     */
	Ucbit	dvd_r_read	: 1;	/* Reads DVD-R media		     */
	Ucbit	dvd_ram_read	: 1;	/* Reads DVD-RAM media		     */
	Ucbit	res_2_67	: 2;	/* Reserved			     */
	Ucbit	cd_r_write	: 1;	/* Supports writing CD-R  media	     */
	Ucbit	cd_rw_write	: 1;	/* Supports writing CD-RW media	     */
	Ucbit	test_write	: 1;	/* Supports emulation write	     */
	Ucbit	res_3_3		: 1;	/* Reserved			     */
	Ucbit	dvd_r_write	: 1;	/* Supports writing DVD-R media	     */
	Ucbit	dvd_ram_write	: 1;	/* Supports writing DVD-RAM media    */
	Ucbit	res_3_67	: 2;	/* Reserved			     */
	Ucbit	audio_play	: 1;	/* Supports Audio play operation     */
	Ucbit	composite	: 1;	/* Deliveres composite A/V stream    */
	Ucbit	digital_port_2	: 1;	/* Supports digital output on port 2 */
	Ucbit	digital_port_1	: 1;	/* Supports digital output on port 1 */
	Ucbit	mode_2_form_1	: 1;	/* Reads Mode-2 form 1 media (XA)    */
	Ucbit	mode_2_form_2	: 1;	/* Reads Mode-2 form 2 media	     */
	Ucbit	multi_session	: 1;	/* Reads multi-session media	     */
	Ucbit	BUF		: 1;	/* Supports Buffer under. free rec.  */
	Ucbit	cd_da_supported	: 1;	/* Reads audio data with READ CD cmd */
	Ucbit	cd_da_accurate	: 1;	/* READ CD data stream is accurate   */
	Ucbit	rw_supported	: 1;	/* Reads R-W sub channel information */
	Ucbit	rw_deint_corr	: 1;	/* Reads de-interleved R-W sub chan  */
	Ucbit	c2_pointers	: 1;	/* Supports C2 error pointers	     */
	Ucbit	ISRC		: 1;	/* Reads ISRC information	     */
	Ucbit	UPC		: 1;	/* Reads media catalog number (UPC)  */
	Ucbit	read_bar_code	: 1;	/* Supports reading bar codes	     */
	Ucbit	lock		: 1;	/* PREVENT/ALLOW may lock media	     */
	Ucbit	lock_state	: 1;	/* Lock state 0=unlocked 1=locked    */
	Ucbit	prevent_jumper	: 1;	/* State of prev/allow jumper 0=pres */
	Ucbit	eject		: 1;	/* Ejects disc/cartr with STOP LoEj  */
	Ucbit	res_6_4		: 1;	/* Reserved			     */
	Ucbit	loading_type	: 3;	/* Loading mechanism type	     */
	Ucbit	sep_chan_vol	: 1;	/* Vol controls each channel separat */
	Ucbit	sep_chan_mute	: 1;	/* Mute controls each channel separat*/
	Ucbit	disk_present_rep: 1;	/* Changer supports disk present rep */
	Ucbit	sw_slot_sel	: 1;	/* Load empty slot in changer	     */
	Ucbit	side_change	: 1;	/* Side change capable		     */
	Ucbit	pw_in_lead_in	: 1;	/* Reads raw P-W sucode from lead in */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Uchar	max_read_speed[2];	/* Max. read speed in KB/s	     */
	Uchar	num_vol_levels[2];	/* # of supported volume levels	     */
	Uchar	buffer_size[2];		/* Buffer size for the data in KB    */
	Uchar	cur_read_speed[2];	/* Current read speed in KB/s	     */
	Uchar	res_16;			/* Reserved			     */
	Ucbit	res_17_0	: 1;	/* Reserved			     */
	Ucbit	BCK		: 1;	/* Data valid on falling edge of BCK */
	Ucbit	RCK		: 1;	/* Set: HIGH high LRCK=left channel  */
	Ucbit	LSBF		: 1;	/* Set: LSB first Clear: MSB first   */
	Ucbit	length		: 2;	/* 0=32BCKs 1=16BCKs 2=24BCKs 3=24I2c*/
	Ucbit	res_17		: 2;	/* Reserved			     */
	Uchar	max_write_speed[2];	/* Max. write speed supported in KB/s*/
	Uchar	cur_write_speed[2];	/* Current write speed in KB/s	     */

					/* Byte 22 ... Only in MMC-2	     */
	Uchar	copy_man_rev[2];	/* Copy management revision supported*/
	Uchar	res_24;			/* Reserved			     */
	Uchar	res_25;			/* Reserved			     */

					/* Byte 26 ... Only in MMC-3	     */
	Uchar	res_26;			/* Reserved			     */
	Ucbit	res_27_27	: 6;	/* Reserved			     */
	Ucbit	rot_ctl_sel	: 2;	/* Rotational control selected	     */
	Uchar	v3_cur_write_speed[2];	/* Current write speed in KB/s	     */
	Uchar	num_wr_speed_des[2];	/* # of wr speed perf descr. tables  */
	struct cd_wr_speed_performance
		wr_speed_des[1];	/* wr speed performance descriptor   */
					/* Actually more (num_wr_speed_des)  */
};

#else				/* Motorola byteorder */

struct cd_wr_speed_performance {
	Uchar	res0;			/* Reserved			     */
	Ucbit	res_1_27	: 6;	/* Reserved			     */
	Ucbit	rot_ctl_sel	: 2;	/* Rotational control selected	     */
	Uchar	wr_speed_supp[2];	/* Supported write speed	     */
};

struct cd_mode_page_2A {		/* CD Cap / mech status */
		MP_P_CODE;		/* parsave & pagecode */
	Uchar	p_len;			/* 0x14 = 20 Bytes (MMC) */
					/* 0x18 = 24 Bytes (MMC-2) */
					/* 0x1C >= 28 Bytes (MMC-3) */
	Ucbit	res_2_67	: 2;	/* Reserved			     */
	Ucbit	dvd_ram_read	: 1;	/* Reads DVD-RAM media		     */
	Ucbit	dvd_r_read	: 1;	/* Reads DVD-R media		     */
	Ucbit	dvd_rom_read	: 1;	/* Reads DVD ROM media		     */
	Ucbit	method2		: 1;	/* Reads fixed packet method2 media  */
	Ucbit	cd_rw_read	: 1;	/* Reads CD-RW media		     */
	Ucbit	cd_r_read	: 1;	/* Reads CD-R  media		     */
	Ucbit	res_3_67	: 2;	/* Reserved			     */
	Ucbit	dvd_ram_write	: 1;	/* Supports writing DVD-RAM media    */
	Ucbit	dvd_r_write	: 1;	/* Supports writing DVD-R media	     */
	Ucbit	res_3_3		: 1;	/* Reserved			     */
	Ucbit	test_write	: 1;	/* Supports emulation write	     */
	Ucbit	cd_rw_write	: 1;	/* Supports writing CD-RW media	     */
	Ucbit	cd_r_write	: 1;	/* Supports writing CD-R  media	     */
	Ucbit	BUF		: 1;	/* Supports Buffer under. free rec.  */
	Ucbit	multi_session	: 1;	/* Reads multi-session media	     */
	Ucbit	mode_2_form_2	: 1;	/* Reads Mode-2 form 2 media	     */
	Ucbit	mode_2_form_1	: 1;	/* Reads Mode-2 form 1 media (XA)    */
	Ucbit	digital_port_1	: 1;	/* Supports digital output on port 1 */
	Ucbit	digital_port_2	: 1;	/* Supports digital output on port 2 */
	Ucbit	composite	: 1;	/* Deliveres composite A/V stream    */
	Ucbit	audio_play	: 1;	/* Supports Audio play operation     */
	Ucbit	read_bar_code	: 1;	/* Supports reading bar codes	     */
	Ucbit	UPC		: 1;	/* Reads media catalog number (UPC)  */
	Ucbit	ISRC		: 1;	/* Reads ISRC information	     */
	Ucbit	c2_pointers	: 1;	/* Supports C2 error pointers	     */
	Ucbit	rw_deint_corr	: 1;	/* Reads de-interleved R-W sub chan  */
	Ucbit	rw_supported	: 1;	/* Reads R-W sub channel information */
	Ucbit	cd_da_accurate	: 1;	/* READ CD data stream is accurate   */
	Ucbit	cd_da_supported	: 1;	/* Reads audio data with READ CD cmd */
	Ucbit	loading_type	: 3;	/* Loading mechanism type	     */
	Ucbit	res_6_4		: 1;	/* Reserved			     */
	Ucbit	eject		: 1;	/* Ejects disc/cartr with STOP LoEj  */
	Ucbit	prevent_jumper	: 1;	/* State of prev/allow jumper 0=pres */
	Ucbit	lock_state	: 1;	/* Lock state 0=unlocked 1=locked    */
	Ucbit	lock		: 1;	/* PREVENT/ALLOW may lock media	     */
	Ucbit	res_7		: 2;	/* Reserved			     */
	Ucbit	pw_in_lead_in	: 1;	/* Reads raw P-W sucode from lead in */
	Ucbit	side_change	: 1;	/* Side change capable		     */
	Ucbit	sw_slot_sel	: 1;	/* Load empty slot in changer	     */
	Ucbit	disk_present_rep: 1;	/* Changer supports disk present rep */
	Ucbit	sep_chan_mute	: 1;	/* Mute controls each channel separat*/
	Ucbit	sep_chan_vol	: 1;	/* Vol controls each channel separat */
	Uchar	max_read_speed[2];	/* Max. read speed in KB/s	     */
	Uchar	num_vol_levels[2];	/* # of supported volume levels	     */
	Uchar	buffer_size[2];		/* Buffer size for the data in KB    */
	Uchar	cur_read_speed[2];	/* Current read speed in KB/s	     */
	Uchar	res_16;			/* Reserved			     */
	Ucbit	res_17		: 2;	/* Reserved			     */
	Ucbit	length		: 2;	/* 0=32BCKs 1=16BCKs 2=24BCKs 3=24I2c*/
	Ucbit	LSBF		: 1;	/* Set: LSB first Clear: MSB first   */
	Ucbit	RCK		: 1;	/* Set: HIGH high LRCK=left channel  */
	Ucbit	BCK		: 1;	/* Data valid on falling edge of BCK */
	Ucbit	res_17_0	: 1;	/* Reserved			     */
	Uchar	max_write_speed[2];	/* Max. write speed supported in KB/s*/
	Uchar	cur_write_speed[2];	/* Current write speed in KB/s	     */

					/* Byte 22 ... Only in MMC-2	     */
	Uchar	copy_man_rev[2];	/* Copy management revision supported*/
	Uchar	res_24;			/* Reserved			     */
	Uchar	res_25;			/* Reserved			     */

					/* Byte 26 ... Only in MMC-3	     */
	Uchar	res_26;			/* Reserved			     */
	Ucbit	res_27_27	: 6;	/* Reserved			     */
	Ucbit	rot_ctl_sel	: 2;	/* Rotational control selected	     */
	Uchar	v3_cur_write_speed[2];	/* Current write speed in KB/s	     */
	Uchar	num_wr_speed_des[2];	/* # of wr speed perf descr. tables  */
	struct cd_wr_speed_performance
		wr_speed_des[1];	/* wr speed performance descriptor   */
					/* Actually more (num_wr_speed_des)  */
};

#endif

#define	LT_CADDY	0
#define	LT_TRAY		1
#define	LT_POP_UP	2
#define	LT_RES3		3
#define	LT_CHANGER_IND	4
#define	LT_CHANGER_CART	5
#define	LT_RES6		6
#define	LT_RES7		7


struct scsi_mode_data {
	struct scsi_mode_header		header;
	struct scsi_mode_blockdesc	blockdesc;
	union	pagex	{
		struct acb_mode_data		acb;
		struct scsi_mode_page_01	page1;
		struct scsi_mode_page_02	page2;
		struct scsi_mode_page_03	page3;
		struct scsi_mode_page_04	page4;
		struct scsi_mode_page_05	page5;
		struct scsi_mode_page_07	page7;
		struct scsi_mode_page_08	page8;
		struct scsi_mode_page_09	page9;
		struct scsi_mode_page_0A	pageA;
		struct scsi_mode_page_0B	pageB;
		struct scsi_mode_page_0C	pageC;
		struct scsi_mode_page_0D	pageD;
		struct sony_mode_page_20	sony20;
		struct toshiba_mode_page_20	toshiba20;
		struct ccs_mode_page_38		ccs38;
	} pagex;
};

struct scsi_capacity {
	Int32_t	c_baddr;		/* must convert byteorder!! */
	Int32_t	c_bsize;		/* must convert byteorder!! */
};

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_def_header {
	Ucbit		: 8;
	Ucbit	format	: 3;
	Ucbit	gdl	: 1;
	Ucbit	mdl	: 1;
	Ucbit		: 3;
	Uchar	length[2];
};

#else					/* Motorola byteorder */

struct scsi_def_header {
	Ucbit		: 8;
	Ucbit		: 3;
	Ucbit	mdl	: 1;
	Ucbit	gdl	: 1;
	Ucbit	format	: 3;
	Uchar	length[2];
};
#endif


#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_format_header {
	Ucbit	res		: 8;	/* Adaptec 5500: 1 --> format track */
	Ucbit	vu		: 1;	/* Vendor Unique		    */
	Ucbit	immed		: 1;	/* Return Immediately from Format   */
	Ucbit	tryout		: 1;	/* Check if format parameters OK    */
	Ucbit	ipattern	: 1;	/* Init patter descriptor present   */
	Ucbit	serr		: 1;	/* Stop on error		    */
	Ucbit	dcert		: 1;	/* Disable certification	    */
	Ucbit	dmdl		: 1;	/* Disable manufacturer defect list */
	Ucbit	enable		: 1;	/* Enable to use the next 3 bits    */
	Uchar	length[2];		/* Length of following list in bytes*/
};

#else					/* Motorola byteorder */

struct scsi_format_header {
	Ucbit	res		: 8;	/* Adaptec 5500: 1 --> format track */
	Ucbit	enable		: 1;	/* Enable to use the next 3 bits    */
	Ucbit	dmdl		: 1;	/* Disable manufacturer defect list */
	Ucbit	dcert		: 1;	/* Disable certification	    */
	Ucbit	serr		: 1;	/* Stop on error		    */
	Ucbit	ipattern	: 1;	/* Init patter descriptor present   */
	Ucbit	tryout		: 1;	/* Check if format parameters OK    */
	Ucbit	immed		: 1;	/* Return Immediately from Format   */
	Ucbit	vu		: 1;	/* Vendor Unique		    */
	Uchar	length[2];		/* Length of following list in bytes*/
};
#endif

struct	scsi_def_bfi {
	Uchar	cyl[3];
	Uchar	head;
	Uchar	bfi[4];
};

struct	scsi_def_phys {
	Uchar	cyl[3];
	Uchar	head;
	Uchar	sec[4];
};

struct	scsi_def_list {
	struct	scsi_def_header	hd;
	union {
			Uchar		list_block[1][4];
		struct	scsi_def_bfi	list_bfi[1];
		struct	scsi_def_phys	list_phys[1];
	} def_list;
};

struct	scsi_format_data {
	struct scsi_format_header hd;
	union {
			Uchar		list_block[1][4];
		struct	scsi_def_bfi	list_bfi[1];
		struct	scsi_def_phys	list_phys[1];
	} def_list;
};

#define	def_block	def_list.list_block
#define	def_bfi		def_list.list_bfi
#define	def_phys	def_list.list_phys

#define	SC_DEF_BLOCK	0
#define	SC_DEF_BFI	4
#define	SC_DEF_PHYS	5
#define	SC_DEF_VU	6
#define	SC_DEF_RES	7

struct scsi_format_cap_header {
	Uchar	res[3];			/* Reserved			*/
	Uchar	len;			/* Len (a multiple of 8)	*/
};

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct scsi_format_cap_desc {
	Uchar	nblock[4];		/* Number of blocks		*/
	Ucbit	desc_type	: 2;	/* Descriptor type		*/
	Ucbit	fmt_type	: 6;	/* Format Taype			*/
	Uchar	blen[3];		/* Logical block length		*/
};

#else					/* Motorola byteorder */

struct scsi_format_cap_desc {
	Uchar	nblock[4];		/* Number of blocks		*/
	Ucbit	fmt_type	: 6;	/* Format Taype			*/
	Ucbit	desc_type	: 2;	/* Descriptor type		*/
	Uchar	blen[3];		/* Logical block length		*/
};
#endif

/*
 * Defines for 'fmt_type'.
 * 
 */
#define	FCAP_TYPE_DVDPLUS_FULL	0x26	/* DVD+RW Full Format		*/

/*
 * Defines for 'desc_type'.
 * In case of FCAP_DESC_RES, the descriptor is a formatted capacity descriptor
 * and the 'blen' field is type dependent.
 * For all other cases, this is the Current/Maximum Capacity descriptor and
 * the value of 'fmt_type' is reserved and must be zero.
 */
#define	FCAP_DESC_RES		0	/* Reserved			*/
#define	FCAP_DESC_UNFORM	1	/* Unformatted Media		*/
#define	FCAP_DESC_FORM		2	/* Formatted Media		*/
#define	FCAP_DESC_NOMEDIA	3	/* No Media			*/

struct	scsi_cap_data {
	struct scsi_format_cap_header	hd;
	struct scsi_format_cap_desc	list[1];
};


struct	scsi_send_diag_cmd {
	Uchar	cmd;
	Uchar	addr[4];
	Ucbit		: 8;
};

#if	defined(_BIT_FIELDS_LTOH)	/* Intel byteorder */

struct	scsi_sector_header {
	Uchar	cyl[2];
	Uchar	head;
	Uchar	sec;
	Ucbit		: 5;
	Ucbit	rp	: 1;
	Ucbit	sp	: 1;
	Ucbit	dt	: 1;
};

#else					/* Motorola byteorder */

struct	scsi_sector_header {
	Uchar	cyl[2];
	Uchar	head;
	Uchar	sec;
	Ucbit	dt	: 1;
	Ucbit	sp	: 1;
	Ucbit	rp	: 1;
	Ucbit		: 5;
};
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCSIREG_H */
/* @(#)scgops.h	1.5 02/10/19 Copyright 2000 J. Schilling */
/*
 *	Copyright (c) 2000 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file COPYING.  If not, write to
 * the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef	_SCG_SCGOPS_H
#define	_SCG_SCGOPS_H
typedef	struct scg_scsi	SCSI;

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct scg_ops {
	int	(*scgo_send)		__PR((SCSI *scgp));

	char *	(*scgo_version)		__PR((SCSI *scgp, int what));
#ifdef	EOF	/* stdio.h has been included */
	int	(*scgo_help)		__PR((SCSI *scgp, FILE *f));
#else
	int	(*scgo_help)		__PR((SCSI *scgp, void *f));
#endif
	int	(*scgo_open)		__PR((SCSI *scgp, char *device));
	int	(*scgo_close)		__PR((SCSI *scgp));
	long	(*scgo_maxdma)		__PR((SCSI *scgp, long amt));
	void *	(*scgo_getbuf)		__PR((SCSI *scgp, long amt));
	void	(*scgo_freebuf)		__PR((SCSI *scgp));


	BOOL	(*scgo_havebus)		__PR((SCSI *scgp, int busno));
	int	(*scgo_fileno)		__PR((SCSI *scgp, int busno, int tgt, int tlun));
	int	(*scgo_initiator_id)	__PR((SCSI *scgp));
	int	(*scgo_isatapi)		__PR((SCSI *scgp));
	int	(*scgo_reset)		__PR((SCSI *scgp, int what));
} scg_ops_t;

#define	SCGO_SEND(scgp)				(*(scgp)->ops->scgo_send)(scgp)
#define	SCGO_VERSION(scgp, what)		(*(scgp)->ops->scgo_version)(scgp, what)
#define	SCGO_HELP(scgp, f)			(*(scgp)->ops->scgo_help)(scgp, f)
#define	SCGO_OPEN(scgp, device)			(*(scgp)->ops->scgo_open)(scgp, device)
#define	SCGO_CLOSE(scgp)			(*(scgp)->ops->scgo_close)(scgp)
#define	SCGO_MAXDMA(scgp, amt)			(*(scgp)->ops->scgo_maxdma)(scgp, amt)
#define	SCGO_GETBUF(scgp, amt)			(*(scgp)->ops->scgo_getbuf)(scgp, amt)
#define	SCGO_FREEBUF(scgp)			(*(scgp)->ops->scgo_freebuf)(scgp)
#define	SCGO_HAVEBUS(scgp, busno)		(*(scgp)->ops->scgo_havebus)(scgp, busno)
#define	SCGO_FILENO(scgp, busno, tgt, tlun)	(*(scgp)->ops->scgo_fileno)(scgp, busno, tgt, tlun)
#define	SCGO_INITIATOR_ID(scgp)			(*(scgp)->ops->scgo_initiator_id)(scgp)
#define	SCGO_ISATAPI(scgp)			(*(scgp)->ops->scgo_isatapi)(scgp)
#define	SCGO_RESET(scgp, what)			(*(scgp)->ops->scgo_reset)(scgp, what)

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCGOPS_H */
/* @(#)scsitransp.h	1.54 03/05/03 Copyright 1995 J. Schilling */
/*
 *	Definitions for commands that use functions from scsitransp.c
 *
 *	Copyright (c) 1995 J. Schilling
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; see the file COPYING.  If not, write to the Free Software
 * Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef	_SCG_SCSITRANSP_H
#define	_SCG_SCSITRANSP_H

#ifdef	__cplusplus
extern "C" {
#endif


typedef struct {
	int	scsibus;	/* SCSI bus #    for next I/O		*/
	int	target;		/* SCSI target # for next I/O		*/
	int	lun;		/* SCSI lun #    for next I/O		*/
} scg_addr_t;


typedef	int	(*scg_cb_t)	__PR((void *));

struct scg_scsi {
	scg_ops_t *ops;		/* Ptr to low level SCSI transport ops	*/
	int	fd;		/* File descriptor for next I/O		*/
	scg_addr_t	addr;	/* SCSI address for next I/O		*/
	int	flags;		/* Libscg flags (see below)		*/
	int	dflags;		/* Drive specific flags (see below)	*/
	int	kdebug;		/* Kernel debug value for next I/O	*/
	int	debug;		/* Debug value for SCSI library		*/
	int	silent;		/* Be silent if value > 0		*/
	int	verbose;	/* Be verbose if value > 0		*/
	int	overbose;	/* Be verbose in open() if value > 0	*/
	int	disre_disable;
	int	deftimeout;
	int	noparity;	/* Do not use SCSI parity fo next I/O	*/
	int	dev;		/* from scsi_cdr.c			*/
	struct scg_cmd *scmd;
	char	*cmdname;
	char	*curcmdname;
	BOOL	running;
	int	error;		/* libscg error number			*/

	long	maxdma;		/* Max DMA limit for this open instance	*/
	long	maxbuf;		/* Cur DMA buffer limit for this inst.	*/
				/* This is the size behind bufptr	*/
	struct timeval	*cmdstart;
	struct timeval	*cmdstop;
	const char	**nonstderrs;
	void	*local;		/* Local data from the low level code	*/
	void	*bufbase;	/* needed for scsi_freebuf()		*/
	void	*bufptr;	/* DMA buffer pointer for appl. use	*/
	char	*errstr;	/* Error string for scsi_open/sendmcd	*/
	char	*errbeg;	/* Pointer to begin of not flushed data	*/
	char	*errptr;	/* Actual write pointer into errstr	*/
	void	*errfile;	/* FILE to write errors to. NULL for not*/
				/* writing and leaving errs in errstr	*/
	scg_cb_t cb_fun;
	void	*cb_arg;

	struct scsi_inquiry *inq;
	struct scsi_capacity *cap;
};

/*
 * Macros for accessing members of the scg address structure.
 * scg_settarget() is the only function that is allowed to modify
 * the values of the SCSI address.
 */
#define	scg_scsibus(scgp)	(scgp)->addr.scsibus
#define	scg_target(scgp)	(scgp)->addr.target
#define	scg_lun(scgp)		(scgp)->addr.lun

/*
 * Flags for struct SCSI:
 */
/* NONE yet */

/*
 * Drive specific flags for struct SCSI:
 */
#define	DRF_MODE_DMA_OVR	0x0001		/* Drive gives DMA overrun */
						/* on mode sense	   */

#define	SCSI_ERRSTR_SIZE	4096

/*
 * Libscg error codes:
 */
#define	SCG_ERRBASE		1000000
#define	SCG_NOMEM		1000001

/*
 * Function codes for scg_version():
 */
#define	SCG_VERSION		0	/* libscg or transport version */
#define	SCG_AUTHOR		1	/* Author of above */
#define	SCG_SCCS_ID		2	/* SCCS id of above */
#define	SCG_RVERSION		10	/* Remote transport version */
#define	SCG_RAUTHOR		11	/* Remote transport author */
#define	SCG_RSCCS_ID		12	/* Remote transport SCCS ID */
#define	SCG_KVERSION		20	/* Kernel transport version */

/*
 * Function codes for scg_reset():
 */
#define	SCG_RESET_NOP		0	/* Test if reset is supported */
#define	SCG_RESET_TGT		1	/* Reset Target only */
#define	SCG_RESET_BUS		2	/* Reset complete SCSI Bus */

/*
 * Helpers for the error buffer in SCSI*
 */
#define	scg_errsize(scgp)	((scgp)->errptr - (scgp)->errstr)
#define	scg_errrsize(scgp)	(SCSI_ERRSTR_SIZE - scg_errsize(scgp))

/*
 * From scsitransp.c:
 */
extern	char	*scg_version		__PR((SCSI *scgp, int what));
extern	int	scg__open		__PR((SCSI *scgp, char *device));
extern	int	scg__close		__PR((SCSI *scgp));
extern	BOOL	scg_havebus		__PR((SCSI *scgp, int));
extern	int	scg_initiator_id	__PR((SCSI *scgp));
extern	int	scg_isatapi		__PR((SCSI *scgp));
extern	int	scg_reset		__PR((SCSI *scgp, int what));
extern	void	*scg_getbuf		__PR((SCSI *scgp, long));
extern	void	scg_freebuf		__PR((SCSI *scgp));
extern	long	scg_bufsize		__PR((SCSI *scgp, long));
extern	void	scg_setnonstderrs	__PR((SCSI *scgp, const char **));
extern	BOOL	scg_yes			__PR((char *));
extern	int	scg_cmd			__PR((SCSI *scgp));
extern	void	scg_vhead		__PR((SCSI *scgp));
extern	int	scg_svhead		__PR((SCSI *scgp, char *buf, int maxcnt));
extern	int	scg_vtail		__PR((SCSI *scgp));
extern	int	scg_svtail		__PR((SCSI *scgp, int *retp, char *buf, int maxcnt));
extern	void	scg_vsetup		__PR((SCSI *scgp));
extern	int	scg_getresid		__PR((SCSI *scgp));
extern	int	scg_getdmacnt		__PR((SCSI *scgp));
extern	BOOL	scg_cmd_err		__PR((SCSI *scgp));
extern	void	scg_printerr		__PR((SCSI *scgp));
#ifdef	EOF	/* stdio.h has been included */
extern	void	scg_fprinterr		__PR((SCSI *scgp, FILE *f));
#endif
extern	int	scg_sprinterr		__PR((SCSI *scgp, char *buf, int maxcnt));
extern	int	scg__sprinterr		__PR((SCSI *scgp, char *buf, int maxcnt));
extern	void	scg_printcdb		__PR((SCSI *scgp));
extern	int	scg_sprintcdb		__PR((SCSI *scgp, char *buf, int maxcnt));
extern	void	scg_printwdata		__PR((SCSI *scgp));
extern	int	scg_sprintwdata		__PR((SCSI *scgp, char *buf, int maxcnt));
extern	void	scg_printrdata		__PR((SCSI *scgp));
extern	int	scg_sprintrdata		__PR((SCSI *scgp, char *buf, int maxcnt));
extern	void	scg_printresult		__PR((SCSI *scgp));
extern	int	scg_sprintresult 	__PR((SCSI *scgp, char *buf, int maxcnt));
extern	void	scg_printstatus		__PR((SCSI *scgp));
extern	int	scg_sprintstatus 	__PR((SCSI *scgp, char *buf, int maxcnt));
#ifdef	EOF	/* stdio.h has been included */
extern	void	scg_fprbytes		__PR((FILE *, char *, unsigned char *, int));
extern	void	scg_fprascii		__PR((FILE *, char *, unsigned char *, int));
#endif
extern	void	scg_prbytes		__PR((char *, unsigned char *, int));
extern	void	scg_prascii		__PR((char *, unsigned char *, int));
extern	int	scg_sprbytes		__PR((char *buf, int maxcnt, char *, unsigned char *, int));
extern	int	scg_sprascii		__PR((char *buf, int maxcnt, char *, unsigned char *, int));
#ifdef	EOF	/* stdio.h has been included */
extern	void	scg_fprsense		__PR((FILE *f, unsigned char *, int));
#endif
extern	void	scg_prsense		__PR((unsigned char *, int));
extern	int	scg_sprsense		__PR((char *buf, int maxcnt, unsigned char *, int));
extern	int	scg_cmd_status		__PR((SCSI *scgp));
extern	int	scg_sense_key		__PR((SCSI *scgp));
extern	int	scg_sense_code		__PR((SCSI *scgp));
extern	int	scg_sense_qual		__PR((SCSI *scgp));
#ifdef	_SCG_SCSIREG_H
#ifdef	EOF	/* stdio.h has been included */
extern	void	scg_fprintdev		__PR((FILE *, struct scsi_inquiry *));
#endif
extern	void	scg_printdev		__PR((struct scsi_inquiry *));
#endif
extern	int	scg_printf		__PR((SCSI *scgp, const char *form, ...));
extern	int	scg_errflush		__PR((SCSI *scgp));
#ifdef	EOF	/* stdio.h has been included */
extern	int	scg_errfflush		__PR((SCSI *scgp, FILE *f));
#endif

/*
 * From scsierrmsg.c:
 */
extern	const char	*scg_sensemsg	__PR((int, int, int,
						const char **, char *, int maxcnt));
#ifdef	_SCG_SCSISENSE_H
extern	int		scg__errmsg	__PR((SCSI *scgp, char *obuf, int maxcnt,
						struct scsi_sense *,
						struct scsi_status *,
						int));
#endif

/*
 * From scsiopen.c:
 */
#ifdef	EOF	/* stdio.h has been included */
extern	int	scg_help	__PR((FILE *f));
#endif
extern	SCSI	*scg_open	__PR((char *scsidev, char *errs, int slen, int odebug, int be_verbose));
extern	int	scg_close	__PR((SCSI * scgp));
extern	void	scg_settimeout	__PR((SCSI * scgp, int timeout));
extern	SCSI	*scg_smalloc	__PR((void));
extern	void	scg_sfree	__PR((SCSI *scgp));

/*
 * From scgsettarget.c:
 */
extern	int	scg_settarget		__PR((SCSI *scgp, int scsibus, int target, int lun));

/*
 * From scsi-remote.c:
 */
extern	scg_ops_t *scg_remote	__PR((void));

/*
 * From scsihelp.c:
 */
#ifdef	EOF	/* stdio.h has been included */
extern	void	__scg_help	__PR((FILE *f, char *name, char *tcomment,
					char *tind,
					char *tspec,
					char *texample,
					BOOL mayscan,
					BOOL bydev));
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _SCG_SCSITRANSP_H */
extern  void    __scg_times     __PR((SCSI *scgp));
