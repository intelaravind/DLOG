/**
 * Author aravind
 * @brief slightly advanced timed graph with more than one graph per page
 */

//compile with -lrt flag
#include "../DLOG_TIMED_PIE_GRAPH.hpp"

int main()
{
	DLOG_TIMED_PIE_GRAPH testgraph("APOLLO_test_timed_graph_adv.html");

	int graph_id = testgraph.newgraph("graph1", "just testing graph1 pie");

	int graph_id2 = testgraph.newgraph("graph2", "just testing graph1 pie");

	TID_PAIR t1, t2, t3, t4, t5;

	t4 = testgraph.start_new(graph_id2, "super Full");
	t1 = testgraph.start_new(graph_id, "Full");
	t2 = testgraph.start_new(graph_id, "first");
	sleep(2);
	testgraph.stop(t2);
	t3 = testgraph.start_new(graph_id, "second");
	sleep(3);
	testgraph.stop(t3);
	testgraph.stop(t1);

	t5 = testgraph.start_new(graph_id2, "super small");
	sleep(1);
	testgraph.stop(t5);

	testgraph.stop(t4);

	//the second graph

	return 0;
}
