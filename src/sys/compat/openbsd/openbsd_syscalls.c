/*	$MirOS$	*/

/*
 * System call names.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * created from;	MirOS: src/sys/compat/openbsd/syscalls.master,v 1.3 2005/07/01 13:55:58 tg Exp 
 */

char *openbsd_syscallnames[] = {
	"syscall",			/* 0 = syscall */
	"exit",			/* 1 = exit */
	"fork",			/* 2 = fork */
	"read",			/* 3 = read */
	"write",			/* 4 = write */
	"open",			/* 5 = open */
	"close",			/* 6 = close */
	"wait4",			/* 7 = wait4 */
	"ocreat",			/* 8 = ocreat */
	"link",			/* 9 = link */
	"unlink",			/* 10 = unlink */
	"#11 (obsolete execv)",		/* 11 = obsolete execv */
	"chdir",			/* 12 = chdir */
	"fchdir",			/* 13 = fchdir */
	"mknod",			/* 14 = mknod */
	"chmod",			/* 15 = chmod */
	"chown",			/* 16 = chown */
	"break",			/* 17 = break */
	"ogetfsstat",			/* 18 = ogetfsstat */
	"olseek",			/* 19 = olseek */
	"getpid",			/* 20 = getpid */
	"mount",			/* 21 = mount */
	"unmount",			/* 22 = unmount */
	"setuid",			/* 23 = setuid */
	"getuid",			/* 24 = getuid */
	"geteuid",			/* 25 = geteuid */
#ifdef PTRACE
	"ptrace",			/* 26 = ptrace */
#else
	"#26 (unimplemented ptrace)",		/* 26 = unimplemented ptrace */
#endif
	"recvmsg",			/* 27 = recvmsg */
	"sendmsg",			/* 28 = sendmsg */
	"recvfrom",			/* 29 = recvfrom */
	"accept",			/* 30 = accept */
	"getpeername",			/* 31 = getpeername */
	"getsockname",			/* 32 = getsockname */
	"access",			/* 33 = access */
	"chflags",			/* 34 = chflags */
	"fchflags",			/* 35 = fchflags */
	"sync",			/* 36 = sync */
	"kill",			/* 37 = kill */
	"ostat",			/* 38 = ostat */
	"getppid",			/* 39 = getppid */
	"olstat",			/* 40 = olstat */
	"dup",			/* 41 = dup */
	"opipe",			/* 42 = opipe */
	"getegid",			/* 43 = getegid */
	"profil",			/* 44 = profil */
#ifdef KTRACE
	"ktrace",			/* 45 = ktrace */
#else
	"#45 (unimplemented ktrace)",		/* 45 = unimplemented ktrace */
#endif
	"sigaction",			/* 46 = sigaction */
	"getgid",			/* 47 = getgid */
	"sigprocmask",			/* 48 = sigprocmask */
	"getlogin",			/* 49 = getlogin */
	"setlogin",			/* 50 = setlogin */
#ifdef ACCOUNTING
	"acct",			/* 51 = acct */
#else
	"#51 (unimplemented acct)",		/* 51 = unimplemented acct */
#endif
	"sigpending",			/* 52 = sigpending */
	"osigaltstack",			/* 53 = osigaltstack */
	"ioctl",			/* 54 = ioctl */
	"reboot",			/* 55 = reboot */
	"revoke",			/* 56 = revoke */
	"symlink",			/* 57 = symlink */
	"readlink",			/* 58 = readlink */
	"execve",			/* 59 = execve */
	"umask",			/* 60 = umask */
	"chroot",			/* 61 = chroot */
	"ofstat",			/* 62 = ofstat */
	"ogetkerninfo",			/* 63 = ogetkerninfo */
	"ogetpagesize",			/* 64 = ogetpagesize */
	"omsync",			/* 65 = omsync */
	"vfork",			/* 66 = vfork */
	"#67 (obsolete vread)",		/* 67 = obsolete vread */
	"#68 (obsolete vwrite)",		/* 68 = obsolete vwrite */
	"sbrk",			/* 69 = sbrk */
	"#70 (unimplemented sstk)",		/* 70 = unimplemented sstk */
	"ommap",			/* 71 = ommap */
	"vadvise",			/* 72 = vadvise */
	"munmap",			/* 73 = munmap */
	"mprotect",			/* 74 = mprotect */
	"madvise",			/* 75 = madvise */
	"#76 (obsolete vhangup)",		/* 76 = obsolete vhangup */
	"#77 (obsolete vlimit)",		/* 77 = obsolete vlimit */
	"mincore",			/* 78 = mincore */
	"getgroups",			/* 79 = getgroups */
	"setgroups",			/* 80 = setgroups */
	"getpgrp",			/* 81 = getpgrp */
	"setpgid",			/* 82 = setpgid */
	"setitimer",			/* 83 = setitimer */
	"owait",			/* 84 = owait */
	"swapon",			/* 85 = swapon */
	"getitimer",			/* 86 = getitimer */
	"ogethostname",			/* 87 = ogethostname */
	"osethostname",			/* 88 = osethostname */
	"ogetdtablesize",			/* 89 = ogetdtablesize */
	"dup2",			/* 90 = dup2 */
	"#91 (unimplemented getdopt)",		/* 91 = unimplemented getdopt */
	"fcntl",			/* 92 = fcntl */
	"select",			/* 93 = select */
	"#94 (unimplemented setdopt)",		/* 94 = unimplemented setdopt */
	"fsync",			/* 95 = fsync */
	"setpriority",			/* 96 = setpriority */
	"socket",			/* 97 = socket */
	"connect",			/* 98 = connect */
	"oaccept",			/* 99 = oaccept */
	"getpriority",			/* 100 = getpriority */
	"osend",			/* 101 = osend */
	"orecv",			/* 102 = orecv */
	"sigreturn",			/* 103 = sigreturn */
	"bind",			/* 104 = bind */
	"setsockopt",			/* 105 = setsockopt */
	"listen",			/* 106 = listen */
	"#107 (obsolete vtimes)",		/* 107 = obsolete vtimes */
	"osigvec",			/* 108 = osigvec */
	"osigblock",			/* 109 = osigblock */
	"osigsetmask",			/* 110 = osigsetmask */
	"sigsuspend",			/* 111 = sigsuspend */
	"osigstack",			/* 112 = osigstack */
	"orecvmsg",			/* 113 = orecvmsg */
	"osendmsg",			/* 114 = osendmsg */
	"#115 (obsolete vtrace)",		/* 115 = obsolete vtrace */
	"gettimeofday",			/* 116 = gettimeofday */
	"getrusage",			/* 117 = getrusage */
	"getsockopt",			/* 118 = getsockopt */
	"#119 (obsolete resuba)",		/* 119 = obsolete resuba */
	"readv",			/* 120 = readv */
	"writev",			/* 121 = writev */
	"settimeofday",			/* 122 = settimeofday */
	"fchown",			/* 123 = fchown */
	"fchmod",			/* 124 = fchmod */
	"orecvfrom",			/* 125 = orecvfrom */
	"setreuid",			/* 126 = setreuid */
	"setregid",			/* 127 = setregid */
	"rename",			/* 128 = rename */
	"otruncate",			/* 129 = otruncate */
	"oftruncate",			/* 130 = oftruncate */
	"flock",			/* 131 = flock */
	"mkfifo",			/* 132 = mkfifo */
	"sendto",			/* 133 = sendto */
	"shutdown",			/* 134 = shutdown */
	"socketpair",			/* 135 = socketpair */
	"mkdir",			/* 136 = mkdir */
	"rmdir",			/* 137 = rmdir */
	"utimes",			/* 138 = utimes */
	"#139 (obsolete 4.2 sigreturn)",		/* 139 = obsolete 4.2 sigreturn */
	"adjtime",			/* 140 = adjtime */
	"ogetpeername",			/* 141 = ogetpeername */
	"ogethostid",			/* 142 = ogethostid */
	"osethostid",			/* 143 = osethostid */
	"ogetrlimit",			/* 144 = ogetrlimit */
	"osetrlimit",			/* 145 = osetrlimit */
	"okillpg",			/* 146 = okillpg */
	"setsid",			/* 147 = setsid */
	"quotactl",			/* 148 = quotactl */
	"#149 (unimplemented oquota)",		/* 149 = unimplemented oquota */
	"ogetsockname",			/* 150 = ogetsockname */
	"#151 (unimplemented)",		/* 151 = unimplemented */
	"#152 (unimplemented)",		/* 152 = unimplemented */
	"#153 (unimplemented)",		/* 153 = unimplemented */
	"#154 (unimplemented)",		/* 154 = unimplemented */
#if defined(NFSCLIENT) || defined(NFSSERVER)
	"nfssvc",			/* 155 = nfssvc */
#else
	"#155 (unimplemented nfssvc)",		/* 155 = unimplemented nfssvc */
#endif
	"ogetdirentries",			/* 156 = ogetdirentries */
	"statfs25",			/* 157 = statfs25 */
	"fstatfs25",			/* 158 = fstatfs25 */
	"#159 (unimplemented)",		/* 159 = unimplemented */
	"#160 (unimplemented)",		/* 160 = unimplemented */
	"getfh",			/* 161 = getfh */
	"ogetdomainname",			/* 162 = ogetdomainname */
	"osetdomainname",			/* 163 = osetdomainname */
	"ouname",			/* 164 = ouname */
	"sysarch",			/* 165 = sysarch */
	"#166 (unimplemented)",		/* 166 = unimplemented */
	"#167 (unimplemented)",		/* 167 = unimplemented */
	"#168 (unimplemented)",		/* 168 = unimplemented */
#if defined(SYSVSEM) && !defined(__LP64__)
	"osemsys",			/* 169 = osemsys */
#else
	"#169 (unimplemented 1.0 semsys)",		/* 169 = unimplemented 1.0 semsys */
#endif
#if defined(SYSVMSG) && !defined(__LP64__)
	"omsgsys",			/* 170 = omsgsys */
#else
	"#170 (unimplemented 1.0 msgsys)",		/* 170 = unimplemented 1.0 msgsys */
#endif
#if defined(SYSVSHM) && !defined(__LP64__)
	"oshmsys",			/* 171 = oshmsys */
#else
	"#171 (unimplemented 1.0 shmsys)",		/* 171 = unimplemented 1.0 shmsys */
#endif
	"#172 (unimplemented)",		/* 172 = unimplemented */
	"pread",			/* 173 = pread */
	"pwrite",			/* 174 = pwrite */
	"#175 (unimplemented ntp_gettime)",		/* 175 = unimplemented ntp_gettime */
	"#176 (unimplemented ntp_adjtime)",		/* 176 = unimplemented ntp_adjtime */
	"#177 (unimplemented)",		/* 177 = unimplemented */
	"#178 (unimplemented)",		/* 178 = unimplemented */
	"#179 (unimplemented)",		/* 179 = unimplemented */
	"#180 (unimplemented)",		/* 180 = unimplemented */
	"setgid",			/* 181 = setgid */
	"setegid",			/* 182 = setegid */
	"seteuid",			/* 183 = seteuid */
	"#184 (unimplemented)",		/* 184 = unimplemented */
	"#185 (unimplemented)",		/* 185 = unimplemented */
	"#186 (unimplemented)",		/* 186 = unimplemented */
	"#187 (unimplemented)",		/* 187 = unimplemented */
	"stat35",			/* 188 = stat35 */
	"fstat35",			/* 189 = fstat35 */
	"lstat35",			/* 190 = lstat35 */
	"pathconf",			/* 191 = pathconf */
	"fpathconf",			/* 192 = fpathconf */
	"swapctl",			/* 193 = swapctl */
	"getrlimit",			/* 194 = getrlimit */
	"setrlimit",			/* 195 = setrlimit */
	"getdirentries",			/* 196 = getdirentries */
	"mmap",			/* 197 = mmap */
	"__syscall",			/* 198 = __syscall */
	"lseek",			/* 199 = lseek */
	"truncate",			/* 200 = truncate */
	"ftruncate",			/* 201 = ftruncate */
	"__sysctl",			/* 202 = __sysctl */
	"mlock",			/* 203 = mlock */
	"munlock",			/* 204 = munlock */
	"#205 (unimplemented sys_undelete)",		/* 205 = unimplemented sys_undelete */
	"futimes",			/* 206 = futimes */
	"getpgid",			/* 207 = getpgid */
	"#208 (unimplemented)",		/* 208 = unimplemented */
	"#209 (unimplemented)",		/* 209 = unimplemented */
#ifdef LKM
	"lkmnosys",			/* 210 = lkmnosys */
	"lkmnosys",			/* 211 = lkmnosys */
	"lkmnosys",			/* 212 = lkmnosys */
	"lkmnosys",			/* 213 = lkmnosys */
	"lkmnosys",			/* 214 = lkmnosys */
	"lkmnosys",			/* 215 = lkmnosys */
	"lkmnosys",			/* 216 = lkmnosys */
	"lkmnosys",			/* 217 = lkmnosys */
	"lkmnosys",			/* 218 = lkmnosys */
	"lkmnosys",			/* 219 = lkmnosys */
#else	/* !LKM */
	"#210 (unimplemented)",		/* 210 = unimplemented */
	"#211 (unimplemented)",		/* 211 = unimplemented */
	"#212 (unimplemented)",		/* 212 = unimplemented */
	"#213 (unimplemented)",		/* 213 = unimplemented */
	"#214 (unimplemented)",		/* 214 = unimplemented */
	"#215 (unimplemented)",		/* 215 = unimplemented */
	"#216 (unimplemented)",		/* 216 = unimplemented */
	"#217 (unimplemented)",		/* 217 = unimplemented */
	"#218 (unimplemented)",		/* 218 = unimplemented */
	"#219 (unimplemented)",		/* 219 = unimplemented */
#endif	/* !LKM */
#ifdef SYSVSEM
	"semctl23",			/* 220 = semctl23 */
	"semget",			/* 221 = semget */
	"semop35",			/* 222 = semop35 */
	"#223 (obsolete sys_semconfig)",		/* 223 = obsolete sys_semconfig */
#else
	"#220 (unimplemented semctl)",		/* 220 = unimplemented semctl */
	"#221 (unimplemented semget)",		/* 221 = unimplemented semget */
	"#222 (unimplemented semop)",		/* 222 = unimplemented semop */
	"#223 (unimplemented semconfig)",		/* 223 = unimplemented semconfig */
#endif
#ifdef SYSVMSG
	"msgctl23",			/* 224 = msgctl23 */
	"msgget",			/* 225 = msgget */
	"msgsnd",			/* 226 = msgsnd */
	"msgrcv",			/* 227 = msgrcv */
#else
	"#224 (unimplemented msgctl23)",		/* 224 = unimplemented msgctl23 */
	"#225 (unimplemented msgget)",		/* 225 = unimplemented msgget */
	"#226 (unimplemented msgsnd)",		/* 226 = unimplemented msgsnd */
	"#227 (unimplemented msgrcv)",		/* 227 = unimplemented msgrcv */
#endif
#ifdef SYSVSHM
	"shmat",			/* 228 = shmat */
	"shmctl23",			/* 229 = shmctl23 */
	"shmdt",			/* 230 = shmdt */
	"shmget35",			/* 231 = shmget35 */
#else
	"#228 (unimplemented shmat)",		/* 228 = unimplemented shmat */
	"#229 (unimplemented shmctl23)",		/* 229 = unimplemented shmctl23 */
	"#230 (unimplemented shmdt)",		/* 230 = unimplemented shmdt */
	"#231 (unimplemented shmget35)",		/* 231 = unimplemented shmget35 */
#endif
	"clock_gettime",			/* 232 = clock_gettime */
	"clock_settime",			/* 233 = clock_settime */
	"clock_getres",			/* 234 = clock_getres */
	"#235 (unimplemented timer_create)",		/* 235 = unimplemented timer_create */
	"#236 (unimplemented timer_delete)",		/* 236 = unimplemented timer_delete */
	"#237 (unimplemented timer_settime)",		/* 237 = unimplemented timer_settime */
	"#238 (unimplemented timer_gettime)",		/* 238 = unimplemented timer_gettime */
	"#239 (unimplemented timer_getoverrun)",		/* 239 = unimplemented timer_getoverrun */
	"nanosleep",			/* 240 = nanosleep */
	"#241 (unimplemented)",		/* 241 = unimplemented */
	"#242 (unimplemented)",		/* 242 = unimplemented */
	"#243 (unimplemented)",		/* 243 = unimplemented */
	"#244 (unimplemented)",		/* 244 = unimplemented */
	"#245 (unimplemented)",		/* 245 = unimplemented */
	"#246 (unimplemented)",		/* 246 = unimplemented */
	"#247 (unimplemented)",		/* 247 = unimplemented */
	"#248 (unimplemented)",		/* 248 = unimplemented */
	"#249 (unimplemented)",		/* 249 = unimplemented */
	"minherit",			/* 250 = minherit */
	"rfork",			/* 251 = rfork */
	"poll",			/* 252 = poll */
	"issetugid",			/* 253 = issetugid */
	"lchown",			/* 254 = lchown */
	"getsid",			/* 255 = getsid */
	"msync",			/* 256 = msync */
#ifdef SYSVSEM
	"semctl35",			/* 257 = semctl35 */
#else
	"#257 (unimplemented semctl35)",		/* 257 = unimplemented semctl35 */
#endif
#ifdef SYSVSHM
	"shmctl35",			/* 258 = shmctl35 */
#else
	"#258 (unimplemented shmctl35)",		/* 258 = unimplemented shmctl35 */
#endif
#ifdef SYSVMSG
	"msgctl35",			/* 259 = msgctl35 */
#else
	"#259 (unimplemented msgctl35)",		/* 259 = unimplemented msgctl35 */
#endif
	"getfsstat",			/* 260 = getfsstat */
	"statfs",			/* 261 = statfs */
	"fstatfs",			/* 262 = fstatfs */
	"pipe",			/* 263 = pipe */
	"fhopen",			/* 264 = fhopen */
	"fhstat35",			/* 265 = fhstat35 */
	"fhstatfs",			/* 266 = fhstatfs */
	"preadv",			/* 267 = preadv */
	"pwritev",			/* 268 = pwritev */
	"kqueue",			/* 269 = kqueue */
	"kevent",			/* 270 = kevent */
	"mlockall",			/* 271 = mlockall */
	"munlockall",			/* 272 = munlockall */
	"getpeereid",			/* 273 = getpeereid */
	"#274 (unimplemented sys_extattrctl)",		/* 274 = unimplemented sys_extattrctl */
	"#275 (unimplemented sys_extattr_set_file)",		/* 275 = unimplemented sys_extattr_set_file */
	"#276 (unimplemented sys_extattr_get_file)",		/* 276 = unimplemented sys_extattr_get_file */
	"#277 (unimplemented sys_extattr_delete_file)",		/* 277 = unimplemented sys_extattr_delete_file */
	"#278 (unimplemented sys_extattr_set_fd)",		/* 278 = unimplemented sys_extattr_set_fd */
	"#279 (unimplemented sys_extattr_get_fd)",		/* 279 = unimplemented sys_extattr_get_fd */
	"#280 (unimplemented sys_extattr_delete_fd)",		/* 280 = unimplemented sys_extattr_delete_fd */
	"getresuid",			/* 281 = getresuid */
	"setresuid",			/* 282 = setresuid */
	"getresgid",			/* 283 = getresgid */
	"setresgid",			/* 284 = setresgid */
	"#285 (obsolete sys_omquery)",		/* 285 = obsolete sys_omquery */
	"mquery",			/* 286 = mquery */
	"closefrom",			/* 287 = closefrom */
	"sigaltstack",			/* 288 = sigaltstack */
#ifdef SYSVSHM
	"shmget",			/* 289 = shmget */
#else
	"#289 (unimplemented shmget)",		/* 289 = unimplemented shmget */
#endif
#ifdef SYSVSEM
	"semop",			/* 290 = semop */
#else
	"#290 (unimplemented semop)",		/* 290 = unimplemented semop */
#endif
	"stat",			/* 291 = stat */
	"fstat",			/* 292 = fstat */
	"lstat",			/* 293 = lstat */
	"fhstat",			/* 294 = fhstat */
#ifdef SYSVSEM
	"__semctl",			/* 295 = __semctl */
#else
	"#295 (unimplemented semctl)",		/* 295 = unimplemented semctl */
#endif
#ifdef SYSVSHM
	"shmctl",			/* 296 = shmctl */
#else
	"#296 (unimplemented shmctl)",		/* 296 = unimplemented shmctl */
#endif
#ifdef SYSVMSG
	"msgctl",			/* 297 = msgctl */
#else
	"#297 (unimplemented msgctl)",		/* 297 = unimplemented msgctl */
#endif
};
