#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])

AC_CONFIG_AUX_DIR([build-aux])

AM_INIT_AUTOMAKE([foreign])

AC_CONFIG_SRCDIR([src/packcc.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

#m4_ifndef([PKG_CHECK_EXISTS],[m4_fatal([must install pkg-config 0.18 or later before running autoconf/autogen])])

#PKG_CHECK_EXISTS([dummy])

# Checks for programs.
#echo '----------------------------------------------'
#AC_PROG_CC
echo '----------------------------------------------'
AX_PROG_CC_FOR_BUILD
echo '----------------------------------------------'

# We need to compile and run a program on the build machine.  A
# comment in libgpg-error says that the AC_PROG_CC_FOR_BUILD macro in
# the AC archive is broken for autoconf 2.57.  Given that there is no
# newer version of that macro, we assume that it is also broken for
# autoconf 2.61 and thus we use a simple but usually sufficient
# approach.
AC_MSG_CHECKING(for cc for build)
if test "$cross_compiling" = "yes"; then
  CC_FOR_BUILD="${CC_FOR_BUILD-cc}"
else
  CC_FOR_BUILD="${CC_FOR_BUILD-$CC}"
fi
AC_MSG_RESULT($CC_FOR_BUILD)
AC_ARG_VAR(CC_FOR_BUILD,[build system C compiler])

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
