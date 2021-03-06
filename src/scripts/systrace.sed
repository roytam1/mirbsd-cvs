Policy: @@PROG@@, Emulation: native
	native-__getcwd: permit
	native-__semctl: permit
	native-__sysctl: permit
	native-accept: permit
	native-bind: sockaddr match "/tmp" then permit
	native-bind: sockaddr match "/var/tmp" then permit
	native-bind: sockaddr match "@@RO_DIR@@" then deny[eperm]
	native-bind: sockaddr match "@@RW_DIR@@" then permit
	native-bind: sockaddr match "/<non-existent filename>: *" then deny[enoent]
	native-break: permit
	native-chdir: permit
	native-chflags: filename match "/tmp" then permit
	native-chflags: filename match "/var/tmp" then permit
	native-chflags: filename match "@@RO_DIR@@" then deny[eperm]
	native-chflags: filename match "@@RW_DIR@@" then permit
	native-chflags: filename match "/<non-existent filename>: *" then deny[enoent]
	native-chmod: filename match "/tmp" then permit
	native-chmod: filename match "/var/tmp" then permit
	native-chmod: filename match "@@RO_DIR@@" then deny[eperm]
	native-chmod: filename match "@@RW_DIR@@" then permit
	native-chmod: filename match "/<non-existent filename>: *" then deny[enoent]
	native-chown: filename match "/tmp" then permit
	native-chown: filename match "/var/tmp" then permit
	native-chown: filename match "@@RO_DIR@@" then deny[eperm]
	native-chown: filename match "@@RW_DIR@@" then permit
	native-chown: filename match "/<non-existent filename>: *" then deny[enoent]
	native-chroot: permit
	native-clock_getres: permit
	native-clock_gettime: permit
	native-close: permit
	native-closefrom: permit
	native-compat_43_ogetdtablesize: permit
	native-compat_43_ogetpagesize: permit
	native-compat_43_olseek: permit
	native-connect: sockaddr eq "family(0)" then permit
	native-connect: sockaddr match "/dev/log" then permit
	native-connect: sockaddr match "/tmp" then permit
	native-connect: sockaddr match "/var/tmp" then permit
	native-connect: sockaddr match "@@RO_DIR@@" then deny[eperm]
	native-connect: sockaddr match "@@RW_DIR@@" then permit
	native-connect: sockaddr match "/<non-existent filename>: *" then deny[enoent]
	native-dup2: permit
	native-dup: permit
	native-execve: true then permit
	native-exit: permit
	native-fchdir: permit
	native-fchflags: permit
	native-fchmod: permit
	native-fchown: permit
	native-fcntl: permit
	native-flock: permit
	native-fork: permit
	native-fsread: filename eq "" then deny[enoent]
	native-fsread: true then permit
	native-fstat: permit
	native-fstatfs: permit
	native-fswrite: filename eq "" then deny[enoent]
	native-fswrite: filename eq "/dev/crypto" then permit
	native-fswrite: filename eq "/dev/null" then permit
	native-fswrite: filename eq "/dev/stdout" then permit
	native-fswrite: filename eq "/dev/tty" then permit
	native-fswrite: filename eq "/dev/zero" then permit
	native-fswrite: filename match "/tmp" then permit
	native-fswrite: filename match "/var/tmp" then permit
	native-fswrite: filename match "@@RO_DIR@@" then deny[eperm]
	native-fswrite: filename match "@@RW_DIR@@" then permit
	native-fswrite: filename match "/<non-existent filename>: *" then deny[enoent]
	native-fsync: permit
	native-ftruncate: permit
	native-futimes: permit
	native-getdirentries: permit
	native-getegid: permit
	native-geteuid: permit
	native-getfsstat: permit
	native-getgid: permit
	native-getgroups: permit
	native-getlogin: permit
	native-getpeername: permit
	native-getpgid: permit
	native-getpgrp: permit
	native-getpid: permit
	native-getppid: permit
	native-getpriority: permit
	native-getrlimit: permit
	native-getrusage: permit
	native-getsid: permit
	native-getsockname: permit
	native-getsockopt: permit
	native-getthrid: permit
	native-gettimeofday: permit
	native-getuid: permit
	native-ioctl: permit
	native-issetugid: permit
	native-kevent: permit
	native-kill: permit
	native-kqueue: permit
	native-lchown: filename match "/tmp" then permit
	native-lchown: filename match "/var/tmp" then permit
	native-lchown: filename match "@@RO_DIR@@" then deny[eperm]
	native-lchown: filename match "@@RW_DIR@@" then permit
	native-lchown: filename match "/<non-existent filename>: *" then deny[enoent]
	native-link: filename match "/tmp" and filename[1] match "/tmp" then permit
	native-link: filename match "/var/tmp" and filename[1] match "/var/tmp" then permit
	native-link: filename match "@@RO_DIR@@" or filename[1] match "@@RO_DIR@@" then deny[eperm]
	native-link: filename match "@@RW_DIR@@" and filename[1] match "@@RW_DIR@@" then permit
	native-link: filename match "/<non-existent filename>: *" then deny[enoent]
	native-listen: permit
	native-lseek: permit
	native-madvise: permit
	native-mknod: filename match "/tmp" then permit
	native-mknod: filename match "/var/tmp" then permit
	native-mknod: filename match "@@RO_DIR@@" then deny[eperm]
	native-mknod: filename match "@@RW_DIR@@" then permit
	native-mlock: permit
	native-mlockall: permit
	native-mmap: permit
	native-mprotect: permit
	native-mquery: permit
	native-msync: permit
	native-munmap: permit
	native-nanosleep: permit
	native-osigaltstack: permit
	native-pathconf: permit
	native-pipe: permit
	native-poll: permit
	native-pread: permit
	native-pwrite: permit
	native-quotactl: permit
	native-read: permit
	native-readv: permit
	native-recvfrom: permit
	native-recvmsg: permit
	native-rename: filename match "/tmp" and filename[1] match "/tmp" then permit
	native-rename: filename match "/tmp" and filename[1] match "/var/tmp" then permit
	native-rename: filename match "@@RO_DIR@@" or filename[1] match "@@RO_DIR@@" then deny[eperm]
	native-rename: filename match "/tmp" and filename[1] match "@@RW_DIR@@" then permit
	native-rename: filename match "/var/tmp" and filename[1] match "/var/tmp" then permit
	native-rename: filename match "/var/tmp" and filename[1] match "@@RW_DIR@@" then permit
	native-rename: filename match "@@RW_DIR@@" and filename[1] match "@@RW_DIR@@" then permit
	native-rename: filename match "/<non-existent filename>: *" then deny[enoent]
	native-rfork: permit
	native-sched_yield: permit
	native-select: permit
	native-semctl: permit
	native-semget: permit
	native-semop: permit
	native-sendmsg: permit
	native-sendto: permit
	native-setegid: permit
	native-setgid: permit
	native-setgroups: permit
	native-setitimer: permit
	native-setpgid: permit
	native-setpriority: permit
	native-setregid: permit
	native-setresgid: permit
	native-setresuid: permit
	native-setreuid: permit
	native-setrlimit: permit
	native-setsid: permit
	native-setsockopt: permit
	native-setuid: permit
	native-shmat: permit
	native-shmctl: permit
	native-shmdt: permit
	native-shmget: permit
	native-shutdown: permit
	native-sigaction: permit
	native-sigaltstack: permit
	native-sigprocmask: permit
	native-sigreturn: permit
	native-sigsuspend: permit
	native-socket: permit
	native-socketpair: permit
	native-statfs: permit
	native-symlink: filename match "/tmp" then permit
	native-symlink: filename match "/var/tmp" then permit
	native-symlink: filename match "@@RO_DIR@@" then deny[eperm]
	native-symlink: filename match "@@RW_DIR@@" then permit
	native-symlink: string eq "" and filename eq "" then deny[enoent]
	native-sync: permit
	native-threxit: permit
	native-thrsigdivert: permit
	native-thrsleep: permit
	native-thrwakeup: permit
	native-umask: permit
	native-utimes: permit
	native-vfork: permit
	native-wait4: permit
	native-write: permit
	native-writev: permit

