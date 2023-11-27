#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([growable-buf], [0.1.0], [growable.buf@nonext.xxx])
AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])
AC_CONFIG_SRCDIR([src/buf.h])
AC_CONFIG_HEADERS([config.h])

PKG_CHECK_MODULES([CHECK],[check])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h])

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    test/Makefile
])

AC_ARG_ENABLE(
    [gcov],
    [AS_HELP_STRING([--enable-gcov],
    [use Gcov to test suites])],
    [],
    [enable_gcov=no]
)

AM_CONDITIONAL([COND_GCOV],[test '!' "$enable_gcov" = no])

AC_OUTPUT
