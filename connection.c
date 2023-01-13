
#include "php.h"
#include "php_yaep.h"
#include "yaep_arginfo.h"
#include "zend_exceptions.h"
#include "node.h"
#include "connection.h"
#include "inbox.h"

yaep_node_entry *global_nodes_list;

void yaep_conn_purge_all(yaep_conn_entry *head)
{
    yaep_conn_entry *cur = head;
    yaep_conn_entry *next = NULL;

    while (NULL != cur)
    {
        next = cur->next;

        ei_close_connection(cur->conn->fd);
        pefree(cur->conn, 1);
        cur->next = NULL;
        pefree(cur, 1);

        cur = next;
    }
}

yaep_conn_entry *_yaep_conn_lookup(yaep_conn_entry *head, char *node, long unsigned node_len)
{
    yaep_conn_entry *cur = head;
    yaep_conn_entry *next = NULL;

    while (NULL != cur)
    {
        if (0 == strcmp(cur->name, node))
        {
            return cur;
        }

        cur = cur->next;
    }
}

void _yaep_conn_prepend(yaep_conn_entry *head, char *name, long unsigned name_len, yaep_conn_p *conn)
{
    yaep_conn_entry *elem = pemalloc(sizeof(yaep_conn_entry), 1);
    elem->next = NULL;
    elem->conn = conn;
    elem->name = strdup(name);

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

yaep_conn_p *yaep_conn_init(yaep_node_p *node_p, char *node, long unsigned node_len, long unsigned timeout)
{
    if (NULL != node_p->connections)
    {
        yaep_conn_entry *entry = _yaep_conn_lookup(node_p->connections, node, node_len);
        if (NULL != entry)
        {
            return entry->conn;
        }
    }

    int fd = ei_connect_tmo(node_p->ec, node, timeout);
    // todo: respect return values on failure
    // EHOSTUNREACH
    //      The remote host node is unreachable.
    // ENOMEM
    //      No more memory is available.
    // EIO
    //      I/O error.
    if (0 > fd)
    {
        // todo: throw

        return NULL;
    }

    yaep_conn_p *conn = pemalloc(sizeof(yaep_conn_p), 1);
    conn->ec = node_p->ec;
    conn->fd = fd;

    _yaep_conn_prepend(node_p->connections, node, node_len, conn);

    return conn;
}

yaep_node_p *yaep_mgr_node_init(char *name, long unsigned name_len, char *cookie, long unsigned cookie_len, short creation)
{
    return yaep_node_init(global_nodes_list, name, name_len, cookie, cookie_len, creation);
}

yaep_conn_p *yaep_mgr_connect(yaep_node_p *this_node_p, char *node, long unsigned node_len, long unsigned timeout)
{
    return yaep_conn_init(this_node_p, node, node_len, timeout);
}

void yaep_mgr_free()
{
    yaep_inbox_purge(global_inbox, NULL);
    yaep_node_purge_all(global_nodes_list);
}

zend_class_entry *a_conn;

zend_object *yaep_conn_new(zend_class_entry *ce)
{
    yaep_conn_t *conn = zend_object_alloc(sizeof(yaep_conn_t), ce);
    zend_object_std_init(&conn->std, ce);
    conn->std.handlers = &yaep_conn_object_handlers;
    return &conn->std;
}

int encode_into_buffer(ei_x_buff *buf, yaep_term_t *t_msg)
{
    unsigned i;
    unsigned size;

    switch (t_msg->type)
    {
    case ERL_ATOM_EXT:
        if (0 > ei_x_encode_atom(buf, t_msg->val.s))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode atom", 0);
            return -1;
        }
        break;

    case ERL_BINARY_EXT:
        if (0 > ei_x_encode_binary(buf, t_msg->val.s, t_msg->size))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode binary", 0);
            return -1;
        }
        break;

    case ERL_BIT_BINARY_EXT:
        ei_x_free(buf);
        zend_throw_exception(e_term_enc, /* todo */ "Bit binaries are not supported yet", 0);
        return -1;

    case ERL_FLOAT_EXT:
        if (0 > ei_x_encode_double(buf, t_msg->val.f))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode double precision number", 0);
            return -1;
        }
        break;

    case ERL_NEW_FUN_EXT:
    case ERL_FUN_EXT:
    case ERL_EXPORT_EXT:
        if (0 > ei_x_encode_fun(buf, (erlang_fun *)t_msg->val.s))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode function", 0);
            return -1;
        }
        break;

    case ERL_SMALL_INTEGER_EXT:
    case ERL_INTEGER_EXT:
    case ERL_SMALL_BIG_EXT:
    case ERL_LARGE_BIG_EXT:
        if (0 > ei_x_encode_long(buf, t_msg->val.i))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode integer number", 0);
            return -1;
        }
        break;

    case ERL_LIST_EXT:
    case ERL_NIL_EXT:
        size = zend_array_count(t_msg->val.ht);
        if (0 > ei_x_encode_list_header(buf, size))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode list", 0);
            return -1;
        }

        if (0 < size)
        {
            for (i = 0; i < size; i++)
            {
                if (0 > encode_into_buffer(buf, Z_STRUCT_ZVAL_OBJ_P(zend_hash_index_find(t_msg->val.ht, i), yaep_term_t)))
                {
                    return -1;
                }
            }
            // final tail
            ei_x_encode_empty_list(buf);
        }
        break;

    case ERL_STRING_EXT:
        if (0 > ei_x_encode_string(buf, t_msg->val.s))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode string", 0);
            return -1;
        }
        break;

    case ERL_MAP_EXT:
        size = zend_array_count(t_msg->val.ht);
        if (0 > ei_x_encode_map_header(buf, size / 2))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode map", 0);
            return -1;
        }

        for (i = 0; i < size; i++)
        {
            if (0 > encode_into_buffer(buf, Z_STRUCT_ZVAL_OBJ_P(zend_hash_index_find(t_msg->val.ht, i), yaep_term_t)))
            {
                return -1;
            }
        }
        break;

    case ERL_PID_EXT:
        if (0 > ei_x_encode_pid(buf, (erlang_pid *)t_msg->val.s))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode PID", 0);
            return -1;
        }
        break;

    case ERL_PORT_EXT:
        if (0 > ei_x_encode_port(buf, (erlang_port *)t_msg->val.s))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode port", 0);
            return -1;
        }
        break;

    case ERL_NEW_REFERENCE_EXT:
        if (0 > ei_x_encode_ref(buf, (erlang_ref *)t_msg->val.s))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode reference", 0);
            return -1;
        }
        break;

    case ERL_SMALL_TUPLE_EXT:
    case ERL_LARGE_TUPLE_EXT:
        size = zend_array_count(t_msg->val.ht);
        if (0 > ei_x_encode_tuple_header(buf, size))
        {
            ei_x_free(buf);
            zend_throw_exception(e_term_enc, /* todo */ "Failed to encode tuple", 0);
            return -1;
        }

        for (i = 0; i < size; i++)
        {
            if (0 > encode_into_buffer(buf, Z_STRUCT_ZVAL_OBJ_P(zend_hash_index_find(t_msg->val.ht, i), yaep_term_t)))
            {
                return -1;
            }
        }
        break;

    default:
        zend_throw_exception(e_term_enc, /* todo */ "Unknown type", t_msg->type);
        return -1;
    }

    return 1;
}

PHP_METHOD(Yaep_Connection, getPid)
{
    yaep_conn_t *conn = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_conn_t);
    zend_object *obj = yaep_term_new_s(a_pid_term, (char *)conn->pid, 0, ERL_PID_EXT);
    RETURN_OBJ(obj);
}
PHP_METHOD(Yaep_Connection, receive)
{
    long unsigned timeout;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(timeout)
    ZEND_PARSE_PARAMETERS_END();

    ei_x_buff buf;
    ei_x_new_with_version(&buf);

    erlang_msg msg;
    yaep_conn_t *conn = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_conn_t);
    zend_object *obj;
    int erl_recv;
    struct timeval tv_recv_start;
    long unsigned recv_start;

    gettimeofday(&tv_recv_start, NULL);
    recv_start = tv_recv_start.tv_sec * 1000 + tv_recv_start.tv_usec / 1000;

    struct timeval tv_recv_next;

    long unsigned tmo_shift;

    yaep_inbox_entry *entry;

    // use messages buffer and filter by this connections' receiver pid
    // read buffer for messages for self, go further only if its empty
    if (NULL != (entry = yaep_inbox_pop(global_inbox, conn->pid)))
    {

        // accept message
        if (NULL == (obj = _yaep_do_decode_message(entry->msg, entry->buf)))
        {
            RETURN_NULL();
        }
        else
        {
            RETURN_OBJ(obj);
        }

        pefree(entry->msg, 1);
        pefree(entry, 1);
        ei_x_free(&buf);
        return;
    }

    for (;;)
    {
        // update "timeout" monotonic shift due to inbox buffer lookup
        // if "timeout" is not positive (mind unsigned), then return null as if receive timed out
        gettimeofday(&tv_recv_next, NULL);
        if ((tmo_shift = (tv_recv_next.tv_sec * 1000 + tv_recv_next.tv_usec / 1000) - recv_start) >= timeout)
        {
            RETURN_NULL();
            return;
        }

        if (ERL_TICK == (erl_recv = ei_xreceive_msg_tmo(conn->conn->fd, &msg, &buf, timeout - tmo_shift)))
        {
            continue;
        }

        if (ERL_ERROR == erl_recv && ETIMEDOUT != erl_errno)
        {
            ei_x_free(&buf);
            zend_throw_exception(e_msg_rcv, /* todo */ "Unknown message receive error", erl_errno);
            return;
        }

        if (ERL_MSG == erl_recv)
        {
            // todo: if ERL_REG_SEND accept only 'broadcast' or something
            if (ERL_REG_SEND == msg.msgtype || ERL_SEND == msg.msgtype)
            {
                // accept message if 'msg.to' matches 'conn->pid'
                if (
                    0 == strcmp("php", msg.toname) || // todo/fixme: debug condition
                    yaep_pid_match(&(msg.to), conn->pid))
                {
                    // accept message
                    if (NULL == (obj = _yaep_do_decode_message(&msg, &buf)))
                    {
                        RETURN_NULL();
                    }
                    else
                    {
                        RETURN_OBJ(obj);
                    }

                    ei_x_free(&buf);
                    return;
                }
                else
                {
                    // buffer messages globally for other recipients
                    yaep_inbox_push(global_inbox, &msg, &buf);
                    // Heads up! No "ei_x_free" for buf!
                    continue;
                }
            }
            else
            {
                ei_x_free(&buf);
                zend_throw_exception(e_msg_rcv, /* todo */ "Unexpected message type", 0);
                return;
            }
        }

        break;
    }

    RETURN_NULL();
}
PHP_METHOD(Yaep_Connection, send)
{
    zend_object *pid_term;

    zend_object *msg_term;

    long unsigned timeout;

    ZEND_PARSE_PARAMETERS_START(3, 3)
    Z_PARAM_OBJ_OF_CLASS(pid_term, a_pid_term);
    Z_PARAM_OBJ_OF_CLASS(msg_term, a_term);
    Z_PARAM_LONG(timeout)
    ZEND_PARSE_PARAMETERS_END();

    yaep_conn_t *t_conn = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_conn_t);
    yaep_term_t *t_pid = Z_STRUCT_OBJ_P(pid_term, yaep_term_t);
    yaep_term_t *t_msg = Z_STRUCT_OBJ_P(msg_term, yaep_term_t);

    ei_x_buff buf;
    ei_x_new_with_version(&buf);

    if (0 > encode_into_buffer(&buf, t_msg))
    {
        return;
    }

    if (0 > ei_send_tmo(t_conn->conn->fd, (erlang_pid *)(t_pid->val.s), buf.buff, buf.index, timeout))
    {
        ei_x_free(&buf);
        zend_throw_exception(e_msg_send, /* todo */ "Failed to send message", 0);
        return;
    }

    ei_x_free(&buf);
}

zend_object *yaep_node_new(zend_class_entry *ce)
{
    yaep_node_t *node = zend_object_alloc(sizeof(yaep_node_t), ce);
    zend_object_std_init(&node->std, ce);
    node->std.handlers = &yaep_node_object_handlers;
    return &node->std;
}

PHP_METHOD(Yaep_Node, __construct)
{
    yaep_node_t *this_node = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_node_t);

    char *name;
    long unsigned name_len;

    char *cookie;
    long unsigned cookie_len;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(name, name_len)
    Z_PARAM_STRING(cookie, cookie_len)
    ZEND_PARSE_PARAMETERS_END();

    this_node->node = yaep_mgr_node_init(name, name_len, cookie, cookie_len, 0);
    if (NULL == this_node->node)
    {
        zend_throw_exception(e_node_init, NULL, 0);
        return;
    }
}
PHP_METHOD(Yaep_Node, connect)
{
    char *node;
    long unsigned node_len;

    long unsigned timeout;

    ZEND_PARSE_PARAMETERS_START(2, 2)
    Z_PARAM_STRING(node, node_len)
    Z_PARAM_LONG(timeout)
    ZEND_PARSE_PARAMETERS_END();

    yaep_node_t *this_node = Z_STRUCT_ZVAL_OBJ_P(ZEND_THIS, yaep_node_t);
    yaep_conn_p *conn_p = yaep_mgr_connect(this_node->node, node, node_len, timeout);

    if (NULL == conn_p)
    {
        zend_throw_exception(e_node_conn, NULL, 0);
        return;
    }

    zend_object *obj = yaep_conn_new(a_conn);
    yaep_conn_t *conn_t = Z_STRUCT_OBJ_P(obj, yaep_conn_t);
    conn_t->conn = conn_p;
    conn_t->pid = emalloc(sizeof(erlang_pid));
    if (0 > ei_make_pid(conn_p->ec, conn_t->pid))
    {
        efree(conn_t->pid);
        zend_throw_exception(e_node_cpid, NULL, 0);
        return;
    }

    RETURN_OBJ(&conn_t->std);
}

void yaep_register_conn()
{
    // Node
    register_class_Yaep_Node()->create_object = yaep_node_new;
    memcpy(&yaep_node_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    yaep_node_object_handlers.offset = XtOffsetOf(yaep_node_t, std);

    // Conn
    a_conn = register_class_Yaep_Connection();
    a_conn->create_object = yaep_conn_new;
    memcpy(&yaep_conn_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    yaep_conn_object_handlers.offset = XtOffsetOf(yaep_conn_t, std);
}
