
#ifndef YAEP_EXCEPTIONS_H
#define YAEP_EXCEPTIONS_H

#include "php.h"
#include "php_yaep.h"

extern zend_class_entry *e_node_init, *e_node_conn, *e_node_cpid, *e_msg_rcv, *e_msg_send, *e_term_dec, *e_term_enc;

void yaep_register_exceptions();

#endif /* YAEP_EXCEPTIONS_H */
