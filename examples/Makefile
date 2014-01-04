all: libs
	g++ DLOG_SIMPLE.cpp -o DLOG_SIMPLE.out ../lib/libDLOG.a
	g++ DLOG_SIMPLE2_CRASH_TEST.cpp -o DLOG_SIMPLE2_CRASH_TEST.out ../lib/libDLOG.a
	
libs:
	g++ -c -std=c++11 ../DLOG.cpp -o DLOG.o
	ar -cq libDLOG.a DLOG.o
	rm DLOG.o
	mv libDLOG.a ../lib/
	
clean:
	rm *.out
