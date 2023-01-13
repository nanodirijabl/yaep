
#ifndef YAEP_DEBUG_H
#define YAEP_DEBUG_H

#include "php.h"

#define PRINT_TERM_P(tag, term) php_printf("[%s] type: %c size: %ld ht ref: %ld, s ref: %ld\n", tag, term->type, term->size, term->val.ht, term->val.s)
#define PRINT_EIBUF_P(tag, buf) php_printf("[%s] buffsz: %d index: %d buff ref: %ld\n", tag, buf->buffsz, buf->index, buf->buff)
#define PRINT_EIBUF(tag, buf) php_printf("[%s] buffsz: %d index: %d buff ref: %ld\n", tag, buf.buffsz, buf.index, buf.buff)
#define PRINT_EIPID_P(pid) php_printf("PID[%d:%d:%d @ %s]\n", pid->num, pid->serial, pid->creation, pid->node)
#define PRINT_EIPID(pid) php_printf("PID[%d:%d:%d @ %s]\n", pid.num, pid.serial, pid.creation, pid.node)

#endif /* YAEP_DEBUG_H */
