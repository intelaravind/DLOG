/*
 * DLOG_TIMED_PIE_GRAPH.hpp
 *
 *  Created on: Nov 8, 2013
 *      Author: Aravind
 */

#ifndef DLOG_TIMED_PIE_GRAPH_HPP_
#define DLOG_TIMED_PIE_GRAPH_HPP_

#include "DLOG_PIE_GRAPH.hpp"
#include "DLOG_TIMER.hpp"

typedef std::pair<int,int> TID_PAIR;

class DLOG_TIMED_PIE_GRAPH
{
	DLOG_PIE_GRAPH *pie_graph;
	std::vector<DLOG_TIMER> timer;
	std::vector<std::string> items;

public:

	DLOG_TIMED_PIE_GRAPH(const char *PATH)
	{
		pie_graph = new DLOG_PIE_GRAPH(PATH);
	}

	int newgraph(const char * name, const char *title)
	{
		DLOG_TIMER temp;
		timer.push_back(temp);
		return pie_graph->dlog_add_graph(name, title);
	}

	TID_PAIR start_new(int graph_id, const char* item)
	{
		items.push_back(std::string(item));
		int tempid= timer[graph_id].start_new();
		return TID_PAIR(graph_id,tempid);
	}
	long int stop(TID_PAIR id)
	{

		int graph_id = id.first;
		int timer_id = id.second;
		long int time = timer[graph_id].stop(timer_id);

		pie_graph->dlog_insert_val(graph_id, time, items[timer_id].c_str());
		return time;
	}
	long int reset(TID_PAIR id)
	{
		int graph_id = id.first;
		int timer_id = id.second;
		timer[graph_id].reset(timer_id);
	}
	~DLOG_TIMED_PIE_GRAPH()
	{
		delete pie_graph;
	}
};

#endif /* DLOG_TIMED_PIE_GRAPH_HPP_ */
