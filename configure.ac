AC_INIT([src/class_Array_i.c])
AM_INIT_AUTOMAKE([libtgcl],[0.0.1])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])

AC_LANG_C
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AC_HEADER_STDC
AC_CHECK_HEADERS([ctype.h stdio.h errno.h],,AC_MSG_ERROR([
required header file missing]))

AC_C_INLINE
AC_TYPE_SIZE_T

AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset strtol strtoul strncmp strncpy],,AC_MSG_ERROR([
required standard library function missing]))

AC_CONFIG_FILES([
  Makefile
  src/Makefile
]) 
AC_OUTPUT
