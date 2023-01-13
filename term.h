
#ifndef YAEP_TERM_H
#define YAEP_TERM_H

#include "php.h"
#include "php_yaep.h"
#include "exceptions.h"

extern zend_class_entry *a_term, *a_pid_term, *a_ref_term, *a_port_term, *a_fun_term, *a_atom_term, *a_binary_term, *a_bit_binary_term, *a_int_term, *a_float_term, *a_str_term, *a_tuple_term, *a_list_term, *a_map_term;

static zend_object_handlers yaep_term_object_handlers;

typedef struct _yaep_term_t
{
    int type;
    long unsigned size;
    union
    {
        long i;
        double f;
        char *s;
        HashTable *ht;
    } val;
    zend_object std;
} yaep_term_t;

zend_object *yaep_term_new(zend_class_entry *ce);

void yaep_term_free_obj(zend_object *object);

zend_object *yaep_term_new_ht(zend_class_entry *ce, HashTable *val, int size, int type);

zend_object *yaep_term_new_s(zend_class_entry *ce, char *val, int size, int type);

zend_object *yaep_term_new_i(zend_class_entry *ce, long val, int size, int type);

zend_object *yaep_term_new_f(zend_class_entry *ce, double val, int size, int type);

zend_object *_yaep_do_decode_term(erlang_msg *in_msg, ei_x_buff *in_buf);

zend_object *_yaep_do_decode_message(erlang_msg *in_msg, ei_x_buff *in_buf);

void yaep_register_terms();

#endif /* YAEP_TERM_H */
