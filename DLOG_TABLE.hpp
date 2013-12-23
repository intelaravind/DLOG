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

typedef std::vector<double> t_row;

class DLOG_TABLE
{

	std::set<std::string> set_table_col;
	std::set<std::string> set_table_row;

public:
	std::vector<std::string> table_head_row;
	std::vector<std::string> table_head_column;
	std::vector<t_row> values;
	std::string table_name;
	int cur_row = 0;
	void table_dump();
	void table_html_dump();
	void insert_in_head_row(std::string inp)
	{
		if (set_table_row.find(inp) == set_table_row.end())
		{
			table_head_row.push_back(inp);
			set_table_row.insert(inp);
		}
	}
	void insert_in_head_col(std::string inp)
	{
		if (set_table_col.find(inp) == set_table_col.end())
		{
			table_head_column.push_back(inp);
			set_table_col.insert(inp);
		}

	}
};

void DLOG_TABLE::table_html_dump()
{
	std::fstream fwrite;
	fwrite.open("testtable.html", std::fstream::out);
	fwrite << "<h1>Table: " << table_name << "</h1>" << "\n";

	unsigned int n_cols = table_head_row.size();
	unsigned int n_rows = table_head_column.size();
	int i, j;

	fwrite << "<table cellpadding=\"0\" cellspacing=\"0\" border=\"0\" id=\""
			<< table_name << "\" class=\"sortable\">\n";

	fwrite << "<thead><tr>" << "\n";
	for (i = 0; i < n_cols; i++)
	{
		fwrite << "<th><h3>";
		fwrite << table_head_row.at(i);
		fwrite << "</h3></th>\n";
	}
	fwrite << "</tr></thead>" << "\n";

	fwrite << "<body>" << "\n";

	for (i = 0; i < n_rows; i++)
	{
		fwrite << "<tr>" << "\n";
		fwrite << "<td>";
		fwrite << table_head_column.at(i);
		fwrite << "</td>" << "\n";
		t_row *row = &values.at(i);
		for (j = 0; j < row->size(); j++)
		{
			fwrite << "<td>";
			fwrite << row->at(j);
			fwrite << "</td>" "\n";
		}
		fwrite << "</tr>" << "\n";
	}
	fwrite << "</body>" << "\n";
	fwrite << "</table>";
	fwrite.close();
}

void DLOG_TABLE::table_dump()
{
	std::cout << "Table: " << table_name << "\n";
	unsigned int n_cols = table_head_row.size();
	unsigned int n_rows = table_head_column.size();
	int i, j;

	for (i = 0; i < n_cols; i++)
	{
		std::cout << table_head_row.at(i) << "\t\t";
	}

	std::cout << "\n";

	for (i = 0; i < n_rows; i++)
	{
		std::cout << table_head_column.at(i) << "\t\t";
		t_row *row = &values.at(i);
		for (j = 0; j < row->size(); j++)
		{
			std::cout << row->at(j) << "\t\t";
		}
		std::cout << "\n";
	}
	std::cout << "\n\n";
}

#endif /* DLOG_TABLE_HPP_ */
