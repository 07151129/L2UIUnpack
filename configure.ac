#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([L2UIUnpack], 0.1)
AC_CONFIG_SRCDIR([L2UIUnpack/Attribute.cpp])
AC_USE_SYSTEM_EXTENSIONS
AC_PROG_CXX

AM_INIT_AUTOMAKE
LT_INIT

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for libraries.
AM_PATH_XML2(, , AC_MSG_ERROR(Cannot find libxml2.))

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_INT32_T
AC_TYPE_SIZE_T
AC_TYPE_UINT8_T

AC_ARG_ENABLE([static_stdlib],
    AS_HELP_STRING([--enable-static-stdlib], [Enable static libstdc++ and libgcc linkage.]),)

AS_IF([test "x$enable_static_stdlib" == "xyes"], [
        if test "x$GCC" = "xyes"; then
            AC_MSG_NOTICE([Linking libstdc++ and libgcc statically.])
            LDFLAGS="$LDFLAGS -static-libstdc++ -static-libgcc"
        fi
    ])

AC_OUTPUT(Makefile L2UIUnpack/Makefile)
