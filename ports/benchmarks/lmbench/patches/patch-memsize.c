--- src/memsize.c.orig	Sat Nov 11 13:42:42 1995
+++ src/memsize.c	Sat Mar  4 02:38:16 2000
@@ -10,6 +10,7 @@
  */
 char	*id = "$Id$\n";
 
+#include <stdlib.h>
 #include "timing.c"
 
 #define	CHK(x)	if ((x) == -1) { perror("x"); exit(1); }
