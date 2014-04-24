/**
 * Author aravind
 * @brief a simple test timer
 */

//compile with -lrt flag
#include "../DLOG_TIMER.hpp"

int main()
{
	
	DLOG_TIMER timer;
	
	std::cout<<"Will take 7 seconds to run\n";
	TID id1=timer.start_new("whole program"); //starts a timer and returns the id
	sleep(1);
	
	TID id2=timer.start_new();//lets create a new timer (its optional to give a name)
	sleep(2);
	
	TID id3=timer.start_new("timer with pause"); // and create one more
	sleep(1);
	
	//lets pause timer 3
	timer.pause(id3);
	sleep(2);
	
	//lets resume timer 3
	timer.resume(id3);
	sleep(1);
	
	std::cout<<"Time elapsed for Timer id3 = "<<timer.stop(id3)<<"\n"; //expected value 2
	std::cout<<"Time elapsed for Timer id2 = "<<timer.stop(id2)<<"\n"; //expected value 6
	std::cout<<"Time elapsed for Timer id1 = "<<timer.stop(id1)<<"\n"; //expected value 7
	
	//to print the values in a table use the following after stopping timer
	
	timer.draw_table("simple_timer_table_output.html","test timer","./output"); //if the last param is not
																				//given then the env variable
																				//	DLOG_OUTPUT_FOLDER will be used
	

	return 0;
}
