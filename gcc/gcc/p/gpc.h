/*Global definitions for GNU Pascal

  Copyright (C) 1987-2005 Free Software Foundation, Inc.

  Authors: Peter Gerwinski <peter@gerwinski.de>
           Frank Heckenbach <frank@pascal.gnu.de>
           Waldek Hebisch <hebisch@math.uni.wroc.pl>

  This file is part of GNU Pascal.

  GNU Pascal is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 2, or (at your
  option) any later version.

  GNU Pascal is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Pascal; see the file COPYING. If not, write to the
  Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
  02111-1307, USA. */

#ifndef _GPC_H_
#define _GPC_H_

/* GPC compile time configuration switches */

#define USE_GPI_DEBUG_KEY  /* Use debugging keys in GPI files */

/* #undef DEBUG */         /* Used in execute() in module.c */

/* Define this to put error_mark_node in read-only memory to detect some errors
   earlier. The system calls used are not portable, so now only for Linux where
   I can test it (someone might want to investigate and amend autoconf etc.). */
#ifdef linux
#define PROTECT_ERROR_MARK_NODE
#endif

#undef USE_CPPLIB          /* Not suitable for Pascal */

#ifndef GCC_3_3
#define GTY(x)
#endif

#include "gbe.h"

#undef abort
#define abort() USE_ASSERT_RATHER_THAN_ABORT

/* NOTE: GPC relies on an assert macro that always evaluates its argument exactly once! */
/* Don't use the system's <assert.h>, see the comments in ../dwarfout.c */
#undef assert
#ifdef GPC_NO_ASSERTIONS
#define assert(expression) ((void) (expression))  /* Do evaluate expression */
#else
#ifndef __GNUC__
#define __PRETTY_FUNCTION__ NULL
#endif
#define assert(expression) \
  ((void) ((expression) ? 0 : (assert_fail (#expression, __FILE__, __PRETTY_FUNCTION__, __LINE__), 0)))
#endif

/* @@ gcc-3 has a similar mechanism via abort(). Check this after porting to gcc-3. */
#define abort_confused (error ("confused by previous errors, bailing out"), exit (FATAL_EXIT_CODE), 0)

#define EM(t) (TREE_CODE (t) == ERROR_MARK)
#define CHK_EM(t) do { if (EM (t)) return error_mark_node; } while (0)

#ifndef EGCS97
#define SET_DECL_ASSEMBLER_NAME(x, y) (DECL_ASSEMBLER_NAME (x) = (y))
#define DECL_ASSEMBLER_NAME_SET_P(x) (DECL_ASSEMBLER_NAME (x) != NULL_TREE)
#define DECL_ATTRIBUTES(NODE) (DECL_MACHINE_ATTRIBUTES (NODE))
#define COPY_DECL_RTL(x, y) (DECL_RTL (y) = DECL_RTL (x))
#define SET_DECL_RTL(x, y) (DECL_RTL (x) = (y))
#define DECL_RTL_SET_P(x) (DECL_RTL (x) != NULL)
#define COMPLETE_OR_VOID_TYPE_P(NODE) (TYPE_SIZE (NODE) || TREE_CODE (NODE) == VOID_TYPE)
#define bit_position(t) (DECL_FIELD_BITPOS (t))
#define bitsize_zero_node size_zero_node
#define bitsize_one_node size_one_node
#undef bitsize_int
#define bitsize_int(x) (size_int (x))
#define ssize_int(x) (size_int (x))
#define output_constant(x, y, z) (output_constant ((x), (y)))
#define tree_low_cst(x, y) (TREE_INT_CST_LOW (x))
#endif

#ifndef EGCS
#define ssizetype long_integer_type_node
#define usizetype sizetype
#define bitsizetype sizetype
#define sbitsizetype ssizetype
#define ubitsizetype usizetype
#define TREE_CHECK(t, code) (t)
#define TYPE_P(TYPE) (TREE_CODE_CLASS (TREE_CODE (TYPE)) == 't')
#define DECL_P(DECL) (TREE_CODE_CLASS (TREE_CODE (DECL)) == 'd')
#define IS_EXPR_CODE_CLASS(CLASS) \
  (CLASS == '<' || CLASS == '1' || CLASS == '2' || CLASS == 'e')
#define IDENTIFIER_NODE_CHECK(NODE) (TREE_CHECK (NODE, IDENTIFIER_NODE))
#define INTERFACE_NAME_NODE_CHECK(NODE) (TREE_CHECK (NODE, INTERFACE_NAME_NODE))
#define IMPORT_NODE_CHECK(NODE) (TREE_CHECK (NODE, IMPORT_NODE))
#endif

/* Define the dialect of Pascal being compiled.
   Used for reserved word recognition, error and warning messages, etc.
   Let's hope that there will not be more than 31 important dialects ... */
enum
{
  CLASSIC_PASCAL_LEVEL_0 =          1,  /* ISO 7185 Pascal, level 0 */
  CLASSIC_PASCAL_LEVEL_1 =          2,  /* ISO 7185 Pascal, level 1 */
  EXTENDED_PASCAL        =          4,  /* ISO 10206 Extended Pascal */
  OBJECT_PASCAL          =          8,  /* ANSI draft Object Pascal */
  UCSD_PASCAL            =       0x10,  /* UCSD Pascal */
  BORLAND_PASCAL         =       0x20,  /* Borland Pascal 7.0 */
  BORLAND_DELPHI         =       0x40,  /* Borland Delphi */
  PASCAL_SC              =       0x80,  /* Pascal-SC (PXSC) */
  VAX_PASCAL             =      0x100,  /* VAX Pascal */
  SUN_PASCAL             =      0x200,  /* Sun Pascal */
  MAC_PASCAL             =      0x400,  /* Traditional Macintosh Pascal */
  /* to be continued ... */
  GNU_PASCAL             = 0x40000000,  /* GNU Pascal (default) */
  ANY_PASCAL             = 0x7FFFFFFF,

  /* Abbreviations for combinations of these flags */
  E_O_PASCAL         = EXTENDED_PASCAL | OBJECT_PASCAL,
  E_O_M_PASCAL       = E_O_PASCAL | MAC_PASCAL,
  C_E_O_PASCAL       = CLASSIC_PASCAL_LEVEL_0 | CLASSIC_PASCAL_LEVEL_1 | E_O_PASCAL,
  C_E_O_U_PASCAL     = C_E_O_PASCAL | UCSD_PASCAL,
  C_E_O_M_PASCAL     = C_E_O_PASCAL | MAC_PASCAL,
  C_E_O_U_M_PASCAL   = C_E_O_U_PASCAL | MAC_PASCAL,
  B_D_PASCAL         = BORLAND_PASCAL | BORLAND_DELPHI,
  B_D_M_PASCAL       = B_D_PASCAL | MAC_PASCAL,
  U_M_PASCAL         = UCSD_PASCAL | MAC_PASCAL,
  U_B_D_PASCAL       = UCSD_PASCAL | B_D_PASCAL,
  U_B_D_M_PASCAL     = U_B_D_PASCAL | MAC_PASCAL,
  U_B_D_M_O_PASCAL   = U_B_D_M_PASCAL | OBJECT_PASCAL,
  O_D_PASCAL         = OBJECT_PASCAL | BORLAND_DELPHI,
  O_B_D_PASCAL       = O_D_PASCAL | B_D_PASCAL,
  O_B_D_M_PASCAL     = O_B_D_PASCAL | MAC_PASCAL,
  E_O_D_PASCAL       = E_O_PASCAL | O_D_PASCAL,
  E_O_B_D_PASCAL     = E_O_PASCAL | B_D_PASCAL,
  E_O_B_D_M_PASCAL   = E_O_B_D_PASCAL | MAC_PASCAL,
  NOT_CLASSIC_PASCAL = ANY_PASCAL & ~(CLASSIC_PASCAL_LEVEL_0 | CLASSIC_PASCAL_LEVEL_1)
};

#define PEDANTIC(dialect) (pedantic || (co->pascal_dialect && !(co->pascal_dialect & (dialect))))

/* Check the dialect. DIALECT specifies the Pascal dialect(s) in which the
   construct in question is valid (but warn with `--pedantic').
   Otherwise, an error is given. */
#define chk_dialect(MSG, DIALECT) chk_dialect_1 (MSG, DIALECT, NULL)
#define chk_dialect_name(NAME, DIALECT) chk_dialect_1 ("`%s' is", DIALECT, NAME)
#define chk_dialect_1(MSG, DIALECT, ARG) \
  do { if ((DIALECT) != ANY_PASCAL && PEDANTIC (DIALECT)) \
         dialect_msg (co->pascal_dialect && !(co->pascal_dialect & (DIALECT)), \
           (DIALECT), (MSG), " an extension of", (ARG)); } while (0)

#define DEFTREECODE(SYM, NAME, TYPE, LENGTH) SYM,
enum pascal_tree_code
{
  PASCAL_DUMMY_TREE_CODE = LAST_AND_UNUSED_TREE_CODE,
#include "p-tree.def"
  LAST_AND_UNUSED_PASCAL_TREE_CODE
};
#undef DEFTREECODE

#ifndef GCC_3_4
#define FIRST_OPERAND(code) ((code) == CONSTRUCTOR ? 1 : 0)
#else
#define FIRST_OPERAND(code) 0
#endif

#ifndef EGCS97
#define NUMBER_OF_OPERANDS(code) \
  (((code) == SAVE_EXPR || (code) == WITH_CLEANUP_EXPR) ? 1 \
  : ((code) == CALL_EXPR) ? 2 \
  : ((code) == METHOD_CALL_EXPR) ? 3 \
  : tree_code_length[(int) (code)])
#else
#if !defined (GCC_3_4)
#define NUMBER_OF_OPERANDS(code) \
  (((code) == SAVE_EXPR || (code) == WITH_CLEANUP_EXPR) ? 1 \
  : ((code) == METHOD_CALL_EXPR) ? 3 \
  : tree_code_length[(int) (code)])
#else
#define NUMBER_OF_OPERANDS(code) \
  (((code) == SAVE_EXPR || (code) == WITH_CLEANUP_EXPR) ? 1 \
  : tree_code_length[(int) (code)])
#endif
#endif

typedef HOST_WIDE_INT gpi_int;

/* We (mis?)use identifier nodes to get unique permanent string storage
   (which might be relevant especially for input file names which are
   often the same). */
#define PERMANENT_STRING(S) (IDENTIFIER_POINTER (get_identifier (S)))

struct tree_inn GTY(())
{
  struct tree_common common;
  struct interface_table_t * GTY((skip(""))) table;
  gpi_int checksum;
};
#define AS_INTERFACE_NAME_NODE(NODE) ((struct tree_inn *) INTERFACE_NAME_NODE_CHECK (NODE))
#define INTERFACE_TABLE(NODE)    (AS_INTERFACE_NAME_NODE (NODE)->table)
#define INTERFACE_CHECKSUM(NODE) (AS_INTERFACE_NAME_NODE (NODE)->checksum)

typedef enum { IMPORT_USES, IMPORT_QUALIFIED, IMPORT_ISO } import_type;

struct tree_import GTY(())
{
  struct tree_common common;
  gpi_int qualified;
  tree interface;
  tree import_qualifier;
  tree filename;
};
#define AS_IMPORT_NODE(NODE) ((struct tree_import *) IMPORT_NODE_CHECK (NODE))
#define IMPORT_INTERFACE(NODE) (AS_IMPORT_NODE (NODE)->interface)
#define PASCAL_TREE_QUALIFIED(NODE) (AS_IMPORT_NODE (NODE)->qualified)
#define IMPORT_QUALIFIER(NODE) (AS_IMPORT_NODE (NODE)->import_qualifier)
#define IMPORT_FILENAME(NODE) (AS_IMPORT_NODE (NODE)->filename)

#define PREDEF_KEYWORD(NAME, WEAK, DIALECT)
#define PREDEF_CONST(NAME, VALUE, DIALECT)
#define PREDEF_TYPE(NAME, TYPE, DIALECT)
#define PREDEF_SYNTAX(NAME, SIG, ATTRIBUTES, DIALECT)
#define PREDEF_SYMBOL(SYMBOL, RTS_NAME, ALIAS_NAME, SIG, ATTRIBUTES)
/* Do not use CONCAT2 here because it would expand possble macros like `EOF' or `static' too early. */
#if defined (__STDC__) || defined (ALMOST_STDC)
#define PREDEF_ID(NAME, DIALECT) ,p_##NAME
#define PREDEF_INTERFACE(NAME, CONTENT, DIALECT) ,p_##NAME
#define PREDEF_VAR(NAME, DIALECT) ,p_##NAME
#define PREDEF_ROUTINE(NAME, SIG, ATTRIBUTES, DIALECT) ,p_##NAME
#define PREDEF_ALIAS(NAME, RTS_NAME, SIG, ATTRIBUTES, DIALECT) ,p_##NAME
#define PREDEF_ROUTINE_NO_ID(NAME, SIG, ATTRIBUTES) ,p_##NAME
#else
#define PREDEF_ID(NAME) ,p_/**/NAME
#define PREDEF_INTERFACE(NAME) ,p_/**/NAME
#define PREDEF_VAR(NAME, DIALECT) ,p_/**/NAME
#define PREDEF_ROUTINE(NAME, SIG, ATTRIBUTES, DIALECT) ,p_/**/NAME
#define PREDEF_ALIAS(NAME, RTS_NAME, SIG, ATTRIBUTES, DIALECT) ,p_/**/NAME
#define PREDEF_ROUTINE_NO_ID(NAME, SIG, ATTRIBUTES) ,p_/**/NAME
#endif
enum
{
  MIN_EXTRA_SYMBOL = 1000  /* must be greater than all parser tokens */
#include <predef.h>
};

enum built_in_kind
{
  bk_none, bk_keyword, bk_interface, bk_const, bk_type, bk_var, bk_routine, bk_special_syntax
};

/* Attributes in struct predef. Also attributes in build_implicit_routine_decl. */
#define ER_NORETURN   1
#define ER_CONST      2
#define ER_IOCRITICAL 4
#define ER_EXTERNAL   8
#define ER_STATIC    16
#define KW_WEAK      32
#define KW_INFORMED  64

struct predef GTY(())
{
  const char *idname;
  const char *rts_idname;
  const char *alias_name;
  int symbol;
  enum built_in_kind kind;
  const char *signature;
  int attributes;
  unsigned long dialect;
  tree * GTY((skip(""))) value;
  tree decl;
  int user_disabled;
};

#define PD_ACTIVE(PD) ((PD) && (PD)->user_disabled < (!co->pascal_dialect || (co->pascal_dialect & (PD)->dialect)))

/* Language-dependent contents of an identifier. */
struct lang_identifier GTY(())
{
  struct tree_identifier ignore;
  tree value;
  tree error_locus;
  struct predef * GTY((skip(""))) built_in_value;
  const char *spelling;
  const char *spelling_file;
  int spelling_lineno;
  int spelling_column;
};

union lang_tree_node
  GTY((desc ("((TREE_CODE (&%h.generic) == IDENTIFIER_NODE) || (TREE_CODE (&%h.generic) == INTERFACE_NAME_NODE) || (TREE_CODE (&%h.generic) == IMPORT_NODE)) ? TREE_CODE (&%h.generic) : 0"),
       chain_next ("(union lang_tree_node *) TREE_CHAIN (&%h.generic)")))
{
  union tree_node GTY ((tag ("0"), desc ("tree_node_structure (&%h)"))) generic;
  struct lang_identifier GTY ((tag ("IDENTIFIER_NODE"))) identifier;
  struct tree_inn GTY ((tag ("INTERFACE_NAME_NODE"))) interface;
  struct tree_import GTY ((tag ("IMPORT_NODE"))) import;
};

#define AS_LANG_IDENTIFIER_NODE(ID) ((struct lang_identifier *) IDENTIFIER_NODE_CHECK (ID))

/* This represents the current value of the identifier (DECL node or null). */
#define IDENTIFIER_VALUE(ID) (AS_LANG_IDENTIFIER_NODE (ID)->value)

/* This is the last function in which we printed an "undefined variable"
   message for this identifier. Value is a FUNCTION_DECL or null. */
#define IDENTIFIER_ERROR_LOCUS(ID) (AS_LANG_IDENTIFIER_NODE (ID)->error_locus)

#define IDENTIFIER_BUILT_IN_VALUE(ID)  (AS_LANG_IDENTIFIER_NODE (ID)->built_in_value)

#define IDENTIFIER_IS_BUILT_IN(ID, SYMBOL) \
  (IDENTIFIER_BUILT_IN_VALUE (ID) && IDENTIFIER_BUILT_IN_VALUE (ID)->symbol == (SYMBOL))

#define IDENTIFIER_SPELLING(ID)        (AS_LANG_IDENTIFIER_NODE (ID)->spelling)
#define IDENTIFIER_SPELLING_FILE(ID)   (AS_LANG_IDENTIFIER_NODE (ID)->spelling_file)
#define IDENTIFIER_SPELLING_LINENO(ID) (AS_LANG_IDENTIFIER_NODE (ID)->spelling_lineno)
#define IDENTIFIER_SPELLING_COLUMN(ID) (AS_LANG_IDENTIFIER_NODE (ID)->spelling_column)

#define IDENTIFIER_NAME(ID) \
  (IDENTIFIER_SPELLING (ID) ? IDENTIFIER_SPELLING (ID) : IDENTIFIER_POINTER (ID))

/* Record in each node resulting from a binary operator
   what operator was specified for it. */
#define EXP_ORIGINAL_CODE(exp) ((enum tree_code) TREE_COMPLEXITY (exp))

/* Store a value in that field. */
#define SET_EXP_ORIGINAL_CODE(exp, code) (TREE_COMPLEXITY (exp) = (int) (code))

/* IS_EXPR_CODE_CLASS ought to work, but for CONSTRUCTORS the backend overwrites
   this field via TREE_CST_RTL. @@@@@@@@@@ Severe backend bug! This is no fix. */
#define HAS_EXP_ORIGINAL_CODE_FIELD(exp) \
  (IS_EXPR_CODE_CLASS (TREE_CODE_CLASS (TREE_CODE (exp))) && TREE_CODE (exp) != CONSTRUCTOR)

#define IS_EXPR_OR_REF_CODE_CLASS(c) (IS_EXPR_CODE_CLASS (c) || c == 'r')

#define PROMOTING_INTEGER_TYPE(t) \
  (TREE_CODE (t) == INTEGER_TYPE && TYPE_PRECISION (t) < TYPE_PRECISION (integer_type_node))

/* Some Pascal set constructors do not allow us to derive the set size from
   anywhere. In such cases, the maximum allowed members in the set is defined
   here (in bits). (Otherwise, there would be no limit.)
   Users may change this with a `--setlimit=NUMBER' switch at compile time. */
#define DEFAULT_SET_LIMIT (8 * BITS_PER_WORD)

#define ORDINAL_TYPE(code) \
  ((code) == INTEGER_TYPE || (code) == CHAR_TYPE || (code) == BOOLEAN_TYPE || (code) == ENUMERAL_TYPE)

#define ORDINAL_OR_REAL_TYPE(c) (ORDINAL_TYPE (c) || (c) == REAL_TYPE)

#define ORDINAL_REAL_OR_COMPLEX_TYPE(c) (ORDINAL_OR_REAL_TYPE (c) || (c) == COMPLEX_TYPE)

#define SCALAR_TYPE(c) (ORDINAL_REAL_OR_COMPLEX_TYPE (c) || (c) == POINTER_TYPE || (c) == REFERENCE_TYPE)

#define INT_REAL(c) ((c) == INTEGER_TYPE || (c) == REAL_TYPE)

#define IS_NUMERIC(c) (INT_REAL (c) || (c) == COMPLEX_TYPE)

#define RECORD_OR_UNION(c) ((c) == RECORD_TYPE || (c) == UNION_TYPE || (c) == QUAL_UNION_TYPE)

#define STRUCTURED_TYPE(c) (RECORD_OR_UNION (c) || (c) == ARRAY_TYPE)

/* Tree flags 0, 1 are still available. */

/* Note: TREE_PRIVATE used for:
   - implicit result variables (VAR_DECL)
   - built-in interfaces (IMPORT_NODE)
   - `private' object methods and fields (FUNCTION_DECL, FIELD_DECL)
   - temporarily in variable declarations (TREE_LIST) */

#define PUBLIC_PRIVATE_PROTECTED(t) (TREE_PRIVATE (t) ? 2 : TREE_PROTECTED (t) ? 1 : 0)

/* Set if an expression can be used as a statement without complaining
   or a function has been declared as `ignorable'. Used in *_EXPR, *_CST
   and FUNCTION_TYPE nodes. */
#define PASCAL_TREE_IGNORABLE(t) TREE_LANG_FLAG_2 (t)

/* Set if the parameter is a value parameter passed by reference.
   This is necessary for undiscriminated strings/schemata and
   conformant/open arrays passed by value. Used in *_TYPE nodes. */
#define PASCAL_TYPE_VAL_REF_PARM(type) TREE_LANG_FLAG_3 (type)

/* Set for reference parameters. Used in parameter TREE_LIST nodes. */
#define PASCAL_REF_PARM(t) TREE_LANG_FLAG_3 (t)

/* Flag for schema discriminants.
   Used in VAR_DECL, FIELD_DECL, and CONVERT_EXPR nodes. */
#define PASCAL_TREE_DISCRIMINANT(t) TREE_LANG_FLAG_3 (t)

/* Set if an identifier is being declared as a variable.
   Used in IDENTIFIER_NODE nodes. */
#define PASCAL_PENDING_DECLARATION(t) TREE_LANG_FLAG_3 (t)

/* Set if a method is a constructor or destructor (the result type
   tells which). Used in FUNCTION_DECL nodes. */
#define PASCAL_STRUCTOR_METHOD(t) TREE_LANG_FLAG_4 (t)

/* Set for BP initializer lists. Used in initializer TREE_LIST nodes. */
#define PASCAL_BP_INITIALIZER_LIST(list) TREE_LANG_FLAG_4 (list)

/* Set for packed array access constructs.
   Used in NON_LVALUE_EXPR and TREE_LIST nodes. */
#define PASCAL_TREE_PACKED(expr) TREE_LANG_FLAG_5 (expr)

/* Flag for fresh constants (integer, enum, char, Boolean, real, string).
   Used in *_CST nodes. */
#define PASCAL_TREE_FRESH_CST(expr) TREE_LANG_FLAG_5 (expr)

/* Set for virtual methods. Used in FUNCTION_DECL nodes. */
#define PASCAL_VIRTUAL_METHOD(decl) TREE_LANG_FLAG_5 (decl)

/* Set for set CONSTRUCTOR nodes that consist of only INTEGER_CSTs. */
#define PASCAL_CONSTRUCTOR_INT_CST(expr) TREE_LANG_FLAG_5 (expr)

/* Set artificial VAR_DECL nodes whose value contains side-effects. */
#define PASCAL_HAD_SIDE_EFFECTS(expr) TREE_LANG_FLAG_5 (expr)

/* Set for abstract methods. Used in FUNCTION_DECL nodes. */
#define PASCAL_ABSTRACT_METHOD(decl) TREE_LANG_FLAG_6 (decl)

/* Set for an `absolute' clause (in BP sense) instead of a
   variable initializer. Used in *_EXPR nodes. */
#define PASCAL_ABSOLUTE_CLAUSE(init) TREE_LANG_FLAG_6 (init)

/* Set for a declaration that is `external' in the Pascal sense;
   it has been mentioned in the program heading. Used in VAR_DECL
   nodes. (In Extended Pascal it does not have to be a file.) */
#define PASCAL_EXTERNAL_OBJECT(object) TREE_LANG_FLAG_6 (object)

/* Set for `const' parameters. Used in *_TYPE and some temporary TREE_LIST nodes. */
#define PASCAL_CONST_PARM(type) TREE_LANG_FLAG_6 (type)

/* Set if identifier is a qualified identifer. Used in IDENTIFIER_NODEs. */
#define PASCAL_QUALIFIED_ID(id) TREE_LANG_FLAG_6 (id)

/* GPC specific decl node extensions. */

/* Decl flag 0 is still available. */

/* Set for declarations imported from other modules/units. */
#define PASCAL_DECL_IMPORTED(NODE) DECL_LANG_FLAG_1 (NODE)

/* Set if declaration is imported via `uses' (so it can be
   overriden). */
#define PASCAL_DECL_WEAK(NODE) DECL_LANG_FLAG_2 (NODE)

/* Borland Pascal allows a "typed constant" to be used as an initialized
   variable and does not even warn if a value is written to it (because
   there are no other initialized variables).
   To be compatible, we don't flag typed constants with TREE_READONLY, but
   with this flag. Like this, assignments will work, but we can warn and
   keep a clean conscience. Used in VAR_DECL nodes. */
#define PASCAL_DECL_TYPED_CONST(NODE) DECL_LANG_FLAG_3 (NODE)

/* Set if the label has been set. Used in LABEL_DECL nodes. */
#define PASCAL_LABEL_SET(NODE) DECL_LANG_FLAG_3 (NODE)

/* Set for fields of explicitly packed structures. Used in FIELD_DECL nodes. */
#define DECL_PACKED_FIELD(NODE) DECL_LANG_FLAG_4 (NODE)

/* Set when a VAR_DECL node is threatened. */
#define PASCAL_VALUE_ASSIGNED(decl) DECL_LANG_FLAG_4 (decl)

/* Set when a VAR_DECL node is threatened in a subroutine. */
#define PASCAL_VALUE_ASSIGNED_SUBROUTINE(decl) DECL_LANG_FLAG_5 (decl)

/* Set for FUNCTION_DECLs which are object methods.
   @@ Maybe use METHOD_TYPE for their type instead. */
#define PASCAL_METHOD(decl) DECL_LANG_FLAG_5 (decl)

/* Set for operators that are both built-in and overloaded. Used in OPERATOR_DECL nodes. */
#define PASCAL_BUILTIN_OPERATOR(decl) DECL_LANG_FLAG_5 (decl)

/* Set when a VAR_DECL node is initialized. */
#define PASCAL_INITIALIZED(decl) DECL_LANG_FLAG_6 (decl)

/* Set for standard Pascal procedural parameter, not for non-standard routine
   pointer parameters where the routine is not automatically called when
   referenced. Used in PARM_DECL nodes. */
#define PASCAL_PROCEDURAL_PARAMETER(decl) DECL_LANG_FLAG_6 (decl)

/* Set for forward declarations. Used in FUNCTION_DECL nodes. */
#define PASCAL_FORWARD_DECLARATION(decl) DECL_LANG_FLAG_7 (decl)

/* Set temporarily while a variable is being used as a `for' loop counter.
   Used in VAR_DECL nodes. */
#define PASCAL_FOR_LOOP_COUNTER(decl) DECL_LANG_FLAG_7 (decl)

/* Set if a declaration represents the principal identifier of a constant
   (see EP 6.10.2). Used in CONST_DECL nodes. */
#define PASCAL_CST_PRINCIPAL_ID(decl) DECL_LANG_FLAG_7 (decl)

struct lang_decl GTY(())
{
  tree info;
  tree info2;
  tree info3;
};

#define DECL_LANG_INFO1(decl) (DECL_LANG_SPECIFIC (decl)->info)
#define DECL_LANG_INFO2(decl) (DECL_LANG_SPECIFIC (decl)->info2)
#define DECL_LANG_INFO3(decl) (DECL_LANG_SPECIFIC (decl)->info3)

/* The meaning of DECL_LANG_FIXUPLIST:
   - undiscriminated schema: list, pointing to fixup places
   - prediscriminated schema: NULL_TREE
   - discriminated schema: expression, contains discriminant initializer
   Used in FIELD_DECL and VAR_DECL nodes. */
#define DECL_LANG_FIXUPLIST(decl) DECL_LANG_INFO1 (decl)

/* Chain of formal parameters of the routine. (TYPE_ARG_TYPES contains only
   the types, not the argument names.) Used in FUNCTION_DECL nodes. */
#define DECL_LANG_PARMS(decl) DECL_LANG_INFO1 (decl)

/* The Pascal result variable of the function (VAR_DECL while implementing the
   function, IDENTIFIER_NODE otherwise). Used in FUNCTION_DECL nodes. */
#define DECL_LANG_RESULT_VARIABLE(decl) DECL_LANG_INFO2 (decl)

/* Used in method FUNCTION_DECL nodes. */
#define DECL_LANG_METHOD_DECL(decl) DECL_LANG_INFO3 (decl)

/* Used in operator FUNCTION_DECL nodes.
   Note: Testing DECL_LANG_OPERATOR_DECL is the only way to tell whether a
   FUNCTION_DECL is an operator. But methods use the same field, so we have
   to check for them here. Consequently, we also need a set macro. */
#define DECL_LANG_OPERATOR_DECL(decl) \
  ((DECL_LANG_SPECIFIC (decl) && !PASCAL_METHOD (decl)) ? DECL_LANG_INFO3 (decl) : NULL_TREE)
#define SET_DECL_LANG_OPERATOR_DECL(decl, t) (DECL_LANG_INFO3 (decl) = (t))

/* GPC specific type node extensions. */

/* This flag is set if the type is `packed' */
#define PASCAL_TYPE_PACKED(type) TYPE_PACKED (type)

/* Type flags 0, 6 are still available. */

/* Set for the type of an IO-critical function. Used in FUNCTION_TYPE nodes. */
#define PASCAL_TYPE_IOCRITICAL(type) TYPE_LANG_FLAG_1 (type)

/* Set for `restricted' types. */
#define PASCAL_TYPE_RESTRICTED(type) TYPE_LANG_FLAG_2 (type)

/* Set for `bindable' types. */
#define PASCAL_TYPE_BINDABLE(type) TYPE_LANG_FLAG_3 (type)

/* Set for BP "open array" parameters. Used in ARRAY_TYPE and INTEGER_TYPE nodes. */
#define PASCAL_TYPE_OPEN_ARRAY(type) TYPE_LANG_FLAG_4 (type)

/* Set for conformant array bound types. Used in ordinal type nodes. */
#define PASCAL_TYPE_CONFORMANT_BOUND(type) TYPE_LANG_FLAG_5 (type)

/* Set for intermediate array types in array type declarations with several
   index types. Used in ARRAY_TYPE nodes. */
#define PASCAL_TYPE_INTERMEDIATE_ARRAY(type) TYPE_LANG_FLAG_5 (type)

struct lang_type GTY(())
{
  int code;
  tree info;
  tree info2;
  tree base;
  tree initial;
  tree * GTY((length ("%h.field_count"))) sorted_fields;
  int field_count;
};

/* Tag info for variant records, file domain, object type name,
   or declared string capacity. Used in RECORD_TYPE nodes,
   depending on the TYPE_LANG_CODE. */
#define TYPE_LANG_INFO(type) (TYPE_LANG_SPECIFIC (type)->info)
#define TYPE_LANG_VARIANT_TAG(type) TYPE_LANG_INFO (type)
#define TYPE_LANG_FILE_DOMAIN(type) TYPE_LANG_INFO (type)
#define TYPE_LANG_VMT_FIELD(type) TYPE_LANG_INFO (type)
#define TYPE_LANG_DECLARED_CAPACITY(type) TYPE_LANG_INFO (type)
#define TYPE_LANG_FAKE_ARRAY_ELEMENTS(type) TYPE_LANG_INFO (type)

/* To speed up find_field() */
#define TYPE_LANG_SORTED_FIELDS(type) (TYPE_LANG_SPECIFIC (type)->sorted_fields)
#define TYPE_LANG_FIELD_COUNT(type) (TYPE_LANG_SPECIFIC (type)->field_count)

/* Object VMT variable. Used in RECORD_TYPE nodes (objects). */
#define TYPE_LANG_INFO2(type) (TYPE_LANG_SPECIFIC (type)->info2)
#define TYPE_LANG_VMT_VAR(type) TYPE_LANG_INFO2 (type)

/* Base type info for objects and schemata. Used in RECORD_TYPE nodes
   (objects and schemata). */
#define TYPE_LANG_BASE(type) (TYPE_LANG_SPECIFIC (type)->base)

/* Initial value associated to the type. Used in all type nodes. */
#define TYPE_LANG_INITIAL(type) (TYPE_LANG_SPECIFIC (type)->initial)
#define TYPE_GET_INITIALIZER(type) \
  (TYPE_LANG_SPECIFIC (type) ? TYPE_LANG_INITIAL (type) : NULL_TREE)

/* Distinguish variant records, files, objects, strings and
   schemata from ordinary records. */
#define TYPE_LANG_CODE(type) (TYPE_LANG_SPECIFIC (type)->code)

#define PASCAL_LANG_PLAIN_RECORD             0
#define PASCAL_LANG_VARIANT_RECORD           1
#define PASCAL_LANG_NON_TEXT_FILE            2
#define PASCAL_LANG_TEXT_FILE                3
#define PASCAL_LANG_OBJECT                   4
#define PASCAL_LANG_ABSTRACT_OBJECT          5
#define PASCAL_LANG_UNDISCRIMINATED_STRING   6
#define PASCAL_LANG_PREDISCRIMINATED_STRING  7
#define PASCAL_LANG_DISCRIMINATED_STRING     8
#define PASCAL_LANG_UNDISCRIMINATED_SCHEMA   9
#define PASCAL_LANG_PREDISCRIMINATED_SCHEMA 10
#define PASCAL_LANG_DISCRIMINATED_SCHEMA    11
#define PASCAL_LANG_FAKE_ARRAY              12

/* Determine if a given TYPE node represents the given lang code. */
#define TYPE_LANG_CODE_TEST(type, code) \
  (TREE_CODE (type) == RECORD_TYPE      \
   && TYPE_LANG_SPECIFIC (type)         \
   && TYPE_LANG_CODE (type) == (code))

#define PASCAL_TYPE_NON_TEXT_FILE(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_NON_TEXT_FILE)

#define PASCAL_TYPE_TEXT_FILE(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_TEXT_FILE)

#define PASCAL_TYPE_FILE(type)      \
  (PASCAL_TYPE_NON_TEXT_FILE (type) \
   || PASCAL_TYPE_TEXT_FILE (type))

#define PASCAL_TYPE_ANYFILE(type) \
  (TYPE_MAIN_VARIANT (type) == any_file_type_node)

/* Determine if a given TYPE node represents a variant record type. */
#define PASCAL_TYPE_VARIANT_RECORD(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_VARIANT_RECORD)

/* Determine if a given TYPE node represents an object type. */
#define PASCAL_TYPE_OBJECT(type)                  \
  (TYPE_LANG_CODE_TEST (type, PASCAL_LANG_OBJECT) \
   || TYPE_LANG_CODE_TEST (type, PASCAL_LANG_ABSTRACT_OBJECT))

/* Determine whether some TYPE is an undiscriminated string. */
#define PASCAL_TYPE_UNDISCRIMINATED_STRING(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_UNDISCRIMINATED_STRING)

/* Determine whether some TYPE is a pre-discriminated string. */
#define PASCAL_TYPE_PREDISCRIMINATED_STRING(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_PREDISCRIMINATED_STRING)

/* Determine whether some TYPE is a discriminated string. */
#define PASCAL_TYPE_DISCRIMINATED_STRING(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_DISCRIMINATED_STRING)

/* Determine if a given TYPE node represents a string type. */
#define PASCAL_TYPE_STRING(type)                 \
  (PASCAL_TYPE_UNDISCRIMINATED_STRING (type)     \
   || PASCAL_TYPE_PREDISCRIMINATED_STRING (type) \
   || PASCAL_TYPE_DISCRIMINATED_STRING (type))

/* Return the Pascal string value of expr. */
#define PASCAL_STRING_VALUE(expr) \
  (PASCAL_TYPE_STRING (TREE_TYPE (expr)) \
   ? build_component_ref (expr, schema_id) \
   : expr)

#define IS_CONSTANT_EMPTY_STRING(expr) \
  (TREE_CODE (expr) == STRING_CST && TREE_STRING_LENGTH (expr) == 1)

#define IS_STRING_CST(t) \
  (TREE_CODE (t) == STRING_CST || (TREE_CODE (t) == INTEGER_CST && TREE_CODE (TREE_TYPE (t)) == CHAR_TYPE))

/* Each variable length string has a `Length' field, the length of a char is
   always 1, fixed-length-string length is the size of the domain range. */
#define PASCAL_STRING_LENGTH(expr)                         \
  (EM (TREE_TYPE (expr))                                   \
   ? error_mark_node                                       \
   : PASCAL_TYPE_STRING (TREE_TYPE (expr))                 \
   ? build_component_ref (expr, get_identifier ("length")) \
   : convert (pascal_integer_type_node,                    \
     TREE_CODE (TREE_TYPE (expr)) == CHAR_TYPE             \
   ? integer_one_node                                      \
   : TREE_CODE (expr) == STRING_CST                        \
   ? build_int_2 (TREE_STRING_LENGTH (expr) - 1, 0)        \
   : fold (build_binary_op (PLUS_EXPR,                     \
       build_binary_op (MINUS_EXPR,                        \
         convert (pascal_integer_type_node, TYPE_MAX_VALUE (TYPE_DOMAIN (TREE_TYPE (expr)))),  \
         convert (pascal_integer_type_node, TYPE_MIN_VALUE (TYPE_DOMAIN (TREE_TYPE (expr))))), \
       integer_one_node))))

/* Access an EP string's capacity. */
#define PASCAL_STRING_CAPACITY(expr) TYPE_LANG_DECLARED_CAPACITY (TREE_TYPE (expr))

/* Determine whether some TYPE is an undiscriminated schema. */
#define PASCAL_TYPE_UNDISCRIMINATED_SCHEMA(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_UNDISCRIMINATED_SCHEMA)

/* Determine whether some TYPE is a prediscriminated schema. */
#define PASCAL_TYPE_PREDISCRIMINATED_SCHEMA(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_PREDISCRIMINATED_SCHEMA)

/* Determine whether some TYPE is a discriminated schema. */
#define PASCAL_TYPE_DISCRIMINATED_SCHEMA(type) \
  TYPE_LANG_CODE_TEST (type, PASCAL_LANG_DISCRIMINATED_SCHEMA)

/* Determine if a given TYPE node represents a schema type. */
#define PASCAL_TYPE_SCHEMA(type)                 \
  (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (type)     \
   || PASCAL_TYPE_PREDISCRIMINATED_SCHEMA (type) \
   || PASCAL_TYPE_DISCRIMINATED_SCHEMA (type))

#define DEREFERENCE_SCHEMA(val) \
  do { while (PASCAL_TYPE_SCHEMA (TREE_TYPE (val))) \
         (val) = build_component_ref ((val), schema_id); } while (0)

/* Determine if a given TYPE node represents a conformant array type. */
#define PASCAL_TYPE_CONFORMANT_ARRAY(type) \
  (TREE_CODE (type) == ARRAY_TYPE          \
   && TREE_TYPE (TYPE_DOMAIN (type))       \
   && PASCAL_TYPE_CONFORMANT_BOUND (TREE_TYPE (TYPE_DOMAIN (type))))

/* Identify constructor and destructor methods as such. This only checks for
   function declarations, not for field declarations and call expressions. */
#define PASCAL_CONSTRUCTOR_METHOD(decl) \
  (PASCAL_STRUCTOR_METHOD (decl)        \
   && TREE_CODE (decl) == FUNCTION_DECL \
   && TREE_TYPE (decl)                  \
   && TREE_TYPE (TREE_TYPE (decl)) == boolean_type_node)

#define PASCAL_DESTRUCTOR_METHOD(decl)  \
  (PASCAL_STRUCTOR_METHOD ((decl))      \
   && TREE_CODE (decl) == FUNCTION_DECL \
   && TREE_TYPE (decl)                  \
   && TREE_TYPE (TREE_TYPE (decl)) == void_type_node)

/* Pascal type variants. */
#define TYPE_QUALIFIER_PACKED      1
#define TYPE_QUALIFIER_PROTECTED   2
#define TYPE_QUALIFIER_BINDABLE    4
#define TYPE_QUALIFIER_RESTRICTED  8
#define TYPE_QUALIFIER_CONFORMANT 16

/* Determine if something may be a function call. */
#define MAYBE_CALL_FUNCTION(target)                           \
  (TREE_CODE (target) == FUNCTION_DECL                        \
   || (TREE_TYPE (target)                                     \
       && (TREE_CODE (TREE_TYPE (target)) == REFERENCE_TYPE   \
           || TREE_CODE (TREE_TYPE (target)) == POINTER_TYPE) \
       && TREE_CODE (TREE_TYPE (TREE_TYPE (target))) == FUNCTION_TYPE))

/* Determine if something is a method call. */
#define CALL_METHOD(target)            \
  (TREE_CODE (target) == COMPONENT_REF \
   && TREE_CODE (TREE_TYPE (target)) == FUNCTION_TYPE)

/* Determine if something is a BP style procedural type. */
#define PASCAL_PROCEDURAL_TYPE(t) \
  (TREE_CODE (t) == REFERENCE_TYPE && TREE_CODE (TREE_TYPE (t)) == FUNCTION_TYPE)

/* Contains the jmpbuf VAR_DECL in non-local main program LABEL_DECL nodes. */
#define DECL_LANG_LABEL_JMPBUF(decl) DECL_INITIAL(decl)

#define VQ_EXTERNAL  1
#define VQ_STATIC    2
#define VQ_VOLATILE  4
#define VQ_REGISTER  8
#define VQ_CONST    16
#define VQ_BP_CONST 32
#define VQ_IMPLICIT 64

#ifdef EGCS97
typedef const char *filename_t;
#else
typedef char *filename_t;
#endif

/* parse.y */

extern void set_yydebug PARAMS ((int));
extern int yyparse PARAMS ((void));

/* Bison doesn't put this in parse.h, so declare it here for all source files, also parse.y */
typedef struct
{
  int option_id;  /* abusing it for options */
  filename_t first_file, last_file;
  int first_line, last_line, first_column, last_column;
} YYLTYPE;
#define YYLTYPE_IS_DECLARED

/* parse.c contains the same declarations again */
#ifndef LEX_ID
#include "parse.h"
#endif

/* options.c */

typedef struct string_list GTY(())
{
  struct string_list *next;
  char *string;
} string_list;

extern string_list *deferred_options;
extern char *extra_imports;
extern const char *automake_temp_filename;
extern char *automake_gpc;
extern char *automake_gcc;
extern char *automake_gpp;
extern int flag_disable_default_paths;
extern char *unit_path;
extern char *default_unit_path;
extern char *object_path;
extern char *default_object_path;
extern const char *executable_file_name;
extern char *executable_destination_path;
extern char *unit_destination_path;
extern char *object_destination_path;
extern char *gpi_destination_path;
extern int flag_progress_messages;
extern int flag_progress_bar;
extern char *extra_inits;
extern const char *gpc_main;

#define BACKEND_OPTIONS_1 \
  BO (flag_pack_struct) \
  BO (maximum_field_alignment) \
  BO (pedantic) \
  BO (flag_stack_check) \
  BO (flag_short_enums) \
  BO (inhibit_warnings) \
  BO (extra_warnings) \
  BO (warn_shadow) \
  BO (warn_switch) \
  BO (warn_cast_align) \
  BO (warn_inline) \
  BO (warn_uninitialized)
#ifdef EGCS97
#define BACKEND_OPTIONS \
  BACKEND_OPTIONS_1 \
  BO (warn_unused_function) \
  BO (warn_unused_label) \
  BO (warn_unused_parameter) \
  BO (warn_unused_variable) \
  BO (warn_unused_value) \
  BO (warn_notreached) \
  BO (warn_packed) \
  BO (warn_padded) \
  BO (warn_disabled_optimization) \
  BO (warn_deprecated_decl) \
  BO (warn_missing_noreturn)
#else
#define BACKEND_OPTIONS \
  BACKEND_OPTIONS_1 \
  BO (warn_unused)
#endif

struct options
{
  struct options *next;

  int counter;

#define BO(NAME) int NAME;
  BACKEND_OPTIONS
#undef BO

  /* What kind of Pascal is being compiled? */
  unsigned long pascal_dialect;

  /* Warn if adding () is suggested. */
  int warn_parentheses;

  /* Warn about testing equality of floating point numbers. */
  int warn_float_equal;

  /* Nonzero means warn about local external declarations. */
  int warn_local_external;

  /* Nonzero means warn about arrays whose size is determined at run time
     (including array slices). */
  int warn_dynamic_arrays;

  /* Nonzero means allow mixed comments `(* }' and `{ *)'. */
  int mixed_comments;

  /* Nonzero means to warn about mixed comments. */
  int warn_mixed_comments;

  /* Nonzero means allow nested comments `(* (* *) *)' and `{ { } }'. */
  int nested_comments;

  /* Nonzero means to warn about nested comments. */
  int warn_nested_comments;

  /* Nonzero means allow Delphi comments. */
  int delphi_comments;

  /* Nonzero allows GPC to ignore function results without warning. */
  int ignore_function_results;

  /* Nonzero means: In read statements, allow `n#' base specifiers */
  int read_base_specifier;

  /* Nonzero means: In read statements, allow hexadecimal input with `$' */
  int read_hex;

  /* Nonzero means: In read statements, require whitespace after numbers */
  int read_white_space;

  /* Nonzero means to allow string clipping: `Write ('foobar' : 3)' => `foo'. */
  int write_clip_strings;

  /* Nonzero means to allow string truncation: `WriteStr (s3, 'foobar')'
     with `s3' having a capacity of 3 => `foo'. Zero means to produce a
     runtime error. */
  int truncate_strings;

  /* Nonzero means to do exact (lexicographic) string comparisons with
     operators like `<'. Zero means to pad with spaces as ISO requires. */
  int exact_compare_strings;

  /* Nonzero means allow strings enclosed in "". */
  int double_quoted_strings;

  /* Nonzero means to use `longjmp' for all nonlocal labels, not only those in the main program. */
  int longjmp_all_nonlocal_labels;

  /* Nonzero means to produce a blank in front of positive reals (required by ISO). */
  int real_blank;

  /* Nonzero means to write exponents with a capital 'E'.
     Zero means to write a lowercase 'e'. */
  int capital_exponent;

  /* Nonzero means to derive the external file name from
     the name of the file variable. */
  int transparent_file_names;

  /* Nonzero means the result of the address operator is a typed pointer. */
  int typed_address;

  /* Nonzero means that assertions should be checked. */
  int assertions;

  /* Nonzero means to ignore `packed' in the source code. */
  int ignore_packed;

  /* Nonzero means to ignore anything after the terminating `.'. */
  int ignore_garbage_after_dot;

  /* Nonzero means to allow pointer arithmetic. */
  int pointer_arithmetic;

  /* Nonzero means to allow treating CStrings as strings. */
  int cstrings_as_strings;

  /* Nonzero means to warn about variables at absolute adresses and
     `absolute' variable with non-constant addresses. */
  int warn_absolute;

  /* Use short circuit operators with standard AND and OR. */
  int short_circuit;

  /* Nonzero means to check for IOResult after each I/O operation. */
  int io_checking;

  /* Nonzero means to do range checking. A value > 1 means to handle range
     errors as I/O errors (only used internally for `Read', `Val', etc.). */
  int range_checking;

  /* Nonzero means to cause a runtime error if a `case' matches no branch. */
  int case_value_checking;

  /* The endianness as given by a command-line option (-1 means none given). */
  int option_big_endian;

  /* Nonzero means printing of needed options was requested. */
  int print_needed_options;

  /* Nonzero means to warn about a semicolon after `then', `else' or `do'. */
  int warn_semicolon;

  /* Nonzero means automatically re-export all imported declarations. */
  int propagate_units;

  /* Nonzero if only the interface part of a unit/module should be compiled. */
  int interface_only;

  /* Nonzero if only the implementation part of a unit/module should be compiled. */
  int implementation_only;

  /* 2 means to warn about an identifier written with varying case.
     1 means only within one program/module/unit. */
  int warn_id_case;

  /* Nonzero means to warn when a unit/module interface differs from the file name. */
  int warn_interface_file_name;

  /* Nonzero means to make all methods virtual. */
  int methods_always_virtual;

  /* Nonzero means to warn when an object type not declared `abstract' contains an abstract method. */
  int warn_implicit_abstract;

  /* Nonzero means to warn when an abstract object type inherits from a non-abstract one. */
  int warn_inherited_abstract;

  /* Nonzero means to warn when assigning objects. */
  int warn_object_assignment;

  /* Nonzero means to warn when `Input' or `Output' are used implicitly. */
  int warn_implicit_io;

  /* Nonzero if warnings about the misuse of typed constants as
     initialized variables shall be issued. */
  int warn_typed_const;

  /* Nonzero if warnings about usage of the useless `near' and
     `far' directives shall be issued. */
  int warn_near_far;

  /* Nonzero if warnings about double/leading/trailing underscores in
     identifiers shall be issued. */
  int warn_underscore;

  /* This is the size set with `--setlimit' (or the default). */
  unsigned int set_limit;

  /* Nonzero means to copy the source input to stderr. */
  int debug_source;

  /* Flag for debugging the GPI mechanism. */
  int debug_gpi;

  /* Nonzero means print automake debugging information to stderr. */
  int debug_automake;

  /* 0 = nothing, 1 = autolink (default), 2 = automake, 3 = autobuild. */
  int automake_level;

  /* Option -ffield-widths=... changes default field widths
     (Integer, Real, Boolean, LongInt, LongReal) for `Write' operations. */
  int write_width[5];

  int dummy;
};

extern struct options *lexer_options, *compiler_options, *co;
extern int extra_inits_used;
extern char *save_string PARAMS ((const char *));
extern void pascal_decode_option_1 PARAMS ((const char *p));
extern int pascal_decode_option PARAMS ((int, const char *const *));
extern int is_pascal_option PARAMS ((const char *));
extern int process_pascal_directive PARAMS ((char *, int));
extern void activate_options PARAMS ((struct options *, int));
#ifndef GCC_3_4
extern void pascal_init_options PARAMS ((void));
#else
extern unsigned int pascal_init_options (unsigned int argc, const char **argv);
#endif
extern void do_deferred_options PARAMS ((void));
extern void error_or_warning PARAMS ((int, const char *));
extern void dialect_msg PARAMS ((int, unsigned long, const char *, const char *, const char *));
extern void warn_about_keyword_redeclaration PARAMS ((tree, int));

/* declarations.c */

extern int defining_packed_type;
extern int size_volatile;
extern int current_structor_object_type_constructor;
#ifndef EGCS97
extern tree ptr_type_node;
extern tree null_pointer_node;
extern tree integer_minus_one_node;
extern tree char_type_node;
extern tree const_ptr_type_node;
extern tree double_type_node;
extern tree float_type_node;
extern tree intTI_type_node;
extern tree intDI_type_node;
extern tree intHI_type_node;
extern tree intQI_type_node;
extern tree intSI_type_node;
extern tree integer_type_node;
extern tree long_double_type_node;
extern tree long_integer_type_node;
extern tree long_long_integer_type_node;
extern tree long_long_unsigned_type_node;
extern tree long_unsigned_type_node;
extern tree complex_double_type_node;
extern tree ptrdiff_type_node;
extern tree short_integer_type_node;
extern tree short_unsigned_type_node;
extern tree unsigned_intTI_type_node;
extern tree unsigned_intDI_type_node;
extern tree unsigned_intHI_type_node;
extern tree unsigned_intQI_type_node;
extern tree unsigned_intSI_type_node;
extern tree unsigned_type_node;
extern tree void_type_node;
#endif
extern struct lang_type *allocate_type_lang_specific PARAMS ((void));
extern void copy_type_lang_specific PARAMS ((tree));
extern struct lang_decl *allocate_decl_lang_specific PARAMS ((void));
extern int pascal_global_bindings_p PARAMS ((void));
extern void type_attributes PARAMS ((tree *, tree));
extern void routine_attributes PARAMS ((tree *, tree, tree *));
extern tree check_assembler_name PARAMS ((tree));
extern tree declare_routine PARAMS ((tree, tree, int));
extern tree build_implicit_routine_decl PARAMS ((tree, tree, tree, int));
extern tree numeric_label PARAMS ((tree));
extern void declare_label PARAMS ((tree));
extern void do_setjmp PARAMS ((void));
extern tree build_type_decl PARAMS ((tree, tree, tree));
extern void declare_types PARAMS ((void));
extern tree pascal_shadow_record_fields PARAMS ((tree, tree));
extern void restore_identifiers PARAMS ((tree));
extern void cleanup_routine PARAMS ((void));
extern void finish_routine PARAMS ((void));
extern tree build_routine_heading PARAMS ((tree, tree, tree, tree, tree, int));
extern tree build_operator_heading PARAMS ((tree, tree, tree, tree));
extern void check_routine_decl PARAMS ((tree, tree, tree, int, int, int, tree, filename_t, int));
extern tree start_routine PARAMS ((tree, tree));
extern tree start_implicit_routine PARAMS ((tree, tree, tree, tree));
extern void sort_fields PARAMS ((tree));
extern tree finish_struct PARAMS ((tree, tree, int));
extern tree getdecls PARAMS ((void));
extern int global_bindings_p PARAMS ((void));
extern void init_decl_processing PARAMS ((void));
extern void set_forward_decl PARAMS ((tree, int));
extern void clear_forward_decls PARAMS ((void));
extern void check_forward_decls PARAMS ((int));
extern void insert_block PARAMS ((tree));
extern void set_block PARAMS ((tree));
extern void check_duplicate_id PARAMS ((tree));
extern tree lookup_name PARAMS ((tree));
extern tree lookup_name_current_level PARAMS ((tree));
extern tree get_pointer_domain_type PARAMS ((tree));
extern void set_identifier_spelling PARAMS ((tree, const char *, const char *, int, int));
extern tree make_identifier PARAMS ((const char *, int));
extern tree get_identifier_with_spelling PARAMS ((const char *, const char *));
extern tree get_unique_identifier PARAMS ((const char *));
extern tree build_qualified_id PARAMS ((tree, tree));
extern tree build_qualified_or_component_access PARAMS ((tree, tree));
extern tree check_identifier PARAMS ((tree));
extern tree de_capitalize PARAMS ((tree));
extern tree pascal_mangle_names PARAMS ((const char *, const char *));
extern tree build_formal_param PARAMS ((tree, tree, int, int));
extern tree build_procedural_type PARAMS ((tree, tree));
extern tree build_formal_param_list PARAMS ((tree, tree, tree *));
extern tree add_parm_decl PARAMS ((tree, tree, tree));
extern tree poplevel PARAMS ((int, int, int));
extern void pushlevel_expand PARAMS ((void));
extern tree poplevel_expand PARAMS ((int, int));
extern tree pushdecl PARAMS ((tree));
extern tree pushdecl_import PARAMS ((tree, int));
extern tree pushdecl_nocheck PARAMS ((tree));
extern void pushlevel PARAMS ((int));
extern tree start_struct PARAMS ((enum tree_code));
extern tree build_enum_type PARAMS ((tree));
extern tree declare_constant PARAMS ((tree, tree));
extern tree declare_variables PARAMS ((tree, tree, tree, int, tree));
extern tree declare_variable PARAMS ((tree, tree, tree, int));
extern tree make_new_variable PARAMS ((const char *, tree));
extern tree new_string_by_model PARAMS ((tree, tree, int));
extern tree set_structor_object PARAMS ((tree, int));

/* expressions.c */

extern tree build_pascal_unary_op PARAMS ((enum tree_code, tree));
extern tree build_pascal_pointer_reference PARAMS ((tree));
extern tree undo_schema_dereference PARAMS ((tree));
extern tree build_pascal_address_expression PARAMS ((tree, int));
extern tree build_pascal_lvalue_address_expression PARAMS ((tree));
extern tree get_operator PARAMS ((const char *, const char *, tree, tree, int));
extern tree build_operator_call PARAMS ((tree, tree, tree, int));
extern tree start_boolean_binary_op PARAMS ((enum tree_code, tree));
extern tree finish_boolean_binary_op PARAMS ((enum tree_code, tree, tree, tree));
extern int const_plus1_lt PARAMS ((tree, tree));
extern tree parser_build_binary_op PARAMS ((enum tree_code, tree, tree));
extern tree set_exp_original_code PARAMS ((tree, enum tree_code));
extern tree build_pascal_binary_op PARAMS ((enum tree_code, tree, tree));
extern tree build_implicit_pascal_binary_op PARAMS ((enum tree_code, tree, tree));
extern int operators_defined;
extern tree build_string_constant PARAMS ((const char *, int, int));
extern tree build_caret_string_constant PARAMS ((int));
extern tree combine_strings PARAMS ((tree, int));
extern void constant_expression_warning PARAMS ((tree));
extern tree range_check_2 PARAMS ((tree, tree, tree));
extern tree range_check PARAMS ((tree, tree));
extern tree convert_and_check PARAMS ((tree, tree));
extern tree truthvalue_conversion PARAMS ((tree));
extern tree build_binary_op PARAMS ((enum tree_code, tree, tree));
extern tree build_unary_op PARAMS ((enum tree_code, tree, int));
extern tree build_type_cast PARAMS ((tree, tree));
extern tree build_indirect_ref PARAMS ((tree, const char *));
extern int allow_function_calls PARAMS ((int));
extern tree function_result_type PARAMS ((tree));
extern tree maybe_call_function PARAMS ((tree, int));
extern tree probably_call_function PARAMS ((tree));
extern tree build_iocheck PARAMS ((void));
extern tree build_routine_call PARAMS ((tree, tree));
extern tree build_iso_set_constructor PARAMS ((tree, tree, int));
extern tree build_iso_constructor PARAMS ((tree, tree));
extern tree build_call_or_cast PARAMS ((tree, tree));
extern tree build_modify_expr PARAMS ((tree, enum tree_code, tree));

/* statements.c */

extern void expand_expr_stmt1 PARAMS ((tree));
extern void pascal_expand_asm_operands PARAMS ((tree, tree, tree, tree, int));
extern int mark_lvalue PARAMS ((tree, const char *, int));
extern int check_reference_parameter PARAMS ((tree, int));
extern void expand_return_statement PARAMS ((tree));
extern tree pascal_expand_start_case PARAMS ((tree));
extern void pascal_pushcase PARAMS ((tree));
extern void set_label PARAMS ((tree));
extern void pascal_expand_goto PARAMS ((tree));
extern tree start_for_loop PARAMS ((tree, tree, tree, enum tree_code));
extern void finish_for_loop PARAMS ((tree, enum tree_code));
extern tree start_for_set_loop PARAMS ((tree, tree));
extern void finish_for_set_loop PARAMS ((tree, tree));
extern tree assign_tags PARAMS ((tree, tree));
extern int contains_file_p PARAMS ((tree));
extern int contains_auto_initialized_part_p PARAMS ((tree, int));
extern void init_any PARAMS ((tree, int, int));
extern void un_initialize_block PARAMS ((tree, int, int));
extern void expand_call_statement PARAMS ((tree));
extern void expand_pascal_assignment PARAMS ((tree, tree));
extern tree assign_set PARAMS ((tree, tree));
extern tree assign_string PARAMS ((tree, const tree));
extern void start_main_program PARAMS ((void));
extern void finish_main_program PARAMS ((void));
extern void start_constructor PARAMS ((int));
extern void finish_constructor PARAMS ((void));
extern void start_destructor PARAMS ((void));
extern void finish_destructor PARAMS ((void));
extern void implicit_module_structors PARAMS ((void));

/* typecheck.c */

extern void cstring_inform PARAMS ((void));
extern void ptrarith_inform PARAMS ((void));
extern tree require_complete_type PARAMS ((tree));
extern void incomplete_type_error PARAMS ((tree, tree));
extern int contains_discriminant PARAMS ((tree, tree));
extern tree build_discriminated_schema_type PARAMS ((tree, tree, int));
extern tree default_conversion PARAMS ((tree));
extern tree convert_array_to_pointer PARAMS ((tree));
extern tree convert_arguments PARAMS ((tree, tree, tree));
extern int check_pascal_initializer PARAMS ((tree, tree));
extern tree common_type PARAMS ((tree, tree));
extern int comptypes PARAMS ((tree, tree));
extern int strictly_comp_types PARAMS ((tree, tree));
extern int comp_target_types PARAMS ((tree, tree));
extern int comp_object_or_schema_pointer_types PARAMS ((tree, tree));
extern int lvalue_p PARAMS ((tree));
#ifdef GCC_3_3
extern bool mark_addressable PARAMS ((tree));
extern bool mark_addressable2 PARAMS ((tree, int));
#else
extern int mark_addressable2 PARAMS ((tree, int));
#endif
#ifndef EGCS
extern int mark_addressable PARAMS ((tree));
#endif
extern tree convert_for_assignment PARAMS ((tree, tree, const char *, tree, int));
extern tree initializer_constant_valid_p PARAMS ((tree, tree));
extern tree digest_init PARAMS ((tree, tree, int));
extern tree build_pascal_initializer PARAMS ((tree, tree, const char *, int));
extern tree find_variant_selector PARAMS ((tree, tree));

/* types.c */

extern tree signed_or_unsigned_type PARAMS ((int, tree));
extern tree unsigned_type PARAMS ((tree));
extern tree signed_type PARAMS ((tree));
extern tree type_for_size PARAMS ((unsigned, int));
extern tree type_for_mode PARAMS ((enum machine_mode, int));
extern tree check_result_type PARAMS ((tree));
extern tree convert PARAMS ((tree, tree));
extern tree build_set_constructor PARAMS ((tree));
extern tree construct_set PARAMS ((tree, tree, int));
extern tree build_set_type PARAMS ((tree));
extern tree build_pascal_pointer_type PARAMS ((tree));
extern tree convert_to_cstring PARAMS ((tree));
extern tree string_may_be_char PARAMS ((tree, int));
extern tree char_may_be_string PARAMS ((tree));
extern tree build_pascal_string_schema PARAMS ((tree));
extern tree build_pascal_packed_array_ref  PARAMS ((tree, tree, tree, int));
extern int is_string_compatible_type PARAMS ((tree, int));
extern int is_string_type PARAMS ((tree, int));
extern int is_of_string_type PARAMS ((tree, int));
extern int is_variable_string_type PARAMS ((tree));
extern tree build_discriminants PARAMS ((tree, tree));
extern tree maybe_schema_discriminant PARAMS ((tree));
extern tree build_schema_type PARAMS ((tree, tree, tree));
extern int number_of_schema_discriminants PARAMS ((tree));
extern void prediscriminate_schema PARAMS ((tree));
extern tree base_type PARAMS ((tree));
extern tree build_file_type PARAMS ((tree, tree, int));
extern tree build_field PARAMS ((tree, tree));
extern tree add_type_initializer PARAMS ((tree, tree));
extern tree build_fields PARAMS ((tree, tree, tree));
extern tree build_record PARAMS ((tree, tree, tree));
extern tree pack_type PARAMS ((tree));
extern int is_packed_field PARAMS ((tree));
extern tree count_bits PARAMS ((tree));
extern tree pascal_array_type_nelts PARAMS ((tree));
extern tree size_of_type PARAMS ((tree));
extern int const_lt PARAMS ((tree, tree));
extern tree select_signed_integer_type PARAMS ((tree));
extern tree select_integer_type PARAMS ((tree, tree, enum tree_code));
extern int check_subrange PARAMS ((tree, tree));
extern tree save_nonconstants PARAMS ((tree));
extern tree build_pascal_range_type PARAMS ((tree, tree));
extern tree build_pascal_subrange_type PARAMS ((tree, tree, int));
extern tree find_field PARAMS ((tree, tree, int));
extern tree build_component_ref PARAMS ((tree, tree));
extern tree simple_component_ref PARAMS ((tree, tree));
extern tree build_component_ref_no_schema_dereference PARAMS ((tree, tree, int));
extern tree build_pascal_array_type PARAMS ((tree, tree));
extern tree build_array_slice_ref PARAMS ((tree, tree, tree));
extern tree fold_array_ref PARAMS ((tree));
extern tree build_array_ref_or_constructor PARAMS ((tree, tree));
extern tree build_pascal_array_ref PARAMS ((tree, tree));
extern tree build_array_ref PARAMS ((tree, tree));
extern tree build_simple_array_type PARAMS ((tree, tree));
extern tree build_boolean_type PARAMS ((unsigned));
extern void new_main_variant PARAMS ((tree));
extern tree pascal_type_variant PARAMS ((tree, int));
extern tree p_build_type_variant PARAMS ((tree, int, int));
extern tree build_type_of PARAMS ((tree));

#ifdef EGCS
/* copied from c-decl.c */
/* Add qualifiers to a type, in the fashion for C. */
extern tree c_build_qualified_type PARAMS ((tree, int));
#undef c_build_type_variant
#define c_build_type_variant(TYPE, CONST_P, VOLATILE_P)     \
  c_build_qualified_type (TYPE,                             \
                          ((CONST_P) ? TYPE_QUAL_CONST : 0) \
                          | ((VOLATILE_P) ? TYPE_QUAL_VOLATILE : 0))
#else
extern tree c_build_type_variant PARAMS ((tree, int, int));
#endif

/* objects.c */

extern tree simple_get_field PARAMS ((tree, tree, const char *));
extern tree get_vmt_field PARAMS ((tree));
extern const char *check_private_protected PARAMS ((tree));
extern tree call_method PARAMS ((tree, tree));
extern tree build_inherited_method PARAMS ((tree));
extern tree get_method_name PARAMS ((tree, tree));
extern tree start_object_type PARAMS ((tree));
extern tree finish_object_type PARAMS ((tree, tree, tree, int));
extern tree build_is_as PARAMS ((tree, tree, int));

/* predef.c */

extern void init_predef PARAMS ((void));
extern tree save_expr_string PARAMS ((tree));
extern void build_exit_statement PARAMS ((tree));
extern tree build_predef_call PARAMS ((int, tree));
extern tree build_buffer_ref PARAMS ((tree, int));
extern tree get_builtin_variable PARAMS ((tree));
extern tree build_memcpy PARAMS ((tree, tree, tree));
extern tree build_memset PARAMS ((tree, tree, tree));

/* module.c */

typedef enum { LF_UNIT, LF_COMPILED_UNIT, LF_OBJECT, LF_COMPILED_OBJECT } locate_file_t;

#define MODULE_T_FIRST_TREE_FIELD imports
struct module GTY(())
{
  tree imports;  /* TREE_LIST of IMPORT_NODEs of imported interfaces for this module. */
  tree exports;  /* TREE_LIST of interfaces exported from this module
                    TREE_VALUE is an IDENTIFIER_NODE of an exported
                    interface name. TREE_PURPOSE is TREE_LIST chain of
                    the names exported by this module. */
  tree name;  /* The name of this module. */
  tree initializers;  /* A TREE_LIST of module initializers (IDENTIFIER_NODE).
                         Currently, there is exactly one, but maybe sometime
                         it will be useful to allow for several ones (or none
                         at all). */
  tree initializer;
  tree finalizer;
  tree assembler_name;  /* The "linker name" of this module. */
  tree parms;  /* Module parameters. */
  tree autoexport;  /* What shall be exported automatically? */
  tree output_file_node;  /* Standard output for this module. */
  tree input_file_node;  /* Standard input for this module. */
  tree error_file_node;  /* Standard error file handle for this module. */

  int implementation;  /* Nonzero while compiling a program or unit/module implementation. */
  int interface;  /* Nonzero if this module has an interface part. */
  string_list * GTY((skip(""))) link_files;  /* Files this module wishes to be linked. */
  int main_program;  /* Nonzero if this is the main program. */
  struct module *next;  /* Next module. */
/* NOTE: Add future fields of type tree above and note MODULE_T_LAST_TREE_FIELD below! */

};
#define MODULE_T_LAST_TREE_FIELD error_file_node

typedef struct module *module_t;

#define NULL_MODULE ((module_t) 0)

extern module_t current_module;
extern void associate_external_objects PARAMS ((tree));
extern void check_external_objects PARAMS ((tree));
extern void handle_autoexport PARAMS ((tree));
extern void add_automake_gpc_options PARAMS ((const char *));
extern void append_string_list PARAMS ((string_list **, const char *, int));
extern void add_to_link_file_list PARAMS ((const char *));
extern char *locate_file PARAMS ((const char *, locate_file_t));
extern void store_executable_name PARAMS ((void));
extern int compile_module PARAMS ((const char *, const char *));
extern tree itab_get_initializers PARAMS ((tree));
extern void create_gpi_files PARAMS ((void));
extern void initialize_module PARAMS ((tree, tree, int));
extern void start_module_interface PARAMS ((void));
extern void start_unit_implementation PARAMS ((void));
extern void finalize_module PARAMS ((int));
extern void import_interface PARAMS ((tree, tree, import_type, tree));
extern void export_interface PARAMS ((tree, tree));
extern void do_extra_import PARAMS ((void));
extern int is_gpi_special_node PARAMS ((tree));

/* lang.c */

extern const char *pascal_decl_name PARAMS ((tree, int));
extern void get_current_routine_name PARAMS ((const char **, const char **));
#ifndef EGCS
extern void add_pascal_tree_codes PARAMS ((void));
#endif
extern void pascal_decl_attributes PARAMS ((tree *, tree));
extern void exit_compilation PARAMS ((void));
extern void assert_fail PARAMS ((const char *, const char *, const char *, int)) ATTRIBUTE_NORETURN;

/* gpc-lex.c */

extern filename_t lexer_filename, compiler_filename;
extern int column;
extern int lexer_lineno, lexer_column, compiler_lineno, compiler_column;
extern int syntax_errors;
extern int lex_const_equal;
extern int check_newline PARAMS ((void));
extern void yyerror PARAMS ((const char *));
extern void yyerror_id PARAMS ((tree, const YYLTYPE *));
extern int peek_token PARAMS ((int));
extern void set_old_input_filename PARAMS ((const char *));
extern int yylex PARAMS ((void));
extern void pascal_init_lex PARAMS ((const char *));
extern void init_gpc_lex PARAMS ((const char *));
extern void discard_input PARAMS ((void));
#ifdef GCC_3_4
extern FILE * finput;
#endif

/* Put all global tree node variables here (don't use static ones) */

#define PGT(N) (pascal_global_trees[N])

/* Types */
#define byte_integer_type_node PGT(0)
#define byte_unsigned_type_node PGT(1)
#ifndef GCC_3_4
#define boolean_type_node PGT(2)
#endif
#define cboolean_type_node PGT(3)
#define byte_boolean_type_node PGT(4)
#define short_boolean_type_node PGT(5)
#define word_boolean_type_node PGT(6)
#define long_boolean_type_node PGT(7)
#define long_long_boolean_type_node PGT(8)
#define cstring_type_node PGT(9)
#define wchar_type_node PGT(10)
#define open_array_index_type_node PGT(11)
#define pascal_size_type_node PGT(12)
#define ptrsize_unsigned_type_node PGT(13)
#define ptrsize_integer_type_node PGT(14)
#define untyped_file_type_node PGT(15)
#define text_type_node PGT(16)
#define any_file_type_node PGT(17)
#define complex_type_node PGT(18)
#define packed_array_unsigned_long_type_node PGT(19)
#define packed_array_unsigned_short_type_node PGT(20)
#define gpc_type_DateTimeString PGT(21)  /* Result type of `Date' and `Time' */
#define gpc_type_TimeStamp PGT(22)
#define gpc_type_BindingType PGT(23)
#define gpc_fields_PObjectType PGT(24)
#define gpc_type_PObjectType PGT(25)
#define string_schema_proto_type PGT(26)
#define const_string_schema_proto_type PGT(27)
#define const_string_schema_par_type PGT(28)
#define string255_type_node PGT(29)
#define empty_set_type_node PGT(30)

/* Constants */
#define pascal_maxint_node PGT(31)
#ifndef GCC_3_4
#define boolean_false_node PGT(32)
#define boolean_true_node PGT(33)
#endif
#define char_max_node PGT(34)
#define real_max_node PGT(35)
#define real_min_node PGT(36)
#define real_eps_node PGT(37)
#define real_zero_node PGT(38)
#define real_half_node PGT(39)
#define real_pi_node PGT(40)
#define complex_zero_node PGT(41)
#define empty_string_node PGT(42)

/* Variables */
#define null_pseudo_const_node PGT(43)
#define inoutres_variable_node PGT(44)
#define paramcount_variable_node PGT(45)
#define paramstr_variable_node PGT(46)
#define global_input_file_node PGT(47)
#define global_output_file_node PGT(48)
#define global_error_file_node PGT(49)

/* Routines */
#define memcpy_routine_node PGT(50)
#define memset_routine_node PGT(51)
#define strlen_routine_node PGT(52)
#define setjmp_routine_node PGT(53)
#define longjmp_routine_node PGT(54)
#define return_address_routine_node PGT(55)
#define frame_address_routine_node PGT(56)
#define checkinoutres_routine_node PGT(57)

/* Identifiers */
#define self_id PGT(58)
#define schema_id PGT(59)
#define vmt_id PGT(60)

/* All the nodes above are once initialized and should not change afterwards. */

/* A list of all exported names in all modules seen so far.
   TREE_VALUE is an IDENTIFIER_NODE of an exported interface name, TREE_PURPOSE
   is a TREE_LIST of the names exported by this interface. */
#define exported_interface_list PGT(61)

/* The types in the current `type' declaration part. */
#define current_type_list PGT(62)

/* A list of all initializers that were deferred. */
#define deferred_initializers PGT(63)

/* For type checking while the body of a `case' statement is parsed. */
#define current_case_expression PGT(64)

/* The last expression parsed within parentheses. */
#define last_parenthesized_expression PGT(65)

#define current_structor_object_type PGT(66)

#define PTI_MAX 67
extern GTY(()) tree pascal_global_trees[PTI_MAX];

#define pascal_integer_type_node  ptrsize_integer_type_node
#define pascal_cardinal_type_node ptrsize_unsigned_type_node

/* @@ gcc>3.2 defines size_type_node in tree.h. After dropping support for
      gcc-3.2.x, we can remove pascal_size_type_node (or make it #ifndef EGCS97
      if gcc-2 support is still wanted), and remove the following definition. */
#undef size_type_node
#define size_type_node pascal_size_type_node

#endif /* _GPC_H_ */
