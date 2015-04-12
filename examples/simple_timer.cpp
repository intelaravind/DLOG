/**
 * Author aravind
 * @brief a simple test timer
 */

//compile with " -std=c++11 -lrt" flag
#include "DLOG_TIMER.hpp"

int main()
{

    DLOG_TIMER timer;

    std::cout << "Will take 7 seconds to run\n";
    timer.start("whole program"); //starts a timer and returns the id
    sleep(1);

    timer.start("second timer");//lets create a new timer
    sleep(2);

    timer.start("timer with pause");
    sleep(1);

    //lets pause timer 3
    timer.stop("timer with pause");
    sleep(2);

    //lets resume timer 3
    timer.start("timer with pause");
    sleep(1);

    std::cout << "Time elapsed for Timer id3 = " << timer.stop("timer with pause") << "\n"; //expected value 2
    std::cout << "Time elapsed for Timer id2 = " << timer.stop("second timer") << "\n"; //expected value 6
    std::cout << "Time elapsed for Timer id1 = " << timer.stop("whole program") << "\n"; //expected value 7

    //to print the values in a table use the following after stopping timer

    timer.output_html_table("simple_timer_table_output.html", "test timer", "./output"); //if the last param is not
    //given then the env variable
    //	DLOG_OUTPUT_FOLDER will be used

    //ok lets try to print it on a stream (in this case stdout, you can use any FILE pointer)
    timer.output_stream(stdout, "un formatted");

    //Now lets try to change the delimiter and the human readable format

    DLOG_TIMER_OPTIONS opt;

    opt.delimiter = ","; //Separate the output using "," instead of tab (not applicable for html output)
    opt.human_readable = false ; //Turn off human readable format

    printf("****************** after setting options ********************\n");
    timer.output_html_table("simple_timer_table_output_formatted.html", "test timer", "./output", opt);
    timer.output_stream(stdout, "formatted", opt);

    //Generate Gantt chart (NOTE: requires internet to fetch google charts)
    timer.events_html_gantt("simple_timer_gantt.html", "test timer", "./output");

    //print to FILE* 
    timer.csv_events(stdout);

    return 0;
}

