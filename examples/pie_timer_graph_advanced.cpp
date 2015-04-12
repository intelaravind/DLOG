/**
 * Author aravind
 * @brief slightly advanced timed graph with more than one graph per page
 */

//compile with -lrt flag
#include "DLOG_TIMED_PIE_GRAPH.hpp"

int main()
{
    DLOG_TIMED_PIE_GRAPH testgraph("APOLLO_test_timed_graph_adv.html", "./output");

    testgraph.newgraph("graph1");

    testgraph.newgraph("graph2");

    testgraph.start("graph2", "super full");
    testgraph.start("graph1", "full");
    testgraph.start("graph1", "first");
    sleep(2);
    testgraph.stop("graph1","first");
    testgraph.start("graph1", "second");
    sleep(3);
    testgraph.stop("graph1","second");
    testgraph.stop("graph1","full");

    testgraph.start("graph2", "super small");
    sleep(1);
    testgraph.stop("graph2","super small");

    testgraph.stop("graph2","super full");

    //the second graph

    return 0;
}

