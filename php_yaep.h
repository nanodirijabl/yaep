/* yaep extension for PHP */

#ifndef PHP_YAEP_H
#define PHP_YAEP_H

#ifndef _REENTRANT
#define _REENTRANT /* For some reason __erl_errno is undefined unless _REENTRANT is defined */
#endif

#include "ei.h"
#include "debug.h"

ZEND_BEGIN_MODULE_GLOBALS(yaep)
ZEND_END_MODULE_GLOBALS(yaep)

#ifdef ZTS
#define YAEP_GLOBAL(v) TSRMG(yaep_globals_id, zend_yaep_globals *, v)
#else
#define YAEP_GLOBAL(v) (yaep_globals.v)
#endif

extern zend_module_entry yaep_module_entry;
#define phpext_yaep_ptr &yaep_module_entry

#define PHP_YAEP_VERSION "0.1.0"

#if defined(ZTS) && defined(COMPILE_DL_YAEP)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#define Z_STRUCT_OBJ_P(zo, type) ((type *)((char *)(zo)-XtOffsetOf(type, std)))
#define Z_STRUCT_ZVAL_OBJ_P(zv, type) Z_STRUCT_OBJ_P(Z_OBJ_P(zv), type)

#endif /* PHP_YAEP_H */
