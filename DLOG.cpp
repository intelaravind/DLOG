/*
 * DLOG.cpp
 *
 *  Created on: Jan 4, 2014
 *      Author: aravind
 */

#include "DLOG.hpp"

DLOG::DLOG()
{

}

//template<typename T>
//void DLOG::print(const char *userfile, int lineno, T obj, ADDON addon)
//{
//
//}
//
//template<typename T>
//void DLOG::print(const char *userfile, int lineno, T obj, const char* tag,
//		ADDON addon)
//{
//
//
//}

/**
 * The main DLOG constructor
 * @param userfile : The file which called the constructor
 * @param lineno : The lineno in the user file which called the constructor
 * @param OUT_FILE : The output file name.
 * @param inpPath : The path of output file. If none is given the environment variable DLOG_OUTPUT_FOLDER is used
 */
DLOG::DLOG(const char * userfile, int lineno, const char *OUT_FILE,
		std::string inpPath)
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

	//insert known tags to taglist
	tag_handler("SYSTEM");
	tag_handler("CALLINFO");

	fdata << DIV("SYSTEM") << "Created Debugger " << GREEN(id) << CALLINFO
			<< EDIV;
	id = gid++;

	std::string syscommand;
	//copy the recovery script
	unsigned found = datatempPath.find_last_of("/\\");
	syscommand = "cp -r $DLOG_PATH/recover.sh " + datatempPath.substr(0, found);
	status = system(syscommand.c_str());
	if (status < 0)
		std::cout << "DLOG Error: " << strerror(errno) << '\n';
}

DLOG::~DLOG()
{
	std::string syscommand;
	int status;

	fdata << DIV("SYSTEM") << "Destroyed Debugger " << GREEN(id) << EDIV;
	fdata.close();
	ftags.close();

	unsigned found = datatempPath.find_last_of("/\\");

	syscommand = "cp -r $DLOG_PATH/js " + datatempPath.substr(0, found);
	status = system(syscommand.c_str());
	if (status < 0)
		std::cout << "DLOG Error: " << strerror(errno) << '\n';

	syscommand = "$DLOG_PATH/DLOG_FINALIZER.out " + dataPath;
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
 * set output mode to file or stdout
 * @param mode : DLOG output modes (DLOG_OUTPUT_FILE, DLOG_OUTPUT_STDOUT, DLOG_OUTPUT_BOTH)
 */
void DLOG::set_output_mode(int mode)
{
	outputmode = mode;
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
	if (ret.second == true && input.compare("CALLINFO") != 0)
	{
		ftags << CHKBOX(input);
		ftags.flush();
	}

}

/**
 * Does nothing. Used mainly for disabling DLOG
 */
void DLOG::print()
{

}
