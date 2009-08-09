/* $LynxId: LYJump.h,v 1.8 2009/01/01 22:41:42 tom Exp $ */
#ifndef LYJUMP_H
#define LYJUMP_H

#include <HTList.h>

#ifdef __cplusplus
extern "C" {
#endif
    typedef struct _JumpDatum {
	char *key;
	char *url;
    } JumpDatum;

    struct JumpTable {
	int key;
	unsigned nel;
	char *msg;
	char *file;
	char *shortcut;
	HTList *history;
	JumpDatum *table;
	struct JumpTable *next;
	char *mp;
    };

    extern struct JumpTable *JThead;
    extern void LYJumpTable_free(void);
    extern void LYAddJumpShortcut(HTList *the_history, char *shortcut);
    extern BOOL LYJumpInit(char *config);
    extern char *LYJump(int key);

#ifdef __cplusplus
}
#endif
#endif				/* LYJUMP_H */
