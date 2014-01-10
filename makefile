
all:
	g++ -std=c++11 -O3 DLOG_FINALIZER.cpp  -o DLOG_FINALIZER.out
	g++ -std=c++11 -c -O3 DLOG.cpp -o DLOG.o
	g++ -std=c++11 -shared -o lib/libDLOG.so -fPIC DLOG.cpp
	ar -cvq lib/libDLOG.a DLOG.o

clean:
	rm *.out
	rm lib/*.so
	rm lib/*.a
