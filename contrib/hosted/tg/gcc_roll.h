/* $MirOS: src/share/misc/licence.template,v 1.28 2008/11/14 15:33:44 tg Rel $ */

/*-
 * Copyright (c) 2009
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
 * ROL, ROR, RCL, RCR for kernel / gcc (multi-evaluation safe macros)
 */

#ifdef __i386__
#define rol32(ax,cl)	__extension__({			\
	register uint32_t rol32_ax = (uint32_t)(ax);	\
	register uint8_t rol32_cl = (cl) & 31;		\
							\
	__asm__("roll	%1,%0"				\
	    : "=g" (rol32_ax)				\
	    : "cI" (rol32_cl), "0" (rol32_ax)		\
	    : "cc");					\
	(rol32_ax);					\
})
#define ror32(ax,cl)	__extension__({			\
	register uint32_t ror32_ax = (uint32_t)(ax);	\
	register uint8_t ror32_cl = (cl) & 31;		\
							\
	__asm__("rorl	%1,%0"				\
	    : "=g" (ror32_ax)				\
	    : "cI" (ror32_cl), "0" (ror32_ax)		\
	    : "cc");					\
	(ror32_ax);					\
})
#define rcl32(ax,cl)	__extension__({			\
	register uint32_t rcl32_ax = (uint32_t)(ax);	\
	register uint8_t rcl32_cl = (cl) & 31;		\
							\
	__asm__("rcll	%1,%0"				\
	    : "=g" (rcl32_ax)				\
	    : "cI" (rcl32_cl), "0" (rcl32_ax)		\
	    : "cc");					\
	(rcl32_ax);					\
})
#define rcr32(ax,cl)	__extension__({			\
	register uint32_t rcr32_ax = (uint32_t)(ax);	\
	register uint8_t rcr32_cl = (cl) & 31;		\
							\
	__asm__("rcrl	%1,%0"				\
	    : "=g" (rcr32_ax)				\
	    : "cI" (rcr32_cl), "0" (rcr32_ax)		\
	    : "cc");					\
	(rcr32_ax);					\
})
#define rol16(ax,cl)	__extension__({			\
	register uint16_t rol16_ax = (uint16_t)(ax);	\
	register uint8_t rol16_cl = (cl) & 15;		\
							\
	__asm__("rolw	%1,%0"				\
	    : "=g" (rol16_ax)				\
	    : "cI" (rol16_cl), "0" (rol16_ax)		\
	    : "cc");					\
	(rol16_ax);					\
})
#define ror16(ax,cl)	__extension__({			\
	register uint16_t ror16_ax = (uint16_t)(ax);	\
	register uint8_t ror16_cl = (cl) & 15;		\
							\
	__asm__("rorw	%1,%0"				\
	    : "=g" (ror16_ax)				\
	    : "cI" (ror16_cl), "0" (ror16_ax)		\
	    : "cc");					\
	(ror16_ax);					\
})
#define rcl16(ax,cl)	__extension__({			\
	register uint16_t rcl16_ax = (uint16_t)(ax);	\
	register uint8_t rcl16_cl = (cl) & 15;		\
							\
	__asm__("rclw	%1,%0"				\
	    : "=g" (rcl16_ax)				\
	    : "cI" (rcl16_cl), "0" (rcl16_ax)		\
	    : "cc");					\
	(rcl16_ax);					\
})
#define rcr16(ax,cl)	__extension__({			\
	register uint16_t rcr16_ax = (uint16_t)(ax);	\
	register uint8_t rcr16_cl = (cl) & 15;		\
							\
	__asm__("rcrw	%1,%0"				\
	    : "=g" (rcr16_ax)				\
	    : "cI" (rcr16_cl), "0" (rcr16_ax)		\
	    : "cc");					\
	(rcr16_ax);					\
})
#define rol8(ax,cl)	__extension__({			\
	register uint8_t rol8_ax = (uint8_t)(ax);	\
	register uint8_t rol8_cl = (cl) & 7;		\
							\
	__asm__("rolb	%1,%0"				\
	    : "=g" (rol8_ax)				\
	    : "cI" (rol8_cl), "0" (rol8_ax)		\
	    : "cc");					\
	(rol8_ax);					\
})
#define ror8(ax,cl)	__extension__({			\
	register uint8_t ror8_ax = (uint8_t)(ax);	\
	register uint8_t ror8_cl = (cl) & 7;		\
							\
	__asm__("rorb	%1,%0"				\
	    : "=g" (ror8_ax)				\
	    : "cI" (ror8_cl), "0" (ror8_ax)		\
	    : "cc");					\
	(ror8_ax);					\
})
#define rcl8(ax,cl)	__extension__({			\
	register uint8_t rcl8_ax = (uint8_t)(ax);	\
	register uint8_t rcl8_cl = (cl) & 7;		\
							\
	__asm__("rclb	%1,%0"				\
	    : "=g" (rcl8_ax)				\
	    : "cI" (rcl8_cl), "0" (rcl8_ax)		\
	    : "cc");					\
	(rcl8_ax);					\
})
#define rcr8(ax,cl)	__extension__({			\
	register uint8_t rcr8_ax = (uint8_t)(ax);	\
	register uint8_t rcr8_cl = (cl) & 7;		\
							\
	__asm__("rcrb	%1,%0"				\
	    : "=g" (rcr8_ax)				\
	    : "cI" (rcr8_cl), "0" (rcr8_ax)		\
	    : "cc");					\
	(rcr8_ax);					\
})
#else
#define rol32(ax,cl)	__extension__({			\
	register uint32_t rol32_ax = (uint32_t)(ax);	\
	register uint8_t rol32_cl = (cl) & 31;		\
							\
	((uint32_t)((rol32_ax << rol32_cl) |		\
	    (rol32_ax >> (32 - rol32_cl))));		\
})
#define ror32(ax,cl)	__extension__({			\
	register uint32_t ror32_ax = (uint32_t)(ax);	\
	register uint8_t ror32_cl = (cl) & 31;		\
							\
	((uint32_t)((ror32_ax << ror32_cl) |		\
	    (ror32_ax >> (32 - ror32_cl))));		\
})
#define rcl32(ax,cl)	__extension__({			\
	register uint32_t rcl32_ax = (uint32_t)(ax);	\
	register uint8_t rcl32_cl = (cl) & 31;		\
							\
	((uint32_t)((rcl32_ax << rcl32_cl) |		\
	    (rcl32_ax >> (32 - rcl32_cl))));		\
})
#define rcr32(ax,cl)	__extension__({			\
	register uint32_t rcr32_ax = (uint32_t)(ax);	\
	register uint8_t rcr32_cl = (cl) & 31;		\
							\
	((uint32_t)((rcr32_ax << rcr32_cl) |		\
	    (rcr32_ax >> (32 - rcr32_cl))));		\
})
#define rol16(ax,cl)	__extension__({			\
	register uint16_t rol16_ax = (uint32_t)(ax);	\
	register uint8_t rol16_cl = (cl) & 15;		\
							\
	((uint16_t)((rol16_ax << rol16_cl) |		\
	    (rol16_ax >> (16 - rol16_cl))));		\
})
#define ror16(ax,cl)	__extension__({			\
	register uint16_t ror16_ax = (uint32_t)(ax);	\
	register uint8_t ror16_cl = (cl) & 15;		\
							\
	((uint16_t)((ror16_ax << ror16_cl) |		\
	    (ror16_ax >> (16 - ror16_cl))));		\
})
#define rcl16(ax,cl)	__extension__({			\
	register uint16_t rcl16_ax = (uint32_t)(ax);	\
	register uint8_t rcl16_cl = (cl) & 15;		\
							\
	((uint16_t)((rcl16_ax << rcl16_cl) |		\
	    (rcl16_ax >> (16 - rcl16_cl))));		\
})
#define rcr16(ax,cl)	__extension__({			\
	register uint16_t rcr16_ax = (uint32_t)(ax);	\
	register uint8_t rcr16_cl = (cl) & 15;		\
							\
	((uint16_t)((rcr16_ax << rcr16_cl) |		\
	    (rcr16_ax >> (16 - rcr16_cl))));		\
})
#define rol8(ax,cl)	__extension__({			\
	register uint8_t rol8_ax = (uint32_t)(ax);	\
	register uint8_t rol8_cl = (cl) & 7;		\
							\
	((uint8_t)((rol8_ax << rol8_cl) |		\
	    (rol8_ax >> (8 - rol8_cl))));		\
})
#define ror8(ax,cl)	__extension__({			\
	register uint8_t ror8_ax = (uint32_t)(ax);	\
	register uint8_t ror8_cl = (cl) & 7;		\
							\
	((uint8_t)((ror8_ax << ror8_cl) |		\
	    (ror8_ax >> (8 - ror8_cl))));		\
})
#define rcl8(ax,cl)	__extension__({			\
	register uint8_t rcl8_ax = (uint32_t)(ax);	\
	register uint8_t rcl8_cl = (cl) & 7;		\
							\
	((uint8_t)((rcl8_ax << rcl8_cl) |		\
	    (rcl8_ax >> (8 - rcl8_cl))));		\
})
#define rcr8(ax,cl)	__extension__({			\
	register uint8_t rcr8_ax = (uint32_t)(ax);	\
	register uint8_t rcr8_cl = (cl) & 7;		\
							\
	((uint8_t)((rcr8_ax << rcr8_cl) |		\
	    (rcr8_ax >> (8 - rcr8_cl))));		\
})
#endif
