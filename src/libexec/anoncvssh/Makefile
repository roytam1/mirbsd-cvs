# $MirOS: src/libexec/anoncvssh/Makefile,v 1.8 2008/11/29 17:03:53 tg Exp $

# Note: you DO want to compile this, as well as the anoncvsbin
# and rsync, statically. It is not possible, however, to do that
# when your system uses PAM authentication. That's why, use of
# systems with PAM (such as GNU libc based systems) is strongly
# disrecommended - better alternatives such as BSD auth exist.

# The following line defines where your CVS Root (repository) lives.
DEFS+=		-DLOCALROOT=\"/cvs\"

# Two ways to specify the user/host part of $CVSROOT:
# a) Simple - just specify user@host
#DEFS+=		-DHOSTNAME=\"_anoncvs@host.domain.com\"
# b) Split - define user and host (default)
#    Advantage: a warning will be issued if someone
#    other than the user specified (or root) invokes us.
#DEFS+=		-DANONCVS_USER=\"_anoncvs\" -DFQDN=\"host.domain.com\"
DEFS+=		-DANONUSERLIST='"_anoncvs", "_rsync", "anoncvs", "rsync"'

# Enable rsync for the user.
# Warning: this also makes rsync writes possible
# if the file ownership and permissions don't forbid it!
DEFS+=		-DACCESS_RSYNC
# if not using the standard path...
#DEFS+=		-DRSYNC=\"/bin/rsync\"

# Specify if you *DON'T* want to set CVSREADONLYFS=1.
# This can be used if you want to give a user CVS
# read/write access, but no shell account. Use with care!
#DEFS+=		-DACCESS_READWRITE

# If there is more than one person with ACCESS_READWRITE
# and the OS does not implement nullfs correctly (vnodes
# just don't like to show up in more than one place) put
# all of their homes and the CVS Root into a common dir,
# ensure nobody else can write to it (the common dir can
# still be the _anoncvs user's home) and define this:
#XXX rework this some time
#DEFS+=		-DCHROOT_PARENT_DIR

# Specify this if you want to allow :pserver: access.
# *Not recommended* because pserver is a security hole!
#DEFS+=		-DACCESS_PSERVER

# Specify this if you want to log :pserver: connections
# and unauthorised access.
DEFS+=		-DUSE_SYSLOG

# Name of this program. Set e.g. to "anoncvssh.mirbsd"
# if running more than one anoncvs user, and for read-
# write users, to "anoncvs-username" (thus you can place
# them in the common parent dir).
PROG?=		anoncvssh${PROGSUFF}

# Use 'chflags uchg /usr/libexec/anoncvssh' to prevent the
# generated file from being overwritten once you customised
# this Makefile. Use ...nouchg... to disable the protection
# whenever you are going to update this.

CPPFLAGS+=	${DEFS} -DANONCVSSH_NAME=\"${PROG}\"
CDIAGFLAGS+=	-Wno-cast-qual
BINOWN=		root
BINGRP=		_anoncvs
BINMODE=	4110
BINDIR?=	/usr/libexec
LDFLAGS+=	-static
SRCS=		anoncvssh.c
NOMAN=		yes

anoncvssh.o: Makefile

.include <bsd.prog.mk>
