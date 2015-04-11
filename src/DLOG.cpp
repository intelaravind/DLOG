/*
 * DLOG.cpp
 *
 *  Created on: Jan 4, 2014
 *      Author: aravind
 */

#include "DLOG.hpp"
#include "config.h"
#include "DLOG_COMMON.hpp"

DLOG::DLOG()
{
    isEnabled = false;
}


static int gid = 0;

/**
 * The main DLOG constructor
 * @param userfile : The file which called the constructor
 * @param lineno : The lineno in the user file which called the constructor
 * @param OUT_FILE : The output file name.
 * @param inpPath : The path of output file. If none is given the environment variable DLOG_OUTPUT_FOLDER is used
 */
DLOG::DLOG(const char *userfile, int lineno, const char *OUT_FILE,
           const char *inpPath_p): fileName(OUT_FILE)
{
    std::string syscommand;
    this->dataPath = DLOG_NS::get_path(inpPath_p);
    id = gid++;

    isEnabled = true;

    // std::cout << dataPath << "\n";

    outputmode = DLOG_OUTPUT_FILE;

    syscommand = "rm -f " + this->dataPath + "/" + fileName;

    DLOG_NS::sys_call(syscommand);

    fdata.open(this->dataPath + "/" + fileName + ".temp", std::fstream::out);
    ftags.open(this->dataPath + "/" + fileName + ".tag", std::fstream::out);

    //insert known tags to taglist
    tag_handler("SYSTEM");
    tag_handler("CALLINFO");

    fdata << DIV("SYSTEM") << "Created Debugger " << GREEN(id) << CALLINFO
          << EDIV;

    //copy the recovery script
    syscommand = "ln -sfF " SRC_PATH "/recover.sh " + this->dataPath;
    DLOG_NS::sys_call(syscommand);
}

DLOG::~DLOG()
{

    if(isEnabled == false)
        return;
    std::string syscommand;
    int status;

    fdata << DIV("SYSTEM") << "Destroyed Debugger " << GREEN(id) << EDIV;
    fdata.close();
    ftags.close();

    syscommand = "ln -sfF " SRC_PATH "/js " + dataPath;
    DLOG_NS::sys_call(syscommand);

    syscommand = SRC_PATH "/DLOG_FINALIZER " + dataPath + "/" + fileName;
    DLOG_NS::sys_call(syscommand);
    
#if (DLOG_KEEP_TEMP_FILES ==0)

    //.temp
    syscommand = "rm -f " + dataPath + "/" + fileName + ".temp";
    DLOG_NS::sys_call(syscommand);

    //.tag
    syscommand = "rm -f " + dataPath + "/" + fileName + ".tag";
    DLOG_NS::sys_call(syscommand);
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


