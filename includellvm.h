/*
 * includellvm.h
 *
 *  Created on: Jul 11, 2013
 *      Author: aravind
 */

#ifndef INCLUDELLVM_H_
#define INCLUDELLVM_H_

#include "llvm/Pass.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"

#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/Local.h"
#include "llvm/Transforms/Utils/SSAUpdater.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/GraphWriter.h"


#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringExtras.h"

//#include "llvm/Assembly/Writer.h"
//#include "llvm/Assembly/PrintModulePass.h"
//#include "llvm/Assembly/AssemblyAnnotationWriter.h"

#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Metadata.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/GlobalValue.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/DerivedTypes.h"



#endif /* INCLUDELLVM_H_ */
