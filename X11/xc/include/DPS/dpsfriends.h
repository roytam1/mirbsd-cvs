/*
 *  dpsfriends.h -- Low-level interface to the Display PostScript Library.
 *
 * (c) Copyright 1988-1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */
/* $XFree86: xc/include/DPS/dpsfriends.h,v 1.5 2002/08/20 09:48:18 herrb Exp $ */

#ifndef	DPSFRIENDS_H
#define	DPSFRIENDS_H

#include <DPS/dpsconfig.h>

/*=== CONSTANTS ===*/

/* TokenType values, used to specify the format of numeric values
   for the system on which the client library is built. See DPS language
   reference manual */

#define DPS_HI_IEEE	128
#define DPS_LO_IEEE	129
#define DPS_HI_NATIVE	130
#define DPS_LO_NATIVE	131
  
#ifndef DPS_DEF_TOKENTYPE

#if IEEEFLOAT

#if SWAPBITS
#define DPS_DEF_TOKENTYPE DPS_LO_IEEE
#else /* SWAPBITS */
#define DPS_DEF_TOKENTYPE DPS_HI_IEEE
#endif /* SWAPBITS */

#else /* IEEEFLOAT */

#if SWAPBITS
#define DPS_DEF_TOKENTYPE DPS_LO_NATIVE
#else /* SWAPBITS */
#define DPS_DEF_TOKENTYPE DPS_HI_NATIVE
#endif /* SWAPBITS */

#endif /* IEEEFLOAT */

#endif /* DPS_DEF_TOKENTYPE */

  /* DPS_DEF_TOKENTYPE is the specification code for the form of binary
     object sequences generated by PSWrap. The C code generated by pswrap
     references this name. DPS_DEF_TOKENTYPE is system-dependent. */


/* --- binary object sequence support --- */

/* Object attributes & types: Values for attributedTypes */

#define DPS_LITERAL	0
#define DPS_EXEC	0x080

  /* Attribute masks */


#define DPS_NULL	0
#define DPS_INT		1
#define DPS_REAL	2
#define DPS_NAME	3
#define DPS_BOOL	4
#define DPS_STRING	5
#define DPS_IMMEDIATE	6
#define DPS_ARRAY	9
#define	DPS_MARK	10

  /* Type values */


/* Object sequence constants */

#define DPS_HEADER_SIZE		4
#define DPS_EXT_HEADER_SIZE	8


/*=== TYPES ===*/ 
     
typedef enum {
  dps_ascii, dps_binObjSeq, dps_encodedTokens
  } DPSProgramEncoding;
  /* Defines the 3 possible encodings of PostScript language programs. */
     
typedef enum {
  dps_indexed, dps_strings
  } DPSNameEncoding;
  /* Defines the 2 possible encodings for user names in the
     dps_binObjSeq and dps_encodedTokens forms of PostScript language
     programs. */     
  
typedef enum {
  dps_tBoolean,
  dps_tChar,	dps_tUChar,
  dps_tFloat,	dps_tDouble,
  dps_tShort,	dps_tUShort,
  dps_tInt,	dps_tUInt,
  dps_tLong,	dps_tULong } DPSDefinedType;
  
struct _t_DPSContextRec;

  /* Enumerates the C data types that can be used to describe wrap
     parameters. */

typedef void (*DPSContextProc)(
			       struct _t_DPSContextRec *ctxt
);

typedef void (*DPSContextBufProc)(
				  struct _t_DPSContextRec *ctxt, char *buf,
				  unsigned int count
);

typedef void (*DPSContextTypedArrayProc)(
					 struct _t_DPSContextRec *ctxt,
					 DPSDefinedType type,
					 char *array, unsigned int length
);

typedef void (*DPSWriteNumStringProc)(
				         struct _t_DPSContextRec *ctxt,
					 DPSDefinedType type,
					 const void *array,
					 unsigned int count,
					 int scale
);

typedef struct {
  DPSContextBufProc BinObjSeqWrite;
       /* Begin a new binary object sequence. 'buf' contains 'count'
	  bytes of a binary object sequence. 'buf' must point to the
	  beginning of a sequence, which includes at least the header
	  and the entire top-level sequence of objects.  It may also
	  include subsidiary array elements and/or string chars.
	  Writes PostScript language as specified by the
	  encoding variables of ctxt, doing appropriate conversions as
	  needed. 'buf' and its contents must remain valid until the
	  entire binary object sequence has been sent. */

  DPSContextTypedArrayProc WriteTypedObjectArray;
       /* 'array' points at an array of 'length' elements of 'type'.
	  'array' contains the element values for the body of a subsidiary
	  array in a binary object sequence. Writes PostScript language
	  as specified by the 4 format and encoding variables of ctxt, doing
	  appropriate conversions as needed. 'array' and its contents must
	  remain valid until the entire binary object sequence has been sent */

  DPSContextBufProc WriteStringChars;
       /* Used both to implement DPSWritePostScript and to send the bodies of
          strings in binary object sequences. 'buf' contains 'count' bytes.
	  For the latter, 'buf' and its contents must remain valid until the
	  entire binary object sequence has been sent.*/

  DPSContextBufProc WriteData;
       /* See DPSWriteData in dpsclient.h */

  DPSContextBufProc WritePostScript;
       /* See DPSWritePostScript in dpsclient.h */

  DPSContextProc FlushContext;
       /* See DPSFlushContext in dpsclient.h */

  DPSContextProc ResetContext;
       /* See DPSResetContext in dpsclient.h */

  DPSContextProc UpdateNameMap;
       /* This routine is called if the context's space's name map is
          out-of-sync with that of the client library's name map. It may
          send a series of "defineusername" commands to the service. */

  DPSContextProc AwaitReturnValues;
       /* Called to receive return values.
          ctxt->resultTableLength and ctxt->resultTable must have been
          set previously. Returns when all expected results are received.
     
          This is normally called from wraps. It is unusual for an application
          program to call this directly.
     
          See the definitions of DPSResultsRec and DPSContextRec for more info.
	  */

  DPSContextProc Interrupt;
       /* See DPSInterrupt in dpsclient.h */

  DPSContextProc DestroyContext;
       /* See DPSDestroyContext in dpsclient.h */

  DPSContextProc WaitContext;
       /* See DPSWaitContext in dpsclient.h */

  DPSWriteNumStringProc WriteNumString;
       /* Write a number string, possibly marking it to be converted into
	  an array depending upon the context flags. */

} DPSProcsRec, *DPSProcs;

  /* The DPSProcsRec may be extended to include system-specific items */

struct _t_DPSSpaceRec;

typedef void (*DPSSpaceProc)(
			     struct _t_DPSSpaceRec *space
);

typedef struct {
  DPSSpaceProc DestroySpace;
       /* See DPSDestroySpace in dpsclient.h */

} DPSSpaceProcsRec, *DPSSpaceProcs;
  
  /* The DPSSpaceProcsRec may be extended to include system-specific items */
  
typedef struct {
  DPSDefinedType type;
  int count;
  char *value;
} DPSResultsRec, *DPSResults;
  
  /* A DPSResultsRec defines one of the formal result args of a wrapped
     procedure.  The 'type' field specifies the formal type of the
     return value. The 'count' field specifies the number of values
     expected (this supports array formals). The 'value' field points
     to the location of the first value; the storage beginning there
     must have room for count values of type.   If 'count' == -1, then
     'value' points to a scalar (single) result arg. */

typedef struct _t_DPSSpaceRec {
  DPSSpaceProcs procs;
} DPSSpaceRec, *DPSSpace;

  /* A DPSSpaceRec provides a representation of a space.
     
     The DPSSpaceRec may be extended to include system-specific items.

     BEWARE an implementation of the DPS client library is also likely to
     extend the DPSSpaceRec to include implementation-dependent information
     in additional fields. */

typedef struct _t_DPSContextExtensionRec {
  int extensionId;
  struct _t_DPSContextExtensionRec *next;
} DPSContextExtensionRec;

struct _t_DPSContextRec;

typedef struct _t_DPSContextRec {
  char *priv;
  DPSSpace space;
  DPSProgramEncoding programEncoding;
  DPSNameEncoding nameEncoding;
  DPSProcs procs;
  void (*textProc)(struct _t_DPSContextRec *, char *, long unsigned);
  void (*errorProc)(struct _t_DPSContextRec *, int, long unsigned, long unsigned);
  DPSResults resultTable;
  unsigned int resultTableLength;
  struct _t_DPSContextRec *chainParent, *chainChild;
  unsigned int contextFlags;
  DPSContextExtensionRec *extension;
} DPSContextRec, *DPSContext;
  
  /* A DPSContextRec provides a representation of a context.
  
     The 'priv' field is provided for use by application code. It is
     initialized to NULL and is not touched thereafter by the client
     library implementation.
	 
     The 'space' field is the space to which the context belongs.  The
     'programEncoding' and 'nameEncoding' fields describe the encodings
     preferred by the context (server). The values in these fields are
     established when the DPSContext is created and cannot be changed
     therafter. The 'procs' field points to a vector of procedures
     (in a DPSProcsRec) that implement the context operations.

     The 'textProc' and 'errorProc' are called by the client library
     implementation to dispose of ascii text and errors, respectively, that
     the PostScript interpreter produces.
     
     The 'resultTableLength' and 'resultTable' fields define the number, type
     and location of values expected back from the PostScript interpreter.
     They should be set up before writing any PostScript language that
     may return values.
     
     The chainParent field is non-NIL if this context automatically receives
     a copy of any PostScript language sent to the referenced (parent) context.
     
     The chainChild field is non-NIL if this context automatically sends
     a copy of any PostScript language it receives to the referenced (child)
     context.
     
     The contextFlags parameter contains a set of bit flags.  The bits 0-15
     are reserved for system-independent flags, bits 16-31 for
     system-specific flags.

     The extension parameter points to a linked list of extension records
     to allow toolkit to associate arbitrary data with contexts.

     NOTE the client library implementation extends the DPSContextRec to
     include implementation-dependent information in additional fields.
     
     You may read the fields of a DPSContextRec directly, but you should
     never modify them directly. Use the macros provided for that purpose. */

#define DPS_FLAG_SYNC			0x1
#define DPS_FLAG_CONVERT_NUMSTRINGS	0x2
#define DPS_FLAG_NO_BINARY_CONVERSION	0x4
#define DPS_FLAG_USE_ABBREVS		0x8

/* -- binary object sequence support -- */

#define DPSSYSNAME	0x0FFFF		/* unsigned rep. of -1 */

typedef struct {
    unsigned char attributedType;
    unsigned char tag;
    unsigned short length;
    int val;
} DPSBinObjGeneric;	/* boolean, int, string, name and array */


typedef struct {
    unsigned char attributedType;
    unsigned char tag;
    unsigned short length;
    float realVal;
} DPSBinObjReal;	/* float */


typedef struct {
    unsigned char attributedType;
    unsigned char tag;
    unsigned short length;
    union {
        int integerVal;
        float realVal;
        int nameVal;    /* offset or index */
        int booleanVal;
        int stringVal;  /* offset */
        int arrayVal;  /* offset */
    } val;
} DPSBinObjRec, *DPSBinObj;

typedef struct {
    unsigned char tokenType;
    unsigned char nTopElements;
    unsigned short length;
    DPSBinObjRec objects[1];
} DPSBinObjSeqRec, *DPSBinObjSeq;

typedef struct {
    unsigned char tokenType;
    unsigned char escape;  /* zero if this is an extended sequence */
    unsigned short nTopElements;
    unsigned length;
    DPSBinObjRec objects[1];
} DPSExtendedBinObjSeqRec, *DPSExtendedBinObjSeq;
    
/*=== SYNCHRONIZATION MACRO ===*/

#ifndef NeXTSTEP
#define DPSSYNCHOOK(ctxt) \
	if ((ctxt)->contextFlags & DPS_FLAG_SYNC) DPSWaitContext(ctxt);
#endif /* NeXT */

/*=== PROCEDURES ===*/

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void DPSAwaitReturnValues(DPSContext ctxt);
  
extern void DPSUpdateNameMap(DPSContext ctxt);
  
extern void DPSBinObjSeqWrite(DPSContext ctxt, char *buf, unsigned int count);
  
extern DPSContext DPSPrivCurrentContext(void);
    
extern void DPSWriteStringChars(DPSContext ctxt, char *buf,
				unsigned int count);
  
extern void DPSWriteNumString(DPSContext ctxt, DPSDefinedType type,
			      char *data, unsigned int size, int scale);
  
extern void DPSWriteTypedObjectArray(DPSContext ctxt, DPSDefinedType type,
				     char *array, unsigned int length);

extern void DPSSetResultTable(DPSContext ctxt, DPSResults tbl,
			      unsigned int len);
  

/* Support for user names */

extern void DPSMapNames(DPSContext ctxt, unsigned int nNames, char **names,
			int **indices);
  
  /* This routine assigns indices to the given user names. It is
     called once for each wrapped procedure. The parameters 'nNames' and
     'names' define an array of strings which are the user names. The
     parameter 'indices' is an array of (int *) which are the locations
     in which to store the indices. The caller must ensure that the string
     pointers remain valid after the return. 
     
     As a storage optimization, DPSMapNames will interpret a NIL
     value in the names array as the previous valid string in
     the name array. Effectively, if names[n] == NIL, DPSMapNames
     will decrement n until names[] is non-NIL and use that string.
     names[0] must be non-NIL. */
     
extern char *DPSNameFromIndex(long int index);

  /* This routine returns the text for the user name with the given index. 
     The string returned is owned by the library (treat it as readonly). */

extern DPSContextExtensionRec *DPSGetContextExtensionRec(DPSContext ctxt,
							 int extensionId);

  /* This procedure finds the context extension record with the given id */

extern void DPSAddContextExtensionRec(DPSContext ctxt,
				      DPSContextExtensionRec *rec);

  /* This procedure adds a context extension record */

extern DPSContextExtensionRec *DPSRemoveContextExtensionRec(DPSContext ctxt,
							    int extensionId);

  /* This procedure removes a context extension record */

extern int DPSGenerateExtensionRecID(void);

  /* This procedure generates a unique extension record id. */

extern void DPSWaitContext(DPSContext ctxt);

  /* Waits until the PostScript interpreter is ready for more input to
     this context.  This is useful for synchronizing an application
     with the DPS server.

     If 'ctxt' represents an invalid context, for example because
     the context has terminated in the server, the dps_err_invalidContext
     error will be reported via ctxt's error proc. */
  
#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* DPSFRIENDS_H */
