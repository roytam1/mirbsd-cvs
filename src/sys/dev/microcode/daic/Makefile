# /* ISDN4BSD code */
# The Microcode for the Eicon.Diehl active ISDN cards comes in two parts.
# A tiny bootstrap loader delivered by Diehl as "dnload.bin" and a
# D-channel protocol specific file, e.g. "te_etsi.sx" for the SX card
# running E-DSS1.
# We can not deliver either of these files. The user is assumed to use
# the ones distributed with his card or download the newest version from
# http://www.diehl.de.
# The bootstrap loader is compiled into the kernel, as it is needed to 
# identify the card. The protocol specific part is later downloaded by
# the ISDN management daemon.

dnload.h::	dnload.bin dnload.h-dist gendnloadh
	@rm -f dnload.h
	@${SHELL} ${.CURDIR}/gendnloadh

dnload.bin:

.PHONY:	dnload.bin
