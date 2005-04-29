$MirOS$
--- tests/Performance/Startup/editor.c.orig	Wed May  3 09:12:26 2000
+++ tests/Performance/Startup/editor.c	Thu Apr 28 23:41:18 2005
@@ -238,7 +238,7 @@ Boolean SaveFile()
 
     strcpy(tempname, "/tmp/xmeditXXXXXX");
     
-    if ((tfp = fopen(mktemp(tempname), "w")) == NULL) {
+    if ((tfp = mkstemp(tempname)) == NULL) {
        fprintf(stderr, "Warning: unable to open temp file, text not saved.\n");
        return(False);;
     }
