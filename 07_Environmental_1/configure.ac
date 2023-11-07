#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([RHasher], [0.1.0], [rhasher@nonext.xxx])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign subdir-objects])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([rhash],[rhash_library_init],[],[AC_MSG_ERROR([Missing rhash library])])
AC_CHECK_LIB([readline],[readline],[],[])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T
AC_ARG_ENABLE(
    [readline],
    AS_HELP_STRING(
        [--enable-readline],
        [Use readline function]
    ),
    AC_DEFINE(
        READLINE,
        [1],
        [Readline mode]
    ),
    [use_readline="false"]
)
AS_IF([test "x$use_readline" = "xfalse"], [AC_SUBST(LIBS, ["-lrhash"])])

# Checks for library functions.
AC_CHECK_FUNCS([strcasecmp strerror])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
