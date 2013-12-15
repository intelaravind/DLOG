/*
 * DLOG_LLVM_SUPPORT.hpp
 *
 *  Created on: Dec 15, 2013
 *      Author: aravind
 */

#ifndef DLOG_LLVM_SUPPORT_HPP_
#define DLOG_LLVM_SUPPORT_HPP_

#include "includellvm.h"
#include "DLOG_HELPER.hpp"

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

template<typename T>
std::string llvm_to_str(T &obj)
{
	std::string msg;
	llvm::raw_string_ostream Msg(msg);
	Msg << obj;
	return Msg.str();
}

std::string dlog_format_llvm(std::string obj)
{
	replaceAll(obj, "\n", mendl);
	return obj;
}

#endif /* DLOG_LLVM_SUPPORT_HPP_ */
