/**
 * Author aravind
 * @brief a simple test timed pie chart with only one chart
 */

//compile with -lrt flag
#include "DLOG_TIMED_PIE_GRAPH.hpp"

int main()
{
	DLOG_TIMED_PIE_GRAPH testgraph("APOLLO_test_timed_graph.html");

	testgraph.newgraph("graph1", "just testing graph1 pie");

	testgraph.start("graph1", "full");
	testgraph.start("graph1", "first");
	sleep(2);
	testgraph.stop("graph1", "first");
	testgraph.start("graph1", "second");
	sleep(3);
	testgraph.stop("graph1", "second");
	testgraph.stop("graph1", "full");

	return 0;
}
