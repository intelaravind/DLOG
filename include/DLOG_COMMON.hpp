
/*
 * DLOG_COMMON.hpp
 *
 *  Created on: April 11, 2015
 *      Author: aravind
 *
 * Common functions
 */

#ifndef DLOG_COMMON_HPP_
#define DLOG_COMMON_HPP_

#include <string.h>
#include <iostream>

namespace DLOG_NS
{

enum class MSG_LEVEL
{
    quite, normal, verbose
};

static std::string strip_path(const std::string full_path)
{
    unsigned found = full_path.find_last_of("/\\");
    return full_path.substr(0, found) + "/";

}

static int sys_call(std::string syscommand, MSG_LEVEL level = MSG_LEVEL::normal)
{
    int status = system(syscommand.c_str());
    if (status < 0 && level != MSG_LEVEL::quite)
        std::cout << "DLOG System error: " << strerror(errno) << '\n';

    return status;
}

static void create_directory_if_not_exist(std::string fullpath)
{
    std::string syscommand = "mkdir -p " + fullpath;
    sys_call(syscommand);
}


static std::string get_path(const char* path)
{
    std::string r_path;
    r_path = (path)?path:"dlog_output/";
    create_directory_if_not_exist(r_path);
    return r_path;

}

}



#endif





