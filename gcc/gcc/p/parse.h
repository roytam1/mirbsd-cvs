/* A Bison parser, made by GNU Bison 2.0.  */

/* Skeleton parser for GLR parsing with Bison,
   Copyright (C) 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     prec_id = 258,
     prec_if = 259,
     prec_lower_than_error = 260,
     prec_import = 261,
     p_operator = 262,
     p_destructor = 263,
     p_constructor = 264,
     p_implementation = 265,
     p_initialization = 266,
     p_uses = 267,
     p_else = 268,
     p_and = 269,
     p_array = 270,
     p_begin = 271,
     p_case = 272,
     p_div = 273,
     p_do = 274,
     p_downto = 275,
     p_end = 276,
     p_file = 277,
     p_for = 278,
     p_function = 279,
     p_goto = 280,
     p_if = 281,
     p_in = 282,
     p_label = 283,
     p_mod = 284,
     p_nil = 285,
     p_not = 286,
     p_of = 287,
     p_or = 288,
     p_packed = 289,
     p_procedure = 290,
     p_to = 291,
     p_program = 292,
     p_record = 293,
     p_repeat = 294,
     p_set = 295,
     p_then = 296,
     p_type = 297,
     p_until = 298,
     p_var = 299,
     p_while = 300,
     p_with = 301,
     p_absolute = 302,
     p_abstract = 303,
     p_and_then = 304,
     p_as = 305,
     p_asm = 306,
     p_attribute = 307,
     p_bindable = 308,
     p_const = 309,
     p_external = 310,
     p_far = 311,
     p_finalization = 312,
     p_forward = 313,
     p_import = 314,
     p_inherited = 315,
     p_is = 316,
     p_near = 317,
     p_object = 318,
     p_only = 319,
     p_otherwise = 320,
     p_or_else = 321,
     p_pow = 322,
     p_restricted = 323,
     p_shl = 324,
     p_shr = 325,
     p_unit = 326,
     p_value = 327,
     p_virtual = 328,
     p_xor = 329,
     p_asmname = 330,
     p_c = 331,
     p_c_language = 332,
     p_Addr = 333,
     p_Assigned = 334,
     p_Dispose = 335,
     p_FormatString = 336,
     p_New = 337,
     p_Return = 338,
     p_Exit = 339,
     LEX_ID = 340,
     LEX_BUILTIN_PROCEDURE = 341,
     LEX_BUILTIN_PROCEDURE_WRITE = 342,
     LEX_BUILTIN_FUNCTION = 343,
     LEX_BUILTIN_FUNCTION_VT = 344,
     LEX_BUILTIN_VARIABLE = 345,
     LEX_INTCONST = 346,
     LEX_INTCONST_BASE = 347,
     LEX_STRCONST = 348,
     LEX_REALCONST = 349,
     LEX_CARET_WHITE = 350,
     LEX_STRUCTOR = 351,
     LEX_CARET_LETTER = 352,
     LEX_CONST_EQUAL = 353,
     LEX_BPPLUS = 354,
     LEX_BPMINUS = 355,
     LEX_RANGE = 356,
     LEX_ELLIPSIS = 357,
     LEX_RENAME = 358,
     LEX_SYMDIFF = 359,
     LEX_ASSIGN = 360,
     LEX_NE = 361,
     LEX_GE = 362,
     LEX_LE = 363,
     LEX_POWER = 364,
     LEX_CEIL_PLUS = 365,
     LEX_CEIL_MINUS = 366,
     LEX_FLOOR_PLUS = 367,
     LEX_FLOOR_MINUS = 368,
     LEX_CEIL_MULT = 369,
     LEX_CEIL_DIV = 370,
     LEX_FLOOR_MULT = 371,
     LEX_FLOOR_DIV = 372
   };
#endif
#define prec_id 258
#define prec_if 259
#define prec_lower_than_error 260
#define prec_import 261
#define p_operator 262
#define p_destructor 263
#define p_constructor 264
#define p_implementation 265
#define p_initialization 266
#define p_uses 267
#define p_else 268
#define p_and 269
#define p_array 270
#define p_begin 271
#define p_case 272
#define p_div 273
#define p_do 274
#define p_downto 275
#define p_end 276
#define p_file 277
#define p_for 278
#define p_function 279
#define p_goto 280
#define p_if 281
#define p_in 282
#define p_label 283
#define p_mod 284
#define p_nil 285
#define p_not 286
#define p_of 287
#define p_or 288
#define p_packed 289
#define p_procedure 290
#define p_to 291
#define p_program 292
#define p_record 293
#define p_repeat 294
#define p_set 295
#define p_then 296
#define p_type 297
#define p_until 298
#define p_var 299
#define p_while 300
#define p_with 301
#define p_absolute 302
#define p_abstract 303
#define p_and_then 304
#define p_as 305
#define p_asm 306
#define p_attribute 307
#define p_bindable 308
#define p_const 309
#define p_external 310
#define p_far 311
#define p_finalization 312
#define p_forward 313
#define p_import 314
#define p_inherited 315
#define p_is 316
#define p_near 317
#define p_object 318
#define p_only 319
#define p_otherwise 320
#define p_or_else 321
#define p_pow 322
#define p_restricted 323
#define p_shl 324
#define p_shr 325
#define p_unit 326
#define p_value 327
#define p_virtual 328
#define p_xor 329
#define p_asmname 330
#define p_c 331
#define p_c_language 332
#define p_Addr 333
#define p_Assigned 334
#define p_Dispose 335
#define p_FormatString 336
#define p_New 337
#define p_Return 338
#define p_Exit 339
#define LEX_ID 340
#define LEX_BUILTIN_PROCEDURE 341
#define LEX_BUILTIN_PROCEDURE_WRITE 342
#define LEX_BUILTIN_FUNCTION 343
#define LEX_BUILTIN_FUNCTION_VT 344
#define LEX_BUILTIN_VARIABLE 345
#define LEX_INTCONST 346
#define LEX_INTCONST_BASE 347
#define LEX_STRCONST 348
#define LEX_REALCONST 349
#define LEX_CARET_WHITE 350
#define LEX_STRUCTOR 351
#define LEX_CARET_LETTER 352
#define LEX_CONST_EQUAL 353
#define LEX_BPPLUS 354
#define LEX_BPMINUS 355
#define LEX_RANGE 356
#define LEX_ELLIPSIS 357
#define LEX_RENAME 358
#define LEX_SYMDIFF 359
#define LEX_ASSIGN 360
#define LEX_NE 361
#define LEX_GE 362
#define LEX_LE 363
#define LEX_POWER 364
#define LEX_CEIL_PLUS 365
#define LEX_CEIL_MINUS 366
#define LEX_FLOOR_PLUS 367
#define LEX_FLOOR_MINUS 368
#define LEX_CEIL_MULT 369
#define LEX_CEIL_DIV 370
#define LEX_FLOOR_MULT 371
#define LEX_FLOOR_DIV 372




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 118 "parse.y"
typedef union YYSTYPE {
  enum tree_code code;
  long itype;
  tree ttype;
} YYSTYPE;
/* Line 2089 of glr.c.  */
#line 272 "parse.h"
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

#if ! defined (YYLTYPE) && ! defined (YYLTYPE_IS_DECLARED)
typedef struct YYLTYPE
{

  int first_line;
  int first_column;
  int last_line;
  int last_column;

} YYLTYPE;
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;


