#include "../DLOG.hpp"

int main()
{
	DLOG dbg DLOG_CREATE("DLOG_SIMPLE.html");

	//testing string
	DLOG_PRINT(dbg,"testing with string");

	//testing number
	DLOG_PRINT(dbg,1);

	//testing character
	DLOG_PRINT(dbg,'c');

	//lets add some tags
	DLOG_PRINT(dbg,"some output 1 regarding main()","main");
	DLOG_PRINT(dbg,"some output 2 regarding main()","main");
	DLOG_PRINT(dbg,"some output 3 regarding main()","main");

	DLOG_PRINT(dbg,"some output 1 regarding fun1()","fun1");
	DLOG_PRINT(dbg,"some output 2 regarding fun1()","fun1");
	DLOG_PRINT(dbg,"some output 3 regarding fun1()","fun1");

	DLOG_PRINT(dbg,"some output 1 regarding fun2()","fun2");
	DLOG_PRINT(dbg,"some output 2 regarding fun2()","fun2");

	return 0;
}
