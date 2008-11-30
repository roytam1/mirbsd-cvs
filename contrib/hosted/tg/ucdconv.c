/* Copyright (C) 1999-2001 Free Software Foundation, Inc.
   This file is part of the GNU UTF-8 Library.

   The GNU UTF-8 Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The GNU UTF-8 Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the GNU UTF-8 Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Generate tables for towlower, towupper, and the isw* functions. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

struct unicode_attribute unicode_attributes [0x110000];

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

  if (i >= 0x110000) {
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

static void fill_attributes (const char* unicodedata_filename)
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

  for (i = 0; i < 0x110000; i++)
    unicode_attributes[i].name = NULL;

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

static int isCLbothcase (unsigned int ch)
{
  unsigned int ch1 = uppercase(ch);
  unsigned int ch2 = lowercase(ch);
  return ((ch1 == ch || ch2 == ch)
          && (ch1 != ch2)
          && uppercase(ch1) == ch1
          && uppercase(ch2) == ch1
          && lowercase(ch1) == ch2
          && lowercase(ch2) == ch2
         );
}

/* Create uni_upcase.c, used by clisp. */
void output_clisp_upcase_table (void)
{
  int pages[0x1100];
  int p, p1, p2, i1, i2;
  const char* filename = "uni_upcase.c";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  fprintf(f, "/*\n");
  fprintf(f, " * %s\n", filename);
  fprintf(f, " *\n");
  fprintf(f, " * Common Lisp upcase table.\n");
  fprintf(f, " * Generated automatically by the gentables utility.\n");
  fprintf(f, " */\n");
  fprintf(f, "\n");
  for (p = 0; p < 0x1100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x1100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (isCLbothcase(ch) && (uppercase(ch) != ch)) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x1100; p++)
    if (pages[p]) {
      fprintf(f, "static const cint up_case_table_page%02x[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        fprintf(f, "  ");
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          unsigned int ch2 = (isCLbothcase(ch) ? uppercase(ch) : ch);
          int j = ((int)ch2 - (int)ch) & 0xffff;
          if (ch2 != ch + (short)j) {
            fprintf(stderr, "upper case maps 0x%04x to different plane\n", ch);
            exit(1);
          }
          fprintf(f, "0x%04x%s ", j, (8*i1+i2<255?",":" "));
        }
        fprintf(f, "/* 0x%02x-0x%02x */\n", 8*i1, 8*i1+7);
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "static const cint * const up_case_table[0x1100] = {\n");
  for (p1 = 0; p1 < 0x440; p1++) {
    fprintf(f, "  ");
    for (p2 = 0; p2 < 4; p2++) {
      p = 4*p1 + p2;
      if (pages[p])
        fprintf(f, "up_case_table_page%02x%s ", p, (p<0x1100-1?",":" "));
      else
        fprintf(f, "nop_page%s ", (p<0x1100-1?",":" "));
    }
    fprintf(f, "/* 0x%02x-0x%02x */\n", 4*p1, 4*p1+3);
  }
  fprintf(f, "};\n");
  fprintf(f, "\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

/* Create uni_downcase.c, used by clisp. */
void output_clisp_downcase_table (void)
{
  int pages[0x1100];
  int p, p1, p2, i1, i2;
  const char* filename = "uni_downcase.c";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  fprintf(f, "/*\n");
  fprintf(f, " * %s\n", filename);
  fprintf(f, " *\n");
  fprintf(f, " * Common Lisp downcase table.\n");
  fprintf(f, " * Generated automatically by the gentables utility.\n");
  fprintf(f, " */\n");
  fprintf(f, "\n");
  for (p = 0; p < 0x1100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x1100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (isCLbothcase(ch) && (lowercase(ch) != ch)) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x1100; p++)
    if (pages[p]) {
      fprintf(f, "static const cint down_case_table_page%02x[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        fprintf(f, "  ");
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          unsigned int ch2 = (isCLbothcase(ch) ? lowercase(ch) : ch);
          int j = ((int)ch2 - (int)ch) & 0xffff;
          if (ch2 != ch + (short)j) {
            fprintf(stderr, "lower case maps 0x%04x to different plane\n", ch);
            exit(1);
          }
          fprintf(f, "0x%04x%s ", j, (8*i1+i2<255?",":" "));
        }
        fprintf(f, "/* 0x%02x-0x%02x */\n", 8*i1, 8*i1+7);
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "static const cint * const down_case_table[0x1100] = {\n");
  for (p1 = 0; p1 < 0x440; p1++) {
    fprintf(f, "  ");
    for (p2 = 0; p2 < 4; p2++) {
      p = 4*p1 + p2;
      if (pages[p])
        fprintf(f, "down_case_table_page%02x%s ", p, (p<0x1100-1?",":" "));
      else
        fprintf(f, "nop_page%s ", (p<0x1100-1?",":" "));
    }
    fprintf(f, "/* 0x%02x-0x%02x */\n", 4*p1, 4*p1+3);
  }
  fprintf(f, "};\n");
  fprintf(f, "\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

static void output_copyright (FILE* f)
{
  fprintf(f, "/* Copyright (C) 1999-2001 Free Software Foundation, Inc.\n");
  fprintf(f, "   This file is part of the GNU UTF-8 Library.\n");
  fprintf(f, "\n");
  fprintf(f, "   The GNU UTF-8 Library is free software; you can redistribute it and/or\n");
  fprintf(f, "   modify it under the terms of the GNU Library General Public License as\n");
  fprintf(f, "   published by the Free Software Foundation; either version 2 of the\n");
  fprintf(f, "   License, or (at your option) any later version.\n");
  fprintf(f, "\n");
  fprintf(f, "   The GNU UTF-8 Library is distributed in the hope that it will be useful,\n");
  fprintf(f, "   but WITHOUT ANY WARRANTY; without even the implied warranty of\n");
  fprintf(f, "   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU\n");
  fprintf(f, "   Library General Public License for more details.\n");
  fprintf(f, "\n");
  fprintf(f, "   You should have received a copy of the GNU Library General Public\n");
  fprintf(f, "   License along with the GNU UTF-8 Library; see the file COPYING.LIB.  If not,\n");
  fprintf(f, "   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,\n");
  fprintf(f, "   Boston, MA 02111-1307, USA.  */\n");
}

/* Create toupper.h, used by libutf8. */
void output_toupper_table (void)
{
  int pages[0x1100];
  int p, p1, p2, i1, i2;
  const char* filename = "toupper.h";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  output_copyright(f);
  fprintf(f, "\n");
  fprintf(f, "/* toupper table */\n");
  fprintf(f, "/* Generated automatically by the gentables utility. */\n");
  fprintf(f, "\n");
  for (p = 0; p < 0x1100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x1100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (uppercase(ch) != ch) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x1100; p++)
    if (pages[p]) {
      fprintf(f, "static const short toupper_table_page%02x[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        fprintf(f, "  ");
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          unsigned int ch2 = uppercase(ch);
          int j = ((int)ch2 - (int)ch) & 0xffff;
          if (ch2 != ch + (short)j) {
            fprintf(stderr, "toupper maps 0x%04x to different plane\n", ch);
            exit(1);
          }
          fprintf(f, "0x%04x%s ", j, (8*i1+i2<255?",":" "));
        }
        fprintf(f, "/* 0x%02x-0x%02x */\n", 8*i1, 8*i1+7);
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "const short * const toupper_table[0x1100] = {\n");
  for (p1 = 0; p1 < 0x440; p1++) {
    fprintf(f, "  ");
    for (p2 = 0; p2 < 4; p2++) {
      p = 4*p1 + p2;
      if (pages[p])
        fprintf(f, "toupper_table_page%02x%s ", p, (p<0x1100-1?",":" "));
      else
        fprintf(f, "nop_page%s ", (p<0x1100-1?",":" "));
    }
    fprintf(f, "/* 0x%02x-0x%02x */\n", 4*p1, 4*p1+3);
  }
  fprintf(f, "};\n");
  fprintf(f, "\n");
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
void output_tolower_table (void)
{
  int pages[0x1100];
  int p, p1, p2, i1, i2;
  const char* filename = "tolower.h";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  output_copyright(f);
  fprintf(f, "\n");
  fprintf(f, "/* tolower table */\n");
  fprintf(f, "/* Generated automatically by the gentables utility. */\n");
  fprintf(f, "\n");
  for (p = 0; p < 0x1100; p++)
    pages[p] = 0;
  for (p = 0; p < 0x1100; p++)
    for (i1 = 0; i1 < 0x100; i1++) {
      unsigned int ch = 0x100*p + i1;
      if (lowercase(ch) != ch) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x1100; p++)
    if (pages[p]) {
      fprintf(f, "static const short tolower_table_page%02x[256] = {\n", p);
      for (i1 = 0; i1 < 32; i1++) {
        fprintf(f, "  ");
        for (i2 = 0; i2 < 8; i2++) {
          unsigned int ch = 256*p + 8*i1 + i2;
          unsigned int ch2 = lowercase(ch);
          int j = ((int)ch2 - (int)ch) & 0xffff;
          if (ch2 != ch + (short)j) {
            fprintf(stderr, "tolower maps 0x%04x to different plane\n", ch);
            exit(1);
          }
          fprintf(f, "0x%04x%s ", j, (8*i1+i2<255?",":" "));
        }
        fprintf(f, "/* 0x%02x-0x%02x */\n", 8*i1, 8*i1+7);
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "const short * const tolower_table[0x1100] = {\n");
  for (p1 = 0; p1 < 0x440; p1++) {
    fprintf(f, "  ");
    for (p2 = 0; p2 < 4; p2++) {
      p = 4*p1 + p2;
      if (pages[p])
        fprintf(f, "tolower_table_page%02x%s ", p, (p<0x1100-1?",":" "));
      else
        fprintf(f, "nop_page%s ", (p<0x1100-1?",":" "));
    }
    fprintf(f, "/* 0x%02x-0x%02x */\n", 4*p1, 4*p1+3);
  }
  fprintf(f, "};\n");
  fprintf(f, "\n");
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
void output_attribute_table (void)
{
  int table[0x110000];
  int pages[0x1100];
  int p, q, p1, p2, i;
  unsigned int ch;
  const char* filename = "attribute.h";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  output_copyright(f);
  fprintf(f, "\n");
  fprintf(f, "/* attribute table */\n");
  fprintf(f, "/* Generated automatically by the gentables utility. */\n");
  fprintf(f, "\n");
  for (ch = 0; ch < 0x110000; ch++) {
    int attributes = 0;
    if ((uppercase(ch) == ch || titlecase(uppercase(ch)) == ch)
        && lowercase(ch) != ch)
      attributes |= upper;
    if (lowercase(ch) == ch && uppercase(ch) != ch)
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
    table[ch] = attributes;
  }
  for (p = 0; p < 0x1100; p++) {
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
  for (p = 0; p < 0x1100; p++)
    if (pages[p] < 0) {
      fprintf(f, "static const unsigned char attribute_table_page%02x[256] = {\n", p);
      for (i = 0; i < 0x100; i++) {
        unsigned int ch = 256*p + i;
        int attributes = table[ch];
        int next = 0;
        fprintf(f, "  /* 0x%04x */ ", ch);
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
      fprintf(f, "\n");
    }
  fprintf(f, "const unsigned char * const attribute_table[0x1100] = {\n");
  for (p1 = 0; p1 < 0x880; p1++) {
    fprintf(f, "  ");
    for (p2 = 0; p2 < 2; p2++) {
      p = 2*p1 + p2;
      fprintf(f, "attribute_table_page%02x%s ", (pages[p] >= 0 ? pages[p] : p),
                 (p<0x1100-1?",":" "));
    }
    fprintf(f, "/* 0x%02x-0x%02x */\n", 2*p1, 2*p1+1);
  }
  fprintf(f, "};\n");
  fprintf(f, "\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

static int nonspacing (unsigned int ch)
{
  /* We use the "Non-spacing" property in PropList.txt here, because the
     SUSV2 spec (curses section) talks about "non-spacing wide characters". */
#if 0
  /* This code catches only a subset of the combining characters! */
  const char* combining = unicode_attributes[ch].combining;
  if (combining != NULL && strcmp(combining,"") && strcmp(combining,"0"))
    return 1;
#else
  if (unicode_attributes[ch].bidi != NULL && !strcmp(unicode_attributes[ch].bidi,"NSM"))
    return 1;
#endif
  /* Format control characters have width 0 as well. */
  if (unicode_attributes[ch].bidi != NULL && !strcmp(unicode_attributes[ch].category,"Cf"))
    return 1;
  /* Zero width characters have width 0 as well. */
  if (unicode_attributes[ch].name != NULL && !strncmp(unicode_attributes[ch].name,"ZERO WIDTH ",11))
    return 1;
  return 0;
}

/* Create nonspacing.h, used by libutf8. */
void output_nonspacing_table (void)
{
  int pages[0x440];
  int p, p1, p2, i1, i2, i3;
  const char* filename = "nonspacing.h";
  FILE* f = fopen(filename, "w");
  if (!f) {
    fprintf(stderr, "error during fopen of `%s'\n", filename);
    exit(1);
  }
  output_copyright(f);
  fprintf(f, "\n");
  fprintf(f, "/* Non-spacing attribute table */\n");
  fprintf(f, "/* Generated automatically by the gentables utility. */\n");
  fprintf(f, "\n");
  for (p = 0; p < 0x440; p++)
    pages[p] = 0;
  for (p = 0; p < 0x440; p++)
    for (i1 = 0; i1 < 0x400; i1++) {
      unsigned int ch = 0x400*p + i1;
      if (nonspacing(ch)) {
        pages[p] = 1;
        break;
      }
    }
  for (p = 0; p < 0x440; p++)
    if (pages[p]) {
      fprintf(f, "static const unsigned char nonspacing_table_page%02x[128] = {\n", 4*p);
      for (i1 = 0; i1 < 16; i1++) {
        fprintf(f, "  ");
        for (i2 = 0; i2 < 8; i2++) {
          unsigned char w = 0;
          for (i3 = 0; i3 < 8; i3++) {
            unsigned int ch = 0x400*p + 64*i1 + 8*i2 + i3;
            if (nonspacing(ch))
              w |= (1 << i3);
          }
          fprintf(f, "0x%02x%s ", w, (8*i1+i2<127?",":" "));
        }
        fprintf(f, "/* 0x%04x-0x%04x */\n", 0x400*p+64*i1, 0x400*p+64*i1+63);
      }
      fprintf(f, "};\n");
      fprintf(f, "\n");
    }
  fprintf(f, "static const unsigned char * const nonspacing_table[0x440] = {\n");
  for (p1 = 0; p1 < 0x110; p1++) {
    fprintf(f, "  ");
    for (p2 = 0; p2 < 4; p2++) {
      p = 4*p1 + p2;
      if (pages[p])
        fprintf(f, "nonspacing_table_page%02x%s ", 4*p, (p<0x440-1?",":" "));
      else
        fprintf(f, "NULL%s ", (p<0x440-1?",":" "));
    }
    fprintf(f, "/* 0x%04x-0x%04x */\n", 0x1000*p1, 0x1000*p1+0xfff);
  }
  fprintf(f, "};\n");
  fprintf(f, "\n");
  if (ferror(f)) {
    fprintf(stderr, "error writing on `%s'\n", filename);
    exit(1);
  }
  if (fclose(f)) {
    fprintf(stderr, "error closing `%s'\n", filename);
    exit(1);
  }
}

int main (int argc, char* argv[])
{
  if (argc != 2)
    exit(1);

  fill_attributes(argv[1]);

#if 0
  output_clisp_upcase_table();
  output_clisp_downcase_table();
#endif
  output_toupper_table();
  output_tolower_table();
  output_attribute_table();
  output_nonspacing_table();

  return 0;
}
