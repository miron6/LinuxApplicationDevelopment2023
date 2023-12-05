#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Predictor], [0.1.0], [predictor@nonext.xxx], [predictor])
AM_INIT_AUTOMAKE([foreign])
DX_INIT_DOXYGEN([predictor])
AC_CONFIG_SRCDIR([predictor.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([libintl.h locale.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CHECK_FUNCS([setlocale strcasecmp])

AC_CONFIG_FILES([Makefile Doxyfile])
AC_OUTPUT
