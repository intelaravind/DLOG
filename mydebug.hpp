/*
 * mydebug.hpp
 *
 *  Created on: Apr 26, 2013
 *      Author: aravind
 */

#ifndef MYDEBUG_HPP_
#define MYDEBUG_HPP_

#define FILE_APPEND 1
#define FILE_NEW 0

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <fstream>
#include <stdlib.h>
#include <typeinfo>
#include <vector>
//#include "includellvm.h"

std::string mendl = "<br>\n";
std::string br = "<br>";

#define RED(s) "<FONT COLOR='red'>" << s <<  "</font>"
#define GREEN(s) "<FONT COLOR='green'>" << s << "</font>"
#define BLUE(s) "<FONT COLOR='blue'>" << s << "</font>"
#define BROWN(s) "<FONT COLOR='#595930'>" << s << "</font>"

#define CHKBOX(s) "<input type='checkbox' name='foo' value=\""<<s<<"\" onClick='toggle_hideme(\""<<s<<"\");' checked>"<< s <<mendl

#define BOLD(s) "<b>" << s << "</b>"
#define DIV(s) "<div class='"<<s<<"' id='"<< s <<"' >"
#define SPAN(s) "<span class='"<<s<<"' id='"<< s <<"' >"
#define EDIV "</div>\n"
#define ESPAN "</span>\n"
#define NBSP "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
#define CALLINFO "<span class='CALLINFO' id='CALLINFO' style=\"font-size:12px\">"<<NBSP<<RED(userfile)<<":"<<RED(lineno)<<"</span>\n"

class ADDON {
	std::string s;

public:
	ADDON() {
		s = "";
	}

	ADDON(const std::string in) {
		s = in;
	}

	void operator=(const std::string in) {
		s = in;
	}

//	void operator=(const ADDON &obj) {
//		s = obj.s;
//	}

	ADDON(const ADDON &obj) {
		s = obj.s;
	}

	std::string getString() {
		return s;
	}
};

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void replaceAll(std::string& str, const std::string& from,
		const std::string& to) {
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

static int gid = 0;

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
				llvm::errs() << "ERROR: GRAPH NULL\n";
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

class aravdebug {

	std::string ErrorInfo;
	std::string dataPath;
	std::string datatempPath;
	int id;

	std::set<std::string> tagset;
	llvm::OwningPtr<llvm::raw_ostream> OS;

public:

	aravdebug(const char * userfile, int lineno, const char *PATH) {

		dataPath = getenv("DLOG_OUTPUT_FOLDER") + std::string(PATH);

		//llvm::errs()<<"Data path ::"<<dataPath;
		datatempPath = dataPath + ".temp";
//		tagPath = dataPath + ".tag";

		std::string syscall = "rm -f " + dataPath;

		int status = system(syscall.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';

		OS.reset((new llvm::raw_fd_ostream(datatempPath.c_str(), ErrorInfo)));

		llvm::errs() << ErrorInfo;

		id = gid++;

		//llvm::errs()<<"created DLOG with id "<<id<<"\n";
		tagset.insert("SYSTEM");
		(*OS) << DIV("SYSTEM")<< "Created Debugger " << GREEN(id)
		<< CALLINFO
		<< EDIV;

		tagset.insert("CALLINFO");

		(*OS).flush();
	}

	~aravdebug() {

		//llvm::errs()<<"Datapath "<<dataPath.c_str()<<"\n";
		//llvm::errs()<<"datatempPath "<<datatempPath.c_str()<<"\n";

		int status;
		std::fstream fwrite;
		fwrite.open(dataPath.c_str(), std::fstream::out);

		fwrite
				<< "<head>\n"
						"<script type='text/javascript' src='js/aravind.js' ></script>\n"
						"<script type='text/javascript' src='js/jquery-2.0.3.min.js'></script>\n";

		fwrite
				<< "<script type=\"text/javascript\">"
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
		auto it = tagset.begin();

		//for callinfo
		fwrite
				<< "<ar_menu><span class=\"floating-topic\"><b>&nbsp;&nbsp;Extra info</b></span></ar_menu>\n";

		fwrite << "<div class=\"floating-menu\">" << CHKBOX(*it) << EDIV;

		//for avoiding collapsing problem
		fwrite << DIV("") << EDIV;

		//tags begin here
		fwrite
				<< "<ar_menu><span class=\"floating-topic\"><b>&nbsp;&nbsp;Tags</b></span></ar_menu>\n";

		fwrite << "<div class=\"floating-menu\">";
		++it;
		for (; it != tagset.end(); ++it) {
			fwrite << CHKBOX(*it);

		}

		fwrite
				<< "<input id=\"clickMe\" type=\"button\" value=\"ALL\" onclick=\"toggle_chk_true(this);\" />\n";

		fwrite
				<< "<input id=\"clickMe\" type=\"button\" value=\"NONE\" onclick=\"toggle_chk_false(this);\" />"
				<< mendl;
		fwrite << EDIV;

		fwrite << EDIV; //container

		(*OS) << DIV("SYSTEM")<< br << "Destroyed Debugger " << GREEN(id)
		<< EDIV;
		fwrite << "</body> </html>";
		fwrite.close();

		if (!system(NULL))
			(*OS) << RED("System command failed in debugger\n");

		OS.reset(NULL);

		std::string syscommand = "cat " + datatempPath + " >> " + dataPath;

//llvm::errs()<<syscommand;

		status = system(syscommand.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';

		syscommand = "rm -f " + datatempPath;
		status = system(syscommand.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';

		unsigned found = datatempPath.find_last_of("/\\");

		syscommand = "cp -r $DLOG_PATH/js "
				+ datatempPath.substr(0, found);
		status = system(syscommand.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';



//system("echo `pwd`");

	}

	void print_to_file(const char * userfile, int lineno, const char* tag,
			const char* objS) {

//llvm::errs()<<"I am called in line no"<<__LINE__;
		tagset.insert(tag);
		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
		<< NBSP << BOLD(" Data : <br>") << objS << EDIV;
		(*OS).flush();
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T &obj) {
		std::string msg;
//llvm::errs()<<"I am called in line no"<<__LINE__;

		llvm::raw_string_ostream Msg(msg);
		Msg << obj;
		std::string objS = Msg.str();

		replaceAll(objS, "\n", mendl);
		tagset.insert(tag);
		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
		<< NBSP << BOLD(" Data : <br>") << objS << EDIV;
		(*OS).flush();
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T* obj) {
		std::string msg;

//llvm::errs()<<"I am called in line no"<<__LINE__;

		llvm::raw_string_ostream Msg(msg);
		Msg << *obj;
		std::string objS = Msg.str();

		replaceAll(objS, "\n", mendl);
		tagset.insert(tag);
		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
		<< NBSP << BOLD(" Data : <br>") << objS << EDIV;
		(*OS).flush();
	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, T obj, ADDON addon =
			ADDON()) {

		tagset.insert("notag");
		(*OS) << DIV("notag") << br << BLUE( obj) << NBSP << CALLINFO << NBSP
		<< BROWN(addon.getString()) << NBSP << EDIV;
		(*OS).flush();
	}

//	template<typename T>
//	void print_to_default_file(const char * userfile, int lineno, T obj)
//	{
//
//		tagset.insert("notag");
//		(*OS) << DIV("notag") << br << BLUE( obj) << NBSP << CALLINFO << NBSP
//				<< EDIV;
//		(*OS).flush();
//	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T *obj, ADDON addon) {
		std::string msg;
		llvm::raw_string_ostream Msg(msg);
		Msg << *obj;
		std::string objS = Msg.str();

		replaceAll(objS, "\n", mendl);

		tagset.insert(tag);

		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
		<< NBSP << BROWN(addon.getString()) << NBSP
		<< BOLD(" Data : <br>") << objS << EDIV;
		(*OS).flush();
	}
//
//	template<typename T, typename S>
//	void print_to_default_file(S &tag, T &obj, ADDON addon = ADDON())
//	{
//		std::string msg;
//		llvm::raw_string_ostream Msg(msg);
//		Msg << obj;
//		std::string objS = Msg.str();
//
//		replaceAll(objS, "\n", mendl);
//		tagset.insert(tag);
//
//		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP
//				<< BROWN(addon.getString()) << NBSP << BOLD(" Data : <br>")
//				<< objS << EDIV;
//		(*OS).flush();
//	}

	template<typename S>
	void print_to_file(const char * userfile, int lineno, S tag, int obj,
			ADDON addon = ADDON()) {

		tagset.insert(tag);

		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
		<< NBSP << BROWN(addon.getString()) << NBSP
		<< BOLD(" Data : <br>") << obj << EDIV;
		(*OS).flush();
	}

	template<typename S>
	void print_to_default_file(const char * userfile, int lineno, S tag,
			unsigned int obj, ADDON addon = ADDON()) {

		tagset.insert(tag);
		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
		<< NBSP << BROWN(addon.getString()) << NBSP
		<< BOLD(" Data : <br>") << obj << EDIV;
		(*OS).flush();
	}

};

#endif /* MYDEBUG_HPP_ */

