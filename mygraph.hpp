/*
 * mygraph.hpp
 *
 *  Created on: Nov 1, 2013
 *      Author: aravind
 */

#ifndef MYGRAPH_HPP_
#define MYGRAPH_HPP_
#include "debug_common_headers.hpp"

struct ARAV_GRAPH_VAL {
	std::vector<double> values;
	std::vector<std::string> key;
	double total;
};

class aravgraph {
	std::string ErrorInfo;
	std::string dataPath;
	std::string datatempPath;
	std::vector<ARAV_GRAPH_VAL> graphs;
	std::vector<std::string> graph_names;
	std::vector<std::string> graph_titles;
	int graph_uid;

public:

	aravgraph(const char *PATH) {

		graph_uid = 0;
		dataPath = getenv("DLOG_OUTPUT_FOLDER") + std::string(PATH);
		datatempPath = dataPath + ".temp";

		std::string syscall = "rm -f " + dataPath;
		int status = system(syscall.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';

	}

	int newgraph(const char * name, const char *title) {

		ARAV_GRAPH_VAL tempgraph;
		graphs.push_back(tempgraph);
		graph_names.push_back(name);
		graph_titles.push_back(title);
		return graph_uid++;
	}

	void insertval(int graphid, double val, const char *key) {
		ARAV_GRAPH_VAL *temp = &graphs[graphid];
		temp->values.push_back(val);
		temp->key.push_back(key);
		temp->total += val;
	}

	~aravgraph() {

		int i;
		std::fstream fwrite;
		fwrite.open(dataPath.c_str(), std::fstream::out);

		fwrite
				<< "<html>	<head>	<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
						"<title>DLOG graph</title>\n"
						"<script type='text/javascript' src='js/jquery-2.0.3.min.js'></script>\n"
						"<script type='text/javascript' src='js/highcharts.js'></script>\n"
						"<script type='text/javascript' src='js/modules/exporting.js'></script>\n";

		fwrite << "<script type=\"text/javascript\">\n"
				"$(function () {\n";

		for (i = 0; i < graph_uid; i++) {
			fwrite << "var chart" << i << ";\n";
		}
		fwrite << "$(document).ready(function () {\n";

		for (i = 0; i < graph_uid; i++) {

			fwrite << " $('#container" << i << "').highcharts({";

			fwrite << "            chart: {"
					"plotBackgroundColor: null,"
					"plotBorderWidth: null,"
					"plotShadow: false"
					" },"
					" title: {"
					"text: '" << graph_titles[i].c_str()
					<< "'"
							"},"
							" tooltip: {"
							" pointFormat: '{series.name}: <b>{point.percentage:.1f}%</b>'"
							"},"
							"plotOptions: {"
							" pie: {"
							"allowPointSelect: true,"
							"cursor: 'pointer',"
							"dataLabels: {"
							"enabled: false"
							"},"
							"showInLegend: true"
							"}"
							"},"
							"series: [{"
							"type: 'pie',"
							" name: '" << graph_names[i].c_str() << "',"
					<< "data: [\n";

			ARAV_GRAPH_VAL *temp_graph = &graphs[i];

			if (temp_graph == NULL) {
				std::cout << "ERROR: GRAPH NULL\n";
				exit(1);
			}

			for (unsigned int j = 0; j < temp_graph->values.size(); j++) {

				char tempformater[20];
				sprintf(tempformater, "%.1f", temp_graph->values[j]);

				fwrite << "['" << temp_graph->key[j] << "',";
				fwrite << tempformater;
				fwrite << "],\n";

			}

			fwrite << "]}]});\n";

		}

		fwrite << "});});\n";

		fwrite << "	</script>"
				"</head>"
				"<body>";

		for (i = 0; i < graph_uid; i++) {
			fwrite << "<div id=\"container" << i
					<< "\"style=\"width: 310px; height: 400px; margin: 0 auto\"></div>";
		}

		fwrite << "	</body></html>\n";

		fwrite.close();

		int status;
		std::string syscommand;
		unsigned found = datatempPath.find_last_of("/\\");

		syscommand = "cp -r $DLOG_PATH/js "
				+ datatempPath.substr(0, found);
		status = system(syscommand.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';

	}
};






#endif /* MYGRAPH_HPP_ */
