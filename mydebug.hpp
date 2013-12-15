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

#include "debug_common_headers.hpp"
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

