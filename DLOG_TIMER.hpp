/*
 * DLOG_TIMER.hpp
 *
 *  Created on: Nov 8, 2013
 *      Author: aravind
 */

#ifndef DLOG_TIMER_HPP_
#define DLOG_TIMER_HPP_
#include "debug_common_headers.hpp"
#include "DLOG_TABLE.hpp"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sstream>

template<class T>
static std::string dlog_to_string(T input)
{
	std::ostringstream convert;
	convert << input;
	return convert.str();
}

static std::string humanreadabletime(long input)
{

	input = input/1000000; // max accuray we need is milli second

	std::string hour = dlog_to_string(input / ((long)1000 * 60 * 60));

	input = input % (1000 * 60 * 60);
	std::string min = dlog_to_string(input / ((long)1000 * 60));

	input = input % (1000 * 60);
	std::string sec = dlog_to_string(input / ((double)1000));

	std::string ret = hour + "h : " + min + "m : " + sec + " s";
	return ret;

}
class DLOG_TIMER
{
	std::vector<struct timespec> start_list;
	std::vector<long> times;
	std::vector<std::string> names;

public:
	DLOG_TIMER()
	{

	}
	int start_new(std::string name = "no name")
	{
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit (EXIT_FAILURE);
		}
		start_list.push_back(start);
		times.push_back(0);
		names.push_back(name);
		return times.size() - 1;
	}
	long int stop(int id)
	{
		struct timespec stop;
		if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
		{
			perror("clock gettime");
			exit (EXIT_FAILURE);
		}

		auto val = 1000000000 * (stop.tv_sec - start_list[id].tv_sec)
				+ (stop.tv_nsec - start_list[id].tv_nsec);

		times[id] += val;
		return times[id];
	}

	long int pause(int id)
	{
		return stop(id);
	}

	void resume(int id)
	{
//		std::cout<<"Id = "<<id<<" times "<< times[id] <<"\n";
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit (EXIT_FAILURE);
		}
		start_list[id] = start;
	}

	void reset(int id)
	{
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit (EXIT_FAILURE);
		}
		start_list[id] = start;
	}

	void draw_table(std::string filename, std::string tablename,
			std::string path = "")
	{

		if (path == "")
			path = getenv("DLOG_OUTPUT_FOLDER");

		DLOG_TABLE table(filename.c_str(), tablename.c_str(), path);
		std::vector < std::string > head_row;
		head_row.push_back("Id");
		head_row.push_back("Name");
		head_row.push_back("Time");
		table.insert_row(head_row);

		for (unsigned int i = 0; i < times.size(); i++)
		{
			std::vector < std::string > row;
			std::string str_i = dlog_to_string(i);
			std::string str_times = dlog_to_string(times[i]);

			row.push_back(str_i);
			row.push_back(names[i]);
			row.push_back(str_times + "  (" + humanreadabletime(times[i])+ " )");

			table.insert_row(row);

		}
		table.table_html_dump();
	}
};

#endif /* DLOG_TIMER_HPP_ */
