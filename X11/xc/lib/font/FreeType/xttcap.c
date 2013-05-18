/* ===EmacsMode: -*- Mode: C; tab-width:4; c-basic-offset: 4; -*- === */
/* ===FileName: ===
   Copyright (c) 1998 Takuya SHIOZAKI, All Rights reserved.
   Copyright (c) 1998 X-TrueType Server Project, All rights reserved. 
   Copyright (c) 2003 After X-TT Project, All rights reserved.

===Notice
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   1. Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
   2. Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
   OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
   OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
   SUCH DAMAGE.

   Major Release ID: X-TrueType Server Version 1.4 [Charles's Wain Release 0]

Notice===
 */
/* $XFree86: xc/lib/font/FreeType/xttcap.c,v 1.2 2004/02/24 01:13:04 dawes Exp $ */

/*
#include "xttversion.h"

static char const * const releaseID =
    _XTT_RELEASE_NAME;
*/

#include "fontmisc.h"
#ifndef FONTMODULE
#include <string.h>
#include <ctype.h>
#include <math.h>
#else
#include "Xmd.h"
#include "Xdefs.h"
#include "xf86_ansic.h"
#endif
/*
#include <X11/X.h>
#include <X11/Xmd.h>
#include <X11/Xfuncproto.h>
#include "xf86Module.h"
#include "xf86_ansic.h"
*/

#ifndef True
#define True (-1)
#endif /* True */
#ifndef False
#define False (0)
#endif /* False */

#include "xttcap.h"

#if 0
/*
  Prototypes for obsoleted OS (e.g. SunOS4)
 */

#if (defined(sun) && !(defined(SVR4) || defined(__SVR4)))
double strtod(char *str, char **ptr);
double strtol(char *str, char **ptr, int base);
#endif
#endif


/**************************************************************************
  Private Data Types
 */

/* Property Record List */
/* List Node */
typedef struct TagSPropRecValListNodeP
{
    SPropRecValContainerEntityP containerE;
    struct TagSPropRecValListNodeP *nextNode;
} SPropRecValListNodeP;


/**************************************************************************
  Tables
 */

/* valid record field */
static SPropertyRecord const validRecords[] =
{
    { "FontFile",               eRecTypeString  },
    { "FaceNumber",             eRecTypeString },
    { "AutoItalic",             eRecTypeDouble  },
    { "DoubleStrike",           eRecTypeString  },
    { "FontProperties",         eRecTypeBool    },
    { "ForceSpacing",           eRecTypeString  },
    { "ScaleBBoxWidth",         eRecTypeString  },
    { "ScaleWidth",             eRecTypeDouble  },
    { "EncodingOptions",        eRecTypeString  },
    { "Hinting",                eRecTypeBool    },
    { "VeryLazyMetrics",        eRecTypeBool    },
    { "CodeRange",              eRecTypeString  },
    { "EmbeddedBitmap",         eRecTypeString  },
    { "VeryLazyBitmapWidthScale", eRecTypeDouble  },
    { "ForceConstantSpacingCodeRange", eRecTypeString },
    { "ForceConstantSpacingMetrics", eRecTypeString },
    { "Dummy",                  eRecTypeVoid    }
};
static int const
numOfValidRecords = sizeof(validRecords)/sizeof(validRecords[0]);

/* correspondence between record name and cap variable name */
static struct {
    char const * capVariable;
    char const * recordName;
} const correspondRelations[] = {
    { "fn", "FaceNumber" },
    { "ai", "AutoItalic" },
    { "ds", "DoubleStrike" },
    { "fp", "FontProperties" },
    { "fs", "ForceSpacing" },
    { "bw", "ScaleBBoxWidth" },
    { "sw", "ScaleWidth" },
    { "eo", "EncodingOptions" },
    { "vl", "VeryLazyMetrics" },
    { "bs", "VeryLazyBitmapWidthScale" },
    { "cr", "CodeRange" },
    { "eb", "EmbeddedBitmap" },
    { "hi", "Hinting" },
    { "fc", "ForceConstantSpacingCodeRange" },
    { "fm", "ForceConstantSpacingMetrics" }
};
static int const
numOfCorrespondRelations
= sizeof(correspondRelations)/sizeof(correspondRelations[0]);

/**************************************************************************
  Functions
 */

#ifdef USE_TTP_FILE

#ifndef LEN_LINEBUF
#define LEN_LINEBUF 2048
#endif /* !def LEN_LINEBUF */

/* get one line */
static Bool /* True == Error, False == Success */
get_one_line(FILE *is, char *buf)
{
    Bool result = False;
    int count = 0;
    Bool flHead = True;
    Bool flSpace = False;
    Bool flInSingleQuote = False;
    Bool flInDoubleQuote = False;
    Bool flBackSlash = False;
    Bool flFirstElement = True;
    
    *buf = '\0';
    for (;;) {
        int c = fgetc(is);
        
        if (ferror(is)) {
            fprintf(stderr, "truetype font property file : read error.\n");
            result = True;
            break;
        }

        if (EOF == c) {
            if (flInSingleQuote || flInDoubleQuote) {
                fprintf(stderr,
                        "truetype font property file : unmatched quote.\n");
                result = True;
            }
            break;
        }
        if (flInSingleQuote) {
            if ('\'' == c) {
                /* end of single quoted string */
                flInSingleQuote = False;
                c = -1; /* NOT extract to buffer. */
            } else
                /* others, extract all character to buffer unconditionally. */
                ;
            goto trans;
        }
        if (flBackSlash) {
            /* escape --- when just before character is backslash,
               next character is escaped. */
            flBackSlash = False;
            if ('n' == c)
                /* newline */
                c = '\n';
            if ('\n' == c)
                /* ignore newline */
                c = -1;
            else
                /* others, extract all character to buffer unconditionally. */
                ;
            goto trans;
        }
        if ('\\' == c) {
            /* set flag to escape next character. */
            flBackSlash = True;
            c = -1; /* NOT extract to buffer. */
            goto trans;
        }
        if (flInDoubleQuote) {
            if ('"' == c) {
                /* end of double quoted string */
                flInDoubleQuote = False;
                c = -1; /* NOT extract to buffer. */
            } else
                /* others, extract all character to buffer unconditionally. */
                ;
            goto trans;
        }
        if ('#' == c) {
            /* skip comment till end of line. */
            while ('\n' != c) {
                c = fgetc(is);
                if (ferror(is)) {
                    fprintf(stderr,
                            "truetype font property file : read error.\n");
                    result = True;
                    break;
                }
                if (EOF == c) {
                    break;
                }
            }
            break;
        }
        if ('\'' == c) {
            /* into single quoted string */
            flInSingleQuote = True;
            c = -1; /* NOT extract to buffer. */
            goto trans;
        }
        if ('"' == c) {
            /* into double quoted string */
            flInDoubleQuote = True;
            c = -1; /* NOT extract to buffer. */
            goto trans;
        }
        if ('\n' == c)
            /* End of Line */
            break;
        if (isspace(c)) {
            /* convine multiple spaces */
            if (!flHead)
                /* except space at the head of line */
                flSpace = True;
            continue;
        }
      trans:
        /* set flHead to False, since current character is not white space
           when reaches here. */
        flHead = False;
        do {
          if (count>=LEN_LINEBUF-1) {
              /* overflow */
              fprintf(stderr,
                      "truetype font property file : too long line.\n");
              result = True;
              goto quit;
          }
          if (flSpace) {
              /* just before characters is white space, but
                 current character is not WS. */
              if (flFirstElement) {
                  /* this spaces is the first cell(?) of white spaces. */
                  flFirstElement = False;
                  /* separate record name and record value */
                  *buf = (char)0xff;
              } else
                  *buf = ' ';
              flSpace = False;
          } else
              if (-1 != c) {
                  *buf = c;
                  c = -1; /* invalidate */
              } else
                  /* skip */
                  buf--;
          buf++;
        } while (-1 != c); /* when 'c' is not -1, it means
                              that 'c' contains an untreated character. */
    }
    *buf = '\0';

  quit:
    return result;
}

/* parse one line */
static Bool /* True == Error, False == Success */
parse_one_line(SDynPropRecValList *pThisList, FILE *is)
{
    Bool result = False;
    char *buf = NULL;
    char *recordHead, *valueHead = NULL;
    
    if (NULL == (buf = xalloc(LEN_LINEBUF))) {
        fprintf(stderr,
                "truetype font property file : cannot allocate memory.\n");
        result = True;
        goto abort;
    }
    {
        recordHead = buf;
/*        refRecordValue->refRecordType = NULL;*/
        do {
            if (get_one_line(is, buf)) {
                result = True;
                goto quit;
            }
            if (feof(is)) {
                if ('\0' == *buf)
                    goto quit;
                break;
            }
        } while ('\0' == *buf);

        if (NULL != (valueHead = strchr(buf, 0xff))) {
            *valueHead = '\0';
            valueHead++;
        } else
            valueHead = buf+strlen(buf);
#if 0
        fprintf(stderr,
                "truetype font property file : \n"
                "recName:\"%s\"\nvalue:\"%s\"\n",
                recordHead, valueHead);
#endif
        result = SPropRecValList_add_record(pThisList, recordHead, valueHead);
    }
  quit:
    xfree(buf);
  abort:    
    return result;
}

/* Read Property File */
Bool /* True == Error, False == Success */
SPropRecValList_read_prop_file(SDynPropRecValList *pThisList,
                               char const * const strFileName)
{
    Bool result = False;
    FILE *is;
    
#if 1
    if (!strcmp(strFileName, "-"))
        is = stdin;
    else
#endif
        is = fopen(strFileName, "r");
    if (NULL == is) {
        fprintf(stderr, "truetype font property : cannot open file %s.\n",
                strFileName);
        result = True;
        goto abort;
    }
    {
        for (;;) {
            if (False != (result = parse_one_line(pThisList, is)))
                goto quit;
            if (feof(is))
                break;
        }
    }
  quit:
#if 1
    if (strcmp(strFileName, "-"))
#endif
        fclose(is);
  abort:
    return result;
}
#endif /* USE_TTP_FILE */

/* get property record type by record name */
static Bool /* True == Found, False == Not Found */
get_record_type_by_name(SPropertyRecord const ** const refRefRecord, /*result*/
                        char const *strName)
{
    Bool result = False;
    int i;
    
    *refRefRecord = NULL;
    for (i=0; i<numOfValidRecords; i++) {
        if (!mystrcasecmp(validRecords[i].strRecordName, strName)) {
            result = True;
            *refRefRecord = &validRecords[i];
            break;
        }
    }
    
    return result;
}

/* Constructor for Container Node */
Bool /* True == Error, False == Success */
SPropRecValList_new(SDynPropRecValList *pThisList)
{
    Bool result = False;
    
    pThisList->headNode = NULL;

    return result;
}

/* Destructor for Container List */
Bool /* True == Error, False == Success */
SPropRecValList_delete(SDynPropRecValList *pThisList)
{
    Bool result = False;
    SPropRecValListNodeP *p, *np;

    for (p=pThisList->headNode; NULL!=p; p=np) {
        np = p->nextNode;
        switch (p->containerE.refRecordType->recordType) {
        case eRecTypeInteger:
            break;
        case eRecTypeDouble:
            break;
        case eRecTypeBool:
            break;
        case eRecTypeString:
            if (SPropContainer_value_str(&p->containerE))
                xfree((void*)SPropContainer_value_str(&p->containerE));
            break;
        case eRecTypeVoid:
            break;
        }
        xfree(p);
    }
    
    pThisList->headNode = NULL;

    return result;
}

#ifdef DUMP
void
SPropRecValList_dump(SRefPropRecValList *pThisList)
{
    SPropRecValListNodeP *p;
    for (p=pThisList->headNode; NULL!=p; p=p->nextNode) {
        switch (p->containerE.refRecordType->recordType) {
        case eRecTypeInteger:
            fprintf(stderr, "%s = %d\n",
                    p->containerE.refRecordType->strRecordName,
                    p->containerE.uValue.integerValue);
            break;
        case eRecTypeDouble:
            fprintf(stderr, "%s = %f\n",
                    p->containerE.refRecordType->strRecordName,
                    p->containerE.uValue.doubleValue);
            break;
        case eRecTypeBool:
            fprintf(stderr, "%s = %s\n",
                    p->containerE.refRecordType->strRecordName,
                    p->containerE.uValue.boolValue
                    ? "True":"False");
            break;
        case eRecTypeString:
            fprintf(stderr, "%s = \"%s\"\n",
                    p->containerE.refRecordType->strRecordName,
                    p->containerE.uValue.dynStringValue);
            break;
        case eRecTypeVoid:
            fprintf(stderr, "%s = void\n",
                    p->containerE.refRecordType->strRecordName);
            break;
        }
    }
}
#endif

/* Add Property Record Value */
extern Bool /* True == Error, False == Success */
SPropRecValList_add_record(SDynPropRecValList *pThisList,
                           char const * const recordName,
                           char const * const strValue)
{
    Bool result = False;
    SPropRecValContainerEntityP tmpContainerE;

    if (get_record_type_by_name(&tmpContainerE.refRecordType, recordName)) {
        switch (tmpContainerE.refRecordType->recordType) {
        case eRecTypeInteger:
            {
                int val;
                char *endPtr;
                    
                val = strtol(strValue, &endPtr, 0);
                if ('\0' != *endPtr) {
                    fprintf(stderr,
                            "truetype font property : "
                            "%s record needs integer value.\n",
                            recordName);
                    result = True;
                    goto quit;
                }
                SPropContainer_value_int(&tmpContainerE) = val;
            }
            break;
        case eRecTypeDouble:
            {
                double val;
                char *endPtr;
                    
                val = strtod(strValue, &endPtr);
                if ('\0' != *endPtr) {
                    fprintf(stderr,
                            "truetype font property : "
                            "%s record needs floating point value.\n",
                            recordName);
                    result = True;
                    goto quit;
                }
                SPropContainer_value_dbl(&tmpContainerE) = val;
            }
            break;
        case eRecTypeBool:
            {
                Bool val;
                
                if (!mystrcasecmp(strValue, "yes"))
                    val = True;
                else if (!mystrcasecmp(strValue, "y"))
                    val = True;
                else if (!mystrcasecmp(strValue, "on"))
                    val = True;
                else if (!mystrcasecmp(strValue, "true"))
                    val = True;
                else if (!mystrcasecmp(strValue, "t"))
                    val = True;
                else if (!mystrcasecmp(strValue, "ok"))
                    val = True;
                else if (!mystrcasecmp(strValue, "no"))
                    val = False;
                else if (!mystrcasecmp(strValue, "n"))
                    val = False;
                else if (!mystrcasecmp(strValue, "off"))
                    val = False;
                else if (!mystrcasecmp(strValue, "false"))
                    val = False;
                else if (!mystrcasecmp(strValue, "f"))
                    val = False;
                else if (!mystrcasecmp(strValue, "bad"))
                    val = False;
                else {
                    fprintf(stderr,
                            "truetype font property : "
                            "%s record needs boolean value.\n",
                            recordName);
                    result = True;
                    goto quit;
                }
                SPropContainer_value_bool(&tmpContainerE) = val;
            }
            break;
        case eRecTypeString:
            {
                char *p;
                    
                if (NULL == (p = (char *)xalloc(strlen(strValue)+1))) {
                    fprintf(stderr,
                            "truetype font property : "
                            "cannot allocate memory.\n");
                    result = True;
                    goto quit;
                }
                strcpy(p, strValue);
                SPropContainer_value_str(&tmpContainerE) = p;
            }
            break;
        case eRecTypeVoid:
            if ('\0' != *strValue) {
                fprintf(stderr,
                        "truetype font property : "
                        "%s record needs void.\n", recordName);
                result = True;
            }
            break;
        }
        {
            /* add to list */
            SPropRecValListNodeP *newNode;
            
            if (NULL == (newNode =
                         (SPropRecValListNodeP *)xalloc(sizeof(*newNode)))) {
                fprintf(stderr,
                        "truetype font property : "
                        "cannot allocate memory.\n");
                result = True;
                goto quit;
            }
            newNode->nextNode = pThisList->headNode;
            newNode->containerE = tmpContainerE;
            tmpContainerE.refRecordType = NULL; /* invalidate --
                                                   disown value handle. */
            pThisList->headNode = newNode;
        }
    } else {
        /* invalid record name */
        fprintf(stderr,
                "truetype font : "
                "invalid record name \"%s.\"\n", recordName);
        result = True;
    }

 quit:
    return result;
}


/* Search Property Record */
Bool /* True == Hit, False == Miss */
SPropRecValList_search_record(SRefPropRecValList *pThisList,
                              SPropRecValContainer *refRecValue,
                              char const * const recordName)
{
    Bool result = False;
    SPropRecValListNodeP *p;
    
    *refRecValue = NULL;
    for (p=pThisList->headNode; NULL!=p; p=p->nextNode) {
        if (!mystrcasecmp(p->containerE.refRecordType->strRecordName,
                          recordName)) {
            *refRecValue = &p->containerE;
            result = True;
            break;
        }
    }

    return result;
}


/* Parse TTCap */
Bool /* True == Error, False == Success */
SPropRecValList_add_by_font_cap(SDynPropRecValList *pThisList,
                                char const *strCapHead)
{
    Bool result = False;
    /*    SPropertyRecord const *refRecordType; */
    char const *term;
    
    if (NULL == (term = strrchr(strCapHead, ':')))
        goto abort;

    {
        /* for xfsft compatible */
        char const *p;
        for (p=term-1; p>=strCapHead; p--) {
            if ( ':'==*p ) {
                /*
                 * :num:filename
                 * ^p  ^term
                 */
                if ( p!=term ) {
                    int len = term-p-1;
                    char *value;

                    len = term-p-1;
                    value=(char *)xalloc(len+1);
                    memcpy(value, p+1, len);
                    value[len]='\0';
                    SPropRecValList_add_record(pThisList,
                                               "FaceNumber",
                                               value);
                    xfree(value);
                    term=p;
                }
                break;
            }
            if ( !isdigit(*p) )
                break;
        }
    }

    while (strCapHead<term) {
        int i;
        char const *nextColon = strchr(strCapHead, ':');
        if (0<nextColon-strCapHead) {
            char *duplicated = (char *)xalloc((nextColon-strCapHead)+1);
            {
                char *value;
            
                memcpy(duplicated, strCapHead, nextColon-strCapHead);
                duplicated[nextColon-strCapHead] = '\0';
                if (NULL != (value=strchr(duplicated, '='))) {
                    *value = '\0';
                    value++;
                } else
                    value = &duplicated[nextColon-strCapHead];
            
                for (i=0; i<numOfCorrespondRelations; i++) {
                    if (!mystrcasecmp(correspondRelations[i].capVariable,
                                      duplicated)) {
                        if (SPropRecValList_add_record(pThisList,
                                                        correspondRelations[i]
                                                       .recordName,
                                                       value))
                            break;
                        goto next;
                    }
                }
                fprintf(stderr, "truetype font : Illegal Font Cap.\n");
                result = True;
                break;
              next:
                ;
            }
            xfree(duplicated);
        }
        strCapHead = nextColon+1;
    }
    
    /*  quit: */
  abort:
    return result;
}


/**************************************************************************
  Functions (xttmisc)
 */

/* compare strings, ignoring case */
Bool /* False == equal, True == not equal */
mystrcasecmp(char const *s1, char const *s2)
{
    Bool result = True;
    
#if (defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) ||\
     defined(__bsdi__)) && !defined(FONTMODULE)
    /* 4.4BSD has strcasecmp function. */
    result = strcasecmp(s1, s2) != 0;
#else
    {
        unsigned int len1 = strlen(s1);
        
        if (len1 == strlen(s2)) {
            int i;
            for (i=0; i<len1; i++) {
                if (toupper(*s1++) != toupper(*s2++))
                    goto quit;
            }
            result = False;
        } else
            /* len1 != len2 -> not equal*/
            ;
    }
  quit:
    ;
#endif

    return result;
}


/* strdup clone with using the allocator of X server */
char *
XttXstrdup(char const *str)
{
    char *result;
    
    result = (char *)xalloc(strlen(str)+1);

    if (result)
        strcpy(result, str);

    return result;
}


#if 0
int main()
{
    SDynPropRecValList list;
    
    SPropRecValList_new(&list);
    SPropRecValList_read_prop_file(&list, "-");
    SPropRecValList_dump(&list);
    SPropRecValList_delete(&list);
    
    return 0;
}
#endif

/* end of file */
