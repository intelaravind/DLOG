#include "../DLOG.hpp"


/*
 * A program may crash during the executing. for eg a segfault. This causes DLOG
 * not to produce the output. I this case you should run the recover.sh and everything
 * before crash can be recovered.
 *
 * WARNING: YOU SHOULD RUN "recover.sh" where the DLOG_PATH is set. DLOG_PATH should point to the base folder of DLOG
 * (where DLOG.hpp is present)
 */



int main(int argc, char **argv)
{
	DLOG dbg DLOG_CREATE("DLOG_SIMPLE2_CRASH_TEST.html");

	DLOG_PRINT(dbg, argv[0], "main", ADDON("this is the program name"));

	int *ptr;

	DLOG_PRINT(dbg,"last point before crash");

	std::cout<<"This is gonna crash";
	*ptr=10;

	return 0;
}
