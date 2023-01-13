
#include "php.h"
#include "php_yaep.h"
#include "yaep_arginfo.h"
#include "zend_exceptions.h"
#include "exceptions.h"
#include "term.h"

zend_class_entry *a_term, *a_pid_term, *a_ref_term, *a_port_term, *a_fun_term, *a_atom_term, *a_binary_term, *a_bit_binary_term, *a_int_term, *a_float_term, *a_str_term, *a_tuple_term, *a_list_term, *a_map_term;

zend_object *yaep_term_new(zend_class_entry *ce)
{
    yaep_term_t *term = zend_object_alloc(sizeof(yaep_term_t), ce);
    zend_object_std_init(&term->std, ce);
    term->std.handlers = &yaep_term_object_handlers;
    term->val.ht = NULL;

    return &term->std;
}

void yaep_term_free_obj(zend_object *object)
{
    yaep_term_t *term = Z_STRUCT_OBJ_P(object, yaep_term_t);

    switch (term->type)
    {
    case ERL_LIST_EXT:
    case ERL_NIL_EXT:
    case ERL_MAP_EXT:
    case ERL_SMALL_TUPLE_EXT:
    case ERL_LARGE_TUPLE_EXT:
        zend_hash_destroy(term->val.ht);
        break;

    default:
        break;
    }

    (std_object_handlers.free_obj)(object);
}

zend_object *yaep_term_new_ht(zend_class_entry *ce, HashTable *val, int size, int type)
{
    yaep_term_t *term = Z_STRUCT_OBJ_P(yaep_term_new(ce), yaep_term_t);
    term->type = type;
    term->size = size;
    term->val.ht = val;

    return &term->std;
}

zend_object *yaep_term_new_s(zend_class_entry *ce, char *val, int size, int type)
{
    yaep_term_t *term = Z_STRUCT_OBJ_P(yaep_term_new(ce), yaep_term_t);
    term->type = type;
    term->size = size;
    term->val.ht = NULL;
    term->val.s = val;

    return &term->std;
}

zend_object *yaep_term_new_i(zend_class_entry *ce, long val, int size, int type)
{
    yaep_term_t *term = Z_STRUCT_OBJ_P(yaep_term_new(ce), yaep_term_t);
    term->type = type;
    term->size = size;
    term->val.ht = NULL;
    term->val.i = val;

    return &term->std;
}

zend_object *yaep_term_new_f(zend_class_entry *ce, double val, int size, int type)
{
    yaep_term_t *term = Z_STRUCT_OBJ_P(yaep_term_new(ce), yaep_term_t);
    term->type = type;
    term->size = size;
    term->val.ht = NULL;
    term->val.f = val;

    return &term->std;
}

zend_object *_yaep_do_decode_term(erlang_msg *in_msg, ei_x_buff *in_buf)
{
    zend_object *out_obj;

    HashTable *htable;
    zend_object *tmp_obj;
    zval tmp_zv;

    int type;
    int size;
    char *buff;
    long len;
    long long_value;
    double double_value;
    int i;

    ei_get_type(in_buf->buff, &in_buf->index, &type, &size);
    switch (type)
    {
    case ERL_ATOM_EXT:
        // Decode using either ei_decode_atom(), ei_decode_atom_as(), or ei_decode_boolean().
        buff = emalloc(size + 1);
        ei_decode_atom(in_buf->buff, &in_buf->index, buff);
        buff[size] = '\0';
        out_obj = yaep_term_new_s(a_atom_term, (char *)buff, size, type);
        break;

    case ERL_BINARY_EXT:
        // Decode using either ei_decode_binary(), ei_decode_bitstring(), or ei_decode_iodata().
        buff = emalloc(size);
        ei_decode_binary(in_buf->buff, &in_buf->index, buff, &len);
        out_obj = yaep_term_new_s(a_binary_term, (char *)buff, size, type);
        break;

    case ERL_BIT_BINARY_EXT:
        // Decode using ei_decode_bitstring().
        zend_throw_exception(e_term_dec, /* todo */ "Bit binaries are not supported yet", 0);
        return NULL;

    case ERL_FLOAT_EXT:
        // Decode using ei_decode_double().
        ei_decode_double(in_buf->buff, &in_buf->index, &double_value);
        out_obj = yaep_term_new_f(a_float_term, double_value, 0, type);
        break;

    case ERL_NEW_FUN_EXT:
    case ERL_FUN_EXT:
    case ERL_EXPORT_EXT:
        // Decode using ei_decode_fun().
        buff = emalloc(sizeof(erlang_fun));
        ei_decode_fun(in_buf->buff, &in_buf->index, (erlang_fun *)buff);
        out_obj = yaep_term_new_s(a_fun_term, (char *)buff, 0, type);
        break;

    case ERL_SMALL_INTEGER_EXT:
    case ERL_INTEGER_EXT:
    case ERL_SMALL_BIG_EXT:
    case ERL_LARGE_BIG_EXT:
        // Decode using either ei_decode_char(), ei_decode_long(), ei_decode_longlong(), ei_decode_ulong(), ei_decode_ulonglong(), or ei_decode_bignum().
        ei_decode_long(in_buf->buff, &in_buf->index, &long_value);
        out_obj = yaep_term_new_i(a_int_term, long_value, 0, type);
        break;

    case ERL_LIST_EXT:
    case ERL_NIL_EXT:
        // Decode using either ei_decode_list_header(), or ei_decode_iodata().
        htable = zend_new_array(0);
        ei_decode_list_header(in_buf->buff, &in_buf->index, &size);

        for (i = 0; i < size; i++)
        {
            tmp_obj = _yaep_do_decode_term(in_msg, in_buf);
            ZVAL_OBJ(&tmp_zv, tmp_obj);
            if (!zend_hash_next_index_insert_new(htable, &tmp_zv))
            {
                zend_throw_exception(e_term_dec, /* todo */ "Unable to decode list element", 0);
                return NULL;
            }
        }

        out_obj = yaep_term_new_ht(a_tuple_term, htable, 0, type);
        break;

    case ERL_STRING_EXT:
        // Decode using either ei_decode_string(), or ei_decode_iodata().
        buff = emalloc(size + 1);
        ei_decode_string(in_buf->buff, &in_buf->index, buff);
        buff[size] = '\0';
        out_obj = yaep_term_new_s(a_str_term, (char *)buff, size, type);
        break;

    case ERL_MAP_EXT:
        // Decode using ei_decode_map_header().
        htable = zend_new_array(0);
        ei_decode_map_header(in_buf->buff, &in_buf->index, &size);

        for (i = 0; i < 2 * size; i++)
        {
            tmp_obj = _yaep_do_decode_term(in_msg, in_buf);
            ZVAL_OBJ(&tmp_zv, tmp_obj);
            if (!zend_hash_next_index_insert_new(htable, &tmp_zv))
            {
                zend_throw_exception(e_term_dec, /* todo */ "Unable to decode map element", 0);
                return NULL;
            }
        }

        out_obj = yaep_term_new_ht(a_map_term, htable, 0, type);
        break;

    case ERL_PID_EXT:
        // Decode using ei_decode_pid().
        buff = emalloc(sizeof(erlang_pid));
        ei_decode_pid(in_buf->buff, &in_buf->index, (erlang_pid *)buff);
        out_obj = yaep_term_new_s(a_pid_term, (char *)buff, 0, type);
        break;

    case ERL_PORT_EXT:
        // Decode using ei_decode_port().
        buff = emalloc(sizeof(erlang_port));
        ei_decode_port(in_buf->buff, &in_buf->index, (erlang_port *)buff);
        out_obj = yaep_term_new_s(a_port_term, (char *)buff, 0, type);
        break;

    case ERL_NEW_REFERENCE_EXT:
        // Decode using ei_decode_ref().
        buff = emalloc(sizeof(erlang_ref));
        ei_decode_ref(in_buf->buff, &in_buf->index, (erlang_ref *)buff);
        out_obj = yaep_term_new_s(a_ref_term, (char *)buff, 0, type);
        break;

    case ERL_SMALL_TUPLE_EXT:
    case ERL_LARGE_TUPLE_EXT:
        // Decode using ei_decode_tuple_header().
        htable = zend_new_array(0);
        ei_decode_tuple_header(in_buf->buff, &in_buf->index, &size);

        for (i = 0; i < size; i++)
        {
            tmp_obj = _yaep_do_decode_term(in_msg, in_buf);
            ZVAL_OBJ(&tmp_zv, tmp_obj);
            if (!zend_hash_next_index_insert_new(htable, &tmp_zv))
            {
                zend_throw_exception(e_term_dec, /* todo */ "Unable to decode tuple element", 0);
                return NULL;
            }
        }

        out_obj = yaep_term_new_ht(a_tuple_term, htable, 0, type);
        break;

    default:
        zend_throw_exception(e_term_dec, /* todo */ "Unknown type", 0);
        return NULL;
    }

    return out_obj;
}

zend_object *_yaep_do_decode_message(erlang_msg *in_msg, ei_x_buff *in_buf)
{
    int version;

    in_buf->index = 0;
    ei_decode_version(in_buf->buff, &in_buf->index, &version);

    return _yaep_do_decode_term(in_msg, in_buf);
}

void yaep_register_terms()
{
    a_term = register_class_Yaep_Term_AbstractTerm();

    a_atom_term = register_class_Yaep_Term_AtomTerm(a_term);
    a_atom_term->create_object = yaep_term_new;

    a_binary_term = register_class_Yaep_Term_BinaryTerm(a_term);
    a_binary_term->create_object = yaep_term_new;

    a_bit_binary_term = register_class_Yaep_Term_BitBinaryTerm(a_term);
    a_bit_binary_term->create_object = yaep_term_new;

    a_int_term = register_class_Yaep_Term_IntegerTerm(a_term);
    a_int_term->create_object = yaep_term_new;

    a_float_term = register_class_Yaep_Term_FloatTerm(a_term);
    a_float_term->create_object = yaep_term_new;

    a_str_term = register_class_Yaep_Term_StringTerm(a_term);
    a_str_term->create_object = yaep_term_new;

    a_tuple_term = register_class_Yaep_Term_TupleTerm(a_term);
    a_tuple_term->create_object = yaep_term_new;

    a_list_term = register_class_Yaep_Term_ListTerm(a_term);
    a_list_term->create_object = yaep_term_new;

    a_map_term = register_class_Yaep_Term_MapTerm(a_term);
    a_map_term->create_object = yaep_term_new;

    a_pid_term = register_class_Yaep_Term_PidTerm(a_term);
    a_pid_term->create_object = yaep_term_new;

    a_port_term = register_class_Yaep_Term_PortTerm(a_term);
    a_port_term->create_object = yaep_term_new;

    a_ref_term = register_class_Yaep_Term_RefTerm(a_term);
    a_ref_term->create_object = yaep_term_new;

    a_fun_term = register_class_Yaep_Term_FunctionTerm(a_term);
    a_fun_term->create_object = yaep_term_new;

    memcpy(&yaep_term_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    yaep_term_object_handlers.free_obj = yaep_term_free_obj;
    yaep_term_object_handlers.offset = XtOffsetOf(yaep_term_t, std);
}

PHP_METHOD(Yaep_Term_AtomTerm, __construct)
{
    char *val;
    long unsigned val_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(val, val_len)
    ZEND_PARSE_PARAMETERS_END();

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_ATOM_EXT;
    term->size = val_len;
    term->val.ht = NULL;
    term->val.s = val;
}
PHP_METHOD(Yaep_Term_AtomTerm, toString)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    RETURN_STRING(term->val.s);
}

PHP_METHOD(Yaep_Term_BinaryTerm, __construct)
{
    char *val;
    long unsigned val_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(val, val_len)
    ZEND_PARSE_PARAMETERS_END();

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_BINARY_EXT;
    term->size = val_len;
    term->val.ht = NULL;
    term->val.s = val;
}
PHP_METHOD(Yaep_Term_BinaryTerm, toString)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    RETURN_STRING(term->val.s);
}
PHP_METHOD(Yaep_Term_BinaryTerm, getSize)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    RETURN_LONG(term->size);
}

PHP_METHOD(Yaep_Term_StringTerm, __construct)
{
    char *val;
    long unsigned val_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_STRING(val, val_len)
    ZEND_PARSE_PARAMETERS_END();

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_STRING_EXT;
    term->size = val_len;
    term->val.ht = NULL;
    term->val.s = val;
}
PHP_METHOD(Yaep_Term_StringTerm, getValue)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    RETURN_STRING(term->val.s);
}

PHP_METHOD(Yaep_Term_IntegerTerm, __construct)
{
    long val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(val)
    ZEND_PARSE_PARAMETERS_END();

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_INTEGER_EXT;
    term->size = sizeof(long);
    term->val.ht = NULL;
    term->val.i = val;
}
PHP_METHOD(Yaep_Term_IntegerTerm, getValue)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    RETURN_LONG(term->val.i);
}

PHP_METHOD(Yaep_Term_FloatTerm, __construct)
{
    double val;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_DOUBLE(val)
    ZEND_PARSE_PARAMETERS_END();

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_FLOAT_EXT;
    term->size = 0;
    term->val.ht = NULL;
    term->val.f = val;
}
PHP_METHOD(Yaep_Term_FloatTerm, getValue)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    RETURN_DOUBLE(term->val.f);
}

PHP_METHOD(Yaep_Term_TupleTerm, __construct)
{
    zval *items;
    uint32_t num_items;
    HashTable *named_items;
    zval tmp;

    ZEND_PARSE_PARAMETERS_START(0, -1)
    Z_PARAM_VARIADIC_WITH_NAMED(items, num_items, named_items)
    ZEND_PARSE_PARAMETERS_END();

    HashTable *ht = zend_new_array(num_items);
    for (int i = 0; i < num_items; i++)
    {
        if (Z_TYPE_P(&items[i]) == IS_NULL)
        {
            return;
        }

        ZVAL_OBJ_COPY(&tmp, Z_OBJ_P(&items[i]));
        zend_hash_next_index_insert_new(ht, &tmp);
    }

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_SMALL_TUPLE_EXT;
    term->size = 0;
    term->val.ht = ht;
}
PHP_METHOD(Yaep_Term_TupleTerm, getArity)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    HashTable *htable = term->val.ht;
    RETURN_LONG(zend_array_count(htable));
}
PHP_METHOD(Yaep_Term_TupleTerm, toArray)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    HashTable *htable = term->val.ht;
    zval tmp;

    HashTable *htable_copy = zend_new_array(htable->nNumOfElements);
    for (int i = 0; i < htable->nNumOfElements; i++)
    {
        ZVAL_OBJ_COPY(&tmp, Z_OBJ(*zend_hash_index_find(htable, i)));
        zend_hash_next_index_insert_new(htable_copy, &tmp);
    }

    RETURN_ARR(htable_copy);
}

PHP_METHOD(Yaep_Term_ListTerm, __construct)
{
    zval *items;
    uint32_t num_items;
    HashTable *named_items;
    zval tmp;

    ZEND_PARSE_PARAMETERS_START(0, -1)
    Z_PARAM_VARIADIC_WITH_NAMED(items, num_items, named_items)
    ZEND_PARSE_PARAMETERS_END();

    HashTable *ht = zend_new_array(num_items);
    for (int i = 0; i < num_items; i++)
    {
        if (Z_TYPE_P(&items[i]) == IS_NULL)
        {
            return;
        }

        ZVAL_OBJ_COPY(&tmp, Z_OBJ_P(&items[i]));
        zend_hash_next_index_insert_new(ht, &tmp);
    }

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_LIST_EXT;
    term->size = 0;
    term->val.ht = ht;
}
PHP_METHOD(Yaep_Term_ListTerm, getSize)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    HashTable *htable = term->val.ht;
    RETURN_LONG(zend_array_count(htable));
}
PHP_METHOD(Yaep_Term_ListTerm, toArray)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    HashTable *htable = term->val.ht;
    zval tmp;

    HashTable *htable_copy = zend_new_array(htable->nNumOfElements);
    for (int i = 0; i < htable->nNumOfElements; i++)
    {
        ZVAL_OBJ_COPY(&tmp, Z_OBJ(*zend_hash_index_find(htable, i)));
        zend_hash_next_index_insert_new(htable_copy, &tmp);
    }

    RETURN_ARR(htable_copy);
}

PHP_METHOD(Yaep_Term_MapTerm, __construct)
{
    zval *items;
    uint32_t num_items;
    HashTable *named_items;
    zval tmp;

    ZEND_PARSE_PARAMETERS_START(0, -1)
    Z_PARAM_VARIADIC_WITH_NAMED(items, num_items, named_items)
    ZEND_PARSE_PARAMETERS_END();

    yaep_term_t *tmp_term;

    HashTable *ht = zend_new_array(num_items);
    for (int i = 0; i < num_items; i++)
    {
        if (Z_TYPE_P(&items[i]) == IS_NULL)
        {
            return;
        }

        // todo: validate each key

        // is key
        if (0 == i % 2)
        {
            tmp_term = Z_STRUCT_ZVAL_OBJ_P(&items[i], yaep_term_t);

            switch (tmp_term->type)
            {
            case ERL_ATOM_EXT:
            case ERL_BINARY_EXT:
            case ERL_FLOAT_EXT:
            case ERL_SMALL_INTEGER_EXT:
            case ERL_INTEGER_EXT:
            case ERL_SMALL_BIG_EXT:
            case ERL_LARGE_BIG_EXT:
            case ERL_STRING_EXT:
            case ERL_NEW_REFERENCE_EXT:
                /* it's ok */
                break;

            default:
                zend_throw_exception(e_term_enc, /* todo */ "Map keys must be integers, float numbers, strings, atoms, refrences or binaries", 0);
                break;
            }
        }

        ZVAL_OBJ_COPY(&tmp, Z_OBJ_P(&items[i]));
        zend_hash_next_index_insert_new(ht, &tmp);
    }

    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    term->type = ERL_MAP_EXT;
    term->size = 0;
    term->val.ht = ht;
}
PHP_METHOD(Yaep_Term_MapTerm, toArray)
{
    yaep_term_t *term = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_term_t);
    HashTable *htable = term->val.ht;
    zval tmp;

    HashTable *htable_copy = zend_new_array(htable->nNumOfElements);
    for (int i = 0; i < htable->nNumOfElements; i++)
    {
        ZVAL_OBJ_COPY(&tmp, Z_OBJ(*zend_hash_index_find(htable, i)));
        zend_hash_next_index_insert_new(htable_copy, &tmp);
    }

    RETURN_ARR(htable_copy);
}
