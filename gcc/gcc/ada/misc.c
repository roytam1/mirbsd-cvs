/* $MirOS: gcc/gcc/ada/misc.c,v 1.2 2005/03/25 19:29:16 tg Exp $ */

/****************************************************************************
 *                                                                          *
 *                         GNAT COMPILER COMPONENTS                         *
 *                                                                          *
 *                                 M I S C                                  *
 *                                                                          *
 *                           C Implementation File                          *
 *                                                                          *
 *          Copyright (C) 1992-2004 Free Software Foundation, Inc.          *
 *                                                                          *
 * GNAT is free software;  you can  redistribute it  and/or modify it under *
 * terms of the  GNU General Public License as published  by the Free Soft- *
 * ware  Foundation;  either version 2,  or (at your option) any later ver- *
 * sion.  GNAT is distributed in the hope that it will be useful, but WITH- *
 * OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY *
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License *
 * for  more details.  You should have  received  a copy of the GNU General *
 * Public License  distributed with GNAT;  see file COPYING.  If not, write *
 * to  the Free Software Foundation,  59 Temple Place - Suite 330,  Boston, *
 * MA 02111-1307, USA.                                                      *
 *                                                                          *
 * As a  special  exception,  if you  link  this file  with other  files to *
 * produce an executable,  this file does not by itself cause the resulting *
 * executable to be covered by the GNU General Public License. This except- *
 * ion does not  however invalidate  any other reasons  why the  executable *
 * file might be covered by the  GNU Public License.                        *
 *                                                                          *
 * GNAT was originally developed  by the GNAT team at  New York University. *
 * Extensive contributions were provided by Ada Core Technologies Inc.      *
 *                                                                          *
 ****************************************************************************/

/* This file contains parts of the compiler that are required for interfacing
   with GCC but otherwise do nothing and parts of Gigi that need to know
   about RTL.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tree.h"
#include "real.h"
#include "rtl.h"
#include "errors.h"
#include "diagnostic.h"
#include "expr.h"
#include "libfuncs.h"
#include "ggc.h"
#include "flags.h"
#include "debug.h"
#include "insn-codes.h"
#include "insn-flags.h"
#include "insn-config.h"
#include "optabs.h"
#include "recog.h"
#include "toplev.h"
#include "output.h"
#include "except.h"
#include "tm_p.h"
#include "langhooks.h"
#include "langhooks-def.h"
#include "target.h"

#include "ada.h"
#include "types.h"
#include "atree.h"
#include "elists.h"
#include "namet.h"
#include "nlists.h"
#include "stringt.h"
#include "uintp.h"
#include "fe.h"
#include "sinfo.h"
#include "einfo.h"
#include "ada-tree.h"
#include "gigi.h"
#include "adadecode.h"
#include "opts.h"
#include "options.h"
#include "protector.h"

extern FILE *asm_out_file;
extern int flag_trampolines;

/* The largest alignment, in bits, that is needed for using the widest
   move instruction.  */
unsigned int largest_move_alignment;

static size_t gnat_tree_size		(enum tree_code);
static bool gnat_init			(void);
static void gnat_finish_incomplete_decl	(tree);
static unsigned int gnat_init_options	(unsigned int, const char **);
static int gnat_handle_option		(size_t, const char *, int);
static HOST_WIDE_INT gnat_get_alias_set	(tree);
static void gnat_print_decl		(FILE *, tree, int);
static void gnat_print_type		(FILE *, tree, int);
static const char *gnat_printable_name	(tree, int);
static tree gnat_eh_runtime_type	(tree);
static int gnat_eh_type_covers		(tree, tree);
static void gnat_parse_file		(int);
static rtx gnat_expand_expr		(tree, rtx, enum machine_mode, int,
					 rtx *);
static void internal_error_function	(const char *, va_list *);
static void gnat_adjust_rli		(record_layout_info);

/* Structure giving our language-specific hooks.  */

#undef  LANG_HOOKS_NAME
#define LANG_HOOKS_NAME			"GNU Ada"
#undef  LANG_HOOKS_IDENTIFIER_SIZE
#define LANG_HOOKS_IDENTIFIER_SIZE	sizeof (struct tree_identifier)
#undef  LANG_HOOKS_TREE_SIZE
#define LANG_HOOKS_TREE_SIZE		gnat_tree_size
#undef  LANG_HOOKS_INIT
#define LANG_HOOKS_INIT			gnat_init
#undef  LANG_HOOKS_INIT_OPTIONS
#define LANG_HOOKS_INIT_OPTIONS		gnat_init_options
#undef  LANG_HOOKS_HANDLE_OPTION
#define LANG_HOOKS_HANDLE_OPTION	gnat_handle_option
#undef LANG_HOOKS_PARSE_FILE
#define LANG_HOOKS_PARSE_FILE		gnat_parse_file
#undef LANG_HOOKS_HONOR_READONLY
#define LANG_HOOKS_HONOR_READONLY	1
#undef LANG_HOOKS_FINISH_INCOMPLETE_DECL
#define LANG_HOOKS_FINISH_INCOMPLETE_DECL gnat_finish_incomplete_decl
#undef LANG_HOOKS_GET_ALIAS_SET
#define LANG_HOOKS_GET_ALIAS_SET	gnat_get_alias_set
#undef LANG_HOOKS_EXPAND_EXPR
#define LANG_HOOKS_EXPAND_EXPR		gnat_expand_expr
#undef LANG_HOOKS_MARK_ADDRESSABLE
#define LANG_HOOKS_MARK_ADDRESSABLE	gnat_mark_addressable
#undef LANG_HOOKS_TRUTHVALUE_CONVERSION
#define LANG_HOOKS_TRUTHVALUE_CONVERSION gnat_truthvalue_conversion
#undef LANG_HOOKS_PRINT_DECL
#define LANG_HOOKS_PRINT_DECL		gnat_print_decl
#undef LANG_HOOKS_PRINT_TYPE
#define LANG_HOOKS_PRINT_TYPE		gnat_print_type
#undef LANG_HOOKS_DECL_PRINTABLE_NAME
#define LANG_HOOKS_DECL_PRINTABLE_NAME	gnat_printable_name
#undef LANG_HOOKS_TYPE_FOR_MODE
#define LANG_HOOKS_TYPE_FOR_MODE	gnat_type_for_mode
#undef LANG_HOOKS_TYPE_FOR_SIZE
#define LANG_HOOKS_TYPE_FOR_SIZE	gnat_type_for_size
#undef LANG_HOOKS_SIGNED_TYPE
#define LANG_HOOKS_SIGNED_TYPE		gnat_signed_type
#undef LANG_HOOKS_UNSIGNED_TYPE
#define LANG_HOOKS_UNSIGNED_TYPE	gnat_unsigned_type
#undef LANG_HOOKS_SIGNED_OR_UNSIGNED_TYPE
#define LANG_HOOKS_SIGNED_OR_UNSIGNED_TYPE gnat_signed_or_unsigned_type

const struct lang_hooks lang_hooks = LANG_HOOKS_INITIALIZER;

/* Tables describing GCC tree codes used only by GNAT.

   Table indexed by tree code giving a string containing a character
   classifying the tree code.  Possibilities are
   t, d, s, c, r, <, 1 and 2.  See cp-tree.def for details.  */

#define DEFTREECODE(SYM, NAME, TYPE, LENGTH) TYPE,

const char tree_code_type[] = {
#include "tree.def"
  'x',
#include "ada-tree.def"
};
#undef DEFTREECODE

/* Table indexed by tree code giving number of expression
   operands beyond the fixed part of the node structure.
   Not used for types or decls.  */

#define DEFTREECODE(SYM, NAME, TYPE, LENGTH) LENGTH,

const unsigned char tree_code_length[] = {
#include "tree.def"
  0,
#include "ada-tree.def"
};
#undef DEFTREECODE

/* Names of tree components.
   Used for printing out the tree and error messages.  */
#define DEFTREECODE(SYM, NAME, TYPE, LEN) NAME,

const char *const tree_code_name[] = {
#include "tree.def"
  "@@dummy",
#include "ada-tree.def"
};
#undef DEFTREECODE

/* Command-line argc and argv.
   These variables are global, since they are imported and used in
   back_end.adb  */

unsigned int save_argc;
const char **save_argv;

/* gnat standard argc argv */

extern int gnat_argc;
extern char **gnat_argv;


/* Declare functions we use as part of startup.  */
extern void __gnat_initialize	(void);
extern void adainit		(void);
extern void _ada_gnat1drv	(void);

/* The parser for the language.  For us, we process the GNAT tree.  */

static void
gnat_parse_file (int set_yydebug ATTRIBUTE_UNUSED)
{
  /* call the target specific initializations */
  __gnat_initialize();

  /* Call the front-end elaboration procedures */
  adainit ();

  immediate_size_expand = 1;

  /* Call the front end */
  _ada_gnat1drv ();
}

/* Decode all the language specific options that cannot be decoded by GCC.
   The option decoding phase of GCC calls this routine on the flags that
   it cannot decode.  This routine returns the number of consecutive arguments
   from ARGV that it successfully decoded; 0 indicates failure.  */

static int
gnat_handle_option (size_t scode, const char *arg, int value ATTRIBUTE_UNUSED)
{
  const struct cl_option *option = &cl_options[scode];
  enum opt_code code = (enum opt_code) scode;
  char *q;
  unsigned int i;

  if (arg == NULL && (option->flags & (CL_JOINED | CL_SEPARATE)))
    {
      error ("missing argument to \"-%s\"", option->opt_text);
      return 1;
    }

  switch (code)
    {
    default:
      abort ();

    case OPT_I:
      q = xmalloc (sizeof("-I") + strlen (arg));
      strcpy (q, "-I");
      strcat (q, arg);
      gnat_argv[gnat_argc] = q;
      gnat_argc++;
      break;

      /* All front ends are expected to accept this.  */
    case OPT_Wall:
      /* These are used in the GCC Makefile.  */
    case OPT_Wmissing_prototypes:
    case OPT_Wstrict_prototypes:
    case OPT_Wwrite_strings:
    case OPT_Wlong_long:
      break;

      /* This is handled by the front-end.  */
    case OPT_nostdinc:
      break;

    case OPT_nostdlib:
      gnat_argv[gnat_argc] = xstrdup ("-nostdlib");
      gnat_argc++;
      break;

    case OPT_fRTS:
      gnat_argv[gnat_argc] = xstrdup ("-fRTS");
      gnat_argc++;
      break;

    case OPT_gant:
      warning ("`-gnat' misspelled as `-gant'");

      /* ... fall through ... */

    case OPT_gnat:
      /* Recopy the switches without the 'gnat' prefix.  */
      gnat_argv[gnat_argc] = xmalloc (strlen (arg) + 2);
      gnat_argv[gnat_argc][0] = '-';
      strcpy (gnat_argv[gnat_argc] + 1, arg);
      gnat_argc++;

      if (arg[0] == 'O')
	for (i = 1; i < save_argc - 1; i++)
	  if (!strncmp (save_argv[i], "-gnatO", 6))
	    if (save_argv[++i][0] != '-')
	      {
		/* Preserve output filename as GCC doesn't save it for GNAT. */
		gnat_argv[gnat_argc] = xstrdup (save_argv[i]);
		gnat_argc++;
		break;
	      }
      break;
    }

  return 1;
}

/* Initialize for option processing.  */

static unsigned int
gnat_init_options (unsigned int argc, const char **argv)
{
  /* Initialize gnat_argv with save_argv size.  */
  gnat_argv = (char **) xmalloc ((argc + 1) * sizeof (argv[0]));
  gnat_argv[0] = xstrdup (argv[0]);     /* name of the command */
  gnat_argc = 1;

  save_argc = argc;
  save_argv = argv;

  return CL_Ada;
}

/* Here is the function to handle the compiler error processing in GCC.  */

static void
internal_error_function (const char *msgid, va_list *ap)
{
  char buffer[1000];		/* Assume this is big enough.  */
  char *p;
  String_Template temp;
  Fat_Pointer fp;

  vsprintf (buffer, msgid, *ap);

  /* Go up to the first newline.  */
  for (p = buffer; *p != 0; p++)
    if (*p == '\n')
      {
	*p = '\0';
	break;
      }

  temp.Low_Bound = 1, temp.High_Bound = strlen (buffer);
  fp.Array = buffer, fp.Bounds = &temp;

  Current_Error_Node = error_gnat_node;
  Compiler_Abort (fp, -1);
}

/* Langhook for tree_size: Determine size of our 'x' and 'c' nodes.  */

static size_t
gnat_tree_size (enum tree_code code)
{
  switch (code)
    {
    case GNAT_LOOP_ID:
      return sizeof (struct tree_loop_id);
    default:
      abort ();
    }
  /* NOTREACHED */
}

/* Perform all the initialization steps that are language-specific.  */

static bool
gnat_init (void)
{
  /* Disable ProPolice stack protector, we've got our own.  */
  flag_stack_protection = 0;
  flag_propolice_protection = 0;

  /* XXX Enable the generation of trampolines, for now.  */
  flag_trampolines = 1;

  /* Performs whatever initialization steps needed by the language-dependent
     lexical analyzer.  */
  gnat_init_decl_processing ();

  /* Add the input filename as the last argument.  */
  gnat_argv[gnat_argc] = (char *) main_input_filename;
  gnat_argc++;
  gnat_argv[gnat_argc] = 0;

  global_dc->internal_error = &internal_error_function;

  /* Show that REFERENCE_TYPEs are internal and should be Pmode.  */
  internal_reference_types ();

  set_lang_adjust_rli (gnat_adjust_rli);

  return true;
}

/* This function is called indirectly from toplev.c to handle incomplete
   declarations, i.e. VAR_DECL nodes whose DECL_SIZE is zero.  To be precise,
   compile_file in toplev.c makes an indirect call through the function pointer
   incomplete_decl_finalize_hook which is initialized to this routine in
   init_decl_processing.  */

static void
gnat_finish_incomplete_decl (tree dont_care ATTRIBUTE_UNUSED)
{
  gigi_abort (202);
}

/* Compute the alignment of the largest mode that can be used for copying
   objects.  */

void
gnat_compute_largest_alignment (void)
{
  enum machine_mode mode;

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_INT); mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if (mov_optab->handlers[(int) mode].insn_code != CODE_FOR_nothing)
      largest_move_alignment = MIN (BIGGEST_ALIGNMENT,
				    MAX (largest_move_alignment,
					 GET_MODE_ALIGNMENT (mode)));
}

/* If we are using the GCC mechanism to process exception handling, we
   have to register the personality routine for Ada and to initialize
   various language dependent hooks.  */

void
gnat_init_gcc_eh (void)
{
  /* We shouldn't do anything if the No_Exceptions_Handler pragma is set,
     though. This could for instance lead to the emission of tables with
     references to symbols (such as the Ada eh personality routine) within
     libraries we won't link against.  */
  if (No_Exception_Handlers_Set ())
    return;

  /* Tell GCC we are handling cleanup actions through exception propagation.
     This opens possibilities that we don't take advantage of yet, but is
     nonetheless necessary to ensure that fixup code gets assigned to the
     right exception regions.  */
  using_eh_for_cleanups ();

  eh_personality_libfunc = init_one_libfunc ("__gnat_eh_personality");
  lang_eh_type_covers = gnat_eh_type_covers;
  lang_eh_runtime_type = gnat_eh_runtime_type;

  /* Turn on -fexceptions and -fnon-call-exceptions. The first one triggers
     the generation of the necessary exception runtime tables. The second one
     is useful for two reasons: 1/ we map some asynchronous signals like SEGV
     to exceptions, so we need to ensure that the insns which can lead to such
     signals are correctly attached to the exception region they pertain to,
     2/ Some calls to pure subprograms are handled as libcall blocks and then
     marked as "cannot trap" if the flag is not set (see emit_libcall_block).
     We should not let this be since it is possible for such calls to actually
     raise in Ada.  */

  flag_exceptions = 1;
  flag_non_call_exceptions = 1;

  init_eh ();
#ifdef DWARF2_UNWIND_INFO
  if (dwarf2out_do_frame ())
    dwarf2out_frame_init ();
#endif
}

/* Language hooks, first one to print language-specific items in a DECL.  */

static void
gnat_print_decl (FILE *file, tree node, int indent)
{
  switch (TREE_CODE (node))
    {
    case CONST_DECL:
      print_node (file, "const_corresponding_var",
		  DECL_CONST_CORRESPONDING_VAR (node), indent + 4);
      break;

    case FIELD_DECL:
      print_node (file, "original field", DECL_ORIGINAL_FIELD (node),
		  indent + 4);
      break;

    default:
      break;
    }
}

static void
gnat_print_type (FILE *file, tree node, int indent)
{
  switch (TREE_CODE (node))
    {
    case FUNCTION_TYPE:
      print_node (file, "ci_co_list", TYPE_CI_CO_LIST (node), indent + 4);
      break;

    case ENUMERAL_TYPE:
      print_node (file, "RM size", TYPE_RM_SIZE_ENUM (node), indent + 4);
      break;

    case INTEGER_TYPE:
      if (TYPE_MODULAR_P (node))
	print_node (file, "modulus", TYPE_MODULUS (node), indent + 4);
      else if (TYPE_HAS_ACTUAL_BOUNDS_P (node))
	print_node (file, "actual bounds", TYPE_ACTUAL_BOUNDS (node),
		    indent + 4);
      else if (TYPE_VAX_FLOATING_POINT_P (node))
	;
      else
	print_node (file, "index type", TYPE_INDEX_TYPE (node), indent + 4);

      print_node (file, "RM size", TYPE_RM_SIZE_INT (node), indent + 4);
      break;

    case ARRAY_TYPE:
      print_node (file,"actual bounds", TYPE_ACTUAL_BOUNDS (node), indent + 4);
      break;

    case RECORD_TYPE:
      if (TYPE_IS_FAT_POINTER_P (node) || TYPE_CONTAINS_TEMPLATE_P (node))
	print_node (file, "unconstrained array",
		    TYPE_UNCONSTRAINED_ARRAY (node), indent + 4);
      else
	print_node (file, "Ada size", TYPE_ADA_SIZE (node), indent + 4);
      break;

    case UNION_TYPE:
    case QUAL_UNION_TYPE:
      print_node (file, "Ada size", TYPE_ADA_SIZE (node), indent + 4);
      break;

    default:
      break;
    }
}

static const char *
gnat_printable_name (tree decl, int verbosity)
{
  const char *coded_name = IDENTIFIER_POINTER (DECL_NAME (decl));
  char *ada_name = (char *) ggc_alloc (strlen (coded_name) * 2 + 60);

  __gnat_decode (coded_name, ada_name, 0);

  if (verbosity == 2)
    {
      Set_Identifier_Casing (ada_name, (char *) DECL_SOURCE_FILE (decl));
      ada_name = Name_Buffer;
    }

  return (const char *) ada_name;
}

/* Expands GNAT-specific GCC tree nodes.  The only ones we support
   here are TRANSFORM_EXPR, ALLOCATE_EXPR, USE_EXPR and NULL_EXPR.  */

static rtx
gnat_expand_expr (tree exp, rtx target, enum machine_mode tmode,
		  int modifier, rtx *alt_rtl)
{
  tree type = TREE_TYPE (exp);
  tree new;
  rtx result;

  /* If this is a statement, call the expansion routine for statements.  */
  if (IS_STMT (exp))
    {
      gnat_expand_stmt (exp);
      return const0_rtx;
    }

  /* Update EXP to be the new expression to expand.  */
  switch (TREE_CODE (exp))
    {
    case TRANSFORM_EXPR:
      gnat_to_code (TREE_COMPLEXITY (exp));
      return const0_rtx;
      break;

    case NULL_EXPR:
      expand_expr (TREE_OPERAND (exp, 0), const0_rtx, VOIDmode, 0);

      /* We aren't going to be doing anything with this memory, but allocate
	 it anyway.  If it's variable size, make a bogus address.  */
      if (! host_integerp (TYPE_SIZE_UNIT (type), 1))
	result = gen_rtx_MEM (BLKmode, virtual_stack_vars_rtx);
      else
	result = assign_temp (type, 0, TREE_ADDRESSABLE (exp), 1);

      return result;

    case ALLOCATE_EXPR:
      return
	allocate_dynamic_stack_space
	  (expand_expr (TREE_OPERAND (exp, 0), NULL_RTX, TYPE_MODE (sizetype),
			EXPAND_NORMAL),
	   NULL_RTX, tree_low_cst (TREE_OPERAND (exp, 1), 1));

    case USE_EXPR:
      if (target != const0_rtx)
	gigi_abort (203);

      /* First write a volatile ASM_INPUT to prevent anything from being
	 moved.  */
      result = gen_rtx_ASM_INPUT (VOIDmode, "");
      MEM_VOLATILE_P (result) = 1;
      emit_insn (result);

      result = expand_expr (TREE_OPERAND (exp, 0), NULL_RTX, VOIDmode,
			    modifier);
      emit_insn (gen_rtx_USE (VOIDmode, result));
      return target;

    case GNAT_NOP_EXPR:
      return expand_expr_real (build1 (NOP_EXPR, type, TREE_OPERAND (exp, 0)),
			       target, tmode, modifier, alt_rtl);

    case UNCONSTRAINED_ARRAY_REF:
      /* If we are evaluating just for side-effects, just evaluate our
	 operand.  Otherwise, abort since this code should never appear
	 in a tree to be evaluated (objects aren't unconstrained).  */
      if (target == const0_rtx || TREE_CODE (type) == VOID_TYPE)
	return expand_expr (TREE_OPERAND (exp, 0), const0_rtx,
			    VOIDmode, modifier);

      /* ... fall through ... */

    default:
      gigi_abort (201);
    }

  return expand_expr_real (new, target, tmode, modifier, alt_rtl);
}

/* Adjusts the RLI used to layout a record after all the fields have been
   added.  We only handle the packed case and cause it to use the alignment
   that will pad the record at the end.  */

static void
gnat_adjust_rli (record_layout_info rli ATTRIBUTE_UNUSED)
{
#if 0
  /* ??? This code seems to have no actual effect; record_align should already
     reflect the largest alignment desired by a field.  jason 2003-04-01  */
  unsigned int record_align = rli->unpadded_align;
  tree field;

  /* If an alignment has been specified, don't use anything larger unless we
     have to.  */
  if (TYPE_ALIGN (rli->t) != 0 && TYPE_ALIGN (rli->t) < record_align)
    record_align = MAX (rli->record_align, TYPE_ALIGN (rli->t));

  /* If any fields have variable size, we need to force the record to be at
     least as aligned as the alignment of that type.  */
  for (field = TYPE_FIELDS (rli->t); field; field = TREE_CHAIN (field))
    if (TREE_CODE (DECL_SIZE_UNIT (field)) != INTEGER_CST)
      record_align = MAX (record_align, DECL_ALIGN (field));

  if (TYPE_PACKED (rli->t))
    rli->record_align = record_align;
#endif
}

/* Make a TRANSFORM_EXPR to later expand GNAT_NODE into code.  */

tree
make_transform_expr (Node_Id gnat_node)
{
  tree gnu_result = build (TRANSFORM_EXPR, void_type_node);

  TREE_SIDE_EFFECTS (gnu_result) = 1;
  TREE_COMPLEXITY (gnu_result) = gnat_node;
  return gnu_result;
}

/* Update the setjmp buffer BUF with the current stack pointer.  We assume
   here that a __builtin_setjmp was done to BUF.  */

void
update_setjmp_buf (tree buf)
{
  enum machine_mode sa_mode = Pmode;
  rtx stack_save;

#ifdef HAVE_save_stack_nonlocal
  if (HAVE_save_stack_nonlocal)
    sa_mode = insn_data[(int) CODE_FOR_save_stack_nonlocal].operand[0].mode;
#endif
#ifdef STACK_SAVEAREA_MODE
  sa_mode = STACK_SAVEAREA_MODE (SAVE_NONLOCAL);
#endif

  stack_save
    = gen_rtx_MEM (sa_mode,
		   memory_address
		   (sa_mode,
		    plus_constant (expand_expr
				   (build_unary_op (ADDR_EXPR, NULL_TREE, buf),
				    NULL_RTX, VOIDmode, 0),
				   2 * GET_MODE_SIZE (Pmode))));

#ifdef HAVE_setjmp
  if (HAVE_setjmp)
    emit_insn (gen_setjmp ());
#endif

  emit_stack_save (SAVE_NONLOCAL, &stack_save, NULL_RTX);
}

/* These routines are used in conjunction with GCC exception handling.  */

/* Map compile-time to run-time tree for GCC exception handling scheme.  */

static tree
gnat_eh_runtime_type (tree type)
{
  return type;
}

/* Return true if type A catches type B. Callback for flow analysis from
   the exception handling part of the back-end.  */

static int
gnat_eh_type_covers (tree a, tree b)
{
  /* a catches b if they represent the same exception id or if a
     is an "others".

     ??? integer_zero_node for "others" is hardwired in too many places
     currently.  */
  return (a == b || a == integer_zero_node);
}

/* See if DECL has an RTL that is indirect via a pseudo-register or a
   memory location and replace it with an indirect reference if so.
   This improves the debugger's ability to display the value.  */

void
adjust_decl_rtl (tree decl)
{
  tree new_type;

  /* If this decl is already indirect, don't do anything.  This should
     mean that the decl cannot be indirect, but there's no point in
     adding an abort to check that.  */
  if (TREE_CODE (decl) != CONST_DECL
      && ! DECL_BY_REF_P (decl)
      && (GET_CODE (DECL_RTL (decl)) == MEM
	  && (GET_CODE (XEXP (DECL_RTL (decl), 0)) == MEM
	      || (GET_CODE (XEXP (DECL_RTL (decl), 0)) == REG
		  && (REGNO (XEXP (DECL_RTL (decl), 0))
		      > LAST_VIRTUAL_REGISTER))))
      /* We can't do this if the reference type's mode is not the same
	 as the current mode, which means this may not work on mixed 32/64
	 bit systems.  */
      && (new_type = build_reference_type (TREE_TYPE (decl))) != 0
      && TYPE_MODE (new_type) == GET_MODE (XEXP (DECL_RTL (decl), 0))
      /* If this is a PARM_DECL, we can only do it if DECL_INCOMING_RTL
	 is also an indirect and of the same mode and if the object is
	 readonly, the latter condition because we don't want to upset the
	 handling of CICO_LIST.  */
      && (TREE_CODE (decl) != PARM_DECL
	  || (GET_CODE (DECL_INCOMING_RTL (decl)) == MEM
	      && (TYPE_MODE (new_type)
		  == GET_MODE (XEXP (DECL_INCOMING_RTL (decl), 0)))
	      && TREE_READONLY (decl))))
    {
      new_type
	= build_qualified_type (new_type,
				(TYPE_QUALS (new_type) | TYPE_QUAL_CONST));

      DECL_POINTS_TO_READONLY_P (decl) = TREE_READONLY (decl);
      DECL_BY_REF_P (decl) = 1;
      SET_DECL_RTL (decl, XEXP (DECL_RTL (decl), 0));
      TREE_TYPE (decl) = new_type;
      DECL_MODE (decl) = TYPE_MODE (new_type);
      DECL_ALIGN (decl) = TYPE_ALIGN (new_type);
      DECL_SIZE (decl) = TYPE_SIZE (new_type);

      if (TREE_CODE (decl) == PARM_DECL)
	DECL_INCOMING_RTL (decl) = XEXP (DECL_INCOMING_RTL (decl), 0);

      /* If DECL_INITIAL was set, it should be updated to show that
	 the decl is initialized to the address of that thing.
	 Otherwise, just set it to the address of this decl.
	 It needs to be set so that GCC does not think the decl is
	 unused.  */
      DECL_INITIAL (decl)
	= build1 (ADDR_EXPR, new_type,
		  DECL_INITIAL (decl) != 0 ? DECL_INITIAL (decl) : decl);
    }
}

/* Record the current code position in GNAT_NODE.  */

void
record_code_position (Node_Id gnat_node)
{
  if (global_bindings_p ())
    {
      /* Make a dummy entry so multiple things at the same location don't
	 end up in the same place.  */
      add_pending_elaborations (NULL_TREE, NULL_TREE);
      save_gnu_tree (gnat_node, get_elaboration_location (), 1);
    }
  else
    /* Always emit another insn in case marking the last insn
       addressable needs some fixups and also for above reason.  */
    save_gnu_tree (gnat_node,
		   build (RTL_EXPR, void_type_node, NULL_TREE,
			  (tree) emit_note (NOTE_INSN_DELETED)),
		   1);
}

/* Insert the code for GNAT_NODE at the position saved for that node.  */

void
insert_code_for (Node_Id gnat_node)
{
  if (global_bindings_p ())
    {
      push_pending_elaborations ();
      gnat_to_code (gnat_node);
      Check_Elaboration_Code_Allowed (gnat_node);
      insert_elaboration_list (get_gnu_tree (gnat_node));
      pop_pending_elaborations ();
    }
  else
    {
      rtx insns;

      do_pending_stack_adjust ();
      start_sequence ();
      mark_all_temps_used ();
      gnat_to_code (gnat_node);
      do_pending_stack_adjust ();
      insns = get_insns ();
      end_sequence ();
      emit_insn_after (insns, RTL_EXPR_RTL (get_gnu_tree (gnat_node)));
    }
}

/* Get the alias set corresponding to a type or expression.  */

static HOST_WIDE_INT
gnat_get_alias_set (tree type)
{
  /* If this is a padding type, use the type of the first field.  */
  if (TREE_CODE (type) == RECORD_TYPE
      && TYPE_IS_PADDING_P (type))
    return get_alias_set (TREE_TYPE (TYPE_FIELDS (type)));

  /* If the type is an unconstrained array, use the type of the
     self-referential array we make.  */
  else if (TREE_CODE (type) == UNCONSTRAINED_ARRAY_TYPE)
    return
      get_alias_set (TREE_TYPE (TREE_TYPE (TYPE_FIELDS (TREE_TYPE (type)))));


  return -1;
}

/* GNU_TYPE is a type. Determine if it should be passed by reference by
   default.  */

int
default_pass_by_ref (tree gnu_type)
{
  CUMULATIVE_ARGS cum;

  INIT_CUMULATIVE_ARGS (cum, NULL_TREE, NULL_RTX, 0, 2);

  /* We pass aggregates by reference if they are sufficiently large.  The
     choice of constant here is somewhat arbitrary.  We also pass by
     reference if the target machine would either pass or return by
     reference.  Strictly speaking, we need only check the return if this
     is an In Out parameter, but it's probably best to err on the side of
     passing more things by reference.  */
  return (0
#ifdef FUNCTION_ARG_PASS_BY_REFERENCE
	  || FUNCTION_ARG_PASS_BY_REFERENCE (cum, TYPE_MODE (gnu_type),
					     gnu_type, 1)
#endif
	  || targetm.calls.return_in_memory (gnu_type, NULL_TREE)
	  || (AGGREGATE_TYPE_P (gnu_type)
	      && (! host_integerp (TYPE_SIZE (gnu_type), 1)
		  || 0 < compare_tree_int (TYPE_SIZE (gnu_type),
					   8 * TYPE_ALIGN (gnu_type)))));
}

/* GNU_TYPE is the type of a subprogram parameter.  Determine from the type if
   it should be passed by reference. */

int
must_pass_by_ref (tree gnu_type)
{
  /* We pass only unconstrained objects, those required by the language
     to be passed by reference, and objects of variable size.  The latter
     is more efficient, avoids problems with variable size temporaries,
     and does not produce compatibility problems with C, since C does
     not have such objects.  */
  return (TREE_CODE (gnu_type) == UNCONSTRAINED_ARRAY_TYPE
	  || (AGGREGATE_TYPE_P (gnu_type) && TYPE_BY_REFERENCE_P (gnu_type))
	  || (TYPE_SIZE (gnu_type) != 0
	      && TREE_CODE (TYPE_SIZE (gnu_type)) != INTEGER_CST));
}

/* This function is called by the front end to enumerate all the supported
   modes for the machine.  We pass a function which is called back with
   the following integer parameters:

   FLOAT_P	nonzero if this represents a floating-point mode
   COMPLEX_P	nonzero is this represents a complex mode
   COUNT	count of number of items, nonzero for vector mode
   PRECISION	number of bits in data representation
   MANTISSA	number of bits in mantissa, if FP and known, else zero.
   SIZE		number of bits used to store data
   ALIGN	number of bits to which mode is aligned.  */

void
enumerate_modes (void (*f) (int, int, int, int, int, int, unsigned int))
{
  enum machine_mode i;

  for (i = 0; i < NUM_MACHINE_MODES; i++)
    {
      enum machine_mode j;
      bool float_p = 0;
      bool complex_p = 0;
      bool vector_p = 0;
      bool skip_p = 0;
      int mantissa = 0;
      enum machine_mode inner_mode = i;

      switch (GET_MODE_CLASS (i))
	{
	case MODE_INT:
	  break;
	case MODE_FLOAT:
	  float_p = 1;
	  break;
	case MODE_COMPLEX_INT:
	  complex_p = 1;
	  inner_mode = GET_MODE_INNER (i);
	  break;
	case MODE_COMPLEX_FLOAT:
	  float_p = 1;
	  complex_p = 1;
	  inner_mode = GET_MODE_INNER (i);
	  break;
	case MODE_VECTOR_INT:
	  vector_p = 1;
	  inner_mode = GET_MODE_INNER (i);
	  break;
	case MODE_VECTOR_FLOAT:
	  float_p = 1;
	  vector_p = 1;
	  inner_mode = GET_MODE_INNER (i);
	  break;
	default:
	  skip_p = 1;
	}

      /* Skip this mode if it's one the front end doesn't need to know about
	 (e.g., the CC modes) or if there is no add insn for that mode (or
	 any wider mode), meaning it is not supported by the hardware.  If
	 this a complex or vector mode, we care about the inner mode.  */
      for (j = inner_mode; j != VOIDmode; j = GET_MODE_WIDER_MODE (j))
	if (add_optab->handlers[j].insn_code != CODE_FOR_nothing)
	  break;

      if (float_p)
	{
	  const struct real_format *fmt = REAL_MODE_FORMAT (inner_mode);

	  mantissa = fmt->p * fmt->log2_b;
	}

      if (!skip_p && j != VOIDmode)
	(*f) (float_p, complex_p, vector_p ? GET_MODE_NUNITS (i) : 0,
	      GET_MODE_BITSIZE (i), mantissa,
	      GET_MODE_SIZE (i) * BITS_PER_UNIT, GET_MODE_ALIGNMENT (i));
    }
}

int
fp_prec_to_size (int prec)
{
  enum machine_mode mode;

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_FLOAT); mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if (GET_MODE_PRECISION (mode) == prec)
      return GET_MODE_BITSIZE (mode);

  abort ();
}

int
fp_size_to_prec (int size)
{
  enum machine_mode mode;

  for (mode = GET_CLASS_NARROWEST_MODE (MODE_FLOAT); mode != VOIDmode;
       mode = GET_MODE_WIDER_MODE (mode))
    if (GET_MODE_BITSIZE (mode) == size)
      return GET_MODE_PRECISION (mode);

  abort ();
}

