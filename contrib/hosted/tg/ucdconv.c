#if 0

PROG=		ucdconv
NOMAN=		Yes

.include <bsd.prog.mk>

.if "0" == "1"
#endif

/* Copyright (C) 1999-2001 Free Software Foundation, Inc.
   Copyright (c) 2006-2010 The MirOS Project

   The GNU UTF-8 Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; version 2 of the Licence.

   The GNU UTF-8 Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU UTF-8 Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Generate tables for towlower, towupper, and the isw* functions. */

#define _ALL_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

static const char rcsid_generator[] =
  "$MirOS: contrib/hosted/tg/ucdconv.c,v 1.16 2013/11/30 20:52:16 tg Exp $";

static const char *ucdvsn;

struct unicode_attribute {
  const char* name;           /* Character name */
  const char* category;       /* General category */
  const char* combining;      /* Canonical combining classes */
  const char* bidi;           /* Bidirectional category */
  const char* decomposition;  /* Character decomposition */
  const char* decdigit;       /* Decimal digit value */
  const char* digit;          /* Digit value */
  const char* numeric;        /* Numeric value */
  int mirrored;               /* mirrored */
  const char* oldname;        /* Old Unicode 1.0 name */
  const char* comment;        /* Comment */
  unsigned int upper;         /* Upper case equivalent mapping */
  unsigned int lower;         /* Lower case equivalent mapping */
  unsigned int title;         /* Title case equivalent mapping */
};

#define NONE (~(unsigned int)0)

struct unicode_attribute unicode_attributes [0x10000];

static void fill_attribute (unsigned int i,
                            const char* field1, const char* field2,
                            const char* field3, const char* field4,
                            const char* field5, const char* field6,
                            const char* field7, const char* field8,
                            const char* field9, const char* field10,
                            const char* field11, const char* field12,
                            const char* field13, const char* field14)
{
  struct unicode_attribute * uni;

  if (i >= 0x10000) {
    fprintf(stderr, "index too large\n");
    exit(1);
  }
  if (strcmp(field2,"Cs") == 0)
    return;
  uni = &unicode_attributes[i];
  uni->name = strdup(field1);
  uni->category = (field2[0]=='\0' ? "" : strdup(field2));
  uni->combining = (field3[0]=='\0' ? "" : strdup(field3));
  uni->bidi = (field4[0]=='\0' ? "" : strdup(field4));
  uni->decomposition = (field5[0]=='\0' ? "" : strdup(field5));
  uni->decdigit = (field6[0]=='\0' ? "" : strdup(field6));
  uni->digit = (field7[0]=='\0' ? "" : strdup(field7));
  uni->numeric = (field8[0]=='\0' ? "" : strdup(field8));
  uni->mirrored = (field9[0]=='Y');
  uni->oldname = (field10[0]=='\0' ? "" : strdup(field10));
  uni->comment = (field11[0]=='\0' ? "" : strdup(field11));
  uni->upper = (field12[0]=='\0' ? NONE : strtoul(field12,NULL,16));
  uni->lower = (field13[0]=='\0' ? NONE : strtoul(field13,NULL,16));
  uni->title = (field14[0]=='\0' ? NONE : strtoul(field14,NULL,16));
}

static int getfield (FILE* f, char* buffer, int delim)
{
  int c;
  for (; (c = getc(f)), (c != EOF && c != delim); )
    *buffer++ = c;
  if (c == EOF) return 0;
  *buffer = '\0';
  return 1;
}

static void fill_attributes(void)
{
  unsigned int i, j;
  FILE* f;
  char field0 [100];
  char field1 [100];
  char field2 [100];
  char field3 [100];
  char field4 [100];
  char field5 [100];
  char field6 [100];
  char field7 [100];
  char field8 [100];
  char field9 [100];
  char field10 [100];
  char field11 [100];
  char field12 [100];
  char field13 [100];
  char field14 [100];
  int lineno = 0;
  size_t vsnlen;
  char vsn[30];

  vsn[0] = '\0';
  f = popen("sed -ne '2,$d' -e '1s/^# Blocks-\\([0-9]*\\.[0-9]*\\.[0-9]*\\)\\.txt$/\\1/p' <Blocks.txt", "r");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", "Blocks.txt");
    exit(1);
  }
  (void)fgets(vsn, sizeof(vsn), f);
  if (ferror(f)) {
    fprintf(stderr, "error during pipe I/O on Blocks.txt\n");
    exit(1);
  }
  vsnlen = strlen(vsn);
  if (vsnlen > 0 && vsn[vsnlen - 1] == '\n')
    vsn[--vsnlen] = '\0';
  pclose(f);

  if (!(ucdvsn = strdup(vsn))) {
    fprintf(stderr, "OOM\n");
    exit(1);
  }

  for (i = 0; i < 0x10000; i++)
    unicode_attributes[i].name = NULL;

#define unicodedata_filename "UnicodeData.txt"
  f = fopen(unicodedata_filename, "r");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", unicodedata_filename);
    exit(1);
  }
  for (;;) {
    int n;
    lineno++;
    n = getfield(f, field0, ';') + getfield(f, field1, ';')
        + getfield(f, field2, ';') + getfield(f, field3, ';')
        + getfield(f, field4, ';') + getfield(f, field5, ';')
        + getfield(f, field6, ';') + getfield(f, field7, ';')
        + getfield(f, field8, ';') + getfield(f, field9, ';')
        + getfield(f, field10, ';') + getfield(f, field11, ';')
        + getfield(f, field12, ';') + getfield(f, field13, ';')
        + getfield(f, field14, '\n');
    if (n == 0)
      break;
    if (n != 15) {
      fprintf(stderr, "short line in `%s':%d\n", unicodedata_filename, lineno);
      exit(1);
    }
    i = strtoul(field0,NULL,16);
    if (field1[0] == '<'
        && strlen(field1) >= 9
        && !strcmp(field1+strlen(field1)-8, ", First>")) {
      /* Deal with a range. */
      lineno++;
      n = getfield(f, field0, ';') + getfield(f, field1, ';')
          + getfield(f, field2, ';') + getfield(f, field3, ';')
          + getfield(f, field4, ';') + getfield(f, field5, ';')
          + getfield(f, field6, ';') + getfield(f, field7, ';')
          + getfield(f, field8, ';') + getfield(f, field9, ';')
          + getfield(f, field10, ';') + getfield(f, field11, ';')
          + getfield(f, field12, ';') + getfield(f, field13, ';')
          + getfield(f, field14, '\n');
      if (n != 15) {
        fprintf(stderr, "missing end range in `%s':%d\n", unicodedata_filename, lineno);
        exit(1);
      }
      if (!(field1[0] == '<'
            && strlen(field1) >= 8
            && !strcmp(field1+strlen(field1)-7, ", Last>"))) {
        fprintf(stderr, "missing end range in `%s':%d\n", unicodedata_filename, lineno);
        exit(1);
      }
      field1[strlen(field1)-7] = '\0';
      j = strtoul(field0,NULL,16);
      for (; i <= j; i++)
        fill_attribute(i, field1+1, field2, field3, field4, field5, field6,
                          field7, field8, field9, field10, field11, field12,
                          field13, field14);
    } else {
      /* Single character line */
      fill_attribute(i, field1, field2, field3, field4, field5, field6,
                        field7, field8, field9, field10, field11, field12,
                        field13, field14);
    }
  }
  if (ferror(f)) {
    fprintf(stderr, "error from ferror of `%s'\n", unicodedata_filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error during fclose of `%s'\n", unicodedata_filename);
    exit(1);
  }
}

static unsigned int uppercase (unsigned int ch)
{
  if (unicode_attributes[ch].name != NULL && unicode_attributes[ch].upper != NONE)
    return unicode_attributes[ch].upper;
  else
    return ch;
}

static unsigned int lowercase (unsigned int ch)
{
  if (unicode_attributes[ch].name != NULL && unicode_attributes[ch].lower != NONE)
    return unicode_attributes[ch].lower;
  else
    return ch;
}

static unsigned int titlecase (unsigned int ch)
{
  if (unicode_attributes[ch].name != NULL && unicode_attributes[ch].title != NONE)
    return unicode_attributes[ch].title;
  else
    return ch;
}

/* Create toupper.h, used by libutf8. */
static void output_toupper_table (void)
{
  int pages[0x100];
  int p, p1, p2, i1, i2;
  const char* filename = "tbl_towu.c";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  fprintf(f, "#include <wchar.h>\n\n#define mir18n_caseconv\n");
  fprintf(f, "#include \"mir18n.h\"\n\n__RCSID(\"$""MirOS""$\");\n");
  fprintf(f, "__RCSID(\"$""miros%s\");\n", rcsid_generator + 6);
  fprintf(f, "__IDSTRING(UCD_version, \"%s (BMP)\");\n\n", ucdvsn);
  for (p = 0; p < 0x100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (iswoctet(ch))
	continue;
      if (uppercase(ch) != ch) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x100; p++)
    if (pages[p]) {
      fprintf(f, "static const uint16_t toupper_table_page%02X[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          unsigned int ch2 = uppercase(ch);
          int j = ((int)ch2 - (int)ch) & 0xffff;
          fprintf(f, "%c0x%04X%s", i2==0?'\t':' ', j, (8*i1+i2<255?",":""));
        }
        fprintf(f, "\n");
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "const uint16_t * const toupper_table[0x100] = {\n");
  for (p1 = 0; p1 < 0x80; p1++) {
    for (p2 = 0; p2 < 2; p2++) {
      p = 2*p1 + p2;
      if (pages[p])
        fprintf(f, "%ctoupper_table_page%02X%s", p2?' ':'\t', p, (p<0x100-1?",":""));
      else
        fprintf(f, "%cnop_page%s", p2?' ':'\t', (p<0x100-1?",":""));
    }
    fprintf(f, "\n");
  }
  fprintf(f, "};\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

static void output_totitle_table (void)
{
  int pages[0x100];
  int p, p1, p2, i1, i2;
  const char* filename = "tbl_towt.c";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  fprintf(f, "#include <wchar.h>\n\n#define mir18n_caseconv\n");
  fprintf(f, "#include \"mir18n.h\"\n\n__RCSID(\"$""MirOS""$\");\n");
  fprintf(f, "__RCSID(\"$""miros%s\");\n", rcsid_generator + 6);
  fprintf(f, "__IDSTRING(UCD_version, \"%s (BMP)\");\n\n", ucdvsn);
  for (p = 0; p < 0x100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (iswoctet(ch))
	continue;
      if (uppercase(ch) == ch && titlecase(ch) != ch) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x100; p++)
    if (pages[p]) {
      fprintf(f, "static const uint16_t totitle_table_page%02X[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          int j = 0;
	  if (uppercase(ch) == ch && titlecase(ch) != ch)
	    j = ((int)titlecase(ch) - (int)ch) & 0xFFFF;
          fprintf(f, "%c0x%04X%s", i2==0?'\t':' ', j, (8*i1+i2<255?",":""));
        }
        fprintf(f, "\n");
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "const uint16_t * const totitle_table[0x100] = {\n");
  for (p1 = 0; p1 < 0x80; p1++) {
    for (p2 = 0; p2 < 2; p2++) {
      p = 2*p1 + p2;
      if (pages[p])
        fprintf(f, "%ctotitle_table_page%02X%s", p2?' ':'\t', p, (p<0x100-1?",":""));
      else
        fprintf(f, "%cnop_page%s", p2?' ':'\t', (p<0x100-1?",":""));
    }
    fprintf(f, "\n");
  }
  fprintf(f, "};\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

/* Create tolower.h, used by libutf8. */
static void output_tolower_table (void)
{
  int pages[0x100];
  int p, p1, p2, i1, i2;
  const char* filename = "tbl_towl.c";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  fprintf(f, "#include <wchar.h>\n\n#define mir18n_caseconv\n");
  fprintf(f, "#include \"mir18n.h\"\n\n__RCSID(\"$""MirOS""$\");\n");
  fprintf(f, "__RCSID(\"$""miros%s\");\n", rcsid_generator + 6);
  fprintf(f, "__IDSTRING(UCD_version, \"%s (BMP)\");\n\n", ucdvsn);
  for (p = 0; p < 0x100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (iswoctet(ch))
	continue;
      if (lowercase(ch) != ch) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x100; p++)
    if (pages[p]) {
      fprintf(f, "static const uint16_t tolower_table_page%02X[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          unsigned int ch2 = lowercase(ch);
          int j = ((int)ch2 - (int)ch) & 0xffff;
          fprintf(f, "%c0x%04X%s", i2?' ':'\t', j, (8*i1+i2<255?",":""));
        }
        fprintf(f, "\n");
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "const uint16_t * const tolower_table[0x100] = {\n");
  for (p1 = 0; p1 < 0x80; p1++) {
    for (p2 = 0; p2 < 2; p2++) {
      p = 2*p1 + p2;
      if (pages[p])
        fprintf(f, "%ctolower_table_page%02X%s", p2?' ':'\t', p, (p<0x100-1?",":""));
      else
        fprintf(f, "%cnop_page%s", p2?' ':'\t', (p<0x100-1?",":""));
    }
    fprintf(f, "\n");
  }
  fprintf(f, "};\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

#define upper    1
#define lower    2
#define alpha    4
#define digit    8
#define xdigit  16
#define space   32
#define print   64
#define graph  128
#define blank  256
#define cntrl  512
#define punct 1024
#define alnum 2048

/* Create attribute.h, used by libutf8. */
static void output_attribute_table (void)
{
  int table[0x10000];
  int pages[0x100];
  int p, q, p1, p2, i;
  unsigned int ch;
  const char *filename = "tbl_att0.c";
  FILE* f = NULL;
  for (ch = 0; ch < 0x10000; ch++) {
    int attributes = 0;
    if (unicode_attributes[ch].category &&
     !strcmp(unicode_attributes[ch].category, "Lt"))
      attributes |= upper | lower;	/* title case */
    else if (lowercase(ch) != ch && uppercase(ch) == ch)
      attributes |= upper;
    else if (lowercase(ch) == ch && uppercase(ch) != ch)
      attributes |= lower;
    /* The OpenGroups's susv2/xbd/locale.html says only characters satisfying
       isupper() or islower() can have a nontrivial toupper() or tolower()
       mapping. */
    if ((attributes & (upper | lower)) == 0) {
      if (uppercase(ch) != ch)
        fprintf(stderr, "U%04x is not upper|lower but toupper(U%04x) = U%04x\n", ch, ch, uppercase(ch));
      if (lowercase(ch) != ch)
        fprintf(stderr, "U%04x is not upper|lower but tolower(U%04x) = U%04x\n", ch, ch, lowercase(ch));
    }
    if (unicode_attributes[ch].name != NULL
        && (unicode_attributes[ch].category[0] == 'L'
            || (attributes & (upper | lower)) != 0))
      attributes |= alpha;
    if ((((attributes & upper) != 0) || ((attributes & lower) != 0)) && ((attributes & alpha) == 0))
      fprintf(stderr, "U%04x is upper or lower but not alpha\n", ch);
#if 0
    if (unicode_attributes[ch].name != NULL
        && unicode_attributes[ch].category[0] == 'N'
        && unicode_attributes[ch].category[1] == 'd')
#else
    /* The OpenGroups's susv2/xbd/locale.html and Dinkumware's C lib reference
       say isdigit() may not return true for additional characters. */
    if (ch >= '0' && ch <= '9')
#endif
      attributes |= digit;
    if (((attributes & digit) != 0) && ((attributes & alpha) != 0))
      fprintf(stderr, "U%04x is both digit and alpha\n", ch);
    if (((attributes & digit) != 0) || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
      attributes |= xdigit;
    if (ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t' || ch == '\v')
      attributes |= space;
    /* Don't make U00A0 a space. Non-breaking space means that all programs
       should treat it like a punctuation character, not like a space. */
    if (unicode_attributes[ch].name != NULL
        && strcmp(unicode_attributes[ch].name, "<control>"))
      attributes |= print;
    if (((attributes & print) != 0) && ((attributes & space) == 0))
      attributes |= graph;
    if (ch == ' ' || ch == '\t')
      attributes |= blank;
    if (unicode_attributes[ch].name != NULL
        && !strcmp(unicode_attributes[ch].name, "<control>"))
      attributes |= cntrl;
    if (((attributes & graph) != 0)
        && ((attributes & alpha) == 0) && ((attributes & digit) == 0))
      /* This includes punctuation and symbols. */
      attributes |= punct;
    if (((attributes & alpha) != 0) || ((attributes & digit) != 0))
      attributes |= alnum;
    if (iswoctet(ch))
      attributes = 0;
    table[ch] = attributes;
  }
  for (p = 0; p < 0x100; p++) {
    pages[p] = -1;
    for (q = 0; q < p; q++)
      if (pages[q] < 0) {
        int same = 1;
        for (i = 0; i < 0x100; i++)
          if (table[0x100*p+i] != table[0x100*q+i]) {
            same = 0;
            break;
          }
        if (same) {
          pages[p] = q;
          break;
        }
      }
  }
  for (p = 0; p < 0x100; p++)
    if (pages[p] < 0) {
      if (p < 2) {
        if (f)
          fclose(f);
        if (!(f = fopen(filename, "w"))) {
          fprintf(stderr, "error during fopen of `%s'\n", filename);
          exit(1);
        }
        fprintf(f, "#include <wchar.h>\n\n#define mir18n_attributes\n");
        fprintf(f, "#include \"mir18n.h\"\n\n__RCSID(\"$""MirOS""$\");\n");
        fprintf(f, "__RCSID(\"$""miros%s\");\n", rcsid_generator + 6);
        fprintf(f, "__IDSTRING(UCD_version, \"%s (BMP)\");\n\n", ucdvsn);
        filename = "tbl_attr.c";
      }
      if (p)
	fprintf(f, "static const unsigned char attribute_table_page%02X[256] = {\n", p);
      else
	fprintf(f, "const unsigned char __C_attribute_table_pg[256] = {\n");
      for (i = 0; i < 0x100; i++) {
        unsigned int ch_ = 256*p + i;
        int attributes = table[ch_];
        int next = 0;
        fprintf(f, "\t/* 0x%04X */ ", ch_);
        if (attributes & upper) {
          if (next) fprintf(f, " | ");
          fprintf(f, "upper");
          next = 1;
        }
        if (attributes & lower) {
          if (next) fprintf(f, " | ");
          fprintf(f, "lower");
          next = 1;
        }
        if (attributes & alpha) {
          if (next) fprintf(f, " | ");
          fprintf(f, "alpha");
          next = 1;
        }
        if (attributes & digit) {
          if (next) fprintf(f, " | ");
          fprintf(f, "digit");
          next = 1;
        }
        if (attributes & xdigit) {
          if (next) fprintf(f, " | ");
          fprintf(f, "xdigit");
          next = 1;
        }
        if (attributes & space) {
          if (next) fprintf(f, " | ");
          fprintf(f, "space");
          next = 1;
        }
        if (attributes & print) {
          if (next) fprintf(f, " | ");
          fprintf(f, "print");
          next = 1;
        }
        if (attributes & graph) {
          if (next) fprintf(f, " | ");
          fprintf(f, "graph");
          next = 1;
        }
        if (attributes & blank) {
          if (next) fprintf(f, " | ");
          fprintf(f, "blank");
          next = 1;
        }
        if (attributes & cntrl) {
          if (next) fprintf(f, " | ");
          fprintf(f, "cntrl");
          next = 1;
        }
        if (attributes & punct) {
          if (next) fprintf(f, " | ");
          fprintf(f, "punct");
          next = 1;
        }
        if (attributes & alnum) {
          if (next) fprintf(f, " | ");
          fprintf(f, "alnum");
          next = 1;
        }
        if (!next)
          fprintf(f, "0");
        if (i < 0xff)
          fprintf(f, ",");
        fprintf(f, "\n");
      }
      fprintf(f, "};\n");
      if (p)
        fprintf(f, "\n");
    }
  fprintf(f, "const unsigned char * const attribute_table[0x100] = {\n");
  for (p1 = 0; p1 < 0x80; p1++) {
    for (p2 = 0; p2 < 2; p2++) {
      p = 2*p1 + p2;
      if (p)
	fprintf(f, "%cattribute_table_page%02X%s", p2 == 0 ? '\t' : ' ', (pages[p] >= 0 ? pages[p] : p),
                 (p<0x100-1?",":""));
      else
	fprintf(f, "\t__C_attribute_table_pg,");
    }
    fprintf(f, "\n");
  }
  fprintf(f, "};\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

int main (void)
{
  fill_attributes();

  output_toupper_table();
  output_totitle_table();
  output_tolower_table();
  output_attribute_table();

  return 0;
}

#if 0
.endif
#endif
