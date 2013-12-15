#include "../DLOG.hpp"

int main()
{
	DLOG dbg DLOG_CREATE("DLOG_SIMPLE.html");

	//testing string
	DLOG_PRINT(dbg, "testing with string");

	//testing number
	DLOG_PRINT(dbg, 1);

	//testing character
	DLOG_PRINT(dbg, 'c');

	//lets add some tags
	DLOG_PRINT(dbg, "some output 1 regarding main()", "main");
	DLOG_PRINT(dbg, "some output 2 regarding main()", "main");
	DLOG_PRINT(dbg, "some output 3 regarding main()", "main");

	DLOG_PRINT(dbg, "some output 1 regarding fun1()", "fun1");
	DLOG_PRINT(dbg, "some output 2 regarding fun1()", "fun1");
	DLOG_PRINT(dbg, "some output 3 regarding fun1()", "fun1");

	DLOG_PRINT(dbg, "some output 1 regarding fun2()", "fun2");
	DLOG_PRINT(dbg, "some output 2 regarding fun2()", "fun2");

	//sometimes you want to toggle between stdout and dlog or both
	//to do this you can use DLOG output modes the default output mode is dlog
	//DLOG has the ability to switch between modes. See the below

	dbg.set_output_mode(DLOG_OUTPUT_STDOUT);
	DLOG_PRINT(dbg, "This will be only printed on screen");
	DLOG_PRINT(dbg, "This will also be only printed on screen", "main");

	dbg.set_output_mode(DLOG_OUTPUT_BOTH);
	DLOG_PRINT(dbg, "This will be printed both on screen and dlog");
	DLOG_PRINT(dbg, "This will be printed both on screen and dlog", "main");

	dbg.set_output_mode(DLOG_OUTPUT_FILE);
	DLOG_PRINT(dbg, "And we are back to file only mode");

	return 0;
}
