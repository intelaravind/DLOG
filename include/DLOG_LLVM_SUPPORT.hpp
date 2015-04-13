/*
 * DLOG_LLVM_SUPPORT.hpp
 *
 *  Created on: Dec 15, 2013
 *      Author: aravind
 */

#ifndef DLOG_LLVM_SUPPORT_HPP_
#define DLOG_LLVM_SUPPORT_HPP_

#include "includellvm.hpp"
#include "DLOG_HELPER.hpp"


std::string dlog_format_llvm(std::string);

template<typename T>
std::string llvm_to_str(T &obj)
{
	std::string msg;
	llvm::raw_string_ostream Msg(msg);
	Msg << obj;
	return Msg.str();
}

#endif /* DLOG_LLVM_SUPPORT_HPP_ */
