/*
 * DLOG.hpp
 *
 *  Created on: Jul 11, 2013
 *      Author: aravind
 *
 * This class is a wrapper for mydebug class
 */

#ifndef DLOG_HPP_
#define DLOG_HPP_

#include "DLOG_HELPER.hpp"

//#define DLOG_DEBUG
#define DLOG_ENABLE

//Dont delete the temp files
#define DLOG_KEEP_TEMP_FILES 1

//print the output to file
#define DLOG_OUTPUT_FILE 1

//print the output to stdout
#define DLOG_OUTPUT_STDOUT 0;

#ifdef DLOG_ENABLE
#define DLOG_CREATE(path) (__FILE__,__LINE__,path)
#define DLOG_PRINT(obj,...)  obj.print(__FILE__,__LINE__ ,__VA_ARGS__)
#else
#define DLOG_CREATE(path)()
#define DLOG_PRINT(...)  print()
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
	DLOG()
	{

	}

	DLOG(const char *, int, const char *, std::string);
	~DLOG();

	void tag_handler(std::string);

	template<typename T>
	void print(const char *, int, T);

	void print();
};

/**
 * The main DLOG constructor
 * @param userfile : The file which called the constructor
 * @param lineno : The lineno in the user file which called the constructor
 * @param OUT_FILE : The output file name.
 * @param inpPath : The path of output file. If none is given the environment variable DLOG_OUTPUT_FOLDER is used
 */
DLOG::DLOG(const char * userfile, int lineno, const char *OUT_FILE,
		std::string inpPath = getenv("DLOG_OUTPUT_FOLDER"))
{
	DLOG::dataPath = inpPath + std::string(OUT_FILE);

//	std::cout << dataPath << "\n";

	outputmode = DLOG_OUTPUT_FILE;

	datatempPath = DLOG::dataPath + ".temp";
	tagPath = DLOG::dataPath + ".tag";

	std::string syscall = "rm -f " + DLOG::dataPath;

	int status = system(syscall.c_str());
	if (status < 0)
		std::cout << "DLOG Error: " << strerror(errno) << '\n';

	fdata.open(datatempPath.c_str(), std::fstream::out);
	ftags.open(tagPath.c_str(), std::fstream::out);

	//default tags
	ftags << CHKBOX("SYSTEM");

	//insert known tags to taglist
	tag_handler("SYSTEM");
	tag_handler("CALLINFO");

	fdata << DIV("SYSTEM") << "Created Debugger " << GREEN(id) << CALLINFO
			<< EDIV;
	id = gid++;
}

DLOG::~DLOG()
{
	std::string syscommand;
	int status;

	fdata << DIV("SYSTEM") << "Destroyed Debugger " << GREEN(id) << EDIV;
	fdata.close();

	unsigned found = datatempPath.find_last_of("/\\");

	syscommand = "cp -r $DLOG_PATH/js " + datatempPath.substr(0, found);
	status = system(syscommand.c_str());
	if (status < 0)
		std::cout << "DLOG Error: " << strerror(errno) << '\n';


	syscommand = "$DLOG_PATH/DLOG_FINALIZER.out "
			+ dataPath;
//	std::cout << syscommand<<"\n";
	status = system(syscommand.c_str());
	if (status < 0)
		std::cout << "DLOG Error: " << strerror(errno) << '\n';

#if (DLOG_KEEP_TEMP_FILES ==0)

	syscommand = "rm -f " + datatempPath;
	status = system(syscommand.c_str());
	if (status < 0)
	std::cout << "DLOG Error: " << strerror(errno) << '\n';

	syscommand = "rm -f " + tagPath;
	status = system(syscommand.c_str());
	if (status < 0)
	std::cout << "DLOG Error: " << strerror(errno) << '\n';
#endif

}

/**
 * @brief adds the tag to the file if it does not exit
 * @param input : The input tag
 */
void DLOG::tag_handler(std::string input)
{

	std::pair<std::set<std::string>::iterator, bool> ret;
	ret = tagset.insert(input);

	//A new element was inserted so add it to file
	if (ret.second)
	{
		tagset.insert("SYSTEM");
		tagset.insert("CALLINFO");
	}

}

template<typename T>
void DLOG::print(const char *userfile, int lineno, T obj)
{
	tag_handler("notag");
	fdata
			<< DIV(
					"notag") << br<< CALLINFO << NBSP << BOLD(" Data : <br>") << obj << EDIV;

	fdata.flush();
}

/**
 * Does nothing. Used mainly for disabling DLOG
 */
void DLOG::print()
{

}

#endif /* DLOG_HPP_ */
