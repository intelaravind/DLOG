
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
#include <algorithm>

namespace DLOG_NS
{

enum class MSG_LEVEL
{
    quite, normal, verbose
};

inline std::string strip_path(const std::string full_path)
{
    unsigned found = full_path.find_last_of("/\\");
    return full_path.substr(0, found) + "/";

}

inline int sys_call(std::string syscommand, MSG_LEVEL level = MSG_LEVEL::normal)
{
    int status = system(syscommand.c_str());
    if (status < 0 && level != MSG_LEVEL::quite)
        std::cout << "DLOG System error: " << strerror(errno) << '\n';

    return status;
}

inline void create_directory_if_not_exist(std::string fullpath)
{
    std::string syscommand = "mkdir -p " + fullpath;
    sys_call(syscommand);
}


inline std::string get_path(const char* path)
{
    std::string r_path;
    r_path = (path)?path:"dlog_output/";
    create_directory_if_not_exist(r_path);
    return r_path;

}

inline std::string strip_space(const char *input)
{
	std::string str(input);
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;

}

}



#endif





