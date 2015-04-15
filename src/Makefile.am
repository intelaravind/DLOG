#Author Aravind

#set by autoconf
if EN_LLVM
  AM_CPPFLAGS=-DDLOG_LLVM_ENABLE
else
  AM_CPPFLAGS= 
endif
AM_CPPFLAGS+=-std=c++11 -O3 -I$(top_srcdir)/include #-g
ACLOCAL_AMFLAGS=-I m4

#CPPFLAGS+=$(shell llvm-config --cxxflags) -DDLOG_LLVM_ENABLE

sources= DLOG.cpp DLOG_HELPER.cpp 

#noinst_LIBRARIES = $(top_builddir)/libs/libDLOG.a
#__top_builddir__libs_libDLOG_a_SOURCES = $(sources)

lib_LTLIBRARIES= $(top_builddir)/libDLOG.la
__top_builddir__libDLOG_la_SOURCES = $(sources)
