/*
 * DLOG_TIMER.hpp
 *
 *  Created on: Nov 8, 2013
 *      Author: aravind
 */

#ifndef DLOG_TIMER_HPP_
#define DLOG_TIMER_HPP_
#include "debug_common_headers.hpp"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
class DLOG_TIMER
{
	std::vector<struct timespec> start_list;
	int length;
public:
	DLOG_TIMER()
	{
		length = 0;
	}
	int start_new()
	{
		struct timespec start;
		if (clock_gettime( CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit( EXIT_FAILURE);
		}
		start_list.push_back(start);
		return length++;
	}
	long int stop(int id)
	{
		struct timespec stop;
		if (clock_gettime( CLOCK_REALTIME, &stop) == -1)
		{
			perror("clock gettime");
			exit( EXIT_FAILURE);
		}

		return 1000000000 * ( stop.tv_sec - start_list[id].tv_sec ) + (stop.tv_nsec - start_list[id].tv_nsec);
	}

	void reset(int id)
	{
		struct timespec start;
		if (clock_gettime( CLOCK_REALTIME, &start) == -1)
		{
			perror("clock gettime");
			exit( EXIT_FAILURE);
		}
		start_list[id]=start;
	}
};

#endif /* DLOG_TIMER_HPP_ */
