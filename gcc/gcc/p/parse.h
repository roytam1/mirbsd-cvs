/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for GLR parsing with Bison,
   Copyright (C) 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

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
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     prec_lower_than_error = 258,
     prec_if = 259,
     prec_import = 260,
     p_uses = 261,
     p_else = 262,
     p_and = 263,
     p_array = 264,
     p_begin = 265,
     p_case = 266,
     p_div = 267,
     p_do = 268,
     p_downto = 269,
     p_end = 270,
     p_file = 271,
     p_for = 272,
     p_function = 273,
     p_goto = 274,
     p_if = 275,
     p_in = 276,
     p_label = 277,
     p_mod = 278,
     p_nil = 279,
     p_not = 280,
     p_of = 281,
     p_or = 282,
     p_packed = 283,
     p_procedure = 284,
     p_to = 285,
     p_program = 286,
     p_record = 287,
     p_repeat = 288,
     p_set = 289,
     p_then = 290,
     p_type = 291,
     p_until = 292,
     p_var = 293,
     p_while = 294,
     p_with = 295,
     p_absolute = 296,
     p_abstract = 297,
     p_and_then = 298,
     p_as = 299,
     p_asm = 300,
     p_attribute = 301,
     p_bindable = 302,
     p_const = 303,
     p_constructor = 304,
     p_destructor = 305,
     p_external = 306,
     p_far = 307,
     p_finalization = 308,
     p_forward = 309,
     p_implementation = 310,
     p_import = 311,
     p_inherited = 312,
     p_initialization = 313,
     p_is = 314,
     p_near = 315,
     p_object = 316,
     p_only = 317,
     p_operator = 318,
     p_otherwise = 319,
     p_or_else = 320,
     p_pow = 321,
     p_qualified = 322,
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
     p_class = 333,
     p_override = 334,
     p_reintroduce = 335,
     p_Addr = 336,
     p_Assigned = 337,
     p_Dispose = 338,
     p_Exit = 339,
     p_FormatString = 340,
     p_New = 341,
     p_Return = 342,
     LEX_INTCONST = 343,
     LEX_INTCONST_BASE = 344,
     LEX_STRCONST = 345,
     LEX_REALCONST = 346,
     LEX_BUILTIN_PROCEDURE = 347,
     LEX_BUILTIN_PROCEDURE_WRITE = 348,
     LEX_BUILTIN_FUNCTION = 349,
     LEX_ID = 350,
     LEX_CARET_WHITE = 351,
     LEX_CARET_LETTER = 352,
     LEX_ASSIGN = 353,
     LEX_RENAME = 354,
     LEX_RANGE = 355,
     LEX_ELLIPSIS = 356,
     LEX_CONST_EQUAL = 357,
     LEX_SYMDIFF = 358,
     LEX_NE = 359,
     LEX_GE = 360,
     LEX_LE = 361,
     LEX_POWER = 362,
     LEX_BPPLUS = 363,
     LEX_BPMINUS = 364,
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
/* Tokens.  */
#define prec_lower_than_error 258
#define prec_if 259
#define prec_import 260
#define p_uses 261
#define p_else 262
#define p_and 263
#define p_array 264
#define p_begin 265
#define p_case 266
#define p_div 267
#define p_do 268
#define p_downto 269
#define p_end 270
#define p_file 271
#define p_for 272
#define p_function 273
#define p_goto 274
#define p_if 275
#define p_in 276
#define p_label 277
#define p_mod 278
#define p_nil 279
#define p_not 280
#define p_of 281
#define p_or 282
#define p_packed 283
#define p_procedure 284
#define p_to 285
#define p_program 286
#define p_record 287
#define p_repeat 288
#define p_set 289
#define p_then 290
#define p_type 291
#define p_until 292
#define p_var 293
#define p_while 294
#define p_with 295
#define p_absolute 296
#define p_abstract 297
#define p_and_then 298
#define p_as 299
#define p_asm 300
#define p_attribute 301
#define p_bindable 302
#define p_const 303
#define p_constructor 304
#define p_destructor 305
#define p_external 306
#define p_far 307
#define p_finalization 308
#define p_forward 309
#define p_implementation 310
#define p_import 311
#define p_inherited 312
#define p_initialization 313
#define p_is 314
#define p_near 315
#define p_object 316
#define p_only 317
#define p_operator 318
#define p_otherwise 319
#define p_or_else 320
#define p_pow 321
#define p_qualified 322
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
#define p_class 333
#define p_override 334
#define p_reintroduce 335
#define p_Addr 336
#define p_Assigned 337
#define p_Dispose 338
#define p_Exit 339
#define p_FormatString 340
#define p_New 341
#define p_Return 342
#define LEX_INTCONST 343
#define LEX_INTCONST_BASE 344
#define LEX_STRCONST 345
#define LEX_REALCONST 346
#define LEX_BUILTIN_PROCEDURE 347
#define LEX_BUILTIN_PROCEDURE_WRITE 348
#define LEX_BUILTIN_FUNCTION 349
#define LEX_ID 350
#define LEX_CARET_WHITE 351
#define LEX_CARET_LETTER 352
#define LEX_ASSIGN 353
#define LEX_RENAME 354
#define LEX_RANGE 355
#define LEX_ELLIPSIS 356
#define LEX_CONST_EQUAL 357
#define LEX_SYMDIFF 358
#define LEX_NE 359
#define LEX_GE 360
#define LEX_LE 361
#define LEX_POWER 362
#define LEX_BPPLUS 363
#define LEX_BPMINUS 364
#define LEX_CEIL_PLUS 365
#define LEX_CEIL_MINUS 366
#define LEX_FLOOR_PLUS 367
#define LEX_FLOOR_MINUS 368
#define LEX_CEIL_MULT 369
#define LEX_CEIL_DIV 370
#define LEX_FLOOR_MULT 371
#define LEX_FLOOR_DIV 372




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 108 "parse.y"
typedef union YYSTYPE {
  enum tree_code code;
  long itype;
  tree ttype;
} YYSTYPE;
/* Line 2359 of glr.c.  */
#line 273 "parse.h"
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


