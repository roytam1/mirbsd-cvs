/*Pascal types.

  Copyright (C) 1987-2005 Free Software Foundation, Inc.

  Authors: Jukka Virtanen <jtv@hut.fi>
           Peter Gerwinski <peter@gerwinski.de>
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

#include "gpc.h"
#include "rts/constants.h"

#ifndef LONG_TYPE_SIZE
#define LONG_TYPE_SIZE BITS_PER_WORD
#endif

static tree type_for_size1 PARAMS ((unsigned, int));
static int sce_cmp PARAMS ((const PTR, const PTR));
static tree limited_set PARAMS ((tree));
static int has_side_effects PARAMS ((tree, int));
static void check_nonconstants PARAMS ((tree));

tree
check_result_type (type)
     tree type;
{
  CHK_EM (type);
  if (TREE_CODE (type) == VOID_TYPE)
    error ("function result must not be `Void' (use a procedure instead)");
  else if (contains_file_p (type))
    error ("function result must not be a file");
  else if (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (type))
    error ("function result must not be an undiscriminated schema type");
  else if (PASCAL_PROCEDURAL_TYPE (type))
    error ("function result must not be a procedural type");
  else
    {
      if (PASCAL_TYPE_OBJECT (type))
        {
          if (TYPE_LANG_CODE_TEST (type, PASCAL_LANG_ABSTRACT_OBJECT))
            error ("abstract object type declared as function result type");
          else if (co->warn_object_assignment)
            warning ("object type declared as function result type");
        }
      if (!SCALAR_TYPE (TREE_CODE (type)))
        chk_dialect ("structured function result types are", NOT_CLASSIC_PASCAL);
      return type;
    }
  return error_mark_node;
}

/* Return an unsigned type the same as TYPE in other respects. */
tree
unsigned_type (type)
     tree type;
{
  tree type1 = TYPE_MAIN_VARIANT (type);
  return TREE_UNSIGNED (type) ? type
    : type1 == byte_integer_type_node ? byte_unsigned_type_node
    : type1 == pascal_integer_type_node ? pascal_cardinal_type_node
    : type1 == integer_type_node ? unsigned_type_node
    : type1 == short_integer_type_node ? short_unsigned_type_node
    : type1 == long_integer_type_node ? long_unsigned_type_node
    : type1 == long_long_integer_type_node ? long_long_unsigned_type_node
    : type1 == intDI_type_node ? unsigned_intDI_type_node
    : type1 == intSI_type_node ? unsigned_intSI_type_node
    : type1 == intHI_type_node ? unsigned_intHI_type_node
    : type1 == intQI_type_node ? unsigned_intQI_type_node
    : signed_or_unsigned_type (1, type);
}

/* Return a signed type the same as TYPE in other respects. */
tree
signed_type (type)
     tree type;
{
  tree type1 = TYPE_MAIN_VARIANT (type);
  return !TREE_UNSIGNED (type) ? type
    : type1 == byte_unsigned_type_node ? byte_integer_type_node
    : type1 == pascal_cardinal_type_node ? pascal_integer_type_node
    : type1 == unsigned_type_node ? integer_type_node
    : type1 == short_unsigned_type_node ? short_integer_type_node
    : type1 == long_unsigned_type_node ? long_integer_type_node
    : type1 == long_long_unsigned_type_node ? long_long_integer_type_node
    : type1 == unsigned_intDI_type_node ? intDI_type_node
    : type1 == unsigned_intSI_type_node ? intSI_type_node
    : type1 == unsigned_intHI_type_node ? intHI_type_node
    : type1 == unsigned_intQI_type_node ? intQI_type_node
    : signed_or_unsigned_type (0, type);
}

/* Return an integer type with BITS bits of precision,
   that is unsigned if UNSIGNEDP is nonzero, otherwise signed. */
static tree
type_for_size1 (bits, unsignedp)
     unsigned bits;
     int unsignedp;
{
  if (bits == TYPE_PRECISION (pascal_integer_type_node))
    return unsignedp ? pascal_cardinal_type_node : pascal_integer_type_node;
  if (bits == TYPE_PRECISION (integer_type_node))
    return unsignedp ? unsigned_type_node : integer_type_node;
  if (bits == TYPE_PRECISION (byte_integer_type_node))
    return unsignedp ? byte_unsigned_type_node : byte_integer_type_node;
  if (bits == TYPE_PRECISION (short_integer_type_node))
    return unsignedp ? short_unsigned_type_node : short_integer_type_node;
  if (bits == TYPE_PRECISION (long_integer_type_node))
    return unsignedp ? long_unsigned_type_node : long_integer_type_node;
  if (bits == TYPE_PRECISION (long_long_integer_type_node))
    return unsignedp ? long_long_unsigned_type_node : long_long_integer_type_node;
  return NULL_TREE;
}

/* Return an integer type with BITS bits of precision,
   that is unsigned if UNSIGNEDP is nonzero, otherwise signed. */
tree
type_for_size (bits, unsignedp)
     unsigned bits;
     int unsignedp;
{
  tree t = type_for_size1 (bits, unsignedp);
  if (t)
    return t;
  if (bits <= TYPE_PRECISION (intQI_type_node))
    return unsignedp ? unsigned_intQI_type_node : intQI_type_node;
  if (bits <= TYPE_PRECISION (intHI_type_node))
    return unsignedp ? unsigned_intHI_type_node : intHI_type_node;
  if (bits <= TYPE_PRECISION (intSI_type_node))
    return unsignedp ? unsigned_intSI_type_node : intSI_type_node;
  if (bits <= TYPE_PRECISION (intDI_type_node))
    return unsignedp ? unsigned_intDI_type_node : intDI_type_node;
  if (bits <= TYPE_PRECISION (intTI_type_node))
    return unsignedp ? unsigned_intTI_type_node : intTI_type_node;
  assert (0);
}

/* Return a type of the same precision as TYPE and unsigned or signed
   according to UNSIGNEDP. */
tree
signed_or_unsigned_type (unsignedp, type)
     int unsignedp;
     tree type;
{
  tree t;
  if (!ORDINAL_TYPE (TREE_CODE (type)) || TREE_UNSIGNED (type) == unsignedp)
    return type;
  t = type_for_size1 (TYPE_PRECISION (type), unsignedp);
  return t ? t : type;
}

/* Return a data type that has machine mode MODE. If the mode is an integer,
   then UNSIGNEDP selects between signed and unsigned types. */
tree
type_for_mode (mode, unsignedp)
     enum machine_mode mode;
     int unsignedp;
{
  if (mode == TYPE_MODE (pascal_integer_type_node))
    return unsignedp ? pascal_cardinal_type_node : pascal_integer_type_node;
  if (mode == TYPE_MODE (integer_type_node))
    return unsignedp ? unsigned_type_node : integer_type_node;
  if (mode == TYPE_MODE (byte_integer_type_node))
    return unsignedp ? byte_unsigned_type_node : byte_integer_type_node;
  if (mode == TYPE_MODE (short_integer_type_node))
    return unsignedp ? short_unsigned_type_node : short_integer_type_node;
  if (mode == TYPE_MODE (long_integer_type_node))
    return unsignedp ? long_unsigned_type_node : long_integer_type_node;
  if (mode == TYPE_MODE (long_long_integer_type_node))
    return unsignedp ? long_long_unsigned_type_node : long_long_integer_type_node;
  if (mode == TYPE_MODE (intQI_type_node))
    return unsignedp ? unsigned_intQI_type_node : intQI_type_node;
  if (mode == TYPE_MODE (intHI_type_node))
    return unsignedp ? unsigned_intHI_type_node : intHI_type_node;
  if (mode == TYPE_MODE (intSI_type_node))
    return unsignedp ? unsigned_intSI_type_node : intSI_type_node;
  if (mode == TYPE_MODE (intDI_type_node))
    return unsignedp ? unsigned_intDI_type_node : intDI_type_node;
  if (mode == TYPE_MODE (intTI_type_node))
    return unsignedp ? unsigned_intTI_type_node : intTI_type_node;
  if (mode == TYPE_MODE (float_type_node))
    return float_type_node;
  if (mode == TYPE_MODE (double_type_node))
    return double_type_node;
  if (mode == TYPE_MODE (long_double_type_node))
    return long_double_type_node;
  if (mode == TYPE_MODE (build_pointer_type (char_type_node)))
    return build_pointer_type (char_type_node);
  if (mode == TYPE_MODE (build_pointer_type (pascal_integer_type_node)))
    return build_pointer_type (pascal_integer_type_node);
  if (mode == TYPE_MODE (build_pointer_type (integer_type_node)))
    return build_pointer_type (integer_type_node);
  return NULL_TREE;
}

static int
sce_cmp (xp, yp)
      const PTR xp;
      const PTR yp;
{
  return const_lt (TREE_PURPOSE (*(tree *) xp), TREE_PURPOSE (*(tree *) yp)) ? -1 : 1;
}

/* Build a constructor node for set elements.
   construct_set later converts this to a set. */
tree
build_set_constructor (elements)
     tree elements;
{
  tree t, m;
  int is_constant = 1, is_intcst = 1, side_effects = 0, n = 0;
  for (m = elements; m; m = TREE_CHAIN (m))
    {
      tree lower = TREE_PURPOSE (m), upper = TREE_VALUE (m);
      if (!lower || EM (lower) || (upper && EM (upper)))
        return error_mark_node;
      STRIP_TYPE_NOPS (lower);
      lower = fold (string_may_be_char (lower, 1));
      if (upper)
        {
          STRIP_TYPE_NOPS (upper);
          upper = fold (string_may_be_char (upper, 1));
        }
      if (!ORDINAL_TYPE (TREE_CODE (TREE_TYPE (lower))))
        {
          error ("set constructor elements must be of ordinal type");
          return error_mark_node;
        }
      if (upper && !comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (lower)), TYPE_MAIN_VARIANT (TREE_TYPE (upper))))
        {
          error ("set range bounds are of incompatible type");
          return error_mark_node;
        }
      if (m != elements
          && !comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (TREE_PURPOSE (elements))),
                         TYPE_MAIN_VARIANT (TREE_TYPE (lower))))
        {
          error ("set constructor elements are of incompatible type");
          return error_mark_node;
        }
      if (upper
          && TREE_CODE (lower) == INTEGER_CST
          && TREE_CODE (upper) == INTEGER_CST
          && tree_int_cst_lt (upper, lower))
        {
          error ("set constructor range is empty");
          return error_mark_node;
        }
      if (!TREE_CONSTANT (lower) || (upper && !TREE_CONSTANT (upper)))
        is_constant = 0;
      if (TREE_CODE (lower) != INTEGER_CST || (upper && TREE_CODE (upper) != INTEGER_CST))
        is_intcst = 0;
      if (TREE_SIDE_EFFECTS (lower) || (upper && TREE_SIDE_EFFECTS (upper)))
        side_effects = 1;
      if (!upper)  /* Backend requires upper to be set. */
        {
          if (TREE_SIDE_EFFECTS (lower))
            lower = save_expr (lower);
          upper = lower;
        }
      TREE_PURPOSE (m) = lower;
      TREE_VALUE (m) = upper;
      n++;
    }
  /* A single element/range with side-effects should be safe. */
  if (side_effects && TREE_CHAIN (elements))
    {
      warning ("expressions with side-effects in set constructors are");
      warning (" problematic since evaluation is implementation-dependent");
    }
  /* Sort and merge constant constructor elements */
  if (is_intcst && n)
    {
      tree *p = alloca (n * sizeof (tree));
      int i;
      for (m = copy_list (elements), i = 0; m; m = TREE_CHAIN (m), i++)
        p[i] = m;
      assert (i == n);
      qsort (p, n, sizeof (tree), sce_cmp);
      elements = p[0];
      i = 0;
      while (i < n)
        {
          int j = i + 1;
          tree u = TREE_VALUE (p[i]);
          while (j < n && !const_plus1_lt (u, TREE_PURPOSE (p[j])))
            {
              tree u2 = TREE_VALUE (p[j]);
              if (const_lt (u, u2))
                u = u2;
              j++;
            }
          TREE_VALUE (p[i]) = u;
          TREE_CHAIN (p[i]) = j < n ? p[j] : NULL_TREE;
          i = j;
        }
    }
  t = make_node (CONSTRUCTOR);
  TREE_TYPE (t) = empty_set_type_node;  /* real type not yet known */
  CONSTRUCTOR_ELTS (t) = elements;
  TREE_CONSTANT (t) = TREE_STATIC (t) = is_constant;
  PASCAL_CONSTRUCTOR_INT_CST (t) = is_intcst;
  TREE_SIDE_EFFECTS (t) = side_effects;
  TREE_ADDRESSABLE (t) = 1;
  return t;
}

static tree
limited_set (lo)
     tree lo;
{
  tree hi = fold (build_pascal_binary_op (PLUS_EXPR, lo, size_int (co->set_limit - 1)));
  warning ("constructing limited integer set `%li .. %li';",
           (long int) TREE_INT_CST_LOW (lo),
           (long int) TREE_INT_CST_LOW (hi));
  warning (" use `--setlimit=NUMBER' to change the size limit at compile time.");
  return hi;
}

/* Build a SET_TYPE node from a set constructor.

   CONSTRUCTOR is a CONSTRUCTOR type node whose CONSTRUCTOR_ELTS
   contains a TREE_LIST of the elements(/pairs) of the set.

   If arg_type == 0, target_or_type is a VAR_DECL node where we should construct our set.
   If arg_type == 1, target_or_type is a SET_TYPE node which we should model our new set after.
   If arg_type == 2, target_or_type is a SET_TYPE node passed as a parameter to a function.
                     (Special case for empty set constructor passing)

   target_or_type is NULL_TREE if we don't know the destination
   where we should put the constructed set, nor the type we should
   be cloning to our constructed set.

   Return NULL_TREE if we assigned the set to the existing TARGET_SET,
   else return the constructor whose TREE_TYPE type we now set. */
tree
construct_set (constructor, target_or_type, arg_type)
     tree constructor, target_or_type;
     int arg_type;
{
  tree elements, elem, set_low, set_high, setsize, this_set_type;
  CHK_EM (constructor);
  elements = CONSTRUCTOR_ELTS (constructor);
  if (!elements && (arg_type == 0 || (arg_type == 1 && !target_or_type)))
    {
      if (arg_type == 0 && target_or_type)
        {
          /* Clear the target set. */
#ifdef EGCS
          tree size = size_binop (CEIL_DIV_EXPR, TYPE_SIZE_UNIT (TREE_TYPE (target_or_type)),
            size_int (TYPE_PRECISION (byte_integer_type_node) / BITS_PER_UNIT));
#else
          tree size = size_binop (CEIL_DIV_EXPR, TYPE_SIZE (TREE_TYPE (target_or_type)), size_int (BITS_PER_UNIT));
#endif
          expand_expr_stmt (build_memset (build_unary_op (ADDR_EXPR, target_or_type, 0),
            size, integer_zero_node));
          return NULL_TREE;
        }
      else
        return constructor;
    }
  if (target_or_type)
    {
      this_set_type = arg_type ? target_or_type : TREE_TYPE (target_or_type);
      set_low = TYPE_MIN_VALUE (TYPE_DOMAIN (this_set_type));
      set_high = TYPE_MAX_VALUE (TYPE_DOMAIN (this_set_type));
    }
  else
    {
      tree type;
      if (elements)
        type = base_type (TREE_TYPE (TREE_PURPOSE (elements)));
      else
        {
          /* Empty set constructor to unknown set? */
          assert (target_or_type);
          type = TREE_TYPE (target_or_type);
        }
      set_low = TYPE_MIN_VALUE (type);
      set_high = TYPE_MAX_VALUE (type);

      /* avoid [-MaxInt .. MaxInt] storage request */
      if (TREE_CODE (type) == INTEGER_TYPE)
        {
          tree size = NULL_TREE;
          set_low = NULL_TREE;
          set_high = NULL_TREE;

          /* Scan for the min and max values */
          for (elem = elements; elem; elem = TREE_CHAIN (elem))
            {
              tree lo = TREE_PURPOSE (elem);
              tree hi = TREE_VALUE (elem);
              assert (hi);  /* only ranges here, see build_set_constructor */
              STRIP_NOPS (lo);
              STRIP_NOPS (hi);
              /* Non-constant bounds. Try to rescue it by looking
                 whether their types have reasonable bounds. */
              while (TREE_CODE (lo) != INTEGER_CST)
                lo = TYPE_MIN_VALUE (TREE_TYPE (lo));
              while (TREE_CODE (hi) != INTEGER_CST)
                hi = TYPE_MAX_VALUE (TREE_TYPE (hi));
              if (!set_low || tree_int_cst_lt (lo, set_low))
                set_low = lo;
              if (!set_high || tree_int_cst_lt (set_high, hi))
                set_high = hi;
            }
          if (set_low && set_high)
            size = fold (build (PLUS_EXPR, pascal_integer_type_node, integer_one_node,
                     fold (build (MINUS_EXPR, pascal_integer_type_node,
                                  convert (pascal_integer_type_node, set_high),
                                  convert (pascal_integer_type_node, set_low)))));

          /* If bounds are constant but too big, construct a limited set. */
          if (size
              && (TREE_OVERFLOW (size)
                  || TREE_INT_CST_HIGH (size) != 0
                  || TREE_INT_CST_LOW (size) == 0  /* overflow */
                  || (unsigned HOST_WIDE_INT) TREE_INT_CST_LOW (size) > co->set_limit))
            size = NULL_TREE;

          if (!size)
            {
              if (!set_low || INT_CST_LT (set_low, integer_zero_node))
                set_low = integer_zero_node;
              set_high = limited_set (set_low);
            }
          type = build_range_type (TREE_TYPE (set_low), set_low, set_high);
          TREE_SET_CODE (type, TREE_CODE (TREE_TYPE (set_low)));
        }
      /* non-constant bounds not yet supported (Why???) */
      assert (int_size_in_bytes (type) != -1);
      this_set_type = build_set_type (type);
    }

  /* Now we know the type of the target set, so we switch the constructor
     type to be the correct type. */
  constructor = copy_node (constructor);
  TREE_TYPE (constructor) = this_set_type;

  setsize = size_binop (MINUS_EXPR, convert (sbitsizetype, set_high), convert (sbitsizetype, set_low));
  if (TREE_INT_CST_HIGH (setsize)
      || (signed HOST_WIDE_INT) TREE_INT_CST_LOW (setsize) < 0
      || (signed HOST_WIDE_INT) TREE_INT_CST_LOW (setsize) + 1 < 0)
    {
      error ("set size too big");
      return error_mark_node;
    }

  /* Check that the constructor elements are of valid type
     and within the allowed range. */
  for (elem = elements; elem; elem = TREE_CHAIN (elem))
    {
      tree lo = TREE_PURPOSE (elem), hi = TREE_VALUE (elem);
      if (!comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (lo)), TYPE_MAIN_VARIANT (TREE_TYPE (this_set_type))))
        error ("type mismatch in set constructor");
      TREE_PURPOSE (elem) = range_check_2 (set_low, set_high, lo);
      CHK_EM (TREE_PURPOSE (elem));
      TREE_VALUE (elem) = hi == lo ? TREE_PURPOSE (elem) : range_check_2 (set_low, set_high, hi);
      CHK_EM (TREE_VALUE (elem));
    }
  return constructor;
}

tree
build_set_type (type)
     tree type;
{
  tree t;
  tree lo = TYPE_MIN_VALUE (type);
  tree hi = TYPE_MAX_VALUE (type);
  CHK_EM (type);
  if (!ORDINAL_TYPE (TREE_CODE (type)))
    {
      error ("set base type must be an ordinal type");
      return error_mark_node;
    }
  if (TREE_CODE (lo) != INTEGER_CST || TREE_CODE (hi) != INTEGER_CST)
    {
      /* Otherwise, layout_type would abort */
      error ("internal GPC error: sets with non-constant bounds are not supported yet");
      return error_mark_node;
    }
  else if (TREE_CODE (type) == INTEGER_TYPE)
    {
      /* Avoid huge sets such as `set of Integer' */
      tree sblo = convert (sbitsizetype, lo);
      tree sbhi = convert (sbitsizetype, hi);
      tree bitsize = size_binop (PLUS_EXPR, size_binop (MINUS_EXPR, sbhi, sblo),
                                 convert (sbitsizetype, integer_one_node));
      if (TREE_INT_CST_HIGH (bitsize) != 0
          || TREE_INT_CST_LOW (bitsize) == 0  /* overflow */
          || (unsigned HOST_WIDE_INT) TREE_INT_CST_LOW (bitsize) > co->set_limit)
        {
          sbhi = limited_set (sblo);
          type = build_range_type (pascal_integer_type_node, sblo, sbhi);
          CHK_EM (type);
        }
    }
  t = make_node (SET_TYPE);
  TREE_TYPE (t) = TYPE_DOMAIN (t) = type;
  layout_type (t);
  return t;
}

/* Append `Chr (0)' to the string VAL. If it is not of variable string (schema)
   type already, copy it to a temporary variable first. Appending is always
   possible in string schemata since the size of the char array within the
   string is calculated to reserve place for the #0. */
tree
convert_to_cstring (val)
     tree val;
{
  tree ch0 = convert (char_type_node, integer_zero_node);
  tree orig_val = val, stmts = NULL_TREE, chr, z;
  int need_cond;

  val = char_may_be_string (val);

  /* A string constant or an `array [0 .. ...] of Char' is already
     acceptable as a CString. Just take the address. */
  if (TREE_CODE (val) == STRING_CST
      || (TREE_CODE (TREE_TYPE (val)) == ARRAY_TYPE
          && TREE_CODE (TREE_TYPE (TYPE_MIN_VALUE (TYPE_DOMAIN (TREE_TYPE (val))))) == INTEGER_TYPE
          && integer_zerop (TYPE_MIN_VALUE (TYPE_DOMAIN (TREE_TYPE (val))))))
    {
      while (TREE_CODE (val) == SAVE_EXPR)
        val = TREE_OPERAND (val, 0);
      return convert (cstring_type_node, build_pascal_unary_op (ADDR_EXPR, val));
    }

  /* Dig out the real string, so save_expr does not need to worry about
     NON_LVALUE_EXPRs and such. Track COMPOUND_EXPRs to put back later. */
  while (TREE_CODE (val) == COMPOUND_EXPR
         || TREE_CODE (val) == NON_LVALUE_EXPR
         || TREE_CODE (val) == SAVE_EXPR
         || TREE_CODE (val) == NOP_EXPR)
    if (TREE_CODE (val) == COMPOUND_EXPR)
      {
        if (stmts)
          stmts = build (COMPOUND_EXPR, void_type_node, TREE_OPERAND (val, 0), stmts);
        else
          stmts = TREE_OPERAND (val, 0);
        val = TREE_OPERAND (val, 1);
      }
    else
      val = TREE_OPERAND (val, 0);

  if (is_variable_string_type (TREE_TYPE (val)))
    {
      if (lvalue_p (val))
        val = build_indirect_ref (save_expr (build_unary_op (ADDR_EXPR, val, 0)), NULL);
      else
        val = save_expr (val);
      need_cond = 1;
    }
  else
    {
      orig_val = val = new_string_by_model (NULL_TREE, val, 1);
      need_cond = 0;
    }

  chr = build_array_ref (PASCAL_STRING_VALUE (val),
          build_pascal_binary_op (PLUS_EXPR, PASCAL_STRING_LENGTH (val), integer_one_node));

  TREE_READONLY (chr) = 0;  /* Avoid warning. */
  z = build_modify_expr (chr, NOP_EXPR, ch0);

  /* Don't actually assign the #0 if the memory location contains one
     already. This prevents crashing at runtime if val is in constant
     storage (whether or not it is, is generally not known at
     compile-time, e.g., if it's a reference parameter). If val is a
     temporary variable just created above, we don't need the extra check. */
  if (need_cond)
    z = build (COND_EXPR, char_type_node, build_pascal_binary_op (EQ_EXPR, chr, ch0), ch0, z);
  if (stmts)
    z = build (COMPOUND_EXPR, void_type_node, stmts, z);
  val = build (COMPOUND_EXPR, TREE_TYPE (orig_val), z, val);
  return convert (cstring_type_node, build_pascal_unary_op (ADDR_EXPR, PASCAL_STRING_VALUE (val)));
}

/* Convert string constants of length 1 (or 0) to char constants. */
tree
string_may_be_char (expr, assignment_compatibility)
     tree expr;
     int assignment_compatibility;
{
  if (expr
      && TREE_CODE (expr) == STRING_CST
      && PASCAL_TREE_FRESH_CST (expr)
      && TREE_STRING_LENGTH (expr) <= 2  /* including the trailing #0 */
      && (assignment_compatibility || TREE_STRING_LENGTH (expr) == 2))
    {
      tree t;
      char ch;
      if (TREE_STRING_LENGTH (expr) == 2)
        ch = TREE_STRING_POINTER (expr)[0];
      else
        {
          /* Assigning an empty string to a char.
             According to Extended Pascal this is allowed. (Ouch!) */
          if (pedantic || !(co->pascal_dialect & E_O_PASCAL))
            pedwarn ("assignment of empty string to a char yields a space");
          ch = ' ';
        }
      t = build_int_2 (ch & ((1 << BITS_PER_UNIT) - 1), 0);
      TREE_TYPE (t) = char_type_node;
      PASCAL_TREE_FRESH_CST (t) = PASCAL_TREE_FRESH_CST (expr);
      return t;
    }
  return expr;
}

/* Convert a char constant to a string constant. (Not necessary anymore for
   one generated by the lexer since it always generates string constants,
   but for an explicitly declared Pascal Char constant.) */
tree
char_may_be_string (expr)
     tree expr;
{
  if (TREE_CODE (expr) == INTEGER_CST && TREE_CODE (TREE_TYPE (expr)) == CHAR_TYPE)
    {
      char buf = TREE_INT_CST_LOW (expr);
      expr = build_string_constant (&buf, 1, PASCAL_TREE_FRESH_CST (expr));
    }
  return expr;
}

/* Since Pascal declaration gives a new type we have to defeat
   caching in `build_pointer_type' */
tree
build_pascal_pointer_type (to_type)
     tree to_type;
{
  if (TYPE_POINTER_TO (to_type))
    to_type = build_type_copy (to_type);
  return build_pointer_type (to_type);
}

/* Our string schema looks like this:
   String (Capacity: Cardinal) = record
     Length: Cardinal;
     String: array [1 .. Capacity + 1] of Char
   end;
   (the `+ 1' is for appending a #0 in convert_to_cstring) */
tree
build_pascal_string_schema (capacity)
     tree capacity;
{
  tree string, fields, string_range, internal_capacity = capacity;
  if (capacity)
    {
      CHK_EM (capacity);
      assert (TREE_CODE (TREE_TYPE (capacity)) == INTEGER_TYPE);
    }

#ifndef EGCS97
  push_obstacks_nochange ();
  end_temporary_allocation ();
#endif

  string = start_struct (RECORD_TYPE);

  fields = build_field (get_identifier ("Capacity"), pascal_cardinal_type_node);

#ifdef PG__NEW_STRINGS
  if (capacity == NULL_TREE)
    {
      internal_capacity = build (COMPONENT_REF, pascal_cardinal_type_node,
        build (PLACEHOLDER_EXPR, string), fields);
#if 0
      capacity = integer_zero_node;
#else
      capacity = pascal_maxint_node; /* @@@@ */
#endif
    }
  size_volatile++;  /* @@ Otherwise compilation of 'russ3a.pas' crashes */
#else
  if (capacity == NULL_TREE)
    internal_capacity = capacity = integer_zero_node;
  size_volatile++;
#endif

  string_range = build_range_type (pascal_integer_type_node, integer_one_node,
                   build_pascal_binary_op (PLUS_EXPR, internal_capacity, integer_one_node));
  fields = chainon (fields,
           chainon (build_field (get_identifier ("length"), pascal_cardinal_type_node),
                    build_field (schema_id, build_simple_array_type (char_type_node, string_range))));
  PASCAL_TREE_DISCRIMINANT (fields /* read: first field, i.e. Capacity */) = 1;
  string = finish_struct (string, fields, 0);

#ifndef PG__NEW_STRINGS
  size_volatile--;
#else
  size_volatile--;  /* @@ */
#endif

#ifndef EGCS97
  pop_obstacks ();
#endif

  CHK_EM (string);
  if (!TYPE_LANG_SPECIFIC (string))
    TYPE_LANG_SPECIFIC (string) = allocate_type_lang_specific ();
  TYPE_LANG_CODE (string) = PASCAL_LANG_DISCRIMINATED_STRING;
  TYPE_LANG_BASE (string) = string_schema_proto_type;
  TYPE_LANG_DECLARED_CAPACITY (string) = capacity;
  TYPE_ALIGN (string) = TYPE_ALIGN (pascal_cardinal_type_node);  /* even within packed records */
  return string;
}

int
is_string_compatible_type (string, error_flag)
     tree string;
     int error_flag;
{
  return TREE_CODE (TREE_TYPE (string)) == CHAR_TYPE || is_string_type (string, error_flag);
}

/* Return 1 if the type of the node STRING is a character array node
            or a string constant or a string schema.
   Return 0 if we know it's not a valid string. */
int
is_string_type (string, error_flag)
     tree string;
     int error_flag;
{
  return TREE_CODE (string) == STRING_CST || is_of_string_type (TREE_TYPE (string), error_flag);
}

int
is_of_string_type (type, error_flag)
     tree type;
     int error_flag;
{
  if (PASCAL_TYPE_STRING (type))
    return 1;

  if (TREE_CODE (type) != ARRAY_TYPE || TREE_CODE (TREE_TYPE (type)) != CHAR_TYPE)
    return 0;

  if (!PASCAL_TYPE_PACKED (type))
    {
      if (co->pascal_dialect && !(co->pascal_dialect & (B_D_PASCAL)))
        return 0;
      if (error_flag)
        chk_dialect ("using unpacked character arrays as strings is", B_D_PASCAL);
    }

  /* String type low index must be one and nonvarying according to ISO */
  if (tree_int_cst_equal (TYPE_MIN_VALUE (TYPE_DOMAIN (type)), integer_one_node))
    return 1;

  if (co->pascal_dialect & C_E_O_PASCAL)
    return 0;

  chk_dialect ("using character arrays with lower bound not 1 as strings is", B_D_M_PASCAL);
  return 1;
}

int
is_variable_string_type (type)
     tree type;
{
  return (TREE_CODE (type) == REFERENCE_TYPE && PASCAL_TYPE_STRING (TREE_TYPE (type)))
         || PASCAL_TYPE_STRING (type);
}

tree
build_discriminants (names, type)
      tree names, type;
{
  tree t;
  if (!ORDINAL_TYPE (TREE_CODE (type)))
    {
      error ("schema discriminant type must be ordinal");
      type = pascal_integer_type_node;
    }
  for (t = names; t; t = TREE_CHAIN (t))
    {
      /* Build VAR_DECL nodes to represent the formal discriminants.
         Store the previous meanings of the identifiers
         in the TREE_PURPOSE fields of the id_list. */
      tree id = TREE_VALUE (t);
      tree decl = TREE_VALUE (t) = build_decl (VAR_DECL, id, type);
      SET_DECL_ASSEMBLER_NAME (decl, id);
      DECL_LANG_SPECIFIC (decl) = allocate_decl_lang_specific ();
      PASCAL_TREE_DISCRIMINANT (decl) = 1;
      TREE_PURPOSE (t) = IDENTIFIER_VALUE (id);
      IDENTIFIER_VALUE (id) = decl;
    }
  return names;
}

/* Check whether the expression EXPR (to be used in type definitions) contains
   formal schema discriminants. This is the case if and only if EXPR contains
   VAR_DECLs with PASCAL_TREE_DISCRIMINANT set. If so, replace them with
   CONVERT_EXPRs and add them to the DECL_LANG_FIXUPLIST field of the
   discriminant's VAR_DECL. */
tree
maybe_schema_discriminant (expr)
     tree expr;
{
  enum tree_code code = TREE_CODE (expr);
  if (code == VAR_DECL && PASCAL_TREE_DISCRIMINANT (expr))
    {
      tree new_expr = build1 (CONVERT_EXPR, TREE_TYPE (expr), expr);
      PASCAL_TREE_DISCRIMINANT (new_expr) = 1;
      DECL_LANG_FIXUPLIST (expr) = tree_cons (NULL_TREE, new_expr, DECL_LANG_FIXUPLIST (expr));
      expr = new_expr;
    }
  else if (code == CALL_EXPR)
    {
      tree t;
      TREE_OPERAND (expr, 0) = maybe_schema_discriminant (TREE_OPERAND (expr, 0));
      for (t = TREE_OPERAND (expr, 1); t; t = TREE_CHAIN (t))
        TREE_VALUE (t) = maybe_schema_discriminant (TREE_VALUE (t));
    }
  else if (code == TREE_LIST)
    {
      tree t;
      for (t = expr; t; t = TREE_CHAIN (t))
        TREE_VALUE (t) = maybe_schema_discriminant (TREE_VALUE (t));
    }
  else if (IS_EXPR_OR_REF_CODE_CLASS (TREE_CODE_CLASS (code)))
    {
      int i, l = NUMBER_OF_OPERANDS (code);
      for (i = FIRST_OPERAND (code); i < l; i++)
        if (TREE_OPERAND (expr, i))
          TREE_OPERAND (expr, i) = maybe_schema_discriminant (TREE_OPERAND (expr, i));
    }
  return expr;
}

static int
has_side_effects (t, had)
     tree t;
     int had;
{
  enum tree_code code = TREE_CODE (t);
  if (TREE_CODE_CLASS (code) == 't')
    {
      tree i = TYPE_GET_INITIALIZER (t);
      if (i && has_side_effects (i, 0))
        return 1;
    }
  if (IS_EXPR_OR_REF_CODE_CLASS (TREE_CODE_CLASS (code)))
    {
      int i, l = NUMBER_OF_OPERANDS (code);
      if (!had && TREE_SIDE_EFFECTS (t))
        return 1;
      for (i = FIRST_OPERAND (code); i < l; i++)
        if (TREE_OPERAND (t, i) && has_side_effects (TREE_OPERAND (t, i), 1))
          return 1;
    }
  switch (TREE_CODE (t))
  {
    case TREE_LIST:
      for (; t; t = TREE_CHAIN (t))
        {
          /* @@ This doesn't strictly belong here. As long as the function is
                only called from build_schema_type, it probably doesn't matter,
                and it's easier than another pass. */
          tree p = TREE_PURPOSE (t);
          if (p && TREE_CODE (p) == IDENTIFIER_NODE)
            p = TREE_PURPOSE (t) = check_identifier (p);

          if ((TREE_VALUE (t) && has_side_effects (TREE_VALUE (t), 0))
              || (p && has_side_effects (p, 0)))
            return 1;
        }
      return 0;

    case VAR_DECL:
      return PASCAL_HAD_SIDE_EFFECTS (t);

    case BOOLEAN_TYPE:
    case CHAR_TYPE:
    case ENUMERAL_TYPE:
    case INTEGER_TYPE:
      return has_side_effects (TYPE_MIN_VALUE (t), 0)
             || has_side_effects (TYPE_MAX_VALUE (t), 0)
             || (TREE_TYPE (t) && has_side_effects (TREE_TYPE (t), 0));
    case ARRAY_TYPE:
      return has_side_effects (TREE_TYPE (t), 0) || has_side_effects (TYPE_DOMAIN (t), 0);
    case RECORD_TYPE:
    case UNION_TYPE:
      {
        tree f;
        if (PASCAL_TYPE_STRING (t))
          return has_side_effects (TYPE_LANG_DECLARED_CAPACITY (t), 0);
        for (f = TYPE_FIELDS (t); f; f = TREE_CHAIN (f))
          {
            if (has_side_effects (TREE_TYPE (f), 0)
                || (PASCAL_TREE_DISCRIMINANT (f) && has_side_effects (DECL_LANG_FIXUPLIST (f), 0)))
              return 1;
          }
        return 0;
      }
    default:
      return 0;
  }
}

/* Return a new schema type with formal discriminants discriminants (a TREE_LIST
   holding VAR_DECL nodes) for the type template TYPE. Return a RECORD_TYPE with
   its TYPE_LANG_CODE set accordingly, having as fields the discriminants plus a
   `_p_Schema' field which contains the actual type. */
tree
build_schema_type (type, discriminants, init)
     tree type, discriminants, init;
{
  tree fields = NULL_TREE, d, tmp, t;
  chk_dialect ("schema types are", E_O_M_PASCAL);
  for (d = discriminants; d; d = TREE_CHAIN (d))
    fields = chainon (fields, build_field (DECL_NAME (TREE_VALUE (d)), TREE_TYPE (TREE_VALUE (d))));
  if (!init && !EM (type))
    init = TYPE_GET_INITIALIZER (type);
  fields = chainon (fields, build_field (schema_id, type));
  for (t = fields; t && !has_side_effects (TREE_TYPE (t), 0); t = TREE_CHAIN (t)) ;
  if (t || (init && has_side_effects (init, 0)))
    error ("expressions with side-effects are not allowed in schema types");
  /* Release the identifiers of the discriminants. We must do this also in case
     of a previous error, but has_side_effects still needs them! */
  for (d = discriminants; d; d = TREE_CHAIN (d))
    {
      tree id = DECL_NAME (TREE_VALUE (d));
      IDENTIFIER_VALUE (id) = TREE_PURPOSE (d);
    }
  /* Do not return before this point! */
  CHK_EM (type);
  t = finish_struct (start_struct (RECORD_TYPE), fields, 1);
  CHK_EM (t);
  TREE_USED (t) = TREE_USED (type);
  if (!TYPE_LANG_SPECIFIC (t))
    TYPE_LANG_SPECIFIC (t) = allocate_type_lang_specific ();
  TYPE_LANG_CODE (t) = PASCAL_LANG_UNDISCRIMINATED_SCHEMA;
  if (init)
    TYPE_LANG_INITIAL (t) = save_nonconstants (init);
  /* Copy the fix-up list from the VAR_DECL's DECL_LANG_FIXUPLIST
     to that of the FIELD_DECL. Mark the discriminants as such. */
  for (d = discriminants, tmp = TYPE_FIELDS (t);
       d && tmp; d = TREE_CHAIN (d), tmp = TREE_CHAIN (tmp))
    {
      DECL_LANG_SPECIFIC (tmp) = allocate_decl_lang_specific ();
      DECL_LANG_FIXUPLIST (tmp) = DECL_LANG_FIXUPLIST (TREE_VALUE (d));
      PASCAL_TREE_DISCRIMINANT (tmp) = 1;
    }
  return t;
}

int
number_of_schema_discriminants (type)
     tree type;
{
  if (PASCAL_TYPE_UNDISCRIMINATED_STRING (type)
      || PASCAL_TYPE_PREDISCRIMINATED_STRING (type))
    return 1;
  if (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (type)
      || PASCAL_TYPE_PREDISCRIMINATED_SCHEMA (type))
    {
      int count = 0;
      tree field;
      for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
        if (PASCAL_TREE_DISCRIMINANT (field))
          count++;
      assert (count);
      return count;
    }
  return 0;
}

/* Pre-discriminate an undiscriminated schema which is of pointer or reference
   type, using its own contents. This makes the schema a valid type but
   preserves the fix-up information needed to derive discriminated schemata
   from this schema. (@@ Do we actually need the latter? -- Frank) */
void
prediscriminate_schema (decl)
     tree decl;
{
  if (!((TREE_CODE (TREE_TYPE (decl)) == POINTER_TYPE
        || TREE_CODE (TREE_TYPE (decl)) == REFERENCE_TYPE)
       /* This might be NULL_TREE while loading a GPI file. */
       && TREE_TYPE (TREE_TYPE (decl))
       && !EM (TREE_TYPE (TREE_TYPE (decl)))))
    return;
  if (PASCAL_TYPE_UNDISCRIMINATED_STRING (TREE_TYPE (TREE_TYPE (decl))))
    {
      tree new_type, string_type = TREE_TYPE (TREE_TYPE (decl));
#ifndef PG__NEW_STRINGS
      tree val = build_component_ref (build_indirect_ref (decl, NULL), get_identifier ("Capacity"));

      size_volatile++;
      new_type = build_pascal_string_schema (val);
      size_volatile--;
#else
      new_type = build_pascal_string_schema (NULL_TREE);
#endif
      if (EM (new_type))
        return;
      TYPE_LANG_CODE (new_type) = PASCAL_LANG_PREDISCRIMINATED_STRING;

      /* Preserve volatility and readonlyness. */
      if (TYPE_READONLY (string_type) || TYPE_VOLATILE (string_type))
        {
          new_type = build_type_copy (new_type);
          TYPE_READONLY (new_type) = TYPE_READONLY (string_type);
          TYPE_VOLATILE (new_type) = TYPE_VOLATILE (string_type);
        }

      /* Return the result, but don't spoil pointers/references
         to "the" generic `String' type. */
      TREE_TYPE (decl) = build_type_copy (TREE_TYPE (decl));
      TREE_TYPE (TREE_TYPE (decl)) = new_type;
    }
  else if (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (TREE_TYPE (TREE_TYPE (decl))))
    {
      tree schema_type = TREE_TYPE (TREE_TYPE (decl)), new_type;
      tree field, discr = NULL_TREE, ref = build_indirect_ref (decl, NULL);
      for (field = TYPE_FIELDS (schema_type); field && PASCAL_TREE_DISCRIMINANT (field); field = TREE_CHAIN (field))
        discr = chainon (discr, build_tree_list (NULL_TREE, simple_component_ref (ref, field)));

      /* The size of this type may vary within one function body. */
      size_volatile++;
      new_type = build_discriminated_schema_type (schema_type, discr, 0);
      size_volatile--;
      TYPE_LANG_CODE (new_type) = PASCAL_LANG_PREDISCRIMINATED_SCHEMA;

      /* Make the fixup list of the prediscriminated schema invalid. */
      for (field = TYPE_FIELDS (new_type); field; field = TREE_CHAIN (field))
        if (PASCAL_TREE_DISCRIMINANT (field))
          DECL_LANG_FIXUPLIST (field) = NULL_TREE;

      /* Return the result, but don't spoil pointers/references
         to this (undiscriminated) schema type. */
      TREE_TYPE (decl) = build_type_copy (TREE_TYPE (decl));
      new_main_variant (TREE_TYPE (decl));
      TREE_TYPE (TREE_TYPE (decl)) = new_type;
    }
}

tree
build_type_of (d)
     tree d;
{
  tree t;
  chk_dialect_name ("type of", E_O_PASCAL);
  d = undo_schema_dereference (d);
  t = TREE_TYPE (d);
  CHK_EM (t);
  t = TYPE_MAIN_VARIANT (t);
  assert (!PASCAL_TYPE_UNDISCRIMINATED_STRING (t) && !PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (t));
  if (PASCAL_TYPE_PREDISCRIMINATED_STRING (t))
    t = build_pascal_string_schema (save_nonconstants (TYPE_LANG_DECLARED_CAPACITY (t)));
  else if (PASCAL_TYPE_PREDISCRIMINATED_SCHEMA (t))
    {
      tree field, discr = NULL_TREE;
      for (field = TYPE_FIELDS (t); field && PASCAL_TREE_DISCRIMINANT (field); field = TREE_CHAIN (field))
        discr = chainon (discr, build_tree_list (NULL_TREE, simple_component_ref (d, field)));
      t = build_discriminated_schema_type (TYPE_LANG_BASE (t), discr, 1);
    }
  return t;
}

/* Return the main variant of the base type of an ordinal subrange (also if
   nested, fjf729.pas), or of the type itself if it is not a subrange. */
tree
base_type (type)
     tree type;
{
  CHK_EM (type);
  while (ORDINAL_TYPE (TREE_CODE (type)) && TREE_TYPE (type))
    type = TREE_TYPE (type);
  return TYPE_MAIN_VARIANT (type);
}

/* index_type is NULL_TREE for a non-direct-access file. */
tree
build_file_type (component_type, index_type, allow_void)
     tree component_type, index_type;
     int allow_void;
{
  if (!allow_void && TREE_CODE (component_type) == VOID_TYPE)
    error ("file element type must not be `Void'");
  else if (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (component_type)
           || PASCAL_TYPE_UNDISCRIMINATED_STRING (component_type))
    error ("file element type must not be an undiscriminated schema");
  else if (contains_file_p (component_type))
    error ("file element type must not contain files");
  else
    {
      tree file_type = finish_struct (start_struct (RECORD_TYPE),
             build_field (get_identifier ("_p_File_"), ptr_type_node), 0);
      if (!TYPE_LANG_SPECIFIC (file_type))
        TYPE_LANG_SPECIFIC (file_type) = allocate_type_lang_specific ();
      TYPE_LANG_CODE (file_type) = PASCAL_LANG_NON_TEXT_FILE;
      if (index_type && !EM (index_type))
        TYPE_LANG_FILE_DOMAIN (file_type) = index_type;
      TREE_TYPE (file_type) = component_type;
      return file_type;
    }
  return error_mark_node;
}

tree
build_field (name, type)
     tree name, type;
{
  tree decl;
  CHK_EM (type);
  if (!TYPE_SIZE (type) || TREE_CODE (type) == VOID_TYPE)
    {
      error ("field `%s' has incomplete type", IDENTIFIER_NAME (name));
      return error_mark_node;
    }
  if (PASCAL_TYPE_ANYFILE (type))
    error ("field type must not be `AnyFile'");
  decl = build_decl (FIELD_DECL, name, type);
  TREE_READONLY (decl) |= TYPE_READONLY (type);
  TREE_SIDE_EFFECTS (decl) |= TYPE_VOLATILE (type);
  TREE_THIS_VOLATILE (decl) |= TYPE_VOLATILE (type);
  return decl;
}

tree
build_fields (list, type, init)
     tree list, type, init;
{
  tree link, ret = NULL_TREE, last = NULL_TREE;
  type = add_type_initializer (type, init);
  for (link = list; link; link = TREE_CHAIN (link))
    {
      tree t = build_field (TREE_VALUE (link), type);
      if (EM (t))
        ;
      else if (!last)
        ret = last = t;
      else
        {
          TREE_CHAIN (last) = t;
          last = t;
        }
    }
  return ret;
}

tree
build_record (fixed_part, variant_selector, variant_list)
     tree fixed_part, variant_selector, variant_list;
{
  tree record, init = NULL_TREE, variant_field = NULL_TREE, f, ti;
  tree selector_type = NULL_TREE, selector_field = NULL_TREE;
  if (variant_selector)
    {
      enum tree_code code = UNION_TYPE;
      tree t, vf = NULL_TREE, c;
      selector_type = TREE_PURPOSE (variant_selector);
      selector_field = TREE_VALUE (variant_selector);
      if (!selector_field && TREE_CODE (selector_type) == IDENTIFIER_NODE)
        {
          tree decl = lookup_name (selector_type);
          if (decl && TREE_CODE (decl) == VAR_DECL && PASCAL_TREE_DISCRIMINANT (decl))
            selector_field = decl;
          else if (!(decl && TREE_CODE (decl) == TYPE_DECL))
            {
              error ("selector type name or discriminant identifier expected, `%s' given",
                     IDENTIFIER_NAME (selector_type));
              return error_mark_node;
            }
          selector_type = TREE_TYPE (decl);
        }
      CHK_EM (selector_type);
      for (t = variant_list; t; t = TREE_CHAIN (t))
        {
          CHK_EM (TREE_VALUE (t));
          for (c = TREE_PURPOSE (t); c; c = TREE_CHAIN (c))
            {
              tree lo = TREE_VALUE (c), hi = TREE_PURPOSE (c);
              STRIP_NOPS (lo);
              lo = TREE_VALUE (c) = fold (lo);
              if (hi)
                {
                  STRIP_NOPS (hi);
                  hi = TREE_PURPOSE (c) = fold (hi);
                }
              if (!comptypes (TREE_TYPE (lo), selector_type) || (hi && !comptypes (TREE_TYPE (hi), selector_type)))
                error ("type mismatch in variant selector constant");
            }
          vf = chainon (vf, TREE_VALUE (t));
          /* Don't overlap auto-initialized types. */
          if (code == UNION_TYPE && contains_auto_initialized_part_p (TREE_TYPE (vf), 0))
            code = RECORD_TYPE;
        }
      variant_field = build_field (NULL_TREE, finish_struct (start_struct (code), vf, 1));
      /* Chain the tag field (but not a discriminant used as the tag) */
      if (selector_field && TREE_CODE (selector_field) == FIELD_DECL)
        fixed_part = chainon (fixed_part, selector_field);
    }
  record = finish_struct (start_struct (RECORD_TYPE), chainon (fixed_part, variant_field), 1);
  CHK_EM (record);
  for (f = fixed_part; f; f = TREE_CHAIN (f))
    if ((ti = TYPE_GET_INITIALIZER (TREE_TYPE (f))))
      {
        assert (TREE_CODE (ti) == TREE_LIST && !TREE_PURPOSE (ti));
        init = tree_cons (build_tree_list (DECL_NAME (f), NULL_TREE), TREE_VALUE (ti), init);
      }
  if ((init || variant_selector) && !TYPE_LANG_SPECIFIC (record))
    TYPE_LANG_SPECIFIC (record) = allocate_type_lang_specific ();
  if (variant_selector)
    {
      TYPE_LANG_CODE (record) = PASCAL_LANG_VARIANT_RECORD;
      TYPE_LANG_VARIANT_TAG (record) = build_tree_list (
        build_tree_list (selector_type, selector_field),
        build_tree_list (variant_list, variant_field));
      if ((ti = TYPE_GET_INITIALIZER (selector_type)))
        {
          assert (TREE_CODE (ti) == TREE_LIST && !TREE_PURPOSE (ti));
          f = find_variant_selector (TREE_VALUE (ti), variant_list);
          if (f && (ti = TYPE_GET_INITIALIZER (TREE_TYPE (f))))
            {
              assert (TREE_CODE (ti) == TREE_LIST && !TREE_PURPOSE (ti));
              init = tree_cons (build_tree_list (DECL_NAME (f), NULL_TREE), TREE_VALUE (ti), init);
            }
        }
    }
  if (init)
    TYPE_LANG_INITIAL (record) = build_tree_list (NULL_TREE, init);
  return record;
}

/* Mark type as packed, and re-layout it if necessary. Note: In
   `packed array [5 .. 10] of array of [1 .. 20] of Char' the inner array type
   must not be packed, but in `packed array [5 .. 10, 1 .. 20] of Char' it must.
   build_pascal_array_type sets PASCAL_TYPE_INTERMEDIATE_ARRAY for this purpose. */
tree
pack_type (type)
     tree type;
{
  CHK_EM (type);
  if (!TYPE_PACKED (type))
    type = pascal_type_variant (type, TYPE_QUALIFIER_PACKED);
  if (TREE_CODE (type) == ARRAY_TYPE)
    {
      tree bits, new_size, align, domain = TYPE_DOMAIN (type);

      if (TREE_CODE (TREE_TYPE (type)) == ARRAY_TYPE && PASCAL_TYPE_INTERMEDIATE_ARRAY (TREE_TYPE (type)))
        TREE_TYPE (type) = pack_type (TREE_TYPE (type));

      if (!TYPE_MIN_VALUE (domain) || !TYPE_MAX_VALUE (domain))
        domain = TREE_TYPE (domain);
      assert (domain && TYPE_MIN_VALUE (domain) && TYPE_MAX_VALUE (domain));

      /* layout_type() does not know about Pascal's idea of
         packed arrays, so we re-calculate the size here. */
      if (ORDINAL_TYPE (TREE_CODE (TREE_TYPE (type))))
        bits = count_bits (TREE_TYPE (type));
      else
        bits = NULL_TREE /*TYPE_SIZE (TREE_TYPE (type))*/;

      /* Nothing to pack. */
      if (!bits
          || (TREE_CODE (bits) == INTEGER_CST
              && tree_int_cst_equal (bits, TYPE_SIZE (TREE_TYPE (type)))
              && TREE_INT_CST_LOW (bits) % BITS_PER_UNIT == 0
              && (TREE_INT_CST_LOW (bits) == 0 || 256 % TREE_INT_CST_LOW (bits) == 0)))
        return type;

      if (TREE_UNSIGNED (bits) != TREE_UNSIGNED (type))
        {
          TREE_TYPE (type) = build_type_copy (TREE_TYPE (type));
          TREE_UNSIGNED (TREE_TYPE (type)) = TREE_UNSIGNED (bits);
        }

      TYPE_ALIGN (type) = TYPE_PRECISION (packed_array_unsigned_short_type_node);
      align = bitsize_int (TYPE_ALIGN (type));
      new_size = size_binop (MULT_EXPR,
                   size_binop (CEIL_DIV_EXPR,
                     size_binop (MULT_EXPR,
                       size_binop (PLUS_EXPR,
                         convert (bitsizetype,
                           size_binop (MINUS_EXPR,
                             convert (sbitsizetype, TYPE_MAX_VALUE (domain)),
                             convert (sbitsizetype, TYPE_MIN_VALUE (domain)))),
                         bitsize_one_node),
                       convert (bitsizetype, bits)),
                     align),
                   align);
      TYPE_SIZE (type) = new_size;
#ifdef EGCS
      TYPE_SIZE_UNIT (type) = convert (sizetype,
        size_binop (CEIL_DIV_EXPR, new_size, bitsize_int (BITS_PER_UNIT)));
#endif
    }
  else if (ORDINAL_TYPE (TREE_CODE (type)))
    {
      tree bits = count_bits (type);
      if (bits && TREE_INT_CST_LOW (bits) != TREE_INT_CST_LOW (TYPE_SIZE (type)))
        {
          TYPE_SIZE (type) = NULL_TREE;
#ifdef EGCS
          TYPE_SIZE_UNIT (type) = NULL_TREE;
#endif
          /* The backend doesn't appear to expect types whose precision is not a
             multiple of BITS_PER_UNIT (such as a type of 5 bits, martin4*.pas).
             E.g., force_fit_type() would turn a constant of -21 into +11 which
             would be right when really operating on 5 bit types. However, since
             the CPU operates on BITS_PER_UNIT (usually 8 bit) wide types,
             adding 11 is not equivalent to subtracting 21. So let's just round
             up the precision to a multiple of BITS_PER_UNIT. This should not
             actually make the type bigger. (Packed arrays where it would matter
             are handled differently above, anyway.) */
          TYPE_PRECISION (type) = ((TREE_INT_CST_LOW (bits) + BITS_PER_UNIT - 1)
                                   / BITS_PER_UNIT) * BITS_PER_UNIT;
          layout_type (type);
        }
    }
  return type;
}

tree
add_type_initializer (type, init)
     tree type, init;
{
  if (init && !EM (type))
    {
      type = build_type_copy (type);
      copy_type_lang_specific (type);
      init = save_nonconstants (init);
      if (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (type) || !check_pascal_initializer (type, init))
        {
          if (!TYPE_LANG_SPECIFIC (type))
            TYPE_LANG_SPECIFIC (type) = allocate_type_lang_specific ();
          TYPE_LANG_INITIAL (type) = init;
        }
      else
        error ("initial value is of wrong type");
    }
  return type;
}

/* Return 1 if val is a field of a packed array or record, otherwise 0. */
int
is_packed_field (val)
     tree val;
{
  return TREE_CODE (val) == BIT_FIELD_REF
         || TREE_CODE (val) == PASCAL_BIT_FIELD_REF
         || (TREE_CODE (val) == COMPONENT_REF && DECL_PACKED_FIELD (TREE_OPERAND (val, 1)))
         || (TREE_CODE (val) == ARRAY_REF && TYPE_PACKED (TREE_TYPE (TREE_OPERAND (val, 0))))
         || (IS_EXPR_OR_REF_CODE_CLASS (TREE_CODE_CLASS (TREE_CODE (val))) && PASCAL_TREE_PACKED (val));
}

/* Count how many bits a variable (e.g. a record field) of type TYPE needs.
   Return the result as an INTEGER_CST node, or NULL_TREE if packing of
   this type is not possible. */
tree
count_bits (type)
     tree type;
{
  int positive = 1, bits;
  tree min_val, max_val, result;
  if (!ORDINAL_TYPE (TREE_CODE (type)))
    return NULL_TREE;
  min_val = TYPE_MIN_VALUE (type);
  max_val = TYPE_MAX_VALUE (type);
  if (!min_val
      || !max_val
      || TREE_CODE (min_val) != INTEGER_CST
      || TREE_CODE (max_val) != INTEGER_CST)
    return NULL_TREE;
  if (!TREE_UNSIGNED (type)
      && ((!TREE_UNSIGNED (min_val) && TREE_INT_CST_HIGH (min_val) < 0)
          || (!TREE_UNSIGNED (max_val) && TREE_INT_CST_HIGH (max_val) < 0)))
    positive = 0;
  if (positive)
    {
      int min_bits = 0, max_bits = 0;
      unsigned HOST_WIDE_INT check;
      for (check = TREE_INT_CST_HIGH (min_val); check; check >>= 1)
        min_bits++;
      if (min_bits)
        min_bits += HOST_BITS_PER_WIDE_INT;
      else
        for (check = TREE_INT_CST_LOW (min_val); check; check >>= 1)
          min_bits++;
      for (check = TREE_INT_CST_HIGH (max_val); check; check >>= 1)
        max_bits++;
      if (max_bits)
        max_bits += HOST_BITS_PER_WIDE_INT;
      else
        for (check = TREE_INT_CST_LOW (max_val); check; check >>= 1)
          max_bits++;
      bits = min_bits > max_bits ? min_bits : max_bits;
      if (bits == 0)
        bits++;
    }
  else
    {
      int min_bits = 0, max_bits = 0;
      HOST_WIDE_INT check = TREE_INT_CST_HIGH (min_val);
      unsigned HOST_WIDE_INT ucheck;
      if (check < 0)
        check = ~check;
      for (; check; check >>= 1)
        min_bits++;
      if (min_bits)
        min_bits += HOST_BITS_PER_WIDE_INT;
      else
        {
          ucheck = TREE_INT_CST_LOW (min_val);
          if ((HOST_WIDE_INT) TREE_INT_CST_HIGH (min_val) < 0)
            ucheck = ~ucheck;
          for (; ucheck; ucheck >>= 1)
            min_bits++;
        }
      check = TREE_INT_CST_HIGH (max_val);
      if (check < 0)
        check = ~check;
      for (; check; check >>= 1)
        max_bits++;
      if (max_bits)
        max_bits += HOST_BITS_PER_WIDE_INT;
      else
        {
          ucheck = TREE_INT_CST_LOW (max_val);
          if ((HOST_WIDE_INT) TREE_INT_CST_HIGH (max_val) < 0)
            ucheck = ~ucheck;
          for (; ucheck; ucheck >>= 1)
            max_bits++;
        }
      bits = (min_bits > max_bits ? min_bits : max_bits) + 1;
    }
  assert (bits > 0 && bits <= TYPE_PRECISION (type));
  result = build_int_2 (bits, 0);
  TREE_UNSIGNED (result) = positive;
  return result;
}

/* Return the number of elements of the array type TYPE. Note: array_type_nelts
   returns "max - min", while arrays have actually "max - min + 1" elements. */
tree
pascal_array_type_nelts (type)
     tree type;
{
  tree index_type = TYPE_DOMAIN (type);
  CHK_EM (index_type);
  return size_binop (PLUS_EXPR, convert (bitsizetype, size_binop (MINUS_EXPR,
    convert (sbitsizetype, TYPE_MAX_VALUE (index_type)),
    convert (sbitsizetype, TYPE_MIN_VALUE (index_type)))), bitsize_one_node);
}

tree
size_of_type (type)
     tree type;
{
  if (TREE_CODE (type) == ARRAY_TYPE)
    return build_pascal_binary_op (MULT_EXPR, pascal_array_type_nelts (type), size_of_type (TREE_TYPE (type)));
  else if (TREE_CODE (type) == VOID_TYPE)
    return size_one_node;
  else
    return size_in_bytes (type);
}

/* Compare two integer constants which may both be either signed or unsigned.
   If either of the arguments is no INTEGER_CST node, return 0. */
int
const_lt (val1, val2)
    tree val1, val2;
{
  if (TREE_CODE (val1) != INTEGER_CST || TREE_CODE (val2) != INTEGER_CST)
    return 0;
  else
    {
      int large1 = (TREE_UNSIGNED (val1) || TREE_UNSIGNED (TREE_TYPE (val1)))
                   && INT_CST_LT_UNSIGNED (TYPE_MAX_VALUE (long_long_integer_type_node), val1);
      int large2 = (TREE_UNSIGNED (val2) || TREE_UNSIGNED (TREE_TYPE (val2)))
                   && INT_CST_LT_UNSIGNED (TYPE_MAX_VALUE (long_long_integer_type_node), val2);
      if (large1)
        return large2 && INT_CST_LT_UNSIGNED (val1, val2);
      else
        return large2 || INT_CST_LT (val1, val2);
    }
}

/* Return the smallest standard signed integer type that can hold
   the negative of the unsigned integer type TYPE. */
tree
select_signed_integer_type (type)
     tree type;
{
  int precision = TYPE_PRECISION (type);
  if (precision < TYPE_PRECISION (pascal_integer_type_node))
    return pascal_integer_type_node;
  else if (precision < TYPE_PRECISION (long_integer_type_node))
    return long_integer_type_node;
  else
    return long_long_integer_type_node;
}

/* Return a reasonable common type for the ordinal values VAL1 and VAL2.
   WHY is the operation intended for these values and might be NOP_EXPR. */
tree
select_integer_type (val1, val2, why)
     tree val1, val2;
     enum tree_code why;
{
  tree min_val, max_val;
  assert (TREE_CODE (TREE_TYPE (val1)) == INTEGER_TYPE && TREE_CODE (TREE_TYPE (val2)) == INTEGER_TYPE);

  if (TREE_CODE (val1) != INTEGER_CST || TREE_CODE (val2) != INTEGER_CST)
    {
      if (why == MINUS_EXPR || why == PLUS_EXPR)
        {
          int uns = TREE_UNSIGNED (TREE_TYPE (val1)) && TREE_UNSIGNED (TREE_TYPE (val2));
          int maxprec = MAX (TYPE_PRECISION (TREE_TYPE (val1)), TYPE_PRECISION (TREE_TYPE (val2)));
          /* The difference of two unsigned values should be done unsigned
             (otherwise there's no way to compute in the top range), but if
             possible use a bigger type (so, e.g. `Cardinal - Cardinal' with
             small values doesn't easily lead to negative overflow. */
          if (uns && why == MINUS_EXPR && maxprec < TYPE_PRECISION (long_long_integer_type_node))
            {
              maxprec++;
              uns = 0;
            }
          if (maxprec <= TYPE_PRECISION (pascal_integer_type_node))
            return uns && (maxprec == TYPE_PRECISION (pascal_integer_type_node)) ? pascal_cardinal_type_node : pascal_integer_type_node;
          else if (maxprec <= TYPE_PRECISION (long_integer_type_node))
            return uns && (maxprec == TYPE_PRECISION (long_integer_type_node)) ? long_unsigned_type_node : long_integer_type_node;
          else
            return uns ? long_long_unsigned_type_node : long_long_integer_type_node;
        }
      if (TREE_CODE (val2) == INTEGER_CST)
        {
          tree tmp = val1;
          val1 = val2;
          val2 = tmp;
        }
      if (TREE_CODE (val1) == INTEGER_CST
          && TREE_CODE (TREE_TYPE (val2)) == INTEGER_TYPE
          && TYPE_MIN_VALUE (TREE_TYPE (val2))
          && TYPE_MAX_VALUE (TREE_TYPE (val2))
          && TREE_CODE (TYPE_MIN_VALUE (TREE_TYPE (val2))) == INTEGER_CST
          && TREE_CODE (TYPE_MAX_VALUE (TREE_TYPE (val2))) == INTEGER_CST
          && !const_lt (val1, TYPE_MIN_VALUE (TREE_TYPE (val2)))
          && !const_lt (TYPE_MAX_VALUE (TREE_TYPE (val2)), val1))
        return TREE_TYPE (val2);
      return common_type (TREE_TYPE (val1), TREE_TYPE (val2));
    }

  /* Everything constant. Make it as small as possible, but big
     enough to hold the result of the intended operation (if known)
     and not smaller than the largest explicit type. */
  if (const_lt (val1, val2))
    {
      min_val = val1;
      max_val = val2;
    }
  else
    {
      min_val = val2;
      max_val = val1;
    }
  if (!(TREE_CODE_CLASS (TREE_CODE (val1)) == 'c' && PASCAL_TREE_FRESH_CST (val1)))
    {
      if (const_lt (TYPE_MIN_VALUE (TREE_TYPE (val1)), min_val))
        min_val = TYPE_MIN_VALUE (TREE_TYPE (val1));
      if (const_lt (max_val, TYPE_MAX_VALUE (TREE_TYPE (val1))))
        max_val = TYPE_MAX_VALUE (TREE_TYPE (val1));
    }
  if (!(TREE_CODE_CLASS (TREE_CODE (val2)) == 'c' && PASCAL_TREE_FRESH_CST (val2)))
    {
      if (const_lt (TYPE_MIN_VALUE (TREE_TYPE (val2)), min_val))
        min_val = TYPE_MIN_VALUE (TREE_TYPE (val2));
      if (const_lt (max_val, TYPE_MAX_VALUE (TREE_TYPE (val2))))
        max_val = TYPE_MAX_VALUE (TREE_TYPE (val2));
    }
  switch (why)
  {
    case PLUS_EXPR:
    case MINUS_EXPR:
    case MULT_EXPR:
    case CEIL_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case TRUNC_MOD_EXPR:
    case FLOOR_MOD_EXPR:
    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
    case LROTATE_EXPR:
    case RROTATE_EXPR:
      {
        /* For operations which can make the result take off from zero, take it into account. */
        tree op1 = convert (why != MINUS_EXPR && (TREE_UNSIGNED (val1) || !INT_CST_LT (val1, integer_zero_node))
                            ? long_long_unsigned_type_node
                            : long_long_integer_type_node, val1);
        tree op2 = convert (why != MINUS_EXPR && (TREE_UNSIGNED (val2) || !INT_CST_LT (val2, integer_zero_node))
                            ? long_long_unsigned_type_node
                            : long_long_integer_type_node, val2);
        tree result = fold (build_binary_op (why, op1, op2));
        if (const_lt (result, min_val))
          min_val = result;
        if (const_lt (max_val, result))
          max_val = result;
        break;
      }
    default:
      break;
  }

  if (const_lt (min_val, integer_zero_node))
    {
      if (const_lt (TYPE_MAX_VALUE (long_integer_type_node), max_val)
          || const_lt (min_val, TYPE_MIN_VALUE (long_integer_type_node)))
        return long_long_integer_type_node;
      else if (const_lt (TYPE_MAX_VALUE (pascal_integer_type_node), max_val)
               || const_lt (min_val, TYPE_MIN_VALUE (pascal_integer_type_node)))
        return long_integer_type_node;
      else
        return pascal_integer_type_node;
    }
  else
    {
      /* If `Integer' is sufficient to hold this value, use that. */
      if (const_lt (TYPE_MAX_VALUE (long_unsigned_type_node), max_val))
        return long_long_unsigned_type_node;
      else if (const_lt (TYPE_MAX_VALUE (pascal_cardinal_type_node), max_val))
        return long_unsigned_type_node;
      else if (const_lt (TYPE_MAX_VALUE (pascal_integer_type_node), max_val))
        return long_unsigned_type_node;
      else
        return pascal_integer_type_node;
    }
}

int
check_subrange (lo, hi)
     tree lo, hi;
{
  if (const_lt (hi, lo))
    {
      error ("invalid subrange type");
      return 0;
    }
  if (const_lt (lo, integer_zero_node) && const_lt (TYPE_MAX_VALUE (long_long_integer_type_node), hi))
    {
      error ("range too big");
      return 0;
    }
  if (co->range_checking)
    {
      tree l = TREE_CODE (lo) == INTEGER_CST ? lo : TYPE_MAX_VALUE (TREE_TYPE (lo));
      tree h = TREE_CODE (hi) == INTEGER_CST ? hi : TYPE_MIN_VALUE (TREE_TYPE (hi));
      if (TREE_CODE (l) != INTEGER_CST || TREE_CODE (h) != INTEGER_CST || const_lt (h, l))
        {
          if (co->warn_dynamic_arrays)
            warning ("dynamic array");
          if (current_function_decl)  /* @@ otherwise do it in module constructor */
            expand_expr_stmt (build (COND_EXPR, pascal_integer_type_node,
              build_implicit_pascal_binary_op (LT_EXPR, hi, lo),
              build (COMPOUND_EXPR, pascal_integer_type_node,
                build_predef_call (p_SubrangeError, NULL_TREE), integer_zero_node),
              integer_zero_node));
        }
    }
  return 1;
}

static void
check_nonconstants (expr)
     tree expr;
{
  tree t;
  enum tree_code code = TREE_CODE (expr);
  if (code == VAR_DECL && !PASCAL_INITIALIZED (expr) && !PASCAL_VALUE_ASSIGNED (expr)
      && !PASCAL_TREE_DISCRIMINANT (expr) && DECL_CONTEXT (expr) == current_function_decl)
    warning ("`%s' might be used uninitialized in type definition", IDENTIFIER_NAME (DECL_NAME (expr)));
  else if (IS_EXPR_OR_REF_CODE_CLASS (TREE_CODE_CLASS (code)))
    {
      int i, l = NUMBER_OF_OPERANDS (code);
      for (i = FIRST_OPERAND (code); i < l; i++)
        if (TREE_OPERAND (expr, i))
          check_nonconstants (TREE_OPERAND (expr, i));
    }
  else if (code == TREE_LIST)
    for (t = expr; t; t = TREE_CHAIN (t))
      {
        if (TREE_VALUE (t))
          check_nonconstants (TREE_VALUE (t));
        if (TREE_PURPOSE (t))
          check_nonconstants (TREE_PURPOSE (t));
      }
}

/* Find all nonconstant parts, except discriminants, in expr. For each one,
   create a temp variable, assign the nonconstant part to it and substitute
   that variable into a copy of the expression which is returned. */
tree
save_nonconstants (expr)
     tree expr;
{
  enum tree_code code = TREE_CODE (expr);
  CHK_EM (expr);

  /* Constant expressions are ok. SAVE_EXPRs cannot be copied, and are assumed
     to have been taken care of if they appear here at all. Discriminants should
     not be changed here. */
  if (TREE_CONSTANT (expr)
      || TREE_READONLY (expr)
      || code == SAVE_EXPR
      || ((code == VAR_DECL || code == FIELD_DECL || code == CONVERT_EXPR) && PASCAL_TREE_DISCRIMINANT (expr)))
    return expr;

  if (code == COMPOUND_EXPR)
    {
      expand_expr_stmt1 (TREE_OPERAND (expr, 0));
      return save_nonconstants (TREE_OPERAND (expr, 1));
    }

  if (code != TREE_LIST && code != IDENTIFIER_NODE && !contains_discriminant (expr, NULL_TREE))
    {
      tree temp_var;
      check_nonconstants (expr);
      temp_var = make_new_variable ("nonconstant_expr", TYPE_MAIN_VARIANT (TREE_TYPE (expr)));
      mark_lvalue (temp_var, "internal initialization", 1);
      if (current_function_decl)
        expand_expr_stmt (build_modify_expr (temp_var, NOP_EXPR, expr));
      else
        deferred_initializers = tree_cons (expr, temp_var, deferred_initializers);
      PASCAL_HAD_SIDE_EFFECTS (temp_var) = TREE_SIDE_EFFECTS (expr);
      return temp_var;
    }

  if (IS_EXPR_OR_REF_CODE_CLASS (TREE_CODE_CLASS (code)))
    {
      int i, l = NUMBER_OF_OPERANDS (code);
      expr = copy_node (expr);
      for (i = FIRST_OPERAND (code); i < l; i++)
        if (TREE_OPERAND (expr, i))
          TREE_OPERAND (expr, i) = save_nonconstants (TREE_OPERAND (expr, i));
    }
  else if (code == TREE_LIST)
    {
      tree t;
      expr = copy_list (expr);
      for (t = expr; t; t = TREE_CHAIN (t))
        {
          if (TREE_VALUE (t))
            TREE_VALUE (t) = save_nonconstants (TREE_VALUE (t));
          if (TREE_PURPOSE (t))
            TREE_PURPOSE (t) = save_nonconstants (TREE_PURPOSE (t));
        }
    }
  return expr;
}

/* Build a subrange type. Like build_range_type, but derive the type from the values. */
tree
build_pascal_range_type (lowval, highval)
     tree lowval, highval;
{
  tree type, range_type;
  int discr_lo = contains_discriminant (lowval, NULL_TREE);
  int discr_hi = contains_discriminant (highval, NULL_TREE);
  if (!discr_lo)
    {
      STRIP_TYPE_NOPS (lowval);
      lowval = fold (lowval);
    }
  if (!discr_hi)
    {
      STRIP_TYPE_NOPS (highval);
      highval = fold (highval);
    }
  lowval  = save_nonconstants (lowval);
  highval = save_nonconstants (highval);
  if (!discr_lo && !discr_hi && !check_subrange (lowval, highval))
    return error_mark_node;

  if (TREE_CODE (TREE_TYPE (lowval)) == INTEGER_TYPE)
    type = select_integer_type (lowval, highval, NOP_EXPR);
  else
    type = base_type (TREE_TYPE (lowval));
  range_type = build_range_type (type, lowval, highval);

  /* Restore discriminants in case build_range_type() folded them away. */
  if (discr_lo)
    TYPE_MIN_VALUE (range_type) = build1 (CONVERT_EXPR, type, lowval);
  if (discr_hi)
    TYPE_MAX_VALUE (range_type) = build1 (CONVERT_EXPR, type, highval);

  TREE_SET_CODE (range_type, TREE_CODE (type));
  if (TREE_CODE (lowval) == INTEGER_CST)
    TREE_UNSIGNED (range_type) = !const_lt (lowval, integer_zero_node);
  else
    TREE_UNSIGNED (range_type) = TREE_UNSIGNED (TREE_TYPE (lowval));
  if (discr_hi && !TREE_UNSIGNED (TREE_TYPE (highval)))
    TREE_UNSIGNED (range_type) = 0;
  return range_type;
}

/* Like build_pascal_range_type, but do some more checking and conversions. */
tree
build_pascal_subrange_type (lowval, highval, pack)
     tree lowval, highval;
     int pack;
{
  tree lower = maybe_schema_discriminant (string_may_be_char (lowval, 0));
  tree higher = maybe_schema_discriminant (string_may_be_char (highval, 0));
  tree type_lower = base_type (TREE_TYPE (lower));
  tree type_higher = base_type (TREE_TYPE (higher));
  tree res = error_mark_node;
  if (!ORDINAL_TYPE (TREE_CODE (type_lower)) || !ORDINAL_TYPE (TREE_CODE (type_higher)))
    error ("subrange bounds must be of ordinal type");
  else if (type_lower != type_higher && !(TREE_CODE (type_lower) == INTEGER_TYPE && TREE_CODE (type_higher) == INTEGER_TYPE))
    error ("subrange bounds are not of the same type");
  else
    {
      if (!TREE_CONSTANT (lower) || !TREE_CONSTANT (higher))
        chk_dialect ("non-constant subrange bounds are", E_O_PASCAL);
      res = build_pascal_range_type (lower, higher);
      if (pack)
        res = pack_type (res);
    }
  return res;
}

/* Look up component in a record etc. Return NULL_TREE if not found, otherwise
   a TREE_LIST, with each TREE_VALUE a FIELD_DECL stepping down the chain to
   the component, which is in the last TREE_VALUE of the list. The list is of
   length 1 unless the component is embedded within inner levels (variant parts
   or schema body). Since in Pascal all fields are in the same scope, there can
   be no duplicate names and we can search the levels in any order we like.
   mode 0: normal, 1: implicit (don't check private etc.), 2: just return the
   innermost field instead of the list */
tree
find_field (type, component, mode)
     tree type, component;
     int mode;
{
  enum tree_code form = TREE_CODE (type);
  tree field = NULL_TREE;
  const char *kind = "field", *p;
  if (RECORD_OR_UNION (form))
    {
      /* TYPE_LANG_SORTED_FIELDS can contain the sorted field elements.
         Use a binary search on this array to quickly find the element.
         This doesn't handle inner levels, they're searched afterwards. */
      tree *sorted_fields = TYPE_LANG_SPECIFIC (type) ? TYPE_LANG_SORTED_FIELDS (type) : NULL;
      if (sorted_fields)
        {
          int bottom = 0, top = TYPE_LANG_FIELD_COUNT (type), i;
          while (top - bottom > 1)
            {
              int middle = (top + bottom) / 2;
              if (DECL_NAME (sorted_fields[middle]) == component)
                {
                  bottom = middle;
                  break;
                }
              if (DECL_NAME (sorted_fields[middle]) < component)
                bottom = middle;
              else
                top = middle;
            }
          if (DECL_NAME (sorted_fields[bottom]) == component)
            field = sorted_fields[bottom];
          else
            for (i = 0; i < TYPE_LANG_FIELD_COUNT (type); i++)
              {
                tree field2 = sorted_fields[i], ret;
                if (DECL_NAME (field2) == component)
                  {
                    field = field2;
                    break;
                  }
                else if (DECL_NAME (field2) && DECL_NAME (field2) != schema_id)
                  break;  /* we already checked the rest */
                if ((ret = find_field (TREE_TYPE (field2), component, mode)))
                  return mode == 2 ? ret : tree_cons (NULL_TREE, field2, ret);
              }
        }
      else
        {
          for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
            if (DECL_NAME (field) == component)
              break;
            else if (!DECL_NAME (field) || DECL_NAME (field) == schema_id)
              {
                tree ret = find_field (TREE_TYPE (field), component, mode);
                if (ret)
                  return mode == 2 ? ret : tree_cons (NULL_TREE, field, ret);
              }
        }
      if (!field)
        for (kind = "method", field = TYPE_METHODS (type); field; field = TREE_CHAIN (field))
          if (DECL_NAME (field) == component)
            break;
    }
  if (!field || mode == 2)
    return field;
  if (mode == 0 && (p = check_private_protected (field)))
    error ("access to %s %s `%s'", p, kind, IDENTIFIER_NAME (component));
  return build_tree_list (NULL_TREE, field);
}

tree
build_component_ref_no_schema_dereference (datum, component, implicit)
     tree datum, component;
     int implicit;
{
  tree type = TREE_TYPE (datum), field = NULL_TREE, ref;
  CHK_EM (datum);

  if (TREE_CODE (datum) == TYPE_DECL)
    {
      if (PASCAL_TYPE_OBJECT (TREE_TYPE (datum)))
        field = simple_get_field (component, TREE_TYPE (datum), "");
      if (!field || TREE_CODE (field) != FUNCTION_DECL)
        {
          error ("trying to access fields of a type definition");
          return error_mark_node;
        }
      if (PASCAL_ABSTRACT_METHOD (field))
        error ("trying to access an abstract method");
    }
  else if ((TREE_CODE (datum) == FUNCTION_DECL && RECORD_OR_UNION (TREE_CODE (TREE_TYPE (type))))
           || (TREE_CODE (type) == REFERENCE_TYPE && TREE_CODE (TREE_TYPE (type)) == FUNCTION_TYPE
               && RECORD_OR_UNION (TREE_CODE (TREE_TYPE (TREE_TYPE (type)))))
           || CALL_METHOD (datum))
    {
      datum = undo_schema_dereference (probably_call_function (datum));
      type = TREE_TYPE (datum);
    }

  assert (TREE_CODE (datum) != COND_EXPR);
  if (TREE_CODE (datum) == COMPOUND_EXPR)
    {
      tree value = build_component_ref (TREE_OPERAND (datum, 1), component);
      return build (COMPOUND_EXPR, TREE_TYPE (value), TREE_OPERAND (datum, 0), value);
    }

  /* See if there is a field or component with name COMPONENT. */

  if (RECORD_OR_UNION (TREE_CODE (type)))
    {
      if (!TYPE_SIZE (type) && !PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (type))
        {
          incomplete_type_error (NULL_TREE, type);
          return error_mark_node;
        }

      /* For Pascal: implicitly propagate to the inner layers
         of records and unions whose DECL_NAME is NULL_TREE.
         find_field() also constructs a TREE_LIST of fields and returns that. */
      field = find_field (TREE_TYPE (datum), component, implicit);

      if (!field)
        {
          error ("record, schema or object has no field named `%s'", IDENTIFIER_NAME (component));
          return error_mark_node;
        }

      /* Generate COMPONENT_REFs to access the field */
      ref = datum;
      for (; field; field = TREE_CHAIN (field))
        {
          tree ref1, ftype = TREE_TYPE (TREE_VALUE (field));
          CHK_EM (ftype);
          ref1 = build (COMPONENT_REF, ftype, ref, TREE_VALUE (field));
          if (TREE_READONLY (ref) || TREE_READONLY (TREE_VALUE (field)))
            TREE_READONLY (ref1) = 1;
          if (TREE_THIS_VOLATILE (ref) || TREE_THIS_VOLATILE (TREE_VALUE (field)))
            TREE_THIS_VOLATILE (ref1) = 1;
          ref = fold (ref1);
        }
      return ref;
    }
  else if (!EM (type))
    {
      if (TREE_CODE (datum) == COMPONENT_REF
          && PASCAL_TYPE_SCHEMA (TREE_TYPE (TREE_OPERAND (datum, 0)))
          && DECL_NAME (TREE_OPERAND (datum, 1)) == schema_id)
        {
          if (TREE_CODE (TREE_TYPE (TREE_OPERAND (datum, 1))) == RECORD_TYPE)
            error ("record schema has no field or discriminant named `%s'", IDENTIFIER_NAME (component));
          else
            error ("schema has no discriminant named `%s'", IDENTIFIER_NAME (component));
        }
      else
        {
          error ("request for field `%s' in something not", IDENTIFIER_NAME (component));
          error (" a record, schema or object");
        }
    }
  return error_mark_node;
}

/* Return an expression to refer to the field named component (IDENTIFIER_NODE)
   of record value datum. */
tree
build_component_ref (datum, component)
     tree datum, component;
{
  tree result;
  if (!EM (TREE_TYPE (datum)) && PASCAL_TYPE_RESTRICTED (TREE_TYPE (datum)))
    error ("accessing fields of a restricted record is not allowed");
  result = build_component_ref_no_schema_dereference (datum, component, 0);
  DEREFERENCE_SCHEMA (result);
  prediscriminate_schema (result);
  return result;
}

tree
simple_component_ref (expr, field)
     tree expr, field;
{
  tree ref = build (COMPONENT_REF, TREE_TYPE (field), expr, field);
  if (TREE_CODE (expr) == CONSTRUCTOR)
    ref = save_expr (ref);
  if (TREE_READONLY (expr) || TREE_READONLY (field))
    TREE_READONLY (ref) = 1;
  if (TREE_THIS_VOLATILE (expr) || TREE_THIS_VOLATILE (field))
    TREE_THIS_VOLATILE (ref) = 1;
  return fold (ref);
}

/* The two ways of specifying and accessing arrays, abbreviated (several index
   types in a row) and full (each index type separately), are equivalent.
   We represent arrays internally in their full form and mark intermediate
   arrays for pack_type. type is the element type, index_list is a list of
   index types in order of declaration. Returns the complete array type. */
tree
build_pascal_array_type (type, index_list)
     tree type, index_list;
{
  tree link, init;
  CHK_EM (type);
  if (TREE_CODE (type) == VOID_TYPE)
    {
      error ("array element type must not be `Void'");
      return error_mark_node;
    }
  if (PASCAL_TYPE_ANYFILE (type))
    error ("array element type must not be `AnyFile'");
  if (PASCAL_TYPE_UNDISCRIMINATED_SCHEMA (type)
      || PASCAL_TYPE_UNDISCRIMINATED_STRING (type))
    {
      error ("array element type must not be an undiscriminated schema");
      return error_mark_node;
    }
  init = TYPE_GET_INITIALIZER (type);
  if (init)
    {
      assert (TREE_CODE (init) == TREE_LIST && !TREE_PURPOSE (init));
      init = TREE_VALUE (init);
    }
  for (link = nreverse (index_list); link; link = TREE_CHAIN (link))
    {
      tree index_type = TREE_VALUE (link);
      CHK_EM (index_type);
      if (!ORDINAL_TYPE (TREE_CODE (index_type)))
        {
          error ("array index type must be ordinal");
          return error_mark_node;
        }
      assert (!const_lt (TYPE_MAX_VALUE (index_type), TYPE_MIN_VALUE (index_type)));
      type = build_simple_array_type (type, index_type);
      if (!EM (type) && TREE_CHAIN (link))
        PASCAL_TYPE_INTERMEDIATE_ARRAY (type) = 1;
      if (init)
        init = build_tree_list (build_tree_list (NULL_TREE, NULL_TREE), init);
    }
  if (init)
    {
      if (!TYPE_LANG_SPECIFIC (type))
        TYPE_LANG_SPECIFIC (type) = allocate_type_lang_specific ();
      TYPE_LANG_INITIAL (type) = build_tree_list (NULL_TREE, init);
    }
  return type;
}

/* Build a reference to an array slice. EP requires a string-type, but GPC
   allows slice accesses to all arrays. */
tree
build_array_slice_ref (expr, lower, upper)
     tree expr, lower, upper;
{
  tree sub_domain, sub_type, res, lo, hi, lo_int, t, integer_index_type;
  tree component_type = char_type_node, min = NULL_TREE, max = NULL_TREE, max2 = NULL_TREE;
  int is_cstring = TYPE_MAIN_VARIANT (TREE_TYPE (expr)) == cstring_type_node;
  int is_string = is_string_type (expr, 1);
  int lvalue = lvalue_p (expr);
  if (is_string)
    chk_dialect ("substring access is", E_O_PASCAL);
  else
    chk_dialect ("array slice access to non-strings is", GNU_PASCAL);
  STRIP_TYPE_NOPS (lower);
  lower = fold (lower);
  STRIP_TYPE_NOPS (upper);
  upper = fold (upper);
  if (is_cstring)
    {
      min = integer_zero_node;
      max = pascal_maxint_node;
    }
  else if (!is_string)
    {
      if (TREE_CODE (TREE_TYPE (expr)) != ARRAY_TYPE)
        {
          error ("array slice access requires an array");
          return error_mark_node;
        }
      component_type = TREE_TYPE (TREE_TYPE (expr));
    }
  else if (TREE_CODE (TREE_TYPE (expr)) != ARRAY_TYPE)
    {
      min = integer_one_node;
      max = PASCAL_STRING_LENGTH (expr);
      if (PASCAL_TYPE_STRING (TREE_TYPE (expr)))
        max2 = TYPE_LANG_DECLARED_CAPACITY (TREE_TYPE (expr));
    }
  if (!min)
    min = TYPE_MIN_VALUE (TYPE_DOMAIN (TREE_TYPE (expr)));
  if (!max)
    max = TYPE_MAX_VALUE (TYPE_DOMAIN (TREE_TYPE (expr)));

  lo = save_expr (lower);
  hi = save_expr (upper);
  CHK_EM (lo);
  CHK_EM (hi);
  t = TYPE_MAIN_VARIANT (TREE_TYPE (min));
  if (!comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (lo)), t) || !comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (hi)), t))
    {
      error ("type mismatch in array slice index");
      return error_mark_node;
    }
  if (!check_subrange (lo, hi))
    return error_mark_node;

  lo = range_check_2 (min, max, lo);
  if (max2)
    hi = range_check_2 (hi, max2, hi);
  hi = range_check_2 (min, max, hi);
  CHK_EM (lo);
  CHK_EM (hi);

  if (TREE_CODE (expr) == STRING_CST && TREE_CODE (lower) == INTEGER_CST && TREE_CODE (upper) == INTEGER_CST)
    return build_string_constant (TREE_STRING_POINTER (expr) + TREE_INT_CST_LOW (lower) - 1,
      TREE_INT_CST_LOW (upper) - TREE_INT_CST_LOW (lower) + 1, 0);

  integer_index_type = type_for_size (MAX (TYPE_PRECISION (pascal_integer_type_node),
    MAX (TYPE_PRECISION (TREE_TYPE (lower)), TYPE_PRECISION (TREE_TYPE (upper)))),
    TREE_UNSIGNED (TREE_TYPE (lower)) && TREE_UNSIGNED (TREE_TYPE (upper)));
  lo_int = convert (integer_index_type, lo);

  /* Build an array type that has the same length as the sub-array access.
     In EP mode, the new array always starts from index 1. */
  if (co->pascal_dialect & E_O_PASCAL)
    sub_domain = build_range_type (integer_index_type, integer_one_node,
      build_pascal_binary_op (PLUS_EXPR, integer_one_node,
      build_pascal_binary_op (MINUS_EXPR, convert (integer_index_type, hi), lo_int)));
  else
    sub_domain = build_pascal_range_type (lo, hi);
  sub_type = build_pascal_array_type (component_type, build_tree_list (NULL_TREE, sub_domain));

  /* If the array is packed or a string, so is the subarray. */
  if (is_string || PASCAL_TYPE_PACKED (TREE_TYPE (expr)))
    sub_type = pack_type (sub_type);

  /* Build an access to the slice. */
  if (is_cstring)
    res = build_pascal_binary_op (PLUS_EXPR, expr, lo_int);
  else
    {
      tree actual_array = PASCAL_STRING_VALUE (expr);
      res = build_pascal_binary_op (MINUS_EXPR, build_pascal_binary_op (PLUS_EXPR,
              build1 (ADDR_EXPR, build_pointer_type (TREE_TYPE (TREE_TYPE (actual_array))), actual_array),
              lo_int), convert (integer_index_type, TYPE_MIN_VALUE (TYPE_DOMAIN (TREE_TYPE (actual_array)))));
    }
  res = build1 (INDIRECT_REF, sub_type, convert (build_pointer_type (sub_type), res));
  if (!lvalue)
    res = non_lvalue (res);
  return res;
}

/* BIT_FIELD_REF can only handle constant offsets. To work
   around, create a "read" access out of shift operations here. */
tree
build_pascal_packed_array_ref (array, bits, index, is_read)
     tree array, bits, index;
     int is_read;
{
  tree long_type = packed_array_unsigned_long_type_node;
  tree short_type = packed_array_unsigned_short_type_node;
  tree half_bits_per_long_type = size_int (TYPE_PRECISION (long_type) / 2);
  tree half_bytes_per_long_type = size_int (TYPE_PRECISION (long_type) / (2 * BITS_PER_UNIT));
  tree short_type_ptr = build_pointer_type (short_type);
  tree low_var_access, high_var_access, offset, mask, access;
  tree element_type = TREE_TYPE (TREE_TYPE (array));
  unsigned HOST_WIDE_INT imask, smask;
  index = default_conversion (index);
  offset = build_pascal_binary_op (FLOOR_MOD_EXPR, index, half_bits_per_long_type);
  if (WORDS_BIG_ENDIAN)
    offset = build_pascal_binary_op (MINUS_EXPR,
      size_int (TYPE_PRECISION (long_type) - TREE_INT_CST_LOW (bits)), offset);
  imask = ((unsigned HOST_WIDE_INT) ~0) >> (TYPE_PRECISION (long_type) - TREE_INT_CST_LOW (bits));
  mask = convert (long_type, size_int (imask));
  access = build_binary_op (PLUS_EXPR,
    convert (cstring_type_node, convert_array_to_pointer (array)),
      build_pascal_binary_op (MULT_EXPR, build_pascal_binary_op (FLOOR_DIV_EXPR,
        index, half_bits_per_long_type), half_bytes_per_long_type));

  /* Get the long_type value in two halfs to avoid alignment problems. */
  low_var_access = build_indirect_ref (convert (short_type_ptr, access), NULL);
  access = build_pascal_binary_op (PLUS_EXPR, access, half_bytes_per_long_type);
  high_var_access = build_indirect_ref (convert (short_type_ptr, access), NULL);
  if (WORDS_BIG_ENDIAN)
    {
      tree tmp = low_var_access;
      low_var_access = high_var_access;
      high_var_access = tmp;
    }

  /* OR the two parts (shifted), AND with the mask and shift down. */
  access = build_pascal_binary_op (RSHIFT_EXPR, build_pascal_binary_op (BIT_AND_EXPR,
    build_pascal_binary_op (BIT_IOR_EXPR, convert (long_type, low_var_access),
      build_pascal_binary_op (LSHIFT_EXPR, convert (long_type, high_var_access),
        half_bits_per_long_type)), build_pascal_binary_op (LSHIFT_EXPR, mask, offset)), offset);

  /* sign extend the result when necessary */
  if (!TREE_UNSIGNED (element_type))
    {
      smask = ((unsigned HOST_WIDE_INT) 1) << (TREE_INT_CST_LOW (bits) - 1);
      access = build (COND_EXPR, TREE_TYPE (access),
        build_pascal_binary_op (BIT_AND_EXPR, access, size_int (smask)),
        build_pascal_binary_op (BIT_IOR_EXPR, access, size_int (~imask)),
        access);
    }
  access = convert (element_type, access);
  CHK_EM (access);

  if (is_read)
    return access;

  return build_tree_list (access, build_tree_list (array, build_tree_list (
    build_tree_list (offset, mask), build_tree_list (low_var_access, high_var_access))));
}

tree
build_array_ref_or_constructor (t1, t2)
     tree t1, t2;
{
  if (TREE_CODE (t1) == TYPE_DECL && TREE_CODE (TREE_TYPE (t1)) == SET_TYPE)
    return build_iso_set_constructor (TREE_TYPE (t1), t2, 0);
  else
    {
      tree list = t2;
      while (list)
        {
          tree ind = TREE_PURPOSE (list);
          if (TREE_CODE (ind) == IDENTIFIER_NODE)
            ind = check_identifier (ind);
          TREE_PURPOSE (list) = TREE_VALUE (list);
          TREE_VALUE (list) = ind;
          list = TREE_CHAIN (list);
        }
      return build_pascal_array_ref (t1, t2);
    }
}

/* Constructs a reference to a Pascal array. INDEX_LIST is a
   TREE_LIST chain of expressions to index the array with.
   This INDEX_LIST is passed in forward order. */
tree
build_pascal_array_ref (array, index_list)
     tree array, index_list;
{
  tree link;
  CHK_EM (TREE_TYPE (array));
  array = probably_call_function (array);

  if (PASCAL_TYPE_RESTRICTED (TREE_TYPE (array)))
    error ("accessing a component of a restricted array is not allowed");

  for (link = index_list; link; link = TREE_CHAIN (link))
    {
      /* Catch `array_type[i]' etc. */
      if (TREE_CODE (array) == TYPE_DECL
          || (TREE_CODE (TREE_TYPE (array)) != ARRAY_TYPE
              && !PASCAL_TYPE_STRING (TREE_TYPE (array))
              && !(co->cstrings_as_strings
                   && TYPE_MAIN_VARIANT (TREE_TYPE (array)) == cstring_type_node)))
        {
          error ("subscripted object is not an array or string");
          if (TYPE_MAIN_VARIANT (TREE_TYPE (array)) == cstring_type_node)
            cstring_inform ();
          return error_mark_node;
        }

      if (TREE_PURPOSE (link))
        array = build_array_slice_ref (array, TREE_VALUE (link), TREE_PURPOSE (link));
      else if (TYPE_MAIN_VARIANT (TREE_TYPE (array)) == cstring_type_node)
        {
          tree index = probably_call_function (TREE_VALUE (link));
          CHK_EM (index);
          if (!comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (index)), pascal_integer_type_node))
            {
              error ("type mismatch in CString index");
              return error_mark_node;
            }
          array = build_indirect_ref (build_pascal_binary_op (PLUS_EXPR, array, index), NULL);
        }
      else
        {
          tree bits = NULL_TREE, domain, string = NULL_TREE;
          tree index = probably_call_function (string_may_be_char (TREE_VALUE (link), 1));

          if (PASCAL_TYPE_STRING (TREE_TYPE (array)))
            {
              string = save_expr_string (array);
              array = PASCAL_STRING_VALUE (string);
            }

          domain = TYPE_DOMAIN (TREE_TYPE (array));
          assert (domain);
          CHK_EM (domain);
          CHK_EM (index);

          if (!comptypes (TYPE_MAIN_VARIANT (TREE_TYPE (index)), TYPE_MAIN_VARIANT (domain)))
            {
              error ("type mismatch in array index");
              return error_mark_node;
            }

          /* Note: For strings, EP only allows access up to the current length,
                   BP to the capacity. We never want to allow access to the
                   extra element beyond the capacity (which is the maximum of
                   the domain), reserved for internal purposes. */
          if (string)
            index = range_check_2 (integer_one_node, (co->pascal_dialect & B_D_PASCAL)
              ? PASCAL_STRING_CAPACITY (string) : PASCAL_STRING_LENGTH (string), index);
          else
            index = range_check (domain, index);
          CHK_EM (index);

          if (PASCAL_TYPE_PACKED (TREE_TYPE (array)))
            bits = count_bits (TREE_TYPE (TREE_TYPE (array)));

          if (TREE_CODE (array) == STRING_CST && TREE_CODE (index) == INTEGER_CST)
            {
              array = build_int_2 (TREE_STRING_POINTER (array)[TREE_INT_CST_LOW (index) - 1], 0);
              TREE_TYPE (array) = char_type_node;
            }
          else if (!bits || TREE_INT_CST_LOW (bits) == TREE_INT_CST_LOW (TYPE_SIZE (TREE_TYPE (TREE_TYPE (array)))))
            /* Not packed. Just a normal array reference. */
            array = build_array_ref (array, index);
          else
            {
              tree orig_index = index;
              tree indextype = sizetype;
              tree sindextype = ssizetype;
              /* Accessing a field of a packed array possibly not located on a byte boundary. */
              tree array_type = TREE_TYPE (array);

#ifdef EGCS
              if (LONG_TYPE_SIZE < 64)
                {
                  int big = 1;
                  if (TREE_CODE (TYPE_SIZE (array_type)) == INTEGER_CST
                      && tree_int_cst_lt (TYPE_SIZE (array_type),
                                          TYPE_MAX_VALUE (usizetype)))
                    big = 0;
#if 0
                  /* @@@@@ Non constant, guesstimate */
                  if (TREE_CODE (TYPE_SIZE (array_type)) != INTEGER_CST)
                    {
                      tree low = TYPE_MIN_VALUE (TYPE_DOMAIN (array_type));
                      tree high = TYPE_MAX_VALUE (TYPE_DOMAIN (array_type));
                      debug_tree (low);
                      debug_tree (high);
                    }
#endif
                  if (big)
                    {
                      indextype = bitsizetype;
                      sindextype = sbitsizetype;
                    }
                }
#endif
              bits = convert (indextype, bits);
              /* Index starting from 0. */
              index = size_binop (MINUS_EXPR,
                convert (sindextype, index),
                convert (sindextype, TYPE_MIN_VALUE (TYPE_DOMAIN (array_type))));

              /* Index measured in bits. */
#ifdef EGCS97
              index = size_binop (MULT_EXPR, convert (indextype, index), convert (indextype, bits));
#else
              /* gcc-2.95 only accepts `sizetype' in `size_binop'.
                 But bitsizetype may fail in type_for_size on some platforms
                 (e.g., OSF/Alpha), so better be safe than sorry ... */
              index = fold (build_pascal_binary_op (MULT_EXPR,
                        convert (long_long_integer_type_node, index),
                        convert (long_long_integer_type_node, bits)));
#endif
              STRIP_NOPS (index);

              /* Access the bits. */
              if (TREE_CODE (index) == INTEGER_CST)
                {
                  tree ar = array;
                  if (TREE_CODE (ar) == NON_LVALUE_EXPR)
                    ar = TREE_OPERAND (ar, 0);
                  /* Fold constant reference */
                  if (TREE_CODE (ar) == NOP_EXPR)
                    {
                      tree t = TREE_TYPE (TREE_OPERAND (ar, 0)), elts;
                      if (TYPE_LANG_CODE_TEST (t, PASCAL_LANG_FAKE_ARRAY))
                        {
                          for (elts = TYPE_LANG_FAKE_ARRAY_ELEMENTS (t); elts; elts = TREE_CHAIN (elts))
                            if (tree_int_cst_equal (orig_index, TREE_PURPOSE (elts)))
                              return TREE_VALUE (elts);
                          assert (0);
                        }
                    }
                  array = build (BIT_FIELD_REF, TREE_TYPE (array_type),
                    array, convert (bitsizetype, bits), convert (bitsizetype, index));
                }
              else
                array = build (PASCAL_BIT_FIELD_REF, TREE_TYPE (array_type), array, bits, index);
              TREE_UNSIGNED (array) = TREE_UNSIGNED (TREE_TYPE (array_type));
            }
        }
      if (EM (array))
        break;
      DEREFERENCE_SCHEMA (array);
    }
  prediscriminate_schema (array);
  return array;
}

tree
fold_array_ref (t)
     tree t;
{
  tree arg0, arg1;
  assert (TREE_CODE (t) == ARRAY_REF);
  arg0 = TREE_OPERAND (t, 0);
  arg1 = TREE_OPERAND (t, 1);
  if (TREE_CODE (arg1) == INTEGER_CST && TREE_CODE (arg0) == STRING_CST)
    {
      arg1 = range_check_2 (integer_one_node, build_int_2 (TREE_STRING_LENGTH (arg0) - 1, 0), arg1);
      CHK_EM (arg1);
      t = build_int_2 (TREE_STRING_POINTER (arg0)[TREE_INT_CST_LOW (arg1) - 1], 0);
      TREE_TYPE (t) = char_type_node;
    }
  else if (TREE_CODE (arg1) == INTEGER_CST && TREE_CODE (arg0) == CONSTRUCTOR)
    {
      tree elts = CONSTRUCTOR_ELTS (arg0);
      arg1 = range_check (TYPE_DOMAIN (TREE_TYPE (arg0)), arg1);
      CHK_EM (arg1);
      while (elts)
        {
          if (tree_int_cst_equal (arg1, TREE_PURPOSE (elts)))
            return TREE_VALUE (elts);
          elts = TREE_CHAIN (elts);
        }
    }
  return t;
}

/* Handle array references (`a[i]'). If the array is a variable or a field,
   we generate a primitive ARRAY_REF. This avoids forcing the array out of
   registers, and can work on arrays that are not lvalues (for example,
   fields of structures returned by functions). */
tree
build_array_ref (array, index)
     tree array, index;
{
  tree res;
  int lvalue = lvalue_p (array);

  CHK_EM (TREE_TYPE (array));
  CHK_EM (TREE_TYPE (index));

  assert (index);

  if (!ORDINAL_TYPE (TREE_CODE (TREE_TYPE (index))))
    {
      error ("array index is not of ordinal type");
      return error_mark_node;
    }

  array = probably_call_function (array);
  index = default_conversion (index);

  assert (TREE_CODE (TREE_TYPE (array)) == ARRAY_TYPE);
  if (TREE_CODE (array) != INDIRECT_REF)
    {
      tree rval, type;

      /* An array that is indexed by a non-constant
         cannot be stored in a register; we must be able to do
         address arithmetic on its address.
         Likewise an array of elements of variable size. */
      if ((TREE_CODE (index) != INTEGER_CST
           || (TYPE_SIZE (TREE_TYPE (TREE_TYPE (array)))
               && TREE_CODE (TYPE_SIZE (TREE_TYPE (TREE_TYPE (array)))) != INTEGER_CST))
          && !mark_addressable2 (array, 1))
        return error_mark_node;

      if (pedantic && !lvalue)
        {
          if (DECL_REGISTER (array))
            pedwarn ("indexing of `register' array");
          else
            pedwarn ("indexing of non-lvalue array");
        }

      if (pedantic)
        {
          tree foo = array;
          while (TREE_CODE (foo) == COMPONENT_REF)
            foo = TREE_OPERAND (foo, 0);
          if (TREE_CODE (foo) == VAR_DECL && DECL_REGISTER (foo))
            pedwarn ("indexing of non-lvalue array");
        }

      type = TYPE_MAIN_VARIANT (TREE_TYPE (TREE_TYPE (array)));
      rval = build (ARRAY_REF, type, array, index);
      /* Array ref is const/volatile if the array elements are or if the array is. */
      TREE_READONLY (rval) |= (TYPE_READONLY (TREE_TYPE (TREE_TYPE (array))) | TREE_READONLY (array));
      TREE_SIDE_EFFECTS (rval) |= (TYPE_VOLATILE (TREE_TYPE (TREE_TYPE (array))) | TREE_SIDE_EFFECTS (array));
      TREE_THIS_VOLATILE (rval) |= (TYPE_VOLATILE (TREE_TYPE (TREE_TYPE (array)))
                                   /* This was added by rms on 16 Nov 91. It fixes
                                        volatile struct foo *a;  a->elts[1]
                                      in an inline function. Hope it doesn't break something else. */
                                   | TREE_THIS_VOLATILE (array));
      res = fold_array_ref (rval);
    }
  else
    {
      tree ar = (TYPE_MAIN_VARIANT (TREE_TYPE (array)) == cstring_type_node)
                ? array : convert_array_to_pointer (array);
      CHK_EM (ar);
      assert (TREE_CODE (TREE_TYPE (ar)) == POINTER_TYPE
              && TREE_CODE (TREE_TYPE (TREE_TYPE (ar))) != FUNCTION_TYPE);

      /* @@ jtv: Kenner's code does not handle non-zero low bound array
         indirect_refs, so I leave this code here. When it does
         this can be disabled partially. */
      if (TYPE_DOMAIN (TREE_TYPE (array)))
        {
          tree s_ind = convert (sizetype, index);
          tree s_min = convert (sizetype, TYPE_MIN_VALUE (
                                   TYPE_DOMAIN (TREE_TYPE (array))));
          res = build_indirect_ref (build_pascal_binary_op (PLUS_EXPR, ar,
            fold (build (MINUS_EXPR, sizetype, s_ind, s_min))), NULL);
        }
      else
        res = build_indirect_ref (build_pascal_binary_op (PLUS_EXPR, ar, index), NULL);
    }
  if (!lvalue)  /* e.g. indexing a string constant */
    res = non_lvalue (res);
  return res;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE. This function implements
   all reasonable conversions; callers should filter out those that are
   not permitted by the language being compiled.
   Change of width -- truncation and extension of integers or reals -- is
   represented with NOP_EXPR. Proper functioning of many things assumes that
   no other conversions can be NOP_EXPRs. Some backend functions assume that
   widening and narrowing is always done with a NOP_EXPR (cf. c-convert.c).
   Conversion between integer and pointer is represented with CONVERT_EXPR.
   Converting integer to real uses FLOAT_EXPR. */
tree
convert (type, e)
     tree type, e;
{
  enum tree_code code = TREE_CODE (type);
  assert (type && e);
  if (type == TREE_TYPE (e) || EM (e) || EM (type))
    return e;
  CHK_EM (TREE_TYPE (e));
  if (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (TREE_TYPE (e)))
    return fold (build1 (NOP_EXPR, type, e));
  if (code == SET_TYPE && TREE_CODE (TREE_TYPE (e)) == SET_TYPE)
    return e;
  if (TREE_CODE (TREE_TYPE (e)) == VOID_TYPE)
    {
      error ("void value not ignored as it ought to be");
      return error_mark_node;
    }
  if (code == VOID_TYPE)
    return build1 (CONVERT_EXPR, type, e);
  if (code == INTEGER_TYPE || code == ENUMERAL_TYPE)
    {
      /* @@ convert_to_integer can change the type of the expression itself
            from any ordinal to integer type. This may be ok in C, but not in
            Pascal (i.e., it's a backend bug). To work-around, we wrap the
            expression here to avoid this bug in case there are other
            references to it (as in fact there are in `case', casebool.pas). */
      enum tree_code c = TREE_CODE (e);
      tree e2 = (TREE_CODE_CLASS (c) == '<' || c == TRUTH_AND_EXPR || c == TRUTH_ANDIF_EXPR
        || c == TRUTH_OR_EXPR || c == TRUTH_ORIF_EXPR || c == TRUTH_XOR_EXPR || c == TRUTH_NOT_EXPR) ? copy_node (e) : e;
      tree result = fold (convert_to_integer (type, e2));
      if (TREE_CODE (result) == INTEGER_CST && TREE_UNSIGNED (TREE_TYPE (result)))
        TREE_UNSIGNED (result) = 1;
      return result;
    }
  if (code == POINTER_TYPE)
    {
      /* @@@ REFERENCE_TYPE not utilized fully in GPC. Should be re-implemented.
             (I implemented var parameters before GCC had REFERENCE_TYPE) */
      if (TREE_CODE (TREE_TYPE (e)) == REFERENCE_TYPE)
        return fold (build1 (CONVERT_EXPR, type, e));
      return fold (convert_to_pointer (type, e));
    }
  /* @@@@ Note: I am not sure this is the correct place to try to fix the problem:
          -O6 in alpha compiling zap.pas traps here. But should the reference_type
          be trapped earlier?? */
  if (code == REFERENCE_TYPE)
    {
      if (TREE_CODE (TREE_TYPE (e)) == POINTER_TYPE)
        return fold (build1 (CONVERT_EXPR, type, e));
      return fold (build1 (CONVERT_EXPR, type,
                           fold (convert_to_pointer (build_pointer_type (TREE_TYPE (type)), e))));
    }
  if (code == REAL_TYPE)
    return fold (convert_to_real (type, e));
  if (code == COMPLEX_TYPE)
    return fold (convert_to_complex (type, e));
  if (code == BOOLEAN_TYPE)
    {
      enum tree_code form = TREE_CODE (TREE_TYPE (e));
      if (integer_zerop (e))
        return fold (build1 (NOP_EXPR, type, boolean_false_node));
      else if (integer_onep (e))
        return fold (build1 (NOP_EXPR, type, boolean_true_node));
      else if (form == BOOLEAN_TYPE)
        {
          if (TYPE_PRECISION (TREE_TYPE (e)) == TYPE_PRECISION (type))
            return fold (build1 (NOP_EXPR, type, e));
          else
            return build (NE_EXPR, type, e, convert (TREE_TYPE (e), boolean_false_node));
        }
      else if (ORDINAL_TYPE (form) || form == POINTER_TYPE)
        return fold (build1 (CONVERT_EXPR, type, e));
      error ("cannot convert to a boolean type");
      return error_mark_node;
    }
  if (code == CHAR_TYPE)
    {
      enum tree_code form = TREE_CODE (TREE_TYPE (e));
      if (form == CHAR_TYPE)
        return fold (build1 (NOP_EXPR, type, e));
      /* @@ If it does not fit? */
      if (ORDINAL_TYPE (form))
        return fold (build1 (CONVERT_EXPR, type, e));
      error ("cannot convert to a char type");
      return error_mark_node;
    }
  error ("type mismatch");
  return error_mark_node;
}

tree
build_simple_array_type (elt_type, index_type)
     tree elt_type, index_type;
{
  tree t;
  CHK_EM (elt_type);
  CHK_EM (index_type);
  t = make_node (ARRAY_TYPE);
  TREE_TYPE (t) = elt_type;
  TYPE_DOMAIN (t) = index_type;
  assert (index_type);
  layout_type (t);
  if (!TYPE_SIZE (t) || TREE_OVERFLOW (TYPE_SIZE (t))
      || (integer_zerop (TYPE_SIZE (t)) && !integer_zerop (TYPE_SIZE (elt_type))))
    {
      error ("size of array is too large");
      return error_mark_node;
    }
  return t;
}

/* Return a new Boolean type node with given precision. */
tree
build_boolean_type (precision)
     unsigned precision;
{
  tree r = make_node (BOOLEAN_TYPE);
  TYPE_PRECISION (r) = precision;
  TREE_UNSIGNED (r) = 1;
  fixup_unsigned_type (r);
  return r;
}

/* Give TYPE a new main variant. This is the right thing to do only when
   something "substantial" about TYPE is modified. */
void
new_main_variant (type)
     tree type;
{
  tree t;
  for (t = TYPE_MAIN_VARIANT (type); TYPE_NEXT_VARIANT (t); t = TYPE_NEXT_VARIANT (t))
    if (TYPE_NEXT_VARIANT (t) == type)
      {
        TYPE_NEXT_VARIANT (t) = TYPE_NEXT_VARIANT (type);
        break;
      }
  TYPE_MAIN_VARIANT (type) = type;
  TYPE_NEXT_VARIANT (type) = NULL_TREE;
}

#ifdef EGCS
/* Make a variant type in the proper way for C, propagating qualifiers
   down to the element type of an array. */
tree
c_build_qualified_type (type, type_quals)
     tree type;
     int type_quals;
{
  tree t = build_qualified_type (type, type_quals);
  if (TREE_CODE (type) == ARRAY_TYPE)
    {
      t = build_type_copy (t);
      TREE_TYPE (t) = c_build_qualified_type (TREE_TYPE (type), type_quals);
    }
  return t;
}
#else
tree
c_build_type_variant (type, constp, volatilep)
     tree type;
     int constp, volatilep;
{
  tree t = p_build_type_variant (type, constp, volatilep);
  if (TREE_CODE (type) == ARRAY_TYPE)
    {
      t = build_type_copy (t);
      TREE_TYPE (t) = c_build_type_variant (TREE_TYPE (type), constp, volatilep);
    }
  return t;
}
#endif

/* Build a Pascal variant of the TYPE. Qualifiers are only ever added, not removed. */
tree
pascal_type_variant (type, qualifier)
     tree type;
     int qualifier;
{
  int protected  = !!(qualifier & TYPE_QUALIFIER_PROTECTED);
  int conformant = !!(qualifier & TYPE_QUALIFIER_CONFORMANT);
  int restricted = !!(qualifier & TYPE_QUALIFIER_RESTRICTED);
  int packed     = !!(qualifier & TYPE_QUALIFIER_PACKED);
  int bindable   = !!(qualifier & TYPE_QUALIFIER_BINDABLE);
  int need_new_variant;

  if (bindable && !PASCAL_TYPE_FILE (type))
    warning ("GPC supports `bindable' only for files");

  CHK_EM (type);

  /* Restricted types should not get a new TYPE_MAIN_VARIANT so they're
     compatible to the unrestricted ones in parameter lists. Same for conformant
     which is used for conformant array bounds (not the arrays), which must be
     compatible to the ordinary type which the actual parameters will have. */
  need_new_variant = (packed && !PASCAL_TYPE_PACKED (type))
                     /* Special case for `restricted Void' (fjf369*.pas) */
                     || (restricted && TREE_CODE (type) == VOID_TYPE);

  if (!(need_new_variant
        || PASCAL_TYPE_OPEN_ARRAY (type)
        || (protected  && !TYPE_READONLY (type))
        || (bindable   && !PASCAL_TYPE_BINDABLE (type))
        || (conformant && !PASCAL_TYPE_CONFORMANT_BOUND (type))
        || (restricted && !PASCAL_TYPE_RESTRICTED (type))))
    return type;

  type = build_type_copy (type);
  copy_type_lang_specific (type);

  /* This is a new type, so remove it from the variants of the old type */
  if (need_new_variant)
    new_main_variant (type);

  TYPE_READONLY (type) |= protected;
  PASCAL_TYPE_BINDABLE (type) |= bindable;
  PASCAL_TYPE_CONFORMANT_BOUND (type) |= conformant;
  PASCAL_TYPE_RESTRICTED (type) |= restricted;
  PASCAL_TYPE_PACKED (type) |= packed;
  PASCAL_TYPE_OPEN_ARRAY (type) = 0;

  /* Not allowed */
  if (PASCAL_TYPE_BINDABLE (type) && PASCAL_TYPE_RESTRICTED (type))
    error ("restricted types must not be bindable");

  return type;
}

/* @@ This is just a wrapper around build_type_variant that copies
      TYPE_LANG_SPECIFIC. Shouldn't it be merged with
      pascal_type_variant() (what's the difference, anyway)? -- Frank */
tree
p_build_type_variant (type, constp, volatilep)
     tree type;
     int constp, volatilep;
{
  tree new_type;
  CHK_EM (type);
  new_type = build_type_variant (type, constp, volatilep);
  if (new_type != type
      && TYPE_LANG_SPECIFIC (new_type)
      && TYPE_LANG_SPECIFIC (new_type) == TYPE_LANG_SPECIFIC (type))
    {
      TYPE_LANG_SPECIFIC (new_type) = allocate_type_lang_specific ();
      memcpy (TYPE_LANG_SPECIFIC (new_type), TYPE_LANG_SPECIFIC (type), sizeof (struct lang_type));
    }
  return new_type;
}
