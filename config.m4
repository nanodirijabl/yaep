dnl config.m4 for extension yaep

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use 'with':

dnl PHP_ARG_WITH([yaep],
dnl   [for yaep support],
dnl   [AS_HELP_STRING([--with-yaep],
dnl     [Include yaep support])])

PHP_ARG_WITH([erlang_interface],
  [required erlang interface],
  [AS_HELP_STRING([--with-erlang-interface], [Include erlang interface library and headers])])

dnl Otherwise use 'enable':

PHP_ARG_ENABLE([yaep],
  [whether to enable yaep support],
  [AS_HELP_STRING([--enable-yaep], [Enable yaep support])],
  [no])

if test "$PHP_YAEP" != "no"; then
  dnl Write more examples of tests here...

  dnl Remove this code block if the library does not support pkg-config.
  dnl PKG_CHECK_MODULES([LIBFOO], [foo])
  dnl PHP_EVAL_INCLINE($LIBFOO_CFLAGS)
  dnl PHP_EVAL_LIBLINE($LIBFOO_LIBS, YAEP_SHARED_LIBADD)

  dnl If you need to check for a particular library version using PKG_CHECK_MODULES,
  dnl you can use comparison operators. For example:
  dnl PKG_CHECK_MODULES([LIBFOO], [foo >= 1.2.3])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo < 3.4])
  dnl PKG_CHECK_MODULES([LIBFOO], [foo = 1.2.3])

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-yaep -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/yaep.h"  # you most likely want to change this
  dnl if test -r $PHP_YAEP/$SEARCH_FOR; then # path given as parameter
  dnl   YAEP_DIR=$PHP_YAEP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for yaep files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       YAEP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$YAEP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the yaep distribution])
  dnl fi

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-yaep -> add include path
  dnl PHP_ADD_INCLUDE($YAEP_DIR/include)

  dnl Remove this code block if the library supports pkg-config.
  dnl --with-yaep -> check for lib and symbol presence
  dnl LIBNAME=YAEP # you may want to change this
  dnl LIBSYMBOL=YAEP # you most likely want to change this

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   AC_DEFINE(HAVE_YAEP_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your yaep library.])
  dnl ], [
  dnl   $LIBFOO_LIBS
  dnl ])

  dnl If you need to check for a particular library function (e.g. a conditional
  dnl or version-dependent feature) and you are not using pkg-config:
  dnl PHP_CHECK_LIBRARY($LIBNAME, $LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $YAEP_DIR/$PHP_LIBDIR, YAEP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_YAEP_FEATURE, 1, [ ])
  dnl ],[
  dnl   AC_MSG_ERROR([FEATURE not supported by your yaep library.])
  dnl ],[
  dnl   -L$YAEP_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(YAEP_SHARED_LIBADD)

  if test "${PHP_ERLANG_INTERFACE}" != "no"; then
    PHP_ADD_LIBRARY_WITH_PATH(ei, "${PHP_ERLANG_INTERFACE}/lib", YAEP_SHARED_LIBADD)
    PHP_ADD_INCLUDE("${PHP_ERLANG_INTERFACE}/include")
  fi

  PHP_SUBST(YAEP_SHARED_LIBADD)

  dnl In case of no dependencies
  AC_DEFINE(HAVE_YAEP, 1, [ Have yaep support ])

  PHP_NEW_EXTENSION(yaep, yaep.c node.c exceptions.c term.c connection.c inbox.c, $ext_shared)
fi
