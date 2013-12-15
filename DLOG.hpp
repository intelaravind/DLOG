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

#ifdef DLOG_ENABLE
#define DLOG_CREATE(path)  DLOG(__FILE__,__LINE__,path)
#define PRINT_TO_FILE(...)  print_to_file(__FILE__,__LINE__ ,__VA_ARGS__)
#else
#define DLOG_CREATE(path)  DLOG()
#define PRINT_TO_FILE(...)  print_to_file()
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
	int id;

	std::set<std::string> tagset;

public:

	/**
	 * Empty constructor to do nothing;
	 * Used mainly to disable DLOG
	 */
	DLOG()
	{

	}
	DLOG(const char * userfile, int lineno, const char *PATH)
	{
		dataPath = getenv("DLOG_OUTPUT_FOLDER") + std::string(PATH);

		datatempPath = dataPath + ".temp";
		tagPath = dataPath + ".tag";

		std::string syscall = "rm -f " + dataPath;

		int status = system(syscall.c_str());
		if (status < 0)
			std::cout << "DLOG Error: " << strerror(errno) << '\n';

		//for temporary data
		std::fstream fdata;
		fdata.open(datatempPath.c_str(), std::fstream::out);

		//for temporary tags
		std::fstream ftags;
		ftags.open(tagPath.c_str(), std::fstream::out);

		//default tags
		ftags << CHKBOX("SYSTEM");
		ftags << CHKBOX("CALLINFO");

		fdata << DIV("SYSTEM") << "Created Debugger " << GREEN(id) << CALLINFO
				<< EDIV;

		id = gid++;
	}

	~DLOG()
	{
		std::string syscommand;
		int status;

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

	void print_to_file();
};

/**
 * Do nothing. Used mainly for disabling DLOG
 */
void DLOG::print_to_file()
{

}

#endif /* DLOG_HPP_ */
