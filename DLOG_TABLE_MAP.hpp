/*
 * DLOG_TABLE_MAP.hpp
 *
 *  Created on: Jan 3, 2014
 *      Author: aravind
 */

#ifndef DLOG_TABLE_MAP_HPP_
#define DLOG_TABLE_MAP_HPP_

#include "DLOG_TABLE_COMMON.hpp"
#include "DLOG_HELPER.hpp"

using std::map;
using std::vector;
using std::string;
using std::set;

typedef map<string, string> ROWTYPE;
class DLOG_TABLE_MAP
{

	map<string, ROWTYPE> table;
	std::string dataPath;


public:
	int drawGraph;
	set<string> aggregate_columns;
	std::string table_name;
	DLOG_TABLE_MAP(const char *OUT_FILE, const char *tbl_name,
			std::string inpPath = getenv("DLOG_OUTPUT_FOLDER"))
	{
		dataPath = inpPath + std::string(OUT_FILE);
		table_name = tbl_name;
		drawGraph=0;
	}
	void table_emit_graph_javascript(std::fstream &fwrite);
	void insert_elem(string, string, string);
	void table_map_emit_graph_div(std::fstream &);
	void table_html_dump_unwrap(std::fstream &, int);
	void table_emit_graph_div(std::fstream &fwrite);
	void table_dump();
	void table_html_dump();

};

void DLOG_TABLE_MAP::table_map_emit_graph_div(std::fstream &fwrite)
{
	fwrite << "<div id=\"container" << filter_string(table_name)
			<< "\" style=\"max-width: 1024px; height: 400px; margin: 0 auto\"></div>\n";
}

void DLOG_TABLE_MAP::table_dump()
{

	std::cout << "Table: " << table_name << "\n";

	std::cout << "ROW_ID\t\t";
	for (auto row_head : aggregate_columns)
	{
		std::cout << row_head << "\t\t";
	}
	std::cout << "\n";
	for (auto temp_cur_row : table)
	{
		auto current_row = temp_cur_row.second;
		std::cout << temp_cur_row.first << "\t\t";
		for (auto row_head : aggregate_columns)
		{
			if (current_row.find(row_head) != current_row.end())
			{
				std::cout << current_row.find(row_head)->second << "\t\t";
			}
			else
			{
				std::cout << "NULL\t\t";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";

}

void DLOG_TABLE_MAP::table_emit_graph_javascript(std::fstream &fwrite)
{
	fwrite << "<script type=\"text/javascript\">\n"
			"(function($){\n"
			"$(function () {\n"
			"$('#" << "container" << filter_string(table_name)
			<< "').highcharts({\n"
					"chart: {\n"
					"type: 'column',\n"
					"zoomType: 'xy'\n"
					"},\n"
					"title: {"
					"text: '" << table_name << "'\n"
					" },\n"
					"xAxis: {\n"
					"categories: [\n";

	for (auto temphead : aggregate_columns)
	{
			fwrite << "'" << temphead << "',\n";
	}
	fwrite
			<< "]\n"
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
					"   headerFormat: '<span style=\"font-size:10px\">{point.key}</span><table>',\n"
					"  pointFormat: '<tr><td style=\"color:{series.color};padding:0\">{series.name}: </td>' +\n"
					"     '<td style=\"padding:0\"><b>{point.y:.1f} </b></td></tr>',\n"
					"footerFormat: '</table>',\n"
					"shared: true,\n"
					"useHTML: true\n"
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

	for (auto temp_cur_row : table)
		{
		auto current_row = temp_cur_row.second;
		fwrite << "{\n";
		fwrite << "name: '" << temp_cur_row.first<< "', data\n: [";
		for (auto row_head : aggregate_columns)
		{
			if (current_row.find(row_head) != current_row.end())
			{
				fwrite << current_row.find(row_head)->second<< ",";;
			}
			else
			{
				//value was not populated in table
				fwrite << "-1";
			}
		}

		fwrite << "]},\n";
	}

	fwrite << "]});\n"
			"});\n"
			"})(jQuery);\n"
			"</script>";
}

void DLOG_TABLE_MAP::table_emit_graph_div(std::fstream &fwrite)
{
	fwrite << "<div id=\"container" << filter_string(table_name)
			<< "\" style=\"max-width: 1024px; height: 400px; margin: 0 auto\"></div>\n";
}

void DLOG_TABLE_MAP::table_html_dump_unwrap(std::fstream &fwrite, int hold)
{
	fwrite << "<h1>Table: " << table_name << "</h1>" << "\n";

	if (hold == 0)
	{
		table_html_header(fwrite);
		if (drawGraph == 1)
		{
		table_emit_graph_javascript(fwrite);
		}
		table_html_header_end(fwrite);
	}
	fwrite << "<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" id=\""
			<< filter_string(table_name) << "\" class=\"sortable\">\n";

	fwrite << "<thead><tr>" << "\n";

	fwrite << "<th><h3>ROW_ID</h3></th>\n";
	for (auto row_head : aggregate_columns)
	{
		fwrite << "<th><h3>";
		fwrite << row_head;
		fwrite << "</h3></th>\n";
	}
	fwrite << "</tr></thead>" << "\n";

	for (auto temp_cur_row : table)
	{
		fwrite << "<tr>" << "\n";
		auto current_row = temp_cur_row.second;
		fwrite << "<td>";
		fwrite << temp_cur_row.first;
		fwrite << "</td>" "\n";
		for (auto row_head : aggregate_columns)
		{
			fwrite << "<td>";
			if (current_row.find(row_head) != current_row.end())
			{
				fwrite << current_row.find(row_head)->second;
			}
			else
			{
				fwrite << "NULL";
			}
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
		std::vector<std::string> tempvec;
		tempvec.push_back(table_name);
		table_html_footer(fwrite, tempvec);
		fwrite.close();

	}

	std::string syscommand;
	//copy the recovery script
	unsigned found = dataPath.find_last_of("/\\");
	syscommand = "cp -r $DLOG_PATH/tinytable " + dataPath.substr(0, found);
	int status = system(syscommand.c_str());
	if (status < 0)
		std::cout << "DLOG Table Error: " << strerror(errno) << '\n';

}
void DLOG_TABLE_MAP::table_html_dump()
{

	std::fstream fwrite;
	fwrite.open(dataPath.c_str(), std::fstream::out);

	table_html_dump_unwrap(fwrite, NOHOLD);

}

void DLOG_TABLE_MAP::insert_elem(string row, string column, string value)
{
	aggregate_columns.insert(column);

	//check whether row exist. else insert a new row
	if (table.find(row) == table.end())
	{
		table.insert(std::make_pair(row, ROWTYPE()));
	}

	auto current_row = table.find(row);

	current_row->second.insert(std::make_pair(column, value));

}


class DLOG_TABLES_MAP
{
	std::vector<DLOG_TABLE_MAP> tables;
	std::string dataPath;

public:
	DLOG_TABLES_MAP(const char *OUT_FILE,
			std::string inpPath = getenv("DLOG_OUTPUT_FOLDER"))
	{
		dataPath = inpPath + std::string(OUT_FILE);
	}

	void show_graph(TID tid)
	{
		tables.at(tid).drawGraph = 1;
	}

	TID newtable(const char *tablename)
	{

		DLOG_TABLE_MAP *temptable = new DLOG_TABLE_MAP(dataPath.c_str(), tablename);
		tables.push_back(*temptable);
		return TID(tables.size() - 1);
	}

	void insert_elem(TID tid, string row, string column, string value)
	{
		tables.at(tid).insert_elem(row,column,value);
	}

	void html_dump()
	{
		std::fstream fwrite;
		fwrite.open(dataPath.c_str(), std::fstream::out);

		table_html_header(fwrite);
		for (auto temptable : tables)
		{
			if (temptable.aggregate_columns.size() == 0)
				continue;
			else if (temptable.drawGraph == 1)
			{
				temptable.table_emit_graph_javascript(fwrite);
			}
		}
		table_html_header_end(fwrite);
		std::vector<std::string> names;
		for (auto temptable : tables)
		{
			if (temptable.aggregate_columns.size() == 0)
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

#endif /* DLOG_TABLE_MAP_HPP_ */
