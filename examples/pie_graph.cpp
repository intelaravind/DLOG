/**
 * Author aravind
 */


#include "DLOG_PIE_GRAPH.hpp"

int main() {
	DLOG_PIE_GRAPH testgraph("APOLLO_test_graph.html");
	int graph_id = testgraph.dlog_add_graph("graph1",
			"just testing graph1 pie");

	testgraph.dlog_insert_val(graph_id, 10, "v1");
	testgraph.dlog_insert_val(graph_id, 20, "v2");
	testgraph.dlog_insert_val(graph_id, 30, "v3");

	int graph_id2 = testgraph.dlog_add_graph("second graph",
			"graph2 on same page");

	testgraph.dlog_insert_val(graph_id2, 10, "v11");
	testgraph.dlog_insert_val(graph_id2, 20, "v12");
	testgraph.dlog_insert_val(graph_id2, 30, "v13");
	testgraph.dlog_insert_val(graph_id2, 40, "v13");
	
	return 0;
}
