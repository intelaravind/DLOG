#include "../DLOG.hpp"


//define DLOG_DISABLE in DLOG.hpp or pass -DDLOG_DISABLE to disable the dlog.
//Try the same example with DLOG_DISABLE. This option can be used for performance run, or
//simply to disable dlog

//Note: Be careful while creating a dlog object on a program point which is can be
//reached multiple times (like functions and loops). DLOG object will only save the
//info of last call. This is just like opening a file inside a function in write
//mode. If you call the function multiple times you can only see the last output.
//To overcome this either use
//    static objects "staticDLOG dlog DLOG_CREATE("test.html");"
//    or
//    define it in  global space

int main(int argc, char **argv)
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

	//sometimes we want to add some info with some prints. This is very usefull in llvm mode
	//This is done with the help of addon. Addon is a simple string which will be printed with the object

	DLOG_PRINT(dbg, "This is about DLOG...... A lot to tell, but no time to write", "main", ADDON("about DLOG"));

	return 0;
}
