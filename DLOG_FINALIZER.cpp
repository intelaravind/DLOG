/**
 * DLOG_FINALIZER.cpp
 *
 *  Created on: Dec 15, 2013
 *      Author: aravind
 */

#include "DLOG_HELPER.hpp"

int main(int argc, char **argv)
{
	int status;
	std::fstream fwrite;
	std::fstream ftags;

	std::string dataPath(argv[1]);

	std::string datatempPath = dataPath + ".temp";
	std::string tagPath = dataPath + ".tag";

/*	std::cout << dataPath << "\n";
	std::cout << datatempPath << "\n";
	std::cout << tagPath << "\n";*/

	fwrite.open(dataPath.c_str(), std::fstream::out);

	ftags.open(tagPath.c_str(), std::fstream::in);

	fwrite
			<< "<head>\n"
					"<script type='text/javascript' src='js/aravind.js' ></script>\n"
					"<script type='text/javascript' src='js/jquery-2.0.3.min.js'></script>\n";

	fwrite << "<script type=\"text/javascript\">"
			"$(document).ready(function() {"
			"$(\"ar_menu\").click(function(){"
			"$(this).toggleClass(\"active\");"
			"$(this).next(\"div\").stop('true','true').slideToggle(\"500\");"
			"});"
			"});"
			"</script>\n";
	fwrite << "\n</head>\n ";
	fwrite
			<< "<body>\n"
					"<style>div.floating-menu {background:#fff4c8;border:1px solid #ffcc00;width:150px;margin-top:5px;margin-bottom:10px; } "
					"div.floating-menu a, div.floating-menu h3 {display:block;margin:0 0.5em;} </style>";

	fwrite
			<< "<style>"
					"div.floating-container{top:35%;left:75%;position:fixed;z-index:100;}\n"
					"div.floating-container ar_menu:hover{background:#FFFFE0}\n"
					"div.floating-container ar_menu{list-style-type:none; cursor:pointer; border-top:2px solid #666666; border-bottom:2px solid #666666;padding:2px 2px 2px 2px;margin-top:10px;}\n"
					"div.floating-container ar_menu div:hover{text-decoration:none !important;}\n"
					"div.floating-container ar_menu:before {content: \" + \"; \n"
					"padding:0px 5px 1px 5px; color:red; font-weight:bold;background:#4A5A6D}\n"
					"div.floating-container ar_menu.active:before {content: \" - \";\n"
					" padding:0px 5px 1px 5px; color:red; font-weight:bold;background:#4A5A6D}\n"
					".floating-topic{background:#B7B8B5;display: inline-block; width:125px;margin-bottom:5px;}\n"
					"</style>\n";

	fwrite << DIV("floating-container");

	fwrite
			<< "<ar_menu><span class=\"floating-topic\"><b>&nbsp;&nbsp;Extra info</b></span></ar_menu>\n";

	fwrite << "<div class=\"floating-menu\">" << CHKBOX("CALLINFO") << EDIV;

	//for avoiding collapsing problem
	fwrite << DIV("") << EDIV;

	//tags begin here
	fwrite
			<< "<ar_menu><span class=\"floating-topic\"><b>&nbsp;&nbsp;Tags</b></span></ar_menu>\n";

	fwrite << "<div class=\"floating-menu\">";

	//going to add tags
	std::string line;
	while (!ftags.eof())
	{
//		std::cout << line << "\n";
		getline(ftags, line);
		fwrite << line << '\n';
	}
	//end going to add tags

	fwrite
			<< "<input id=\"clickMe\" type=\"button\" value=\"ALL\" onclick=\"toggle_chk_true(this);\" />\n";

	fwrite
			<< "<input id=\"clickMe\" type=\"button\" value=\"NONE\" onclick=\"toggle_chk_false(this);\" />"
			<< mendl;
	fwrite << EDIV;

	fwrite << EDIV; //container
	fwrite.flush();
	fwrite.close();

	std::string syscommand = "cat " + datatempPath + " >> " + dataPath;

//	std::cout << syscommand << "\n";

	status = system(syscommand.c_str());
	if (status < 0)
		std::cout << "DLOG Error: " << strerror(errno) << '\n';

//	fwrite << "</body>";
//	fwrite << "</html>";

	ftags.close();

	return 0;
}
