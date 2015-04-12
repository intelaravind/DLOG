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


class DLOG_TIMED_PIE_GRAPH
{
    DLOG_PIE_GRAPH *pie_graph;
    std::map<std::string, DLOG_TIMER*> timer_list;

public:

    DLOG_TIMED_PIE_GRAPH(const char *fileName, const char *path = getenv("DLOG_OUTPUT_FOLDER"))
    {
        pie_graph = new DLOG_PIE_GRAPH(fileName, path);
    }

    void newgraph(const char *name, const char *title = "")
    {
        timer_list[name] = new DLOG_TIMER();
	pie_graph->dlog_add_graph(name, title);
    }

    void start(const char* graph_id, const char* item)
    {
        if(timer_list.find(graph_id) != timer_list.end())
        {
            timer_list[graph_id]->start(item);
        }
        else
        {
            std::cerr << "DLOG(ERROR) : Unknown graph id!!!\n";
        }
    }
    void stop(const char* graph_id, const char* timer_id)
    {
        timer_list[graph_id]->stop(timer_id);
    }
    void reset(const char* graph_id, const char* timer_id)
    {
        timer_list[graph_id]->reset();
    }
    ~DLOG_TIMED_PIE_GRAPH()
    {
        for(auto items : timer_list)
        {
	    auto time_list = items.second->get_cummulative_times();
	    
	    for(auto single_timer_item : time_list)
	    {
		pie_graph->dlog_insert_val(items.first.c_str(), single_timer_item.second , single_timer_item.first.c_str());
	    }

            delete items.second;
        }
        delete pie_graph;
    }
};

#endif /* DLOG_TIMED_PIE_GRAPH_HPP_ */

