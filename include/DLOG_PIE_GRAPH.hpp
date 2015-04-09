/*
 * DLOG_PIE_GRAPH.hpp
 *
 *  Created on: Nov 1, 2013
 *      Author: aravind
 */

#ifndef DLOG_PIE_GRAPH_HPP_
#define DLOG_PIE_GRAPH_HPP_

#include "mygraph.hpp"

/**
 * Just a wrapper
 */
class DLOG_PIE_GRAPH
{
	aravgraph* graph;
public:
	DLOG_PIE_GRAPH(const char *PATH)
	{
		graph = new aravgraph(PATH);
	}

	int dlog_add_graph(const char * name, const char *title)
	{
		return graph->newgraph(name, title);

	}

	void dlog_insert_val(int graphid, double val, const char *key)
	{
		graph->insertval(graphid, val, key);
	}
	~DLOG_PIE_GRAPH()
	{
		delete graph;
	}
};







#endif /* DLOG_PIE_GRAPH_HPP_ */
