/*
 *	Menu selection window
 *	Copyright
 *		(C) 1992 Joseph H. Allen
 *
 *	This file is part of JOE (Joe's Own Editor)
 */
#ifndef _JOE_MENU_H
#define _JOE_MENU_H 1

#ifdef EXTERN_CMD_C
__IDSTRING(rcsid_menu_h, "$MirOS: contrib/code/jupp/menu.h,v 1.3 2017/12/02 02:07:29 tg Exp $");
#endif

/* Create a menu */
/* FIXME: ??? ---> */
MENU *mkmenu PARAMS((W *w, unsigned char **s, int (*func) (/* ??? */), int (*abrt) (/* ??? */), int (*backs) (/* ??? */), int cursor, void *object, int *notify));

/* Menu user functions */

int umuparw PARAMS((MENU *m));
int umdnarw PARAMS((MENU *m));
int umpgup PARAMS((MENU *m));
int umpgdn PARAMS((MENU *m));
int umltarw PARAMS((MENU *m));
int umrtarw PARAMS((MENU *m));
int umtab PARAMS((MENU *m));
int umbof PARAMS((MENU *m));
int umeof PARAMS((MENU *m));
int umbol PARAMS((MENU *m));
int umeol PARAMS((MENU *m));
int umbacks PARAMS((MENU *m));

void ldmenu PARAMS((MENU *m, unsigned char **s, int cursor));

unsigned char *mcomplete PARAMS((MENU *m));
unsigned char *find_longest PARAMS((unsigned char **lst));

#endif
