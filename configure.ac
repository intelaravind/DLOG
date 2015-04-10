#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([DLOG], [0.6], [aravind_sr@outlook.com])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

#shared libary
LT_INIT

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
#AC_PROG_RANLIB


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
