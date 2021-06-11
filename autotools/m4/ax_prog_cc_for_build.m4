#echo  ===========================================================================
#echo    https://www.gnu.org/software/autoconf-archive/ax_prog_cc_for_build.html
#echo  ===========================================================================
#echo 
#echo  SYNOPSIS
#echo 
#echo    AX_PROG_CC_FOR_BUILD
#echo 
#echo  DESCRIPTION
#echo 
#echo    This macro searches for a C compiler that generates native executables,
#echo    that is a C compiler that surely is not a cross-compiler. This can be
#echo    useful if you have to generate source code at compile-time like for
#echo    example GCC does.
#echo 
#echo    The macro sets the CC_FOR_BUILD and CPP_FOR_BUILD macros to anything
#echo    needed to compile or link (CC_FOR_BUILD) and preprocess (CPP_FOR_BUILD).
#echo    The value of these variables can be overridden by the user by specifying
#echo    a compiler with an environment variable (like you do for standard CC).
#echo 
#echo    It also sets BUILD_EXEEXT and BUILD_OBJEXT to the executable and object
#echo    file extensions for the build platform, and GCC_FOR_BUILD to `yes' if
#echo    the compiler we found is GCC. All these variables but GCC_FOR_BUILD are
#echo    substituted in the Makefile.
#echo 
#echo  LICENSE
#echo 
#echo    Copyright (c) 2008 Paolo Bonzini <bonzini@gnu.org>
#echo 
#echo    Copying and distribution of this file, with or without modification, are
#echo    permitted in any medium without royalty provided the copyright notice
#echo    and this notice are preserved. This file is offered as-is, without any
#echo    warranty.

#echo serial 18
#echo 111111111111111111111111111111

AC_DEFUN([_AC_BUILD_COMPILER_EXEEXT], [_AC_COMPILER_EXEEXT])
AC_DEFUN([_AC_BUILD_COMPILER_OBJEXT], [_AC_COMPILER_OBJEXT])

AU_ALIAS([AC_PROG_CC_FOR_BUILD], [AX_PROG_CC_FOR_BUILD])
#echo 222222222222222222222222222222
AC_DEFUN([AX_PROG_CC_FOR_BUILD], [dnl
#echo 333333333333333333333333333333
AC_REQUIRE([AC_PROG_CC])dnl
#echo 444444444444444444444444444444
AC_REQUIRE([AC_PROG_CC_C99])dnl
#echo 555555555555555555555555555555
AC_REQUIRE([AC_PROG_CPP])dnl
#echo 66666666666666666666666666666
AC_REQUIRE([AC_CANONICAL_BUILD])dnl


ac_cv_c_compiler_gnu_saved=$ac_cv_c_compiler_gnu

unset ac_cv_c_compiler_gnu

#echo 77777777777777777777777777777
dnl Use the standard macros, but make them use other variable names
dnl
pushdef([ac_cv_prog_CPP], ac_cv_build_prog_CPP)dnl
#echo 88888888888888888888888888888
pushdef([ac_cv_prog_cc_c89], ac_cv_build_prog_cc_c89)dnl
pushdef([ac_cv_prog_cc_c99], ac_cv_build_prog_cc_c99)dnl
#echo 99999999999999999999999999999
pushdef([ac_cv_prog_gcc], ac_cv_build_prog_gcc)dnl
#echo 101010101010101010101010101010
pushdef([ac_cv_prog_cc_works], ac_cv_build_prog_cc_works)dnl
#echo 111111111111111111111111111111
pushdef([ac_cv_prog_cc_cross], ac_cv_build_prog_cc_cross)dnl
#echo 121212121212121212121212121212
pushdef([ac_cv_prog_cc_g], ac_cv_build_prog_cc_g)dnl
#echo 13
pushdef(ac_cv_[]_AC_LANG_ABBREV[]_compiler_gnu, ac_cv_build_[]_AC_LANG_ABBREV[]_compiler_gnu)dnl
pushdef([ac_cv_c_compiler_gnu], ac_cv_build_c_compiler_gnu)dnl
pushdef([ac_compiler_gnu], ac_build_compiler_gnu)dnl
pushdef([_AC_COMPILER_EXEEXT], [_AC_BUILD_COMPILER_EXEEXT])dnl
pushdef([_AC_COMPILER_OBJEXT], [_AC_BUILD_COMPILER_OBJEXT])dnl
#echo 14
pushdef([ac_cv_exeext], ac_cv_build_exeext)dnl
#echo 15
pushdef([ac_cv_objext], ac_cv_build_objext)dnl
#echo 16
pushdef([ac_exeext], ac_build_exeext)dnl
#echo 17
pushdef([ac_objext], ac_build_objext)dnl
#echo 18
pushdef([CC], CC_FOR_BUILD)dnl
#echo 19
pushdef([CPP], CPP_FOR_BUILD)dnl
#echo 20
pushdef([GCC], GCC_FOR_BUILD)dnl
pushdef([CFLAGS], CFLAGS_FOR_BUILD)dnl
pushdef([CPPFLAGS], CPPFLAGS_FOR_BUILD)dnl
pushdef([EXEEXT], BUILD_EXEEXT)dnl
pushdef([LDFLAGS], LDFLAGS_FOR_BUILD)dnl
pushdef([OBJEXT], BUILD_OBJEXT)dnl
pushdef([host], build)dnl
pushdef([host_alias], build_alias)dnl
pushdef([host_cpu], build_cpu)dnl
pushdef([host_vendor], build_vendor)dnl
pushdef([host_os], build_os)dnl
pushdef([ac_cv_host], ac_cv_build)dnl
pushdef([ac_cv_host_alias], ac_cv_build_alias)dnl
pushdef([ac_cv_host_cpu], ac_cv_build_cpu)dnl
pushdef([ac_cv_host_vendor], ac_cv_build_vendor)dnl
pushdef([ac_cv_host_os], ac_cv_build_os)dnl
pushdef([ac_tool_prefix], ac_build_tool_prefix)dnl
pushdef([am_cv_CC_dependencies_compiler_type], am_cv_build_CC_dependencies_compiler_type)dnl
pushdef([am_cv_prog_cc_c_o], am_cv_build_prog_cc_c_o)dnl
pushdef([cross_compiling], cross_compiling_build)dnl

#echo 21
cross_compiling_build=no
#echo 22
ac_build_tool_prefix=
#echo 24
AS_IF([test -n "$build"],      [ac_build_tool_prefix="$build-"],
      [test -n "$build_alias"],[ac_build_tool_prefix="$build_alias-"])
#echo 25
AC_LANG_PUSH([C])
#echo 26
AC_PROG_CC
#echo 27
#_AC_COMPILER_EXEEXT
#echo 28
#_AC_COMPILER_OBJEXT
#echo 29
AC_PROG_CC_C99
#echo 30
AC_PROG_CPP

#ac_cv_c_compiler_gnu=$ac_cv_c_compiler_gnu_saved

#echo 31
dnl Restore the old definitions
dnl
popdef([cross_compiling])dnl
popdef([am_cv_prog_cc_c_o])dnl
popdef([am_cv_CC_dependencies_compiler_type])dnl
popdef([ac_tool_prefix])dnl
popdef([ac_cv_host_os])dnl
popdef([ac_cv_host_vendor])dnl
popdef([ac_cv_host_cpu])dnl
popdef([ac_cv_host_alias])dnl
popdef([ac_cv_host])dnl
popdef([host_os])dnl
popdef([host_vendor])dnl
popdef([host_cpu])dnl
popdef([host_alias])dnl
popdef([host])dnl
popdef([OBJEXT])dnl
popdef([LDFLAGS])dnl
popdef([EXEEXT])dnl
popdef([CPPFLAGS])dnl
popdef([CFLAGS])dnl
popdef([GCC])dnl
popdef([CPP])dnl
popdef([CC])dnl
popdef([ac_objext])dnl
popdef([ac_exeext])dnl
popdef([ac_cv_objext])dnl
popdef([ac_cv_exeext])dnl
popdef([ac_compiler_gnu])dnl
popdef([ac_cv_c_compiler_gnu])dnl
popdef([ac_cv_prog_cc_g])dnl
popdef([ac_cv_prog_cc_cross])dnl
popdef([ac_cv_prog_cc_works])dnl
popdef([ac_cv_prog_cc_c89])dnl
popdef([ac_cv_prog_cc_c99])dnl
popdef([ac_cv_prog_gcc])dnl
popdef([ac_cv_prog_CPP])dnl
#echo 32
dnl restore global variables ac_ext, ac_cpp, ac_compile,
dnl ac_link, ac_compiler_gnu (dependant on the current
dnl language after popping):
AC_LANG_POP([C])
#echo 33
dnl Finally, set Makefile variables
dnl
AC_SUBST(BUILD_EXEEXT)dnl
#echo 34
AC_SUBST(BUILD_OBJEXT)dnl
#echo 35
AC_SUBST([CFLAGS_FOR_BUILD])dnl
#echo 36
AC_SUBST([CPPFLAGS_FOR_BUILD])dnl
#echo 37
AC_SUBST([LDFLAGS_FOR_BUILD])dnl
#echo 38
])
