/*
 * $LynxId: LYHistory.h,v 1.19 2008/02/11 01:05:04 tom Exp $
 */
#ifndef LYHISTORY_H
#define LYHISTORY_H

#ifndef LYSTRUCTS_H
#include <LYStructs.h>
#endif /* LYSTRUCTS_H */

#ifdef __cplusplus
extern "C" {
#endif
    extern BOOLEAN LYwouldPush(const char *title, const char *docurl);
    extern BOOLEAN historytarget(DocInfo *newdoc);
    extern int LYShowVisitedLinks(char **newfile);
    extern int LYhist_next(DocInfo *doc, DocInfo *newdoc);
    extern int LYpush(DocInfo *doc, BOOLEAN force_push);
    extern int showhistory(char **newfile);
    extern void LYAddVisitedLink(DocInfo *doc);
    extern void LYAllocHistory(int entries);
    extern void LYFreePostData(DocInfo *data);
    extern void LYFreeDocInfo(DocInfo *data);
    extern void LYhist_prev(DocInfo *doc);
    extern void LYhist_prev_register(DocInfo *doc);
    extern void LYpop(DocInfo *doc);
    extern void LYpop_num(int number, DocInfo *doc);
    extern void LYstatusline_messages_on_exit(char **buf);
    extern void LYstore_message(const char *message);
    extern void LYstore_message2(const char *message, const char *argument);

    extern HTList *Visited_Links;
    extern int nhist_extra;

#ifdef __cplusplus
}
#endif
#endif				/* LYHISTORY_H */
