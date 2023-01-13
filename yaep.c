/* yaep extension for PHP */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"
#include "php_yaep.h"
#include "yaep_arginfo.h"

#include "zend_interfaces.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"

#include "exceptions.h"
#include "term.h"
#include "node.h"
#include "connection.h"
#include "inbox.h"

yaep_inbox_entry *global_inbox;

/* {{{ PHP_RINIT_FUNCTION */
PHP_RINIT_FUNCTION(yaep)
{
#if defined(ZTS) && defined(COMPILE_DL_YAEP)
    ZEND_TSRMLS_CACHE_UPDATE();
#endif

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_RSHUTDOWN_FUNCTION */
PHP_RSHUTDOWN_FUNCTION(yaep)
{
    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION */
PHP_MINFO_FUNCTION(yaep)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "yaep support", "enabled");
    php_info_print_table_row(2, "version", PHP_YAEP_VERSION);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(yaep)
{
    ei_init();

    yaep_register_exceptions();
    yaep_register_terms();
    yaep_register_conn();

    global_inbox = NULL;

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(yaep)
{
    UNREGISTER_INI_ENTRIES();
    yaep_mgr_free();

    return SUCCESS;
}
/* }}} */

/* {{{ yaep_module_entry */
zend_module_entry yaep_module_entry = {
    STANDARD_MODULE_HEADER,
    "yaep",              /* Extension name */
    NULL,                /* zend_function_entry */
    PHP_MINIT(yaep),     /* PHP_MINIT - Module initialization */
    PHP_MSHUTDOWN(yaep), /* PHP_MSHUTDOWN - Module shutdown */
    PHP_RINIT(yaep),     /* PHP_RINIT - Request initialization */
    PHP_RSHUTDOWN(yaep), /* PHP_RSHUTDOWN - Request shutdown */
    PHP_MINFO(yaep),     /* PHP_MINFO - Module info */
    PHP_YAEP_VERSION,    /* Version */
    STANDARD_MODULE_PROPERTIES};
/* }}} */

#ifdef COMPILE_DL_YAEP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(yaep)
#endif
