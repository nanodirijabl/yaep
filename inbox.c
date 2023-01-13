
#include "inbox.h"
#include "php.h"
#include <string.h>

int yaep_pid_match(erlang_pid *pid1, erlang_pid *pid2)
{
    return pid1->num == pid2->num &&
           pid1->serial == pid2->serial &&
           pid1->creation == pid2->creation &&
           0 == strcmp(pid1->node, pid2->node);
}

void yaep_inbox_purge(yaep_inbox_entry *head, erlang_pid *pid)
{
    yaep_inbox_entry *cur = head;
    yaep_inbox_entry *next = NULL;

    while (NULL != cur)
    {
        next = cur->next;

        if (NULL == pid ||yaep_pid_match(&(cur->msg->to), pid))
        {
            cur->next = NULL;
            ei_x_free(cur->buf);
            pefree(cur->msg, 1);
            pefree(cur, 1);
        }

        cur = next;
    }
}

yaep_inbox_entry *yaep_inbox_pop(yaep_inbox_entry *head, erlang_pid *pid)
{
    yaep_inbox_entry *cur = head;
    yaep_inbox_entry *prev = NULL;

    while (NULL != cur)
    {
        if (yaep_pid_match(&(cur->msg->to), pid))
        {
            prev->next = cur->next;
            cur->next = NULL;
            return cur;
        }

        prev = cur;
        cur = cur->next;
    }

    return NULL;
}

void yaep_inbox_push(yaep_inbox_entry *head, erlang_msg *msg, ei_x_buff *buf)
{
    yaep_inbox_entry *entry = pemalloc(sizeof(yaep_inbox_entry), 1);

    entry->msg = pemalloc(sizeof(msg), 1);
    memcpy(entry->msg, msg, sizeof(msg));

    entry->buf = buf;
    entry->next = NULL;

    if (NULL == head)
    {
        head = entry;
        return;
    }

    head->next = entry;
}
