
#ifndef YAEP_INBOX_H
#define YAEP_INBOX_H

#include "ei.h"

typedef struct _yaep_inbox_entry
{
    erlang_msg *msg;
    ei_x_buff *buf;
    struct _yaep_inbox_entry *next;
} yaep_inbox_entry;

extern yaep_inbox_entry *global_inbox;

int yaep_pid_match(erlang_pid *pid1, erlang_pid *pid2);

void yaep_inbox_purge(yaep_inbox_entry *head, erlang_pid *pid);

yaep_inbox_entry *yaep_inbox_pop(yaep_inbox_entry *head, erlang_pid *pid);

void yaep_inbox_push(yaep_inbox_entry *head, erlang_msg *msg, ei_x_buff *buf);

#endif /* YAEP_INBOX_H */
