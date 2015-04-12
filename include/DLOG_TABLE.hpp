/*
 * DLOG_TABLE.hpp
 *
 *  Created on: Dec 23, 2013
 *      Author: aravind
 */

#ifndef DLOG_TABLE_HPP_
#define DLOG_TABLE_HPP_

#include "DLOG_HELPER.hpp"
#include "DLOG_TABLE_COMMON.hpp"
#include "config.h"
#include "DLOG_COMMON.hpp"

typedef std::vector<std::string> t_row;

class DLOG_TABLE
{

    std::string dataPath;
    std::string outputfilename;

public:
    std::vector<std::string> table_head_row;
    std::vector<std::string> table_head_column;
    std::vector<t_row> values;
    std::string table_name;
    int cur_row = 0;
    int drawGraph = 0;

    DLOG_TABLE(const char *OUT_FILE, const char *tbl_name, const char *inpPath = getenv("DLOG_OUTPUT_FOLDER"))
    {
        dataPath = DLOG_NS::get_path(inpPath);
        table_name = tbl_name;
        outputfilename = OUT_FILE;
    }

    void insert_row(std::vector<std::string> inp)
    {
        t_row temp_values;

        for (auto iter : inp)
        {
            temp_values.push_back(iter);
        }
        values.push_back(temp_values);
    }

    void insert_head_row(std::vector<std::string> &inp)
    {
        t_row temp_values;
        for (auto iter : inp)
        {
            temp_values.push_back(iter);
        }
        values.insert(values.begin(), temp_values);
    }

    void table_emit_graph_div(std::fstream &fwrite)
    {
        fwrite << "<div id=\"container" << filter_string(table_name) << "\" style=\"max-width: 1024px; height: 400px; margin: 0 auto\"></div>\n";
    }

    void table_emit_graph_javascript(std::fstream &fwrite)
    {
        fwrite << "<script type=\"text/javascript\">\n"
               "(function($){\n"
               "$(function () {\n"
               "$('#" << "container" << filter_string(table_name) << "').highcharts({\n"
               "chart: {\n"
               "type: 'column',\n"
               "zoomType: 'xy'\n"
               "},\n"
               "title: {"
               "text: '" << table_name << "'\n"
               " },\n"
               "xAxis: {\n"
               "categories: [\n";

        //The first column is item (this is not a category. So skip it.
        int isfirst = 1;
        for (auto temphead : values.at(0))
        {
            if (isfirst == 1)
                isfirst = 0;
            else
                fwrite << "'" << temphead << "',\n";
        }
        fwrite << "]\n"
               "},\n"
               "yAxis:\n"
               "{\n"
               "min: 0,\n"
               "title:\n"
               "{\n"
               "text: 'params'\n"
               "}\n"
               "},\n"
               "tooltip: {\n"
               "},\n"
               "plotOptions:\n"
               "{\n"
               "	column:\n"
               "	{\n"
               "		pointPadding: 0.2,\n"
               "		borderWidth: 0\n"
               "	}\n"
               "},\n"
               "series: [\n";

        int rowindex = 0;
        for (auto temprow : values)
        {
            //skip first row because its the header row
            if (temprow == values.at(0))
                continue;
            fwrite << "{\n";
            int isfirst = 1;
            for (auto temval : temprow)
            {
                if (isfirst == 1)
                {
                    fwrite << "name: '" << temval << "', data\n: [";
                    isfirst = 0;
                    rowindex++;
                }
                else
                    fwrite << temval << ",";
            }

            fwrite << "]},\n";
        }

        fwrite << "]});\n"
               "});\n"
               "})(jQuery);\n"
               "</script>";
    }

    void table_html_dump_unwrap(std::fstream &fwrite, int hold)
    {

        fwrite << "<h1>Table: " << table_name << "</h1>" << "\n";

        unsigned int n_cols = (values.at(0)).size();
        unsigned int n_rows = values.size();
        unsigned int i, j;

        if (hold == 0)
        {
            table_html_header(fwrite);
            if (drawGraph == 1)
            {
                table_emit_graph_javascript(fwrite);
            }
            table_html_header_end(fwrite);
        }

        fwrite << "<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" id=\"" << filter_string(table_name) << "\" class=\"sortable\">\n";

        fwrite << "<thead><tr>" << "\n";
        for (i = 0; i < n_cols; i++)
        {
            fwrite << "<th><h3>";
            fwrite << (values.at(0)).at(i);
            fwrite << "</h3></th>\n";
        }
        fwrite << "</tr></thead>" << "\n";

        for (i = 1; i < n_rows; i++)
        {
            fwrite << "<tr>" << "\n";
            t_row *row = &values.at(i);
            for (j = 0; j < row->size(); j++)
            {
                fwrite << "<td>";
                fwrite << row->at(j);
                fwrite << "</td>" "\n";
            }
            fwrite << "</tr>" << "\n";
        }
        fwrite << "</table>\n";

        if (hold == 0)
        {
            if (drawGraph == 1)
            {
                table_emit_graph_div(fwrite);
            }
            std::vector < std::string > tempvec;
            tempvec.push_back(table_name);
            table_html_footer(fwrite, tempvec);

            fwrite.close();
        }

	DLOG_NS::sys_call("ln -sfF " SRC_PATH"/tinytable " +  dataPath, DLOG_NS::MSG_LEVEL::quite );
	DLOG_NS::sys_call("ln -sfF " SRC_PATH"/js " +  dataPath, DLOG_NS::MSG_LEVEL::quite );
    }

    void table_html_dump()
    {
        std::fstream fwrite;

        std::string fullpath = dataPath + "/" + outputfilename;
        //std::cerr<<"************fullpath = "<<fullpath<<"\n";
        fwrite.open(fullpath.c_str(), std::fstream::out);
        table_html_dump_unwrap(fwrite, NOHOLD);
    }

    void table_gantt_dump()
    {
        std::fstream fwrite;
        std::string fullpath = dataPath + "/" + outputfilename;
        fwrite.open(fullpath.c_str(), std::fstream::out);

        fwrite << R"(
    <html>
    <head>
    <script type="text/javascript" src="https://www.google.com/jsapi"></script>
    <script type="text/javascript">
      google.load("visualization", "1", {packages:["timeline"]});
      google.setOnLoadCallback(drawChart);

      function drawChart() {
        var container = document.getElementById('timeline');
        var chart = new google.visualization.Timeline(container);
        var dataTable = new google.visualization.DataTable();)";

        fwrite << "\n" << R"(
        dataTable.addColumn({ type: 'string', id: 'Info' });
        dataTable.addColumn({ type: 'string', id: 'Event' });
        dataTable.addColumn({ type: 'number', id: 'Start' });
        dataTable.addColumn({ type: 'number', id: 'End' });)" << "\n";

        unsigned int n_rows = values.size();

        fwrite << "dataTable.addRows([";
        for (unsigned int i = 0; i < n_rows; i++)
        {
            t_row *row = &values.at(i);
            fwrite << "[ '" << row->at(1) << "', '" << row->at(0) << "', " << row->at(2) << ", " << row->at(3) << "],\n";
        }
        fwrite << "]);\n";
        fwrite << R"(  var options = {
timeline: {colorByRowLabel: true, showBarLabels: false}
	  };)" << "\n";
        fwrite << R"(chart.draw(dataTable,options);
      }
    </script>
    </head>
      <body>
        <div id="timeline" style="width: 1024px; height: 1024px;"></div>
      </body>
    </html>)";

        fwrite.close();

    }

    void table_dump()
    {
        std::cout << "Table: " << table_name << "\n";
//	unsigned int n_cols = (values.at(0)).size();
        unsigned int n_rows = values.size();
        unsigned int i, j;

        for (i = 0; i < n_rows; i++)
        {
            t_row *row = &values.at(i);
            for (j = 0; j < row->size(); j++)
            {
                std::cout << row->at(j) << "\t\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
};

class DLOG_TABLES
{
    std::vector<DLOG_TABLE> tables;
    std::vector<int> header_row_populated;
    std::string dataPath;
    std::string outFile;

public:
    DLOG_TABLES(const char *OUT_FILE, const char* inpPath = getenv("DLOG_OUTPUT_FOLDER")) : outFile(OUT_FILE)
    {

        dataPath = DLOG_NS::get_path(inpPath);
    }

    void show_graph(TID tid)
    {
        tables.at(tid).drawGraph = 1;
    }

    TID newtable(const char *tablename)
    {

        DLOG_TABLE *temptable = new DLOG_TABLE(outFile.c_str(), tablename, dataPath.c_str());
        tables.push_back(*temptable);
        header_row_populated.push_back(0);
        return TID(tables.size() - 1);
    }

    void insert_head_row(TID tid, std::vector<std::string> &inp)
    {
        if (header_row_populated[tid] == 0)
        {
            tables.at(tid).insert_head_row(inp);
            header_row_populated[tid] = 1;
        }
    }

    void insert_row(TID tid, std::vector<std::string> &inp)
    {
        tables.at(tid).insert_row(inp);
    }

    void html_dump()
    {
        std::fstream fwrite;
        fwrite.open(dataPath + "/" + outFile , std::fstream::out);

        table_html_header(fwrite);
        for (auto temptable : tables)
        {
            if (temptable.values.size() == 0)
                continue;
            else if (temptable.drawGraph == 1)
            {
                temptable.table_emit_graph_javascript(fwrite);
            }
        }

        table_html_header_end(fwrite);
        std::vector < std::string > names;

        for (auto temptable : tables)
        {
            if (temptable.values.size() == 0)
                continue;
            else
            {
                names.push_back(temptable.table_name);
                temptable.table_html_dump_unwrap(fwrite, HOLD);
                if (temptable.drawGraph == 1)
                {
                    temptable.table_emit_graph_div(fwrite);
                }
            }
        }

        table_html_footer(fwrite, names);

    }

};

#endif /* DLOG_TABLE_HPP_ */
