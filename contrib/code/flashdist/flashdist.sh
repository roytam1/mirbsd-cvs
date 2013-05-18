#!/bin/mksh
# $MirOS$
#
# Copyright (c) 2002, 2003, 2004 Chris Cappuccio.  Pretend that you see BSD
# license blurb, clause 1, 2 and warranty disclaimer here.
#
# This quick and dirty script will setup a flash media with an OpenBSD/i386
# distribution specified by <distfile>.  This script makes many assumptions,
# but should work just dandy with most any OpenBSD/i386 3.x system.  I've
# used it with USB CompactFlash and I suspect it will work fine for IDE CF
# or DOM or anything perhaps.   Maybe.
#
# This script contains a stupid method which occasionally works to make this
# media bootable on a destination which uses a different c/h/s translation
# than the host system.  Of course, this is really just a hack.  This
# is probably no longer necessary with the fixed MBR.
#
# To use this script:
#  1. Run it without using any modified values.  Your system should
#     be able to determine the correct geometry for the media you are
#     installing to.  If this does not work, you can ignore disklabel's
#     values by using -d.
#  2. If this fails to boot on the destination system with 'Bad magic',
#     or other boot errors, then the destination system is not using the
#     same geometry that your install system detected.  You need to manually
#     specify a geometry which will work.  Try the sample ones in here.
#  3. If the destination system now boots when you force a geometry,
#     then you can use disklabel -d wd0 (or sd0 or whatever your boot
#     device is) once you are booted to find out the real geometry
#     that you should be using.
#
# If you cannot boot the resulting media initialized by this script,
# you may need to fill in the following values with the output from
# disklabel -d <device> on the destination system  Of course, you also need
# to uncomment the values (remove the pound sign, eh?)
#
# If you can't get the disklabel -d values for the media on your destination
# system, you can either ask someone else who has the same setup to do
# disklabel -d and send you the output or find some other creative way, like
# writing the miniroot image to your media or something... (The sample values
# which come with this script are for the SanDisk SDCFB-64 as seen by the
# Soekris net4501.)
#
# Value			Disklabel name
#
#totalsize=125440	# "total sectors:" 
#bytessec=512		# "bytes/sector:"
#sectorstrack=32	# "sectors/track:"
#sectorscylinder=256	# "sectors/cylinder:"
#trackscylinder=8	# "tracks/cylinder:"
#cylinders=490		# "cylinders:"
# 
# SimpleTech STI-CF/32 "K0NCF032CI" 32MB values are:
#
#totalsize=62592	# "total sectors:"
#bytessec=512		# "bytes/sector:"
#sectorstrack=32	# "sectors/track:"
#sectorscylinder=128	# "sectors/cylinder:"
#trackscylinder=4	# "tracks/cylinder:"
#cylinders=489		# "cylinders:"
#
# The 'CompactBSD 0.1.0' 32MB values are:
#
#totalsize=62720	# "total sectors:"
#bytessec=512		# "bytes/sector:"
#sectorstrack=32	# "sectors/track:"
#sectorscylinder=256	# "sectors/cylinder:"
#trackscylinder=8	# "tracks/cylinder:"
#cylinders=245		# "cylinders:"
#
# The 'OpenSoekris 1.0.8' 64MB values are:
#
#totalsize=125184	# "total sectors:" 
#bytessec=512		# "bytes/sector:"
#sectorstrack=32	# "sectors/track:"
#sectorscylinder=2048	# "sectors/cylinder:"
#trackscylinder=64	# "tracks/cylinder:"
#cylinders=61		# "cylinders:"
#
# The 'OpenSoekris 1.0.8' 128MB values are:
#
#totalsize=250368	# "total sectors:" 
#bytessec=512		# "bytes/sector:"
#sectorstrack=32	# "sectors/track:"
#sectorscylinder=2048	# "sectors/cylinder:"
#trackscylinder=64	# "tracks/cylinder:"
#cylinders=122		# "cylinders:"
#
# Charles Dietlein sent in 256MB SimpleTech STI-CF/256 values:
#
#totalsize=500400	# "total sectors:"
#bytessec=512		# "bytes/sector:"
#sectorstrack=48	# "sectors/track:"
#sectorscylinder=720	# "sectors/cylinder:"
#trackscylinder=15	# "tracks/cylinder:"
#cylinders=695		# "cylinders:"
#
# In any event, the real goal here is to get something that is bootable
# so you can run disklabel -d wd0 when you are booted on the embedded
# device and get the real values that you should be using.  That is,
# you don't need to use the absolutely correct values for the first run around!
# If you have a 2003 BIOS on a Soekris box, or another BIOS that tells you
# the C/H/S translations it will use for the flash disk, you can start out
# with exact values right away.  Just enter them when you run the script.
#
# Variables you can set in advance
#
# encpass (encrypted root password)
# password (non-encrypted root password, overridden by encpass)
# syslogserver (IP address to send logging data.  If set to "none", syslog
#               will log to the ramdisk.)
# etccopyfiles (files to copy over to destination's /etc directory.  If set
#               to "none", no files will be copied.  Flashdist default for
#               net4501 is "ttys fstab rc syslog.conf boot.cfg")
#
# (commented variables are determined interactively while script runs,
#  uncommented variables are determined right here and now)
#
#encpass='$2a$06$2p5eSJnVp8P5MEQsjlAx2ecpyU5FyQvDlE7BCebRGt4HWRFJP/djq'
#syslogserver="35.42.1.42"
etccopyfiles="ttys fstab rc syslog.conf boot.cfg nshrc"
#
nshdir="nsh"		# where to find nsh (if at all)
savesh="save-ro.sh"	# which save script to use with nsh
#
# Let the beatings begin!

umask 022

vers="20041104"

PATH=/usr/bin:/usr/sbin:/sbin:/bin

usage()
{
 echo "Usage: flashdist.sh [-d] <disk device name> <distfile> <bsd kernel> <openbsd base>"
 echo 
 echo "-d >> this option will cause disklabel to always initialize the media with"
 echo "      the kernel's current idea of the disk geometry even if the old disklabel"
 echo "      has a different idea of the geometry"
 echo "disk device name >> the base name of your flash media, such as sd0"
 echo "distfile >> distribution list file name"
 echo "bsd kernel >> kernel to install on your flash"
 echo "openbsd base >> unpacked OpenBSD distribution (unpacked baseXX.tgz, etcXX.tgz)"
 echo
 echo "example:"
 echo "flashdist.sh sd0 flashsmall.txt /usr/src/sys/arch/i386/compile/NET4501/bsd /tmp/openbsd"
 exit
}

echo flashdist.sh $vers chris@nmedia.net

if [ "$1" == "-d" ]; then
 dflag="-d"
 shift
else
 dflag=""
fi

if [ "$1" == "" ]; then
 usage
else
 disk=/dev/$1c
 if [ ! -b $disk ]; then
   echo $1 is an invalid disk device, $disk not found or not block device
   exit
 else
  echo Using disk device: $1
 fi
fi

if [ "$2" == "" ]; then
 usage
else
 if [ ! -f "$2" ]; then
   echo $2 is an invalid distfile, file not found
   exit
 else
   echo Using distfile: $2
 fi
fi

if [ "$3" == "" ]; then
 usage
else
 if [ ! -f "$3" ]; then
   echo $3 is an invalid kernel, file not found
   exit
 else
   echo Copying kernel from: $3
 fi
fi

if [ "$4" == "" ]; then
 usage
else
 if [ ! -d "$4" ]; then
   echo $4 is not a directory
   exit
 else
   if [ ! -f "$4"/etc/services ]; then
     echo $4 does not contain an unpacked etcXX.tgz file
     exit
   fi
   if [ ! -f "$4"/bin/mksh ]; then
     echo $4 does not contain an unpacked baseXX.tgz file
     exit
   fi
  fi
fi

islezero()
{
  if [ "$1" -le "0" ]; then
   echo expected a value larger than 0, got \"$1\"
   exit
  fi
}

if [ "X$dflag" == "X" -a "$totalsize" == "" ]; then
  echo
  echo You did not specify -d and you did not specify a manual geometry.
  echo Please enter Cylinders/Heads/SectorsPerTrack.
  echo
  echo -n "Cylinders: "
  read cylinders
  islezero $cylinders
  echo -n "Tracks Per Cylinder(Heads): "
  read trackscylinder
  islezero $trackscylinder
  echo -n "Sectors Per Track: "
  read sectorstrack
  islezero $sectorstrack
  bytessec=512
  let totalsize=$cylinders*$trackscylinder*$sectorstrack
  let sectorscylinder=$totalsize/$cylinders
fi

echo
echo Please pay attention to any error messages that you may
echo receive from the commands this script is using.  If you
echo end up having problems, they could explain why.
echo
echo WARNING: This will erase ALL DATA on the $1 disk device!
echo -n Press enter key to continue or Control-C to abort...
read whatever
echo

# XXX somewhat i386 specific for now...
#

TA=`mktemp /tmp/_aaaXXXXXX`
TB=`mktemp /tmp/_bbbXXXXXX`

echo Setting up disklabel...
if ! disklabel $dflag $1 > $TA; then
  echo "Disklabel failed: disklabel $dflag $1 > $TA"
  echo Please fix something.  Aborting...
  echo
  exit
fi
echo

checkd()
{
 if [ "$dflag" == "-d" ]; then
  echo You cannot specify geometry manually and specify the -d flag
  echo "(Please edit the script and comment out the geometry at the top to use -d)"
  echo
  exit
 fi
}

if [ "$totalsize" == "" ]; then
 totalsize=`cat $TA | egrep ^"total sectors:" | awk ' {print $3} '`
else
 checkd
 x=`cat $TA | egrep ^"total sectors:" | awk ' {print $3} '`
 sed -e "s/total sectors: $x/total sectors: $totalsize/" < $TA >$TB
 mv $TB $TA
fi
if [ "$bytessec" == "" ]; then
 bytessec=`cat $TA | egrep ^"bytes/sector:" | awk ' {print $2} '`
else
 checkd
 x=`cat $TA | egrep ^"bytes/sector:" | awk ' {print $2} '`
 sed -e "s/bytes\\/sector: $x/bytes\\/sector: $bytessec/" < $TA >$TB
 mv $TB $TA
fi
if [ "$sectorstrack" == "" ]; then
 sectorstrack=`cat $TA | egrep ^"sectors/track:" | awk ' {print $2} '`
else
 checkd
 x=`cat $TA | egrep ^"sectors/track:" | awk ' {print $2} '`
 sed -e "s/sectors\\/track: $x/sectors\\/track: $sectorstrack/" < $TA >$TB
 mv $TB $TA
fi
if [ "$sectorscylinder" == "" ]; then
 sectorscylinder=`cat $TA | egrep ^"sectors/cylinder:" | awk ' {print $2} '`
else
 checkd
 x=`cat $TA | egrep ^"sectors/cylinder:" | awk ' {print $2} '`
 sed -e "s/sectors\\/cylinder: $x/sectors\\/cylinder: $sectorscylinder/" < $TA >$TB
 mv $TB $TA
fi
if [ "$trackscylinder" == "" ]; then
 trackscylinder=`cat $TA | egrep ^"tracks/cylinder:" | awk ' {print $2} '`
else
 checkd
 x=`cat $TA | egrep ^"tracks/cylinder:" | awk ' {print $2} '`
 sed -e "s/tracks\\/cylinder: $x/tracks\\/cylinder: $trackscylinder/" < $TA >$TB
 mv $TB $TA
fi
if [ "$cylinders" == "" ]; then
 cylinders=`cat $TA | egrep ^"cylinders:" | awk ' {print $2} '`
else
 checkd
 x=`cat $TA | egrep ^"cylinders:" | awk ' {print $2} '`
 sed -e "s/cylinders: $x/cylinders: $cylinders/" < $TA >$TB
 mv $TB $TA
fi

# Strip out existing partitions
T=`mktemp /tmp/_ahhXXXXXX`
cat $TA | egrep -v ^"  .:" >$T

# Now we can reuse $TA and $TB temp file names
echo > $TA

let totalbytes=$totalsize*$bytessec 

echo "The install script is using the following parameters:"
echo "Total size of media: $totalsize sectors ($totalbytes bytes)"
echo "Bytes/Sector: $bytessec"
echo "Sectors/Track: $sectorstrack"
echo "Sectors/Cylinder: $sectorscylinder"
echo "Tracks/Cylinder (heads): $trackscylinder"
echo "Cylinders: $cylinders"
echo
echo -n Press enter key to continue or Control-C to abort...
read whatever
echo

notfound=""

echo Checking distribution list...

# Peanut Butter Wolf, give the people some technology!
for i in `cat $2`; do
 if [ ! -f $4/$i ]; then
  echo $i NOT FOUND
  notfound=1
 elif [ -x $4/$i ]; then
  lib=`ldd $4/$i 2>/dev/null | grep '[0-9a-fA-F] rlib ' | awk ' { print "." \
    $5 } '`
   for z in $lib; do
     if [ ! -f $4/$z ]; then
      echo "$z NOT FOUND (dependency of $i)"
      notfound=1
     else
      echo $z >> $TA
     fi
   done
 fi
done

if [ "$notfound" == "1" ]; then
  echo You are missing files from your chosen distribution list.
  echo All of the file names specified in $2 must exist in the
  echo $4 directory.
  exit
fi

# Sort libraries and then append list to master dist list
sort < $TA | uniq > $TB
cat $2 > $TA
cat $TB >> $TA
rm $TB

echo

echo Updating MBR and partition table...

fdisk -c $cylinders -h $trackscylinder -s $sectorstrack -f $4/usr/mdec/mbr -e $1 << __EOC >/dev/null
reinit
update
write
quit
__EOC

echo "Note, you may ignore \"sysctl(machdep.bios.diskinfo)\" errors if present."
echo

# This $asize method seems to create a disklabel which works
# under other c/h/s translations then the one we installed on.  This is
# probably complete snake oil.
#
# It causes the partition to end on a cylinder boundary.  The idea here is that
# 1. different c/h/s translations on our destinations (like IDE CF or DOM) will
# have a higher number of cylinders then our host USB CF system, and
# 2. our cylinder boundaries will lie on the same sectors when you compare
# the host cylinder boundary sector numbers with the destination cylinder
# boundary sector numbers.  All bets are off if we are 1. going from a host
# system that come up with significantly different numbers of sectors then the
# destination system, 2. systems that use different numbers of bytes per sector,
# or 3. if we are going from a host system with a high cylinder count to a
# destination system that uses a low cylinder count to represent the media.
#
# Of course, this will work fine if both your host and destination systems are
# using the same c/h/s translation.
#
let asize=$cylinders*$sectorscylinder
#
# Here we remove additional cylinders while
# (totalsize <= (cylinders*(sectors/cylinder))) so that
# we have room for the b partition and still lie on a cylinder boundary:
#
while [ "$totalsize" -le "$asize" ]; do
  let asize=$asize-$sectorscylinder
done
#
# Here we allow ourselves to start after the first track, I guess so
# it can store disklabel or whatever.  Seems like tradition, anyways.
#
# This could break things if sectors per track is different on either
# translation:
#
let asize=$asize-$sectorstrack
#
# BLah.
#
let offset=$asize+$sectorstrack

# Here we setup an 'a' partition that takes up the whole flash media
# and a 'b' partition of minimal size which can be used with mount_mfs
echo "a: $asize	$sectorstrack	4.2BSD	1024	8192	16" >> $T
echo "b: 1		$offset	swap" >> $T
echo "c: $totalsize	0	unused	0	0" >> $T

echo Installing disklabel...
disklabel -R $1 $T

echo
echo Creating new filesystem...
newfs -S $bytessec -u $sectorstrack -z $trackscylinder -q /dev/r$1a
echo

TT=`mktemp -d /tmp/_bhhXXXXXX`

echo Mounting destination to $TT...
if ! mount -o async /dev/$1a $TT; then
  echo Mount failed: mount -o async /dev/$1a $TT
  echo Please fix something.  Aborting...
  echo 
  exit
fi

echo -n Copying OpenBSD distribution to media...
tar cf - -C $4 `cat $TA` | tar xpf - -C $TT
echo done

# Here we assume that your new install will want to use the same name
# server as your install box.  sneaky, eh?
echo Copying bsd kernel, boot blocks, /etc/resolv.conf...
cp $4/usr/mdec/boot $TT/boot
cp /etc/resolv.conf $TT/etc/resolv.conf
cp $3 $TT/bsd

echo Installing boot blocks...
/usr/mdec/installboot $TT/boot $4/usr/mdec/biosboot $1

echo -n Running MAKEDEV...
cdir=`pwd`
cd $TT/dev
#
# Try and avoid totally unnecessary use of inodes on limited space flash...
# (no midi, audio, vnd, lkm, raid, scsi scanners, usb, etc...)
sh MAKEDEV tun0 tun1 tun2 tun3 bpf0 bpf1 bpf2 bpf3 bpf4 bpf5 bpf6 bpf7 bpf8 bpf9
sh MAKEDEV fd1 fd1B fd1C fd1D fd1E fd1F fd1G fd1H fd0 fd0B fd0C fd0D fd0E fd0F
sh MAKEDEV fd0G fd0H random crypto pf pctr systrace sd0 sd1 sd2 sd3 sd4 wd0 wd1
sh MAKEDEV wd2 wd3 fd tty00 tty01 tty02 tty03 ttyc0 ttyc1 ttyc2 ttyc3 apm std
#
# Setup links for the ptys on a read-write partition
# (the rc script will copy over anything in devtmp to MFS /var/run/dev upon
#  boot)
mkdir $TT/dev/devtmp
cd $TT/dev/devtmp
sh ../MAKEDEV pty0
#
for i in *; do
 ln -s /var/run/dev/$i $TT/dev/$i
done
echo done
cd $cdir

# run syslogd -p /var/run/log from /etc/rc
ln -s /var/run/log $TT/dev/log

echo Setting up directories and links...
mkdir $TT/tmp $TT/mnt

# /var is really r-w /tmp
ln -s /tmp/var $TT/var

if [ -x $TT/bin/mksh ]; then
# Here we reuse $TA again
# Flashdist's distribution list has mksh and not sh nor csh binaries.
# Of course sh is just a hard link to mksh, but we prefer to stay clean and
# simple on the flash.
 if [ ! -x $TT/bin/sh ]; then
  echo Changing any instance of /bin/sh in $TT/etc/master.passwd to /bin/mksh
  sed -e 's/bin\/sh/bin\/mksh/' <$TT/etc/master.passwd >$TA
  cat <$TA >$TT/etc/master.passwd
 fi
 if [ ! -x $TT/bin/csh ]; then
  echo Changing any instance of /bin/csh in $TT/etc/master.passwd to /bin/mksh
  sed -e 's/bin\/csh/bin\/mksh/' <$TT/etc/master.passwd >$TA
  cat <$TA >$TT/etc/master.passwd
 fi
fi

if [ -d $TT/etc/ssh ]; then
# If the distribution list had ssh, then set it up ahead of time
 echo -n "Generating new RSA host key... "
 if ssh-keygen -q -t rsa -f $TT/etc/ssh/ssh_host_rsa_key -N ''; then
  echo done
 else
  echo FAILED
 fi

 echo -n "Generating new RSA1 host key... "
 if ssh-keygen -q -t rsa1 -f $TT/etc/ssh/ssh_host_key -N ''; then
  echo done
 else
  echo FAILED
 fi

 echo -n "Generating new DSA host key... "
 if /usr/bin/ssh-keygen -q -t dsa -f $TT/etc/ssh/ssh_host_dsa_key -N ''; then
  echo done
 else
  echo FAILED
 fi
fi

getpass()
{
 stty -echo
 echo -n "Password:"
 read pw1
 echo
 echo -n "Verify:"
 read pw2
 echo
 stty echo
 if test "$pw1" = "$pw2"; then
  password="$pw1"
 fi
 if test "$password" = ""; then
  echo "Passwords don't match or password was empty.  Try again."
  getpass
 fi
}

if [ "$encpass" == "" ]; then
 if [ "$password" == "" ]; then
  echo
  echo Please assign a root password...
  getpass
  echo
 fi
fi

if [ "$encpass" == "" ]; then
 encpass=`echo $password | /usr/bin/encrypt -b 6`
fi

echo -n "root:$encpass" > $TA

awk -F : '/^root/ \
{ printf(":%s:%s:%s:%s:%s:%s:%s:%s\n", $3, $4, $5, $6, $7, $8, $9, $10) }' \
< $TT/etc/master.passwd >> $TA

egrep -v "^root:" < $TT/etc/master.passwd >> $TA

cat < $TA > $TT/etc/master.passwd

pwd_mkdb -p -d $TT/etc $TT/etc/master.passwd

if [ "$etccopyfiles" == "" ]; then
cat << __GANJA
Please enter any file name(s), separated by spaces, that you wish to copy
over to the install media's /etc directory.  Files are assumed to be in the
current working directory unless a full path is specified.  (Press enter
for none)

__GANJA
 echo -n "Files to copy: "
 read etccopyfiles
fi

if [ "$etccopyfiles" != "" -a "$etccopyfiles" != "none" ]; then
 echo -n "Copying configuration files to /etc..."
 for i in $etccopyfiles; do
  if [ -f $i ]; then
   echo -n " $i"
   cp $i $TT/etc
  else
   echo
   echo WARNING: Unable to copy \"$i\" to destination filesystem, must be done manually
  fi
 done
 echo
fi

if [ -x "$nshdir/nsh" -a -x "$nshdir/$savesh" ]; then
 echo "Installing NSH ($savesh)..."
  cp $nshdir/nsh $TT/bin/nsh
  mkdir -p $TT/usr/local/bin
  cp $nshdir/$savesh $TT/usr/local/bin/save.sh
fi

if [ -f $TT/etc/syslog.conf ]; then
 if [ "$syslogserver" == "" ]; then
 cat << __BUTTER

Please enter the hostname or IP address of the central log host which will
receive udp syslog packets from this installation. (Press enter for none,
and syslog will log to ramdisk)

__BUTTER
  echo -n "Loghost: "
  read syslogserver
 fi

 if [ "$syslogserver" == "" ]; then
   sed -e "s/MESSAGES/\/var\/log\/messages/" < $TT/etc/syslog.conf > $TA
   sed -e "s/AUTHLOG/\/var\/log\/authlog/" < $TA > $TT/etc/syslog.conf
 else
   sed -e "s/MESSAGES/@$syslogserver/" < $TT/etc/syslog.conf > $TA
   sed -e "s/AUTHLOG/@$syslogserver/" < $TA > $TT/etc/syslog.conf
 fi
fi

# Configure more system values: interfaces, default route, etc ????

echo
echo Installation finished.
echo -n Unmounting filesystem...
umount $TT
rmdir $TT
rm $T $TA

echo done!

