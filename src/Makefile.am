
AM_CPPFLAGS=-std=c++11 -O3 -I$(top_srcdir)/include -I$(top_srcdir)/#-g
ACLOCAL_AMFLAGS=-I m4

#Fix me
#ifdef WITH_LLVM
#CPPFLAGS+=$(shell llvm-config --cxxflags) -DDLOG_LLVM_ENABLE
#endif

sources= DLOG.cpp DLOG_HELPER.cpp DLOG_FINALIZER.cpp

#noinst_LIBRARIES = $(top_builddir)/libs/libDLOG.a
#__top_builddir__libs_libDLOG_a_SOURCES = $(sources)

lib_LTLIBRARIES= $(top_builddir)/libDLOG.la
__top_builddir__libDLOG_la_SOURCES = $(sources)
