/*Object oriented programming support routines for GNU Pascal

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

#include "gpc.h"

static tree current_method PARAMS ((void));

/* Get a FIELD_DECL node of structured type type. This is only applied to
   structures with no variant part and no schemata, so it is much simpler
   than find_field(). We don't use the sorted fields here, because they
   should be either unimportant (schema_id) or not applicable (methods)
   anyway when this is called. */
tree
simple_get_field (name, type, descr)
     tree name, type;
     const char *descr;
{
  tree field = TYPE_FIELDS (type);
  while (field && DECL_NAME (field) != name)
    field = TREE_CHAIN (field);
  if (field)
    return field;
  field = TYPE_METHODS (type);
  while (field && DECL_NAME (field) != name)
    field = TREE_CHAIN (field);
  if (!descr)
    assert (field);
  if (!field && *descr)
    error ("%s `%s' not found", descr, IDENTIFIER_NAME (name));
  return field;
}

tree
get_vmt_field (obj)
     tree obj;
{
  tree vmt_field;
  CHK_EM (obj);
  if ((TREE_CODE (TREE_TYPE (obj)) == FUNCTION_TYPE && RECORD_OR_UNION (TREE_CODE (TREE_TYPE (TREE_TYPE (obj)))))
      || CALL_METHOD (obj))
    obj = undo_schema_dereference (probably_call_function (obj));
  assert (TREE_CODE (obj) != COND_EXPR);
  if (TREE_CODE (obj) == COMPOUND_EXPR)
    {
      tree value = get_vmt_field (TREE_OPERAND (obj, 1));
      return build (COMPOUND_EXPR, TREE_TYPE (value), TREE_OPERAND (obj, 0), value);
    }
  vmt_field = TYPE_LANG_VMT_FIELD (TREE_TYPE (obj));
  return build (COMPONENT_REF, TREE_TYPE (vmt_field), obj, vmt_field);
}

static tree
current_method ()
{
  struct function *p;
  tree decl;
#ifdef EGCS97
  for (p = outer_function_chain; p && p->outer; p = p->outer) ;
#else
  for (p = outer_function_chain; p && p->next; p = p->next) ;
#endif
  decl = p ? p->decl : current_function_decl;
  /* DECL_CONTEXT can be NULL after a previous error */
  return decl && PASCAL_METHOD (decl) && DECL_CONTEXT (decl) ? decl : NULL_TREE;
}

/* To implement `private' with unit/module scope: finish_object_type sets
   TREE_PRIVATE which by itself doesn't prevent access. When importing a field
   with TREE_PRIVATE set, also TREE_PROTECTED is set. So here we check the
   combination of both. TREE_PROTECTED alone means `protected'. */
const char *
check_private_protected (field)
     tree field;
{
  if (TREE_PROTECTED (field) && TREE_PRIVATE (field))
    return "private";
  if (TREE_PROTECTED (field))
    {
      tree t = current_method ();
      if (t)
        for (t = DECL_CONTEXT (t); t && t != DECL_CONTEXT (field); t = TYPE_LANG_BASE (t)) ;
      if (!t)
        return "protected";
    }
  return NULL;
}

/* Build a method call out of a COMPONENT_REF. */
tree
call_method (cref, args)
     tree cref, args;
{
  int is_virtual;
  tree obj = TREE_OPERAND (cref, 0);
  tree fun = TREE_OPERAND (cref, 1);

  if (!PASCAL_TYPE_OBJECT (TREE_TYPE (obj)))
    {
      error ("calling method of something not an object");
      return error_mark_node;
    }

  if (TREE_CODE (fun) != FUNCTION_DECL || TREE_CODE (TREE_TYPE (fun)) != FUNCTION_TYPE)
    {
      error ("invalid method call");
      return error_mark_node;
    }
  assert (PASCAL_METHOD (fun));

  /* @@ Is this the right place to do it? (fjf639x5.pas, fjf644.pas)
        It would seem logical to build a save_expr of the whole object,
        but it doesn't work (works only on scalar types I guess),
        so do it only for INDIRECT_REFs. -- Frank */
  if (TREE_CODE (obj) == INDIRECT_REF)
    obj = build1 (INDIRECT_REF, TREE_TYPE (obj), save_expr (TREE_OPERAND (obj, 0)));

  is_virtual = PASCAL_VIRTUAL_METHOD (fun);
  if (TREE_CODE (obj) == TYPE_DECL)
    {
      if (!current_method ())
        /* Somebody is looking for the address of this method. Give them the FUNCTION_DECL. */
        return fun;

      /* This is an explicit call to an ancestor's method. */
      fun = simple_get_field (DECL_NAME (fun), TREE_TYPE (obj), "method");
      if (!fun)
        return error_mark_node;
      obj = build_indirect_ref (lookup_name (self_id), "`Self' reference");
      is_virtual = 0;
    }

  if (is_virtual)
    {
      tree method = NULL_TREE, type_save;
      /* @@ Here a runtime check can be added: does the VMT field really point to a VMT? */
      char *n = ACONCAT (("method_", IDENTIFIER_POINTER (DECL_NAME (fun)), NULL));
      method = simple_get_field (get_identifier (n), TREE_TYPE (TREE_TYPE (TYPE_LANG_VMT_FIELD (TREE_TYPE (obj)))), NULL);

      type_save = TREE_TYPE (fun);
      fun = build (COMPONENT_REF, TREE_TYPE (method),
        build_indirect_ref (get_vmt_field (obj), NULL), method);
      /* In the VMT, only generic pointers are stored to avoid
         confusion in GPI files. Repair them here. */
      TREE_TYPE (fun) = build_pointer_type (type_save);
      fun = build_indirect_ref (fun, NULL);
    }
  else
    /* Not a virtual method. Use the function definition rather than the
       method field to allow for inline optimizations. */
    fun = DECL_LANG_METHOD_DECL (fun);

  /* Check if OBJ is an lvalue and do the call */
  if (lvalue_or_else (obj, "method call"))
    fun = build_routine_call (fun, tree_cons (NULL_TREE, obj, args));
  return fun;
}

tree
build_inherited_method (id)
     tree id;
{
  tree basetype, method = current_method ();
  if (!method)
    error ("`inherited' used outside of any method");
  else if (!(basetype = TYPE_LANG_BASE (DECL_CONTEXT (method))))
    error ("there is no parent type to inherit from");
  else
    return build_component_ref (TYPE_NAME (basetype), id);
  return error_mark_node;
}

/* Construct the internal name of a method. */
tree
get_method_name (object_name, method_name)
     tree object_name, method_name;
{
  tree t;
  const char *n = IDENTIFIER_POINTER (method_name);
  assert (object_name);
  t = get_identifier (ACONCAT ((IDENTIFIER_POINTER (object_name), "_",
                                (*n >= 'A' && *n <= 'Z') ? "" : "OBJ", n, NULL)));
  if (!IDENTIFIER_SPELLING (t) && IDENTIFIER_SPELLING (object_name) && IDENTIFIER_SPELLING (method_name))
    {
      char *s = ACONCAT ((IDENTIFIER_SPELLING (object_name), ".",
                          IDENTIFIER_SPELLING (method_name), NULL));
      set_identifier_spelling (t, s, NULL, 0, 0);
    }
  return t;
}

tree
start_object_type (name)
     tree name;
{
  tree t = start_struct (RECORD_TYPE);
  if (co->pascal_dialect & MAC_PASCAL)
    warning ("traditional Macintosh Pascal has a different object model from what GNU Pascal supports");
  if (!pascal_global_bindings_p ())
    error ("object type definition only allowed at top level");
  TYPE_MODE (t) = BLKmode;  /* may be used as a value parameter within its methods */
  TYPE_ALIGN (t) = BIGGEST_ALIGNMENT;
  TYPE_LANG_SPECIFIC (t) = allocate_type_lang_specific ();
  TYPE_LANG_CODE (t) = PASCAL_LANG_OBJECT;
  build_type_decl (name, t, NULL_TREE);
  return t;
}

/* Finish an object type started with start_object_type. Note: Don't return
   prematurely in case of error to avoid leaving the type incomplete.
   Items is a mixed chain of:
   - FIELD_DECL
   - FUNCTION_DECL (result of build_routine_heading)
   - TREE_LIST
       VALUE:   IDENTIFIER_NODE (object directive)
       PURPOSE: void_type_node
      or
       VALUE:   IDENTIFIER_NODE (`virtual', `abstract', `attribute')
       PURPOSE: expression (for `virtual', optionally),
                or TREE_LIST (for `attribute')
                or NULL_TREE
     It would be nicer to have them attached to the method descriptions, but
     this seems to be hard to achieve in the parser. So we handle it here. */
tree
finish_object_type (type, parent, items, abstract)
     tree type, parent, items;
     int abstract;
{
  tree fields, methods, field, parm, vmt_entry, vmt_type, size, vmt_field, t;
  tree *pfields, *pmethods, cp, init, f, ti;
  const char *object_name = IDENTIFIER_NAME (DECL_NAME (TYPE_NAME (type))), *n;
  int protected_private = 0, has_virtual_method = 0, has_constructor = 0, i;

  if (parent && EM (parent))
    parent = NULL_TREE;
  if (parent && !PASCAL_TYPE_OBJECT (parent))
    {
      tree parent_name = TYPE_NAME (parent);
      if (TREE_CODE (parent_name) == TYPE_DECL)
        parent_name = DECL_NAME (parent_name);
      error ("parent object type expected, `%s' given", IDENTIFIER_NAME (parent_name));
      parent = NULL_TREE;
    }

  if (parent && PASCAL_TYPE_RESTRICTED (parent))
    error ("trying to declare a subtype of a restricted object type");

  pfields = &fields;
  pmethods = &methods;
  for (cp = items; cp && !EM (cp); cp = TREE_CHAIN (cp))
    if (TREE_CODE (cp) == TREE_LIST)
      {
        assert (TREE_CODE (TREE_VALUE (cp)) == IDENTIFIER_NODE);
        if (TREE_PURPOSE (cp) != void_type_node)
          error ("spurious `%s'", IDENTIFIER_NAME (TREE_VALUE (cp)));
        else
          {
            tree t = TREE_VALUE (cp);
            chk_dialect ("object directives are", B_D_M_PASCAL);
            if (IDENTIFIER_IS_BUILT_IN (t, p_public) || IDENTIFIER_IS_BUILT_IN (t, p_published))
              protected_private = 0;
            else if (IDENTIFIER_IS_BUILT_IN (t, p_protected))
              protected_private = 1;
            else if (IDENTIFIER_IS_BUILT_IN (t, p_private))
              protected_private = 2;
            else
              error ("unknown object directive `%s'", IDENTIFIER_NAME (t));
          }
      }
    else if (TREE_CODE (cp) != FUNCTION_DECL)
      {
        if (!EM (TREE_TYPE (cp)))
          {
            *pfields = cp;
            pfields = &TREE_CHAIN (cp);
            TREE_PROTECTED (cp) = protected_private == 1;
            TREE_PRIVATE (cp) = protected_private == 2;
          }
      }
    else
      {
        tree heading = cp, assembler_name = NULL_TREE, method, method_field;
        tree t = TREE_TYPE (heading), name = DECL_NAME (heading);
        tree method_name = get_method_name (DECL_NAME (TYPE_NAME (type)), name);
        tree args, argtypes = build_formal_param_list (DECL_ARGUMENTS (heading), type, &args);
        int virtual = 0, n = 0;
        filename_t save_input_filename = input_filename;
        int save_lineno = lineno, save_column = column;
        if (!t)
          error ("result type of method function `%s' undefined", IDENTIFIER_NAME (name));
        if (!t || EM (t))
          continue;
        if (co->methods_always_virtual && !(PASCAL_STRUCTOR_METHOD (heading) && t == boolean_type_node))
          virtual = 1;
        method = build_decl (FUNCTION_DECL, method_name, build_function_type (t, argtypes));
        input_filename = DECL_SOURCE_FILE (method) = DECL_SOURCE_FILE (heading);
        lineno = DECL_SOURCE_LINE (method) = DECL_SOURCE_LINE (heading);
        /*@@ column = DECL_SOURCE_COLUMN (method) = DECL_SOURCE_COLUMN (heading); */
        while (TREE_CHAIN (cp) && TREE_CODE (TREE_CHAIN (cp)) == TREE_LIST
               && TREE_CODE (TREE_VALUE (TREE_CHAIN (cp))) == IDENTIFIER_NODE
               && TREE_PURPOSE (TREE_CHAIN (cp)) != void_type_node)
          {
            cp = TREE_CHAIN (cp);
            if (IDENTIFIER_IS_BUILT_IN (TREE_VALUE (cp), p_virtual))
              {
                if (co->methods_always_virtual)
                  warning ("explicit `virtual' given with `--methods-always-virtual'");
                virtual = 1;
                n++;
                if (TREE_PURPOSE (cp))
                  {
                    tree t = TREE_PURPOSE (cp);
                    STRIP_TYPE_NOPS (t);
                    t = fold (t);
                    if (TREE_CODE (t) != INTEGER_CST || TREE_CODE (TREE_TYPE (t)) != INTEGER_TYPE)
                      error ("dynamic method index must be an integer constant");
                    else if (const_lt (t, integer_one_node)
                             || TREE_INT_CST_HIGH (t) != 0 || TREE_INT_CST_LOW (t) > 65535)
                      error ("dynamic method index must be in the range 1 .. 65535");  /* BP's range */
                    /* anyway, ignore the index */
                  }
              }
            else if (IDENTIFIER_IS_BUILT_IN (TREE_VALUE (cp), p_abstract))
              {
                virtual = 2;
                n++;
              }
            else if (IDENTIFIER_IS_BUILT_IN (TREE_VALUE (cp), p_attribute))
              routine_attributes (&method, TREE_PURPOSE (cp), &assembler_name);
            else
              error ("unknown object method directive `%s'", IDENTIFIER_NAME (TREE_VALUE (cp)));
          }
        if (n > 1)
          error ("duplicate `virtual' or `abstract'");
        DECL_EXTERNAL (method) = 1;
        PASCAL_FORWARD_DECLARATION (method) = virtual != 2;
        PASCAL_METHOD (method) = 1;
        TREE_PROTECTED (method) = protected_private == 1;
        TREE_PRIVATE (method) = protected_private == 2;
        if (assembler_name)
          assembler_name = check_assembler_name (assembler_name);
        else
          assembler_name = pascal_mangle_names (object_name,
                              IDENTIFIER_POINTER (name));
        SET_DECL_ASSEMBLER_NAME (method, assembler_name);
        DECL_LANG_SPECIFIC (method) = allocate_decl_lang_specific ();
        DECL_LANG_PARMS (method) = args;
        DECL_LANG_RESULT_VARIABLE (method) = DECL_RESULT (heading);
        PASCAL_STRUCTOR_METHOD (method) = PASCAL_STRUCTOR_METHOD (heading);
        TREE_PUBLIC (method) = virtual == 2 || current_module->main_program || !current_module->implementation;
        if (virtual || TREE_PUBLIC (method))
          mark_addressable (method);
        /* Push also abstract methods (for better error messages on attempts to implement them). */
        method = pushdecl (method);
        assert (!EM (method));
        rest_of_decl_compilation (method, 0, 1, 1);
        if (PASCAL_FORWARD_DECLARATION (method))
          {
            set_forward_decl (method, 1);
            handle_autoexport (method_name);
          }
        DECL_CONTEXT (method) = type;
        DECL_NO_STATIC_CHAIN (method) = 1;  /* @@ ? */
        PASCAL_VIRTUAL_METHOD (method) = virtual != 0;
        PASCAL_ABSTRACT_METHOD (method) = virtual == 2;
        if (virtual && PASCAL_CONSTRUCTOR_METHOD (method))
          error ("constructors must not be virtual or abstract");
        method_field = copy_node (method);
        PASCAL_FORWARD_DECLARATION (method_field) = 0;
        DECL_NAME (method_field) = name;
        /* Also affects method since DECL_LANG_SPECIFIC is not copied, but shouldn't hurt. */
        DECL_LANG_METHOD_DECL (method_field) = method;
        *pmethods = method_field;
        pmethods = &TREE_CHAIN (method_field);
        input_filename = save_input_filename;
        lineno = save_lineno;
        column = save_column;
      }
  *pmethods = NULL_TREE;
  *pfields = NULL_TREE;

  for (i = 0; i <= 1; i++)
    for (field = i ? methods : fields; field; field = TREE_CHAIN (field))
      {
        tree t;
        for (t = parent; t && DECL_NAME (TYPE_NAME (t)) != DECL_NAME (field); t = TYPE_LANG_BASE (t)) ;
        if (t)
          {
            if (PEDANTIC (B_D_PASCAL))  /* forbidden by OOE */
              error ("%s `%s' conflicts with ancestor type name", i ? "method" : "field", IDENTIFIER_NAME (DECL_NAME (field)));
            else
              warning ("%s `%s' conflicts with ancestor type name", i ? "method" : "field", IDENTIFIER_NAME (DECL_NAME (field)));
          }
      }

  if (parent)
    {
      /* Inheritance */
      tree parent_methods, df, pf, *dm, *pm, t;
      for (pf = TYPE_FIELDS (parent); pf; pf = TREE_CHAIN (pf))
        {
          for (df = fields; df && DECL_NAME (df) != DECL_NAME (pf); df = TREE_CHAIN (df));
          if (df)
            {
              error ("cannot overwrite data field `%s' of parent object type", IDENTIFIER_NAME (DECL_NAME (df)));
              continue;
            }
          for (df = methods; df && DECL_NAME (df) != DECL_NAME (pf); df = TREE_CHAIN (df));
          if (df)
            error ("method `%s' conflicts with data field of parent object type", IDENTIFIER_NAME (DECL_NAME (df)));
        }
      parent_methods = copy_list (TYPE_METHODS (parent));
      for (pm = &parent_methods; *pm; )
        {
          for (df = fields; df && DECL_NAME (df) != DECL_NAME (*pm); df = TREE_CHAIN (df));
          if (df)
            error ("data field `%s' conflicts with method of parent object type", IDENTIFIER_NAME (DECL_NAME (df)));
          else
            {
              for (dm = &methods; *dm && DECL_NAME (*dm) != DECL_NAME (*pm); dm = &TREE_CHAIN (*dm));
              if (*dm)
                {
                  static const char *const descr[3] = { "public", "protected", "private" };
                  int p1 = PUBLIC_PRIVATE_PROTECTED (*pm), p2 = PUBLIC_PRIVATE_PROTECTED (*dm);
                  if (p1 < p2)
                    {
                      if (pedantic || !(co->pascal_dialect & B_D_PASCAL))
                        error ("%s method `%s', overrides %s method", descr[p2], IDENTIFIER_NAME (DECL_NAME (*dm)), descr[p1]);
                      else
                        warning ("%s method `%s', overrides %s method", descr[p2], IDENTIFIER_NAME (DECL_NAME (*dm)), descr[p1]);
                    }
                  if (PASCAL_VIRTUAL_METHOD (*pm))
                    {
                      check_routine_decl (DECL_LANG_PARMS (*dm), TREE_TYPE (TREE_TYPE (*dm)),
                        DECL_LANG_RESULT_VARIABLE (*dm), 0, 1, PASCAL_STRUCTOR_METHOD (*dm),
                        *pm, DECL_SOURCE_FILE (*dm), DECL_SOURCE_LINE (*dm));
                      if (PASCAL_TYPE_IOCRITICAL (TREE_TYPE (*dm))
                          && !PASCAL_TYPE_IOCRITICAL (TREE_TYPE (*pm)))
                        warning ("iocritical virtual method overrides non-iocritical one");
                    }
                  if (PASCAL_VIRTUAL_METHOD (*pm) && !PASCAL_VIRTUAL_METHOD (*dm))
                    {
                      /* Overridden virtual methods must be virtual. */
                      warning ("method `%s' is virtual", IDENTIFIER_NAME (DECL_NAME (*dm)));
                      PASCAL_VIRTUAL_METHOD (*dm) = 1;
                    }
                  /* If a virtual method overrides a non-virtual one, we must
                     not put the virtual one in the sequence of the parent
                     methods, so the VMT ordering is preserved (fjf702.pas). */
                  if (!PASCAL_VIRTUAL_METHOD (*pm) && PASCAL_VIRTUAL_METHOD (*dm))
                    {
                      if (PEDANTIC (B_D_PASCAL) || co->pascal_dialect == 0)
                        warning ("virtual method overrides non-virtual one");
                      *pm = TREE_CHAIN (*pm);
                      continue;
                    }
                  else
                    {
                      /* Replace the parent's method with the child's one */
                      t = TREE_CHAIN (*pm);
                      *pm = *dm;
                      *dm = TREE_CHAIN (*dm);
                      TREE_CHAIN (*pm) = t;
                    }
                }
            }
          pm = &TREE_CHAIN (*pm);
        }
      fields = chainon (copy_list (TYPE_FIELDS (parent)), fields);
      methods = chainon (parent_methods, methods);
      vmt_field = fields;  /* i.e., first field */
      assert (DECL_NAME (vmt_field) == vmt_id);
      assert (TREE_CODE (TREE_TYPE (vmt_field)) == POINTER_TYPE);
    }
  else
    {
      vmt_field = build_decl (FIELD_DECL, vmt_id, build_pointer_type (void_type_node));
      fields = chainon (vmt_field, fields);
    }

  TYPE_ALIGN (type) = 0;  /* to avoid blowing up the size unnecessarily */
  type = finish_struct (type, fields, 0);
  TYPE_MODE (type) = BLKmode;  /* be consistent with what was set in parse.y */
  TYPE_ALIGN (type) = BIGGEST_ALIGNMENT;
  TYPE_LANG_CODE (type) = abstract ? PASCAL_LANG_ABSTRACT_OBJECT : PASCAL_LANG_OBJECT;
  TYPE_LANG_VMT_FIELD (type) = vmt_field;
  TYPE_LANG_BASE (type) = parent;
  TYPE_METHODS (type) = methods;

  init = NULL_TREE;
  for (f = fields; f; f = TREE_CHAIN (f))
    if ((ti = TYPE_GET_INITIALIZER (TREE_TYPE (f))))
      {
        assert (TREE_CODE (ti) == TREE_LIST && !TREE_PURPOSE (ti));
        init = tree_cons (build_tree_list (DECL_NAME (f), NULL_TREE), TREE_VALUE (ti), init);
      }
  if (init)
    TYPE_LANG_INITIAL (type) = build_tree_list (NULL_TREE, init);

  /* Check whether the formal parameters and result variables of the methods
     conflict with fields of the object. Do not check inherited methods. */
  for (field = methods; field; field = TREE_CHAIN (field))
    if (DECL_CONTEXT (field) == type)
      {
        const char *name = IDENTIFIER_NAME (DECL_NAME (field));
        for (parm = DECL_LANG_PARMS (field); parm; parm = TREE_CHAIN (parm))
          if (find_field (type, DECL_NAME (parm), 2))
            error ("formal parameter `%s' of method `%s' conflicts with field or method",
                   IDENTIFIER_NAME (DECL_NAME (parm)), name);
        if (DECL_LANG_RESULT_VARIABLE (field) && find_field (type, DECL_LANG_RESULT_VARIABLE (field), 2))
          error ("result variable `%s' of method `%s' conflicts with field or method",
                 IDENTIFIER_NAME (DECL_LANG_RESULT_VARIABLE (field)), name);
      }

  /* Create a record type for the VMT. The fields will contain pointers to all virtual methods. */
  vmt_entry = copy_list (gpc_fields_PObjectType);
  for (field = methods; field; field = TREE_CHAIN (field))
    if (PASCAL_VIRTUAL_METHOD (field))
      {
        /* The real type of this pointer is not needed for type checking
           because it already is in the field of the object. Repeating it
           here would only cause confusion in GPI files if the method has
           a prediscriminated parameter. So use just ptr_type_node. */
        char *n = ACONCAT (("method_", IDENTIFIER_POINTER (DECL_NAME (field)), NULL));
        vmt_entry = chainon (vmt_entry, build_field (get_identifier (n), ptr_type_node));
      }
  vmt_type = finish_struct (start_struct (RECORD_TYPE), vmt_entry, 0);
  TYPE_READONLY (vmt_type) = 1;

  /* Build an initializer for the VMT record */
  size = size_in_bytes (type);
  field = build_pascal_unary_op (NEGATE_EXPR, size);
  vmt_entry = tree_cons (NULL_TREE, size, build_tree_list (NULL_TREE, field));
  if (!parent)
    field = null_pointer_node;
  else
    field = convert (gpc_type_PObjectType, build_unary_op (ADDR_EXPR, TYPE_LANG_VMT_VAR (parent), 0));
  vmt_entry = chainon (vmt_entry, build_tree_list (NULL_TREE, field));
  field = build_pascal_address_expression (build_string_constant (object_name, strlen (object_name), 0), 0);
  vmt_entry = chainon (vmt_entry, build_tree_list (NULL_TREE, field));

  /* Virtual methods */
  for (field = methods; field; field = TREE_CHAIN (field))
    {
      if (PASCAL_VIRTUAL_METHOD (field))
        {
          tree method;
          if (!PASCAL_ABSTRACT_METHOD (field))
            method = build_unary_op (ADDR_EXPR, field, 0);
          else
            {
              if (TYPE_LANG_CODE (type) != PASCAL_LANG_ABSTRACT_OBJECT)
                {
                  TYPE_LANG_CODE (type) = PASCAL_LANG_ABSTRACT_OBJECT;
                  if (co->warn_implicit_abstract)
                    {
                      warning ("object type `%s' is implicitly abstract because", object_name);
                      warning (" it contains abstract method `%s'", IDENTIFIER_NAME (DECL_NAME (field)));
                    }
                }
              method = convert (ptr_type_node, integer_zero_node);
            }
          vmt_entry = chainon (vmt_entry, build_tree_list (NULL_TREE, method));
          has_virtual_method = 1;
        }
      if (PASCAL_CONSTRUCTOR_METHOD (field))
        has_constructor = 1;
    }

  if (TYPE_LANG_CODE (type) == PASCAL_LANG_ABSTRACT_OBJECT)
    {
      /* Set `Size' and `NegatedSize' to 0 for abstract objects */
      TREE_VALUE (vmt_entry) = TREE_VALUE (TREE_CHAIN (vmt_entry)) = size_zero_node;
      if (co->warn_inherited_abstract && parent && TYPE_LANG_CODE (parent) != PASCAL_LANG_ABSTRACT_OBJECT)
        warning ("abstract object type `%s' inherits from non-abstract type `%s'",
                 object_name, IDENTIFIER_NAME (DECL_NAME (TYPE_NAME (parent))));
    }
  else if (has_virtual_method && !has_constructor && !(co->pascal_dialect & MAC_PASCAL))
    warning ("object type has virtual method, but no constructor");

  /* Now create a global var declaration (also for abstract types,
     for `is', `as' and explicit parent type access via VMT).
     VQ_IMPLICIT suppresses `unused variable' warning and prevents it
     from being pushed as a regular declaration (which is unnecessary). */
  n = ACONCAT (("vmt_", IDENTIFIER_POINTER (DECL_NAME (TYPE_NAME (type))), NULL));
  TYPE_LANG_VMT_VAR (type) = declare_variable (get_identifier (n), vmt_type,
    build_tree_list (NULL_TREE, vmt_entry), VQ_IMPLICIT | VQ_CONST | (current_module->implementation ? VQ_STATIC : 0));

  /* Attach VMT_TYPE to the implicit VMT field of the object.
     (Until here it still has the inherited type or ^void type.)
     We also need this for abstract types because their methods
     may call virtual methods via the VMT. */
  TREE_TYPE (vmt_field) = build_pointer_type (vmt_type);

  for (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
    {
      TYPE_MODE (t) = TYPE_MODE (type);
      TYPE_LANG_CODE (t) = TYPE_LANG_CODE (type);
      TYPE_LANG_VMT_FIELD (t) = TYPE_LANG_VMT_FIELD (type);
      TYPE_LANG_VMT_VAR (t) = TYPE_LANG_VMT_VAR (type);
      TYPE_LANG_BASE (t) = TYPE_LANG_BASE (type);
      TYPE_METHODS (t) = TYPE_METHODS (type);
    }

  return type;
}

/* Build an `is' or `as' expression */
tree
build_is_as (left, right, op)
     tree left, right;
     int op;
{
  const char *opname = (op == p_is) ? "is" : "as";
  if (!PASCAL_TYPE_OBJECT (right))
    error ("right operand of `%s' must be an object type", opname);
  else if (!PASCAL_TYPE_OBJECT (TREE_TYPE (left)))
    error ("left operand of `%s' must be an object", opname);
  else
    {
      tree t = right, tl = TYPE_MAIN_VARIANT (TREE_TYPE (left));
      tree l = left;
      while (TREE_CODE (l) == NOP_EXPR
             || TREE_CODE (l) == CONVERT_EXPR
             || TREE_CODE (l) == NON_LVALUE_EXPR)
        l = TREE_OPERAND (l, 0);
      while (t && TYPE_MAIN_VARIANT (t) != tl)
        t = TYPE_LANG_BASE (t);
      if (!t)
        {
          error ("right operand of `%s' must be a derived type", opname);
          error (" of the declared type of the left operand");
        }
      else if (TYPE_MAIN_VARIANT (right) == tl)
        {
          if (op == p_is)
            {
              warning ("`is' always yields `True' if the right operand");
              warning (" is the declared type of the left operand.");
              if (TREE_SIDE_EFFECTS (left))
                warning (" Operand with side-effects is not evaluated.");
              return boolean_true_node;
            }
          else
            {
              warning ("`as' has no effect if the right operand is");
              warning (" the declared type of the left operand");
              return left;
            }
        }
      /* Variables, value parameters and components are not polymorphic.
         (Reference parameters are INDIRECT_REF.) */
      else if (TREE_CODE (l) == VAR_DECL
               || TREE_CODE (l) == PARM_DECL
               || TREE_CODE (l) == COMPONENT_REF
               || TREE_CODE (l) == ARRAY_REF)
        {
          if (op == p_is)
            {
              warning ("`is' always yields `False' if the left operand is not");
              warning (" polymorphic and the right operand is not its type");
              if (TREE_SIDE_EFFECTS (left))
                warning (" Operand with side-effects is not evaluated.");
              return boolean_false_node;
            }
          else
            {
              error ("`as' can never succeed if the left operand is not");
              error (" polymorphic and the right operand is not its type");
            }
        }
      else
        {
          tree vmt_left = get_vmt_field (left);
          tree vmt_right = build_pascal_unary_op (ADDR_EXPR, TYPE_LANG_VMT_VAR (right));
          if (!EM (vmt_left) && !EM (vmt_right))
            {
              tree p_right;
              tree res = build_predef_call (p_is, tree_cons (NULL_TREE, vmt_left,
                           build_tree_list (NULL_TREE, vmt_right)));
              if (op == p_is)
                return res;

              /* (((Left is Right) ? : ObjectTypeAsError), ^Right (@Left))^
                 Note: Moving the `^' inside the COMPOUND_EXPR fails because
                 a later build_component_ref for a method call would move the
                 component ref into the COMPOUND_EXPR's operand, and
                 CALL_METHOD doesn't recognize the (still existing) COMPOUND_EXPR
                 (maybe CALL_METHOD should be fixed, but it works this way).
                 The `((Left is Right) ? : ObjectTypeAsError)' part is not done
                 within the RTS so the compiler can optimize a construction like
                 `if foo is bar then something (foo as bar)'. */
              p_right = build_pointer_type (right);
              return build_pascal_pointer_reference (
                       build (COMPOUND_EXPR, p_right,
                         build (COND_EXPR, void_type_node, res,
                                convert (void_type_node, integer_zero_node),
                                build_predef_call (p_as, NULL_TREE)),
                         convert (p_right, build_pascal_unary_op (ADDR_EXPR, left))));
            }
        }
    }
  return error_mark_node;
}
