
#include "php.h"
#include "node.h"
#include "connection.h"
#include "ei.h"
#include <string.h>

void yaep_node_purge_all(yaep_node_entry *head)
{
    yaep_node_entry *cur = head;
    yaep_node_entry *next = NULL;

    while (NULL != cur)
    {
        next = cur->next;

        yaep_conn_purge_all(cur->node->connections);
        pefree(cur->node->ec, 1);
        pefree(cur->node, 1);
        cur->next = NULL;
        pefree(cur, 1);

        cur = next;
    }
}

yaep_node_entry *_yaep_node_lookup(yaep_node_entry *head, char *name, long unsigned name_len)
{
    yaep_node_entry *cur = head;
    yaep_node_entry *next = NULL;

    while (NULL != cur)
    {
        if (0 == strcmp(cur->name, name))
        {
            return cur;
        }

        cur = cur->next;
    }
}

void _yaep_node_prepend(yaep_node_entry *head, char *name, long unsigned name_len, yaep_node_p *node)
{
    yaep_node_entry *elem = pemalloc(sizeof(yaep_node_entry), 1);
    elem->next = NULL;
    elem->name = strdup(name);
    elem->node = node;

    if (NULL == head)
    {
        elem->next = NULL;
        head = elem;
    }
    else
    {
        elem->next = head;
        head = elem;
    }
}

yaep_node_p *yaep_node_init(yaep_node_entry *head, char *name, long unsigned name_len, char *cookie, long unsigned cookie_len, short creation)
{
    if (NULL != head)
    {
        yaep_node_entry *entry = _yaep_node_lookup(head, name, name_len);
        if (NULL != entry)
        {
            // todo: throw if not matching cookie
            return entry->node;
        }
    }

    yaep_node_p *node = pemalloc(sizeof(yaep_node_p), 1);
    node->ec = pemalloc(sizeof(ei_cnode), 1);
    node->name = name;
    node->cookie = cookie;
    node->connections = NULL;

    if (ei_connect_init(node->ec, name, cookie, creation) < 0)
    {
        pefree(node->ec, 1);
        pefree(node, 1);

        // todo: throw
        return NULL;
    }

    _yaep_node_prepend(head, name, name_len, node);

    return node;
}
