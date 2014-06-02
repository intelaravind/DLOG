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
#include <algorithm>
#include <assert.h>

template<class T>
static std::string dlog_to_string(T input)
{
	std::ostringstream convert;
	convert << input;
	return convert.str();
}

static std::string humanreadabletime(long input)
{

	input = input / 1000000; // max accuray we need is milli second

	std::string hour = dlog_to_string(input / ((long) 1000 * 60 * 60));

	input = input % (1000 * 60 * 60);
	std::string min = dlog_to_string(input / ((long) 1000 * 60));

	input = input % (1000 * 60);
	std::string sec = dlog_to_string(input / ((double) 1000));

	std::string ret = hour + "h : " + min + "m : " + sec + " s";
	return ret;

}

class DLOG_TIMER_OPTIONS
{
public:
	std::string delimiter = "\t";
	bool human_readable = true;
};

class DLOG_TIMER
{
	std::vector<struct timespec> start_list;
	std::vector<long> cummulative_time;
	std::vector<std::string> timer_names;

	int get_id_by_name(std::string name)
	{
		auto it = std::find(timer_names.begin(), timer_names.end(), name);

		assert(it != timer_names.end() && "Accessing uninitialized timer");

		int id = it - timer_names.begin();
		return id;
	}

public:
	DLOG_TIMER()
	{

	}
	void start(std::string name)
	{
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit(EXIT_FAILURE);
		}
		start_list.push_back(start);
		cummulative_time.push_back(0);
		timer_names.push_back(name);
	}

	long int stop(std::string name)
	{
		struct timespec stop;
		if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
		{
			perror("clock gettime");
			exit(EXIT_FAILURE);
		}

		int id = get_id_by_name(name);

		auto val = 1000000000 * (stop.tv_sec - start_list[id].tv_sec)
				+ (stop.tv_nsec - start_list[id].tv_nsec);

		cummulative_time[id] += val;
		return cummulative_time[id];
	}

	long int pause(std::string name)
	{
		return stop(name);
	}

	void resume(std::string name)
	{
		int id = get_id_by_name(name);
//		std::cout<<"Id = "<<id<<" times "<< times[id] <<"\n";
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit(EXIT_FAILURE);
		}
		start_list[id] = start;
	}

	void reset(std::string name)
	{
		int id = get_id_by_name(name);
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit(EXIT_FAILURE);
		}
		start_list[id] = start;
	}

	void output_html_table(std::string filename, std::string tablename =
			"unnamed", std::string path = "", DLOG_TIMER_OPTIONS options =
			DLOG_TIMER_OPTIONS())
	{

		if (path == "")
			path = getenv("DLOG_OUTPUT_FOLDER");

		DLOG_TABLE table(filename.c_str(), tablename.c_str(), path);
		std::vector<std::string> head_row;

		head_row.push_back("Name");
		head_row.push_back("Time");

		if (options.human_readable)
		{
			head_row.push_back("Human readable");
		}
		table.insert_row(head_row);

		for (unsigned int i = 0; i < cummulative_time.size(); i++)
		{
			std::vector<std::string> row;
			std::string str_i = dlog_to_string(i);
			std::string str_times = dlog_to_string(cummulative_time[i]);

			row.push_back(timer_names[i]);
			row.push_back(str_times);
			if (options.human_readable)
			{
				row.push_back(
						"  (" + humanreadabletime(cummulative_time[i]) + " )");
			}

			table.insert_row(row);

		}
		table.table_html_dump();
	}

	void output_stream(FILE *fp, std::string tablename = "unnamed",
			DLOG_TIMER_OPTIONS options = DLOG_TIMER_OPTIONS())
	{

		fprintf(fp, "%s\n", tablename.c_str());

		if (options.human_readable == true)
		{
			fprintf(fp, "Name%sTime%sHuman_readable\n",
					options.delimiter.c_str(), options.delimiter.c_str());
		}
		else
		{
			fprintf(fp, "Name%sTime\n", options.delimiter.c_str());
		}

		fprintf(fp,
				"=============================================================================\n");

		for (unsigned int i = 0; i < cummulative_time.size(); i++)
		{
			std::vector<std::string> row;
			std::string str_i = dlog_to_string(i);
			std::string str_times = dlog_to_string(cummulative_time[i]);

			if (options.human_readable == true)
			{
				std::string hr = "  (" + humanreadabletime(cummulative_time[i])
						+ " )";
				fprintf(fp, "%s%s%s%s%s\n", (timer_names[i]).c_str(),
						options.delimiter.c_str(), str_times.c_str(),
						options.delimiter.c_str(), hr.c_str());

			}
			else
			{
				fprintf(fp, "%s%s%s\n", (timer_names[i]).c_str(),
						options.delimiter.c_str(), str_times.c_str());
			}

		}
	}
};

#endif /* DLOG_TIMER_HPP_ */
