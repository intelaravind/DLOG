all: enabled

CPPFLAGS=-std=c++11 -O3 -fPIC #-g

ifdef WITH_LLVM
CPPFLAGS+=$(shell llvm-config --cxxflags) -DDLOG_LLVM_ENABLE
endif

enabled: 
	g++ $(CPPFLAGS) -c DLOG.cpp -o DLOG.o
	g++ $(CPPFLAGS) -c DLOG_HELPER.cpp -o DLOG_HELPER.o
	g++ $(CPPFLAGS) DLOG_FINALIZER.cpp DLOG_HELPER.o -o DLOG_FINALIZER.out
	g++ $(CPPFLAGS) -shared -o lib/libDLOG.so DLOG.cpp  DLOG_HELPER.cpp
	ar -cvq lib/libDLOG.a *.o

clean:
	rm -rf *.o
	rm -rf *.out
	rm -rf lib/*.so
	rm -rf lib/*.a
