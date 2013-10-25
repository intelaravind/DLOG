DLOG
=====

DLOG LLVM version


Logging and Debugging are essential parts of software development. There are a ton of tools for logging out there in the market. But most of them do lack the ability to handle large projects, or lacks the ability to properly organize the logs. Moreover the output is usually not readable and is not colourised. Wesolve all these problems. Most of the loggers are designed for a single system not for a distributed.

DLOG is designed to solve these problems. It even supports LLVM. You can print anything to the log via a simple print instruction. The logs can be categorized by using "tags". Each log entry contains an optional tag, a message, and an optional addon. The output produced is in HTML format. The system automatically includes the file name and line number which helps in debugging. Moreover the output is colourised and can easily be filtered on the basis of tags. Javascript for this is automatically added. We even support distributed system. Distributed system support is completely optional. Would like to have more features contact us.


Graph Usage Sample
==================

		DLOG_GRAPH testgraph("APOLLO_test_graph.html");
		int graph_id=testgraph.dlog_add_graph("graph1","just testing graph1");

		testgraph.dlog_insert_val(graph_id,10,"v1");
		testgraph.dlog_insert_val(graph_id,20,"v2");
		testgraph.dlog_insert_val(graph_id,30,"v3");


		int graph_id2=testgraph.dlog_add_graph("second graph","graph2 on same page");

		testgraph.dlog_insert_val(graph_id2,10,"v11");
		testgraph.dlog_insert_val(graph_id2,20,"v12");
		testgraph.dlog_insert_val(graph_id2,30,"v13");
		testgraph.dlog_insert_val(graph_id2,40,"v13");
