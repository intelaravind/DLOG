/*
 * mygraph.hpp
 *
 *  Created on: Nov 1, 2013
 *      Author: aravind
 */

#ifndef MYGRAPH_HPP_
#define MYGRAPH_HPP_
#include "debug_common_headers.hpp"
#include "config.h"
#include "DLOG_COMMON.hpp"

struct ARAV_GRAPH_VAL
{
    std::vector<double> values;
    std::vector<std::string> key;
    double total;
};

class aravgraph
{
    std::string ErrorInfo;
    std::string dataPath;
    std::string fileName;
    std::map<std::string, ARAV_GRAPH_VAL> graphs;
    std::map<std::string, std::string> graph_titles;
    int graph_uid;

public:

    aravgraph(const char* in_fileName, const char *path):fileName(in_fileName)
    {

        graph_uid = 0;
        dataPath = DLOG_NS::get_path(path);
        std::string syscall = "rm -rf " + dataPath + "/*";
        DLOG_NS::sys_call(syscall);
    }

    int newgraph(const char *name, const char *title)
    {

        ARAV_GRAPH_VAL tempgraph;
        graphs[name]= tempgraph;
        graph_titles[name] = title;
        return graph_uid++;
    }

    void insertval(const char* graphid, double val, const char *key)
    {
        ARAV_GRAPH_VAL *temp = &graphs[graphid];
        temp->values.push_back(val);
        temp->key.push_back(key);
        temp->total += val;
    }

    ~aravgraph()
    {

        int i;
        std::fstream fwrite;
        fwrite.open(dataPath + "/" + fileName, std::fstream::out);

        fwrite
                << "<html>	<head>	<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
                "<title>DLOG graph</title>\n"
                "<script type='text/javascript' src='js/jquery-2.0.3.min.js'></script>\n"
                "<script type='text/javascript' src='js/highcharts.js'></script>\n"
                "<script type='text/javascript' src='js/modules/exporting.js'></script>\n";

        fwrite << "<script type=\"text/javascript\">\n"
               "$(function () {\n";
        
	fwrite << "$(document).ready(function () {\n";

        for (auto temp_graph_couple : graphs)
        {

            fwrite << " $('#container" << DLOG_NS::strip_space(temp_graph_couple.first.c_str()) << "').highcharts({";

            fwrite << "            chart: {"
                   "plotBackgroundColor: null,"
                   "plotBorderWidth: null,"
                   "plotShadow: false"
                   " },"
                   " title: {"
                   "text: '" << graph_titles[temp_graph_couple.first]
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
                   " name: '" << temp_graph_couple.first << "',"
                   << "data: [\n";

            ARAV_GRAPH_VAL *temp_graph = &temp_graph_couple.second;

            if (temp_graph == NULL)
            {
                std::cout << "ERROR: GRAPH NULL\n";
                exit(1);
            }

            for (unsigned int j = 0; j < temp_graph->values.size(); j++)
            {

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

	for (auto temp_graph_couple : graphs)
        {
            fwrite << "<div id=\"container" << DLOG_NS::strip_space(temp_graph_couple.first.c_str())
                   << "\"style=\"width: 310px; height: 400px; margin: 0 auto\"></div>";
        }

        fwrite << "	</body></html>\n";

        fwrite.close();


        std::string syscommand = "ln -sfF " SRC_PATH "/js " + dataPath;
        DLOG_NS::sys_call(syscommand);
    }
};






#endif /* MYGRAPH_HPP_ */

