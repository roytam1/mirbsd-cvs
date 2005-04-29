$MirOS$
--- lib/Xm/TextF.c.orig	Thu Apr 28 23:41:08 2005
+++ lib/Xm/TextF.c	Thu Apr 28 23:41:18 2005
@@ -84,7 +84,7 @@ static char rcsid[] = "$TOG: TextF.c /ma
 #include <Xm/PrintSP.h>         /* for XmIsPrintShell */
 
 
-#if defined(__FreeBSD__)
+#if defined(__FreeBSD__) || defined(__OpenBSD__)
 /*
  * Modification by Integrated Computer Solutions, Inc.  May 2000
  *
