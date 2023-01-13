
#include "php.h"
#include "php_yaep.h"
#include "yaep_arginfo.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

zend_class_entry *e_node_init, *e_node_conn, *e_node_cpid, *e_msg_rcv, *e_msg_send, *e_term_dec, *e_term_enc;

PHP_METHOD(Yaep_NodeInitializationException, __construct)
{
}

PHP_METHOD(Yaep_NodeConnectionException, __construct)
{
}

PHP_METHOD(Yaep_NodeCreateProcessIdentifierException, __construct)
{
}

PHP_METHOD(Yaep_MessageReceivingException, __construct)
{
}

PHP_METHOD(Yaep_MessageSendingException, __construct)
{
}

PHP_METHOD(Yaep_TermEncodingException, __construct)
{
}

PHP_METHOD(Yaep_TermDecodingException, __construct)
{
}

void yaep_register_exceptions()
{
    e_node_init = register_class_Yaep_NodeInitializationException(spl_ce_RuntimeException);
    e_node_conn = register_class_Yaep_NodeConnectionException(spl_ce_RuntimeException);
    e_node_cpid = register_class_Yaep_NodeCreateProcessIdentifierException(spl_ce_RuntimeException);
    e_msg_rcv = register_class_Yaep_MessageReceivingException(spl_ce_RuntimeException);
    e_msg_send = register_class_Yaep_MessageSendingException(spl_ce_RuntimeException);
    e_term_dec = register_class_Yaep_TermDecodingException(spl_ce_RuntimeException);
    e_term_enc = register_class_Yaep_TermEncodingException(spl_ce_RuntimeException);
}
