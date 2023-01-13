
#ifndef YAEP_NODE_H
#define YAEP_NODE_H

#include "connection.h"

typedef struct _yaep_node_entry
{
    char *name;
    yaep_node_p *node;
    struct _yaep_node_entry *next;
} yaep_node_entry;

extern yaep_node_entry *global_nodes_list;

void yaep_node_purge_all(yaep_node_entry *head);

yaep_node_p *yaep_node_init(yaep_node_entry *head, char *name, long unsigned name_len, char *cookie, long unsigned cookie_len, short creation);

#endif /* YAEP_NODE_H */
