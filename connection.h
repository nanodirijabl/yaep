
#ifndef YAEP_CONN_H
#define YAEP_CONN_H

#include "php.h"
#include "php_yaep.h"
#include "exceptions.h"
#include "term.h"

typedef struct _yaep_conn_p
{
    ei_cnode *ec;
    int fd;
} yaep_conn_p;

typedef struct _yaep_conn_entry
{
    char *name;
    yaep_conn_p *conn;
    struct _yaep_conn_entry *next;
} yaep_conn_entry;

typedef struct _yaep_node_p
{
    ei_cnode *ec;
    char *name;
    char *cookie;
    yaep_conn_entry *connections;
} yaep_node_p;

void yaep_conn_purge_all(yaep_conn_entry *head);

yaep_conn_p *yaep_conn_init(yaep_node_p *node_p, char *node, long unsigned node_len, long unsigned timeout);

yaep_node_p *yaep_mgr_node_init(char *name, long unsigned name_len, char *cookie, long unsigned cookie_len, short creation);

yaep_conn_p *yaep_mgr_connect(yaep_node_p *this_node_p, char *node, long unsigned node_len, long unsigned timeout);

void yaep_mgr_free();

extern zend_class_entry *a_conn;

static zend_object_handlers yaep_conn_object_handlers;

typedef struct _yaep_conn_t
{
    yaep_conn_p *conn;
    erlang_pid *pid;
    zend_object std;
} yaep_conn_t;

zend_object *yaep_conn_new(zend_class_entry *ce);

int encode_into_buffer(ei_x_buff *buf, yaep_term_t *t_msg);

static zend_object_handlers yaep_node_object_handlers;

typedef struct _yaep_node_t
{
    yaep_node_p *node;
    zend_object std;
} yaep_node_t;

zend_object *yaep_node_new(zend_class_entry *ce);

void yaep_register_conn();

#endif /* YAEP_CONN_H */
