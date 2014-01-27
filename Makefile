all: enabled

enabled: 
	g++ -std=c++11 -c -O3 DLOG.cpp -o DLOG.o #-g
	g++ -std=c++11 -c -O3 DLOG_HELPER.cpp -o DLOG_HELPER.o #-g
	g++ -std=c++11 -O3 DLOG_FINALIZER.cpp DLOG_HELPER.o -o DLOG_FINALIZER.out #-g
	g++ -std=c++11 -shared -O3 -o lib/libDLOG.so -fPIC DLOG.cpp  DLOG_HELPER.cpp #-g
	ar -cvq lib/libDLOG.a *.o 

clean:
	rm -rf *.out
	rm -rf lib/*.so
	rm -rf lib/*.a
