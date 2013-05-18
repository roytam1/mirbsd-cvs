/* $MirOS: src/gnu/usr.bin/rcs/conf.h,v 1.1.7.1 2005/03/06 17:00:10 tg Exp $ */

/* RCS compile-time configuration */
/* *NOT* automatically generated. */

#include <errno.h>
#include <stdio.h>
#include <time.h>

/* Comment out #include lines below that do not work.  */
#include <sys/param.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <pwd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utime.h>

#define FOPEN_RB "r"
#define FOPEN_R_WORK "r"
#define FOPEN_WB "w"
#define FOPEN_W_WORK "w"
#define FOPEN_WPLUS_WORK "w+"

/* Define or comment out the following symbols as needed.  */
#include <stdarg.h>
#define bad_chmod_close 0 /* Can chmod() close file descriptors?  */
#define bad_creat0 0 /* Do writes fail after creat(f,0)?  */
#define bad_fopen_wplus 0 /* Does fopen(f,"w+") fail to truncate f?  */
#define getlogin_is_secure 0 /* Is getlogin() secure?  Usually it's not.  */
#define has_dirent 1 /* Do opendir(), readdir(), closedir() work?  */
#define void_closedir 0 /* Does closedir() yield void?  */
#define has_fchmod 1 /* Does fchmod() work?  */
#define has_fflush_input 0 /* Does fflush() work on input files?  */
#define has_fputs 1 /* Does fputs() work?  */
#define has_ftruncate 1 /* Does ftruncate() work?  */
#define has_getuid 1 /* Does getuid() work?  */
#define has_getpwuid 1 /* Does getpwuid() work?  */
#define has_fgets 1 /* Does fgets() work?  */
#define has_memcmp 1 /* Does memcmp() work?  */
#define has_memcpy 1 /* Does memcpy() work?  */
#define has_memmove 1 /* Does memmove() work?  */
#define has_map_fd 0 /* Does map_fd() work?  */
#define has_mmap 1 /* Does mmap() work on regular files?  */
#define has_madvise 1 /* Does madvise() work?  */
#define mmap_signal SIGSEGV /* signal received if you reference nonexistent part of mmapped file */
#define has_rename 1 /* Does rename() work?  */
#define bad_a_rename 0 /* Does rename(A,B) fail if A is unwritable?  */
#define bad_b_rename 0 /* Does rename(A,B) fail if B is unwritable?  */
#define bad_NFS_rename 0 /* Can rename(A,B) falsely report success?  */
#define has_seteuid 1 /* Does seteuid() work?  See ../INSTALL.RCS.  */
#define has_setreuid 0 /* Does setreuid() work?  See ../INSTALL.RCS.  */
#define has_setuid 1 /* Does setuid() exist?  */
#define has_sigaction 1 /* Does struct sigaction work?  */
#define has_sa_sigaction 1 /* Does struct sigaction have sa_sigaction?  */
#define has_signal 1 /* Does signal() work?  */
#define signal_type void /* type returned by signal handlers */
#define sig_zaps_handler 0 /* Must a signal handler reinvoke signal()?  */
#define has_getcwd 1 /* Does getcwd() work?  */
#define needs_getabsname 0 /* Must we define getabsname?  */
#define has_mkstemp 1 /* Does mkstemp() work?  */
#define has_mktemp 1 /* Does mktemp() work?  */
#define has_NFS 1 /* Might NFS be used?  */
#define has_psiginfo 0 /* Does psiginfo() work?  */
#define has_psignal 1 /* Does psignal() work?  */
#define bad_unlink 0 /* Does unlink() fail on unwritable files?  */
#define has_vfork 1 /* Does vfork() work?  */
#define has_fork 1 /* Does fork() work?  */
#define has_waitpid 1 /* Does waitpid() work?  */
#define bad_wait_if_SIGCHLD_ignored 1 /* Does ignoring SIGCHLD break wait()?  */
#define RCS_SHELL "/bin/mksh" /* shell to run RCS subprogrammes */
#define has_vfprintf 1 /* Does vfprintf() work?  */
#define large_memory 1 /* Can main memory hold entire RCS files?  */
/* Do struct stat s and t describe the same file?  Answer d if unknown.  */
#define same_file(s,t,d) ((s).st_ino==(t).st_ino && (s).st_dev==(t).st_dev)
#define CO "/usr/bin/co" /* name of 'co' program */
#define DIFF "/usr/bin/diff" /* name of 'diff' program */
#define DIFF3 "/usr/libexec/diff3prog" /* name of 'diff3' program */
#define DIFF3_BIN 0 /* Is diff3 user-visible (not the /usr/lib auxiliary)?  */
#define DIFFFLAGS "-an" /* Make diff output suitable for RCS.  */
#define DIFF_L 1 /* Does diff -L work?  */
#define DIFF_SUCCESS 0 /* DIFF status if no differences are found */
#define DIFF_FAILURE 1 /* DIFF status if differences are found */
#define DIFF_TROUBLE 2 /* DIFF status if trouble */
#define ED "/bin/ed" /* name of 'ed' program (used only if !DIFF3_BIN) */
#define MERGE "/usr/bin/merge" /* name of 'merge' program */
#define TMPDIR "/tmp" /* default directory for temporary files */
#define SLASH '/' /* principal filename separator */
#define SLASHes '/' /* `case SLASHes:' labels all filename separators */
#define isSLASH(c) ((c) == SLASH) /* Is arg a filename separator?  */
#define ROOTPATH(p) isSLASH((p)[0]) /* Is p an absolute pathname?  */
#define X_DEFAULT ",v/" /* default value for -x option */
#define SENDMAIL "/usr/sbin/sendmail" /* how to send mail */
