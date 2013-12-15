/*
 * DLOG_LLVM.cpp
 *
 *  Created on: Dec 16, 2013
 *      Author: aravind
 */

//These are some sample usages for llvm

//define DLOG_LLVM_ENABLE in DLOG.hpp or use -DDLOG_LLVM_ENABLE to enable llvm

DLOG dlog DLOG_CREATE("test_llvm.html");

//Note: Be careful while creating a dlog object on a program point which is can be
//reached multiple times (like functions and loops). DLOG object will only save the
//info of last call. This is just like opening a file inside a function in write
//mode. If you call the function multiple times you can only see the last output.
//To overcome this either use
//    static objects "staticDLOG dlog DLOG_CREATE("test_llvm.html");"
//    or
//    define it in  global space


//F is llvm::Function
DLOG_LLVM_PRINT(dlog, F,"main output");

//B is llvm::BasicBlock
DLOG_LLVM_PRINT(dlog, B,"main output");

//loop is llvm:Loop
DLOG_LLVM_PRINT(dlog, loop,"function output");

//other useful infor (check the simple examples for more info)

//To print to console and dlog
dlog.set_output_mode(DLOG_OUTPUT_BOTH);

//define DLOG_DISABLE to disable the dlog output
