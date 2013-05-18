/* $MirOS$ */

extern const struct cmd_table cmd_machine[];

#ifndef SMALL_BOOT
int Xboot(void);
int Xdiskinfo(void);
int Xlabel(void);
int Xmdexec(void);
#endif
int Xmemory(void);
#ifndef SMALL_BOOT
int Xregs(void);
#endif
int Xoldbios(void);
