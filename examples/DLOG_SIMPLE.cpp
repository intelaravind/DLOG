#include "../DLOG.hpp"

int main()
{
	DLOG dbg DLOG_CREATE("test.html");

	//testing string
	DLOG_PRINT(dbg,"testing with string");

	//testing number
	DLOG_PRINT(dbg,1);

	//testing character
	DLOG_PRINT(dbg,'c');
	return 0;
}
