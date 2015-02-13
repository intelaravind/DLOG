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
#include <pthread.h>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <limits>
#include <mutex>

#include <assert.h>
#include <unistd.h>

class DLOG_TIMER;
struct finished_event;
struct unfinished_event;

template<class T>
static std::string dlog_to_string(T input)
{
	std::ostringstream convert;
	convert << input;
	return convert.str();
}

static long time_to_long(const struct timespec& t)
{
	return t.tv_sec * 1000000000 + t.tv_nsec;
}

static std::string time_to_str(const struct timespec& t)
{
	return std::to_string(t.tv_sec * 1000000000 + t.tv_nsec);
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

struct event_t
{
	event_t(const char* n, struct timespec b, struct timespec e)
	{
		name = n;
		begin = b;
		end = e;
	}

	struct timespec begin, end;
	const char* name;
};

class DLOG_TIMER_OPTIONS
{
public:
	std::string delimiter = "\t";
	bool human_readable = true;
};

class DLOG_TIMER
{
	std::map<std::string, struct timespec> started;
	std::vector<event_t> events;

	std::mutex mut;

public:
	DLOG_TIMER()
	{
	}

	~DLOG_TIMER()
	{
	}

	void start(const char *name)
	{
		struct timespec start;
		if (clock_gettime(CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit (EXIT_FAILURE);
		}

		mut.lock();

		started[name] = start;

		mut.unlock();
	}

	void stop(const char* name)
	{
		struct timespec stop;
		if (clock_gettime(CLOCK_REALTIME, &stop) == -1)
		{
			perror("clock gettime");
			exit (EXIT_FAILURE);
		}

		mut.lock();

		std::map<std::string, struct timespec>::iterator begin = started.find(name);
		event_t event(name, begin->second, stop);
		events.push_back(event);
		started.erase(begin);

		mut.unlock();
	}

	void reset()
	{
		mut.lock();

		started.clear();
		events.clear();

		mut.unlock();
	}

	std::map<std::string, long> get_cummulative_times()
	{
		std::map<std::string, long> cummul;

		for (event_t &event : events)
			cummul[event.name] = 0;

		for (event_t &event : events)
			cummul[event.name] += time_to_long(event.end) - time_to_long(event.begin);

		return cummul;
	}

	void output_html_table(std::string filename, std::string tablename = "unnamed", std::string path = "", DLOG_TIMER_OPTIONS options = DLOG_TIMER_OPTIONS())
	{

		if (path == "")
			path = getenv("DLOG_OUTPUT_FOLDER");

		DLOG_TABLE table(filename.c_str(), tablename.c_str(), path);
		std::vector < std::string > head_row;

		head_row.push_back("Name");
		head_row.push_back("Time");

		if (options.human_readable)
		{
			head_row.push_back("Human readable");
		}
		table.insert_row(head_row);

		std::map<std::string, long> cummulative_time = get_cummulative_times();

		for (auto pair : cummulative_time)
		{
			std::vector < std::string > row;
			row.push_back(pair.first);
			row.push_back(dlog_to_string(pair.second));

			if (options.human_readable)
			{
				row.push_back("  (" + humanreadabletime(pair.second) + " )");
			}

			table.insert_row(row);
		}
		table.table_html_dump();
	}

	void output_stream(FILE *fp, std::string tablename = "unnamed", DLOG_TIMER_OPTIONS options = DLOG_TIMER_OPTIONS())
	{

		fprintf(fp, "%s\n", tablename.c_str());

		if (options.human_readable == true)
		{
			fprintf(fp, "Name%sTime%sHuman_readable\n", options.delimiter.c_str(), options.delimiter.c_str());
		}
		else
		{
			fprintf(fp, "Name%sTime\n", options.delimiter.c_str());
		}

		fprintf(fp, "=============================================================================\n");

		std::map<std::string, long> cummulative_time = get_cummulative_times();

		for (auto pair : cummulative_time)
		{
			std::string str_times = dlog_to_string(pair.second);

			if (options.human_readable == true)
			{
				std::string hr = "  (" + humanreadabletime(pair.second) + " )";
				fprintf(fp, "%s%s%s%s%s\n", pair.first.c_str(), options.delimiter.c_str(), str_times.c_str(), options.delimiter.c_str(), hr.c_str());
			}
			else
			{
				fprintf(fp, "%s%s%s\n", (pair.first).c_str(), options.delimiter.c_str(), str_times.c_str());
			}
		}
	}

	void csv_events(FILE *fp)
	{
		fprintf(fp, "event,begin,end\n");

		std::map<std::string, int> occurrences;

		for (event_t &event : events)
			occurrences[event.name] = 0;

		for (event_t &event : events)
		{
			fprintf(fp, "%s[%d],\"%ld\",\"%ld\"\n", event.name, occurrences[event.name], time_to_long(event.begin), time_to_long(event.end));
			occurrences[event.name] += 1;
		}
		fprintf(fp, ",,\n");
	}

	void events_html_gantt(std::string filename, std::string tablename = "unnamed", std::string path = "")
	{

		if (path == "")
			path = getenv("DLOG_OUTPUT_FOLDER");

		DLOG_TABLE table(filename.c_str(), tablename.c_str(), path);
		std::vector < std::string > head_row;

		head_row.push_back("Event");
		head_row.push_back("Begin");
		head_row.push_back("End");

		std::map<std::string, int> occurrences;

		for (event_t &event : events)
			occurrences[event.name] = 0;

		long min = std::numeric_limits<long>::max();
		for (event_t &event : events)
		{
			long converted= time_to_long(event.begin);
			min = (min< converted)?min:converted;
		}

		std::cout<<"Min "<<min<<"\n";

		for (event_t &event : events)
		{
			std::vector < std::string > row;
			row.push_back(event.name);
			row.push_back(std::to_string( time_to_long(event.begin) - min));
			row.push_back(std::to_string(time_to_long( event.end) - min));
			table.insert_row(row);
			occurrences[event.name] += 1;
		}
		table.table_gantt_dump();
	}

};

#endif /* DLOG_TIMER_HPP_ */
