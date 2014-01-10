INCLUDE=-I../../include -I../../../build/include

all: lib/libdlog.a lib/dlog.so DLOG_FINALIZER.out

lib/dlog.so: DLOG.cpp *.hpp *.h
	g++ -shared -fPIC ${INCLUDE} -O3 DLOG.cpp -o lib/dlog.so

lib/dlog.o: DLOG.cpp *.hpp *.h
	g++ ${INCLUDE} -O3 -c DLOG.cpp -o lib/dlog.o
	
lib/libdlog.a: lib/dlog.o
	ar -cvq lib/libdlog.a lib/dlog.o

DLOG_FINALIZER.out: DLOG_FINALIZER.cpp *.h *.hpp
	g++ -O3 DLOG_FINALIZER.cpp -o DLOG_FINALIZER.out

clean:
	rm -f lib/* 
