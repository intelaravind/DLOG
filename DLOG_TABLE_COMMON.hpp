/*
 * DLOG_TABLE_COMMON.hpp
 *
 *  Created on: Jan 3, 2014
 *      Author: aravind
 */

#ifndef DLOG_TABLE_COMMON_HPP_
#define DLOG_TABLE_COMMON_HPP_

#include "debug_common_headers.hpp"

#define NOHOLD 0
#define HOLD 1
typedef int TID;
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

#endif /* DLOG_TABLE_COMMON_HPP_ */
