/* $MirOS$ */

/* Support for built-in config files */

typedef struct jfile {
	FILE *f;		/* Regular file, or NULL for built-in */
	unsigned char *p;	/* Built-in file pointer */
} JFILE;

JFILE *jfopen(unsigned char *name, char *mode);
unsigned char *jfgets(unsigned char *buf,int len,JFILE *f);
int jfclose(JFILE *f);

extern unsigned char *builtins[];
