/* $MirOS$ */

#ifndef	_LIBSA_TORI_H
#define	_LIBSA_TORI_H

struct tori_pbk {
	u_int32_t	x1;
	u_int32_t	imgofs;
	u_int32_t	x2;
	u_int32_t	segcnt;
	u_int8_t	x3[3];
};

#define	_B0(a)	((u_int8_t)((a)&0xFF))
#define	_B1(a)	(_B0((a)>>8))
#define	_B2(a)	(_B0((a)>>16))
#define	_B3(a)	(_B0((a)>>24))
#define	_W0(a)	((u_int16_t)((a)&0xFFFF))
#define	_W1(a)	(_W0((a)>>16))

#define	_MKW(a,b)	((((u_int16_t)(a))&0xFF)|((((u_int16_t)(b))&0xFF)<<8))
#define	_MKL(a,b)	((((u_int32_t)(a))&0xFFFF)|((((u_int32_t)(b))&0xFFFF)<<16))

extern struct tori_pbk tori_pblk;

#define	T_LEN	_B0(tori_pblk.x1)
#define	T_EMUL	_B1(tori_pblk.x1)
#define	T_DRV	_B2(tori_pblk.x1)
#define	T_CTRL	_B3(tori_pblk.x1)
#define	T_IMAG	tori_pblk.imgofs
#define	T_LSEG	_W0(tori_pblk.segcnt)
#define	T_LNUM	_W1(tori_pblk.segcnt)
#define	T_G_CH	tori_pblk.x3[0]
#define	T_G_CL	tori_pblk.x3[1]
#define	T_G_DH	tori_pblk.x3[2]

#define	MKTORI(emul,drv,imag,lseg,lnum,ch,cl,dh) do {			 \
		tori_pblk.x1=_MKL(_MKW(0x13,(emul)),_MKW((drv),T_CTRL)); \
		tori_pblk.imgofs=(imag);				 \
		tori_pblk.segcnt=_MKL((lseg),(lnum));			 \
		tori_pblk.x3[0]=(ch);					 \
		tori_pblk.x3[1]=(cl);					 \
		tori_pblk.x3[2]=(dh);					 \
	} while (0)

struct open_file;

/* toridev.c */
int toristrategy(void *, int, daddr_t, size_t, void *, size_t *);
int toriopen(struct open_file *, ...);
int toriclose(struct open_file *);
int toriioctl(struct open_file *, u_long, void *);
int tori_io(daddr_t, void *);

#endif
