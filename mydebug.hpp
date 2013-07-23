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

class ADDON
{
	std::string s;

public:
	ADDON()
	{
		s = "";
	}

	ADDON(const std::string in)
	{
		s = in;
	}

	void operator=(const std::string in)
	{
		s = in;
	}

//	void operator=(const ADDON &obj) {
//		s = obj.s;
//	}

	ADDON(const ADDON &obj)
	{
		s = obj.s;
	}

	std::string getString()
	{
		return s;
	}
};

bool replace(std::string& str, const std::string& from, const std::string& to)
{
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

void replaceAll(std::string& str, const std::string& from,
		const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
	}
}

static int gid = 0;

class aravdebug
{

	std::string ErrorInfo;
	std::string dataPath;
	std::string datatempPath;
	int id;

	std::set<std::string> tagset;
	llvm::OwningPtr<llvm::raw_ostream> OS;

public:

	aravdebug(const char * userfile, int lineno, const char *PATH)
	{

		dataPath = std::string(PATH);
		datatempPath = dataPath + ".temp";
//		tagPath = dataPath + ".tag";

		std::string syscall = "rm -f " + dataPath;

		system(syscall.c_str());

		OS.reset(
				(new llvm::raw_fd_ostream(datatempPath.c_str(), ErrorInfo
						)));

		llvm::errs() <<ErrorInfo;

		id = gid++;

		//llvm::errs()<<"created DLOG with id "<<id<<"\n";
		tagset.insert("SYSTEM");
		(*OS) << DIV("SYSTEM") << "Created Debugger " << GREEN(id) << CALLINFO
				<< EDIV;

		tagset.insert("CALLINFO");

		(*OS).flush();
	}

	~aravdebug()
	{



		//llvm::errs()<<"Datapath "<<dataPath.c_str()<<"\n";
		//llvm::errs()<<"datatempPath "<<datatempPath.c_str()<<"\n";

		std::fstream fwrite;
		fwrite.open(dataPath.c_str(), std::fstream::out);

		fwrite
				<< "<head> <script type='text/javascript' src='aravind.js' ></script> </head> <body> <style>div.floating-menu {position:fixed;background:#fff4c8;border:1px solid #ffcc00;width:150px;z-index:100; left:70%;top:150px;} div.floating-menu a, div.floating-menu h3 {display:block;margin:0 0.5em;} </style>\n";

		fwrite << DIV("floating-menu");
		for (auto it = tagset.begin(); it != tagset.end(); ++it)
		{
			fwrite << CHKBOX(*it);

		}

		fwrite
				<< "<input id=\"clickMe\" type=\"button\" value=\"ALL\" onclick=\"toggle_chk_true(this);\" />\n";

		fwrite
				<< "<input id=\"clickMe\" type=\"button\" value=\"NONE\" onclick=\"toggle_chk_false(this);\" />"
				<< mendl;
		fwrite << EDIV;

		(*OS) << DIV("SYSTEM") << br << "Destroyed Debugger " << GREEN(id)
				<< EDIV;
		fwrite << "</body> </html>";
		fwrite.close();

		if (!system(NULL))
			(*OS) << RED("System command failed in debugger\n");

		OS.reset(NULL);

		std::string syscommand = "cat " + datatempPath
				+ " >> "+dataPath;

		//llvm::errs()<<syscommand;

		system(syscommand.c_str());

		syscommand = "rm -f "+ datatempPath;
		system(syscommand.c_str());

		unsigned found = datatempPath.find_last_of("/\\");
		syscommand = "cp projects/DLOG/aravind.js " + datatempPath.substr(0,found);
		system(syscommand.c_str());

		//system("echo `pwd`");


	}

//	template<typename T, typename F>
//	void graph_save(T &tag, F &fun, std::string s = "", ADDON addon = ADDON())
//	{
//
//		std::string Filename = "/home/nfs/aravind/graph" + llvm::itostr(gid)
//				+ "cfg" + ".dot";
//
//		std::string ErrorInfo;
//		llvm::raw_fd_ostream File(Filename.c_str(), ErrorInfo);
//		if (ErrorInfo.empty())
//		{
//			WriteGraph(File, (const llvm::Function*) &fun, true, "test");
//			ViewGraph(&fun, "cfg:" + llvm::itostr(gid));
//		}
//		else
//		{
//			llvm::errs() << "  error opening file for writing!";
//		}
//
//		llvm::errs() << ErrorInfo;
//		gid++;
//
//	}

	template<typename T>
	void print_to_file(const char * userfile, int lineno, const char* tag,
			T* obj)
	{
		std::string msg;

		llvm::errs()<<"I am called in line no"<<__LINE__;

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
	void print_to_file(const char * userfile, int lineno, T obj,
			ADDON addon = ADDON())
	{

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
			T *obj, ADDON addon)
	{
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
			ADDON addon = ADDON())
	{

		tagset.insert(tag);

		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
				<< NBSP << BROWN(addon.getString()) << NBSP
				<< BOLD(" Data : <br>") << obj << EDIV;
		(*OS).flush();
	}

	template<typename S>
	void print_to_default_file(const char * userfile, int lineno, S tag,
			unsigned int obj, ADDON addon = ADDON())
	{

		tagset.insert(tag);
		(*OS) << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << CALLINFO
				<< NBSP << BROWN(addon.getString()) << NBSP
				<< BOLD(" Data : <br>") << obj << EDIV;
		(*OS).flush();
	}

};

#endif /* MYDEBUG_HPP_ */

