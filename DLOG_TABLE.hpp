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

#define NOHOLD 0
#define HOLD 1

typedef std::vector<std::string> t_row;

class DLOG_TABLE
{

	std::set<std::string> set_table_col;
	std::set<std::string> set_table_row;
	std::string dataPath;
	int finalizer;

public:
	std::vector<std::string> table_head_row;
	std::vector<std::string> table_head_column;
	std::vector<t_row> values;
	std::string table_name;
	int cur_row = 0;
	void table_dump();
	void table_html_dump();

	DLOG_TABLE(const char *OUT_FILE, int finalizer, std::string inpPath =
			getenv("DLOG_OUTPUT_FOLDER"))
	{
		DLOG_TABLE::finalizer = finalizer;
		dataPath = inpPath + std::string(OUT_FILE);
	}

	void insert_head_row(std::vector<std::string> &inp)
	{
		for (auto iter : inp)
		{
			table_head_row.push_back(iter);
			set_table_row.insert(iter);
		}
	}
	void insert_row(std::vector<std::string> &inp)
	{
		t_row temp_values;
		int i = 0;
		for (auto iter : inp)
		{
			if (i == 0)
			{
				table_head_column.push_back(iter);
				set_table_col.insert(iter);
				i++;
			}
			else
			{
				temp_values.push_back(iter);
			}
		}
		values.push_back(temp_values);
	}

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

void table_html_header(std::fstream &fwrite)
{
	fwrite
			<< "<head>\n"
					"<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n"
					"<title>DLOG TABLE</title>\n"
					"<link rel=\"stylesheet\" href=\"tinytable/style.css\" />\n"
					"</head>\n"
					"<body>\n";
}

void table_html_footer(std::fstream &fwrite, std::string table_name)
{
	fwrite
			<< "<script type=\"text/javascript\" src=\"tinytable/script.js\"></script>\n"
					"<script type=\"text/javascript\">\n"
					"var sorter = new TINY.table.sorter(\"sorter\");\n"
					"sorter.head = \"head\";\n"
					"sorter.asc = \"asc\";\n"
					"sorter.desc = \"desc\";\n"
					"sorter.even = \"evenrow\";\n"
					"sorter.odd = \"oddrow\";\n"
					"sorter.evensel = \"evenselected\";\n"
					"sorter.oddsel = \"oddselected\";\n"
					"sorter.paginate = false;\n"
					"sorter.currentid = \"currentpage\";\n"
					"sorter.limitid = \"pagelimit\";\n"
					"sorter.init(\"" << table_name << "\",1);\n"
			"</script>\n"
			"</body>\n"
			"</html>\n";
}

void DLOG_TABLE::table_html_dump()
{
	std::fstream fwrite;
	fwrite.open(dataPath.c_str(), std::fstream::out);

	fwrite << "<h1>Table: " << table_name << "</h1>" << "\n";

	unsigned int n_cols = table_head_row.size();
	unsigned int n_rows = table_head_column.size();
	int i, j;

	if (finalizer == 0)
	{
		table_html_header(fwrite);
	}

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

	if (finalizer == 0)
	{
		table_html_footer(fwrite, table_name);
	}
	fwrite.close();

	std::string syscommand;
		//copy the recovery script
		unsigned found = dataPath.find_last_of("/\\");
		syscommand = "cp -r $DLOG_PATH/tinytable " + dataPath.substr(0, found);
		int status = system(syscommand.c_str());
		if (status < 0)
			std::cout << "DLOG Table Error: " << strerror(errno) << '\n';
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
