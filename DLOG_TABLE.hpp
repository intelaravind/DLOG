/*
 * DLOG_TABLE.hpp
 *
 *  Created on: Dec 23, 2013
 *      Author: aravind
 */

#ifndef DLOG_TABLE_HPP_
#define DLOG_TABLE_HPP_

#include "debug_common_headers.hpp"
#include "DLOG_HELPER.hpp"
#include <boost/regex.hpp>

#define NOHOLD 0
#define HOLD 1

typedef std::vector<std::string> t_row;

std::string filter_string(std::string inp)
{
	std::string output = "";
	for (auto ch : inp)
	{
		if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')
				|| (ch >= '0' && ch <= '9'))
			output = output + ch;
	}
	return output;
}

class DLOG_TABLE
{

	std::string dataPath;

public:
	std::vector<std::string> table_head_row;
	std::vector<std::string> table_head_column;
	std::vector<t_row> values;
	std::string table_name;
	int cur_row = 0;
	int drawGraph = 0;
	void table_dump();
	void table_html_dump();
	void table_html_dump_unwrap(std::fstream &, int);
	void table_emit_graph_javascript(std::fstream &);
	void table_emit_graph_div(std::fstream &);

	DLOG_TABLE(const char *OUT_FILE, const char *tbl_name, std::string inpPath =
			getenv("DLOG_OUTPUT_FOLDER"))
	{
		dataPath = inpPath + std::string(OUT_FILE);
		table_name = tbl_name;
	}

	void insert_row(std::vector<std::string> &inp)
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

//	void insert_in_head_row(std::string inp)
//	{
//		if (set_table_row.find(inp) == set_table_row.end())
//		{
//			table_head_row.push_back(inp);
//			set_table_row.insert(inp);
//		}
//	}
//	void insert_in_head_col(std::string inp)
//	{
//		if (set_table_col.find(inp) == set_table_col.end())
//		{
//			table_head_column.push_back(inp);
//			set_table_col.insert(inp);
//		}
//
//	}
};

void table_html_header(std::fstream &fwrite)
{
	fwrite
			<< "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
					"<html>\n"
					"<head>\n"
					"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
					"<title>DLOG TABLE</title>\n"
					"<link rel=\"stylesheet\" href=\"tinytable/style.css\" />\n"
					"<script type='text/javascript' src='js/jquery-2.0.3.min.js'></script>\n"
					"<script type='text/javascript' src='js/highcharts.js'></script>\n"
					"<script type='text/javascript' src='js/modules/exporting.js'></script>\n";
}

void table_html_header_end(std::fstream &fwrite)
{
	fwrite << "</head>\n"
			"<body>\n";
}

void table_html_footer(std::fstream &fwrite,
		std::vector<std::string> table_name)
{
	fwrite
			<< "<script type=\"text/javascript\" src=\"tinytable/script.js\"></script>\n"
					"<script type=\"text/javascript\">\n";

	for (auto names : table_name)
	{
		std::string name = filter_string(names);
		fwrite << "var " << name << "sorter = new TINY.table.sorter(\"" << name
				<< "sorter\");\n" << name << "sorter.head = \"head\";\n" << name
				<< "sorter.asc = \"asc\";\n" << name
				<< "sorter.desc = \"desc\";\n" << name
				<< "sorter.even = \"evenrow\";\n" << name
				<< "sorter.odd = \"oddrow\";\n" << name
				<< "sorter.evensel = \"evenselected\";\n" << name
				<< "sorter.oddsel = \"oddselected\";\n" << name
				<< "sorter.paginate = false;\n" << name
				<< "sorter.currentid = \"currentpage\";\n" << name
				<< "sorter.limitid = \"pagelimit\";\n";

		fwrite << name << "sorter.init(\"" << name << "\",1);\n";

		fwrite << "\n";
	}
	fwrite << "</script>\n"
			"</body>\n"
			"</html>\n";

}

void DLOG_TABLE::table_emit_graph_div(std::fstream &fwrite)
{
	fwrite << "<div id=\"container" << filter_string(table_name)
			<< "\" style=\"max-width: 1024px; height: 400px; margin: 0 auto\"></div>\n";
}

void DLOG_TABLE::table_emit_graph_javascript(std::fstream &fwrite)
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

	//The column is item (this is not a category. So skip it.
	int isfirst = 1;
	for (auto temphead : values.at(0))
	{
		if (isfirst == 1)
			isfirst = 0;
		else
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

	int rowindex = 0;
	for (auto temprow : values)
	{
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

void DLOG_TABLE::table_html_dump_unwrap(std::fstream &fwrite, int hold)
{

	fwrite << "<h1>Table: " << table_name << "</h1>" << "\n";

	unsigned int n_cols = (values.at(0)).size();
	unsigned int n_rows = values.size();
	int i, j;

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

void DLOG_TABLE::table_html_dump()
{
	std::fstream fwrite;
	fwrite.open(dataPath.c_str(), std::fstream::out);
	table_html_dump_unwrap(fwrite, NOHOLD);
}

void DLOG_TABLE::table_dump()
{
	std::cout << "Table: " << table_name << "\n";
	unsigned int n_cols = (values.at(0)).size();
	unsigned int n_rows = values.size();
	int i, j;

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
typedef int TID;
class DLOG_TABLES
{
	std::vector<DLOG_TABLE> tables;
	std::vector<int> header_row_populated;
	std::string dataPath;

public:
	DLOG_TABLES(const char *OUT_FILE,
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

		DLOG_TABLE *temptable = new DLOG_TABLE(dataPath.c_str(), tablename);
		tables.push_back(*temptable);
		header_row_populated.push_back(0);
		return TID(tables.size() - 1);
		return 0;
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
		fwrite.open(dataPath.c_str(), std::fstream::out);

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
		std::vector<std::string> names;
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
