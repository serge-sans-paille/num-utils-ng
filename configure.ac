
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.67])
AC_INIT([num-utils-ng], [1.0], [serge.guelton@telecom-bretagne.eu])
AM_INIT_AUTOMAKE([gnu])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC_C99

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [sqrt])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([sqrt strstr])

AC_OUTPUT([Makefile src/Makefile docs/Makefile tests/Makefile])
