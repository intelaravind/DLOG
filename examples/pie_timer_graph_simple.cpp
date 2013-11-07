/**
 * Author aravind
 * @brief a simple test timed pie chart with only one chart
 */

//compile with -lrt flag
#include "../DLOG_TIMED_PIE_GRAPH.hpp"

int main()
{
	DLOG_TIMED_PIE_GRAPH testgraph("APOLLO_test_timed_graph.html");

	int graph_id = testgraph.newgraph("graph1", "just testing graph1 pie");

	TID t1, t2, t3;

	t1 = testgraph.start_new(graph_id, "Full");
	t2 = testgraph.start_new(graph_id, "first");
	sleep(2);
	testgraph.stop(t2);
	t3 = testgraph.start_new(graph_id, "second");
	sleep(3);
	testgraph.stop(t3);
	testgraph.stop(t1);

	return 0;
}
