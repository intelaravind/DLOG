/*
 * DLOG.hpp
 *
 *  Created on: Jul 11, 2013
 *      Author: aravind
 *
 * Add some infor about dlog
 */

#ifndef DLOG_HPP_
#define DLOG_HPP_

#include "debug_common_headers.hpp"
#include "DLOG_HELPER.hpp"

#ifndef DLOG_DISABLE
///uncomment this line to disable DLOG or use -DDLOG_DISABLE
#define DLOG_ENABLE
#endif

///uncomment this line to enable llvm support
//#define DLOG_LLVM_ENABLE

#ifdef DLOG_LLVM_ENABLE
#include "DLOG_LLVM_SUPPORT.hpp"
#ifdef DLOG_ENABLE
#define DLOG_LLVM_PRINT(obj,...) (obj).llvm_print(__FILE__,__LINE__ ,__VA_ARGS__)
#else
#define DLOG_LLVM_PRINT(obj,...) (obj).print()
#endif
#endif

//#define DLOG_DEBUG
//Dont delete the temp files
#define DLOG_KEEP_TEMP_FILES 0

//print the output to stdout
#define DLOG_OUTPUT_STDOUT 0

//print the output to file
#define DLOG_OUTPUT_FILE 1

//print the output to stdout
#define DLOG_OUTPUT_BOTH 2

#ifdef DLOG_ENABLE
#define DLOG_CREATE(path) (__FILE__,__LINE__,path)
#define DLOG_PRINT(obj,...)  obj.print(__FILE__,__LINE__ ,__VA_ARGS__)
#else
#define DLOG_CREATE(path) ;
#define DLOG_PRINT(obj,...)  obj.print()
#endif

static int gid = 0;

/**
 * DLOG main class
 */
class DLOG
{
	std::string ErrorInfo;
	std::string dataPath;
	std::string tagPath;
	std::string datatempPath;
	//set of known tags
	std::set<std::string> tagset;

	///for temporary data
	std::fstream fdata;
	///for temporary tags
	std::fstream ftags;

	///Output on file (DLOG_OUTPUT_FILE) or stdout (DLOG_OUTPUT_STDOUT)
	int outputmode;
	int id;

public:

	/**
	 * Empty constructor to do nothing;
	 * Used mainly to disable DLOG
	 */
	DLOG();
	DLOG(const char *, int, const char *, std::string path = getenv("DLOG_OUTPUT_FOLDER"));
	~DLOG();

	void tag_handler(std::string);

	template<typename T>
	void print(const char *userfile, int lineno, T obj, ADDON addon = ADDON())
	{

		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_FILE)
		{
			tag_handler("notag");
			fdata << DIV("notag") << br << CALLINFO << NBSP
			<< BROWN(addon.getString()) << NBSP << BOLD(" Data : <br>")
			<< obj << EDIV;
		}

		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_STDOUT)
		{
			if (addon.getString().length() != 0)
				std::cout << "Addon: " << addon.getString() << "\n";
			std::cout << obj << "\n";
		}

		fdata.flush();
	}
	template<typename T>
	void print(const char *userfile, int lineno, T obj, const char* tag,
			ADDON addon = ADDON())
	{
		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_FILE)

		{
			tag_handler(tag);
			fdata << DIV(tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << br
			<< CALLINFO << BROWN(addon.getString()) << NBSP << NBSP
			<< BOLD(" Data : <br>") << obj << EDIV;
		}
		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_STDOUT)
		{
			std::cout << "Tag : " << tag << "\t";
			if (addon.getString().length() != 0)
				std::cout << "\t Addon: " << addon.getString() << "\n";
			std::cout << obj << "\n";
		}

		fdata.flush();
	}

#ifdef DLOG_LLVM_ENABLE
	template<typename T>
	void llvm_print(const char *userfile, int lineno, T &obj, ADDON addon =
			ADDON())
	{
		std::string unformatted = llvm_to_str(*obj);
		std::string formatted = dlog_format_llvm(unformatted);

		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_FILE)
		{
			tag_handler("notag");
			fdata << DIV("notag") << br << CALLINFO << NBSP
			<< BROWN(addon.getString()) << NBSP << BOLD(" Data : <br>")
			<< formatted << EDIV;
		}

		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_STDOUT)
		{
			if (addon.getString().length() != 0)
			std::cout << "Addon: " << addon.getString() << "\n";
			std::cout << unformatted << "\n";
		}

		fdata.flush();
	}
	template<typename T>
	void llvm_print(const char *userfile, int lineno, T &obj, const char* tag,
			ADDON addon = ADDON())
	{

		std::string unformatted = llvm_to_str(obj);
		std::string formatted = dlog_format_llvm(unformatted);

		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_FILE)

		{
			tag_handler(tag);
			fdata << DIV(
					tag) << BOLD("<br>Tag : ") << RED(tag) << NBSP << br << CALLINFO
			<< BROWN(addon.getString()) << NBSP << NBSP
			<< BOLD(" Data : <br>") << formatted << EDIV;
		}
		if (outputmode == DLOG_OUTPUT_BOTH || outputmode == DLOG_OUTPUT_STDOUT)
		{
			std::cout << "Tag : " << tag << "\t";
			if (addon.getString().length() != 0)
			std::cout << "\t Addon: " << addon.getString() << "\n";
			std::cout << unformatted << "\n";
		}

		fdata.flush();
	}
#endif

	void set_output_mode(int);

	void print();
};

#endif /* DLOG_HPP_ */
