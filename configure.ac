#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([DLOG], [0.6], [aravind_sr@outlook.com])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])


#M4
AC_CONFIG_MACRO_DIR([m4])
m4_ifdef([AM_PROG_AR], [AM_PROG_AR])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR

# Checks for programs.
AC_PROG_CXX
AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET


AC_PROG_RANLIB

#shared libary
LT_INIT

#find the build path
src_full_path=`cd $srcdir && pwd`

AC_DEFINE_UNQUOTED([SRC_PATH], ["$src_full_path"], "full source path")

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_TYPE_SIZE_T


#fix the recover.sh
sed "s%SRC_PATH=.*%SRC_PATH=\"$src_full_path\"%" $src_full_path/recover.template.sh > recover.sh
chmod +x recover.sh

# Checks for library functions.
AC_CHECK_FUNCS([clock_gettime strerror])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
