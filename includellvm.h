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
#include "llvm/Analysis/Dominators.h"
#include "llvm/Analysis/ScalarEvolution.h"

#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/Local.h"
#include "llvm/Transforms/Utils/SSAUpdater.h"

#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include "llvm/Support/IRBuilder.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/GraphWriter.h"


#include "llvm/ADT/Statistic.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringExtras.h"

#include "llvm/Transforms/Utils/FunctionUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"

#include "llvm/Assembly/Writer.h"
#include "llvm/Assembly/PrintModulePass.h"
#include "llvm/Assembly/AssemblyAnnotationWriter.h"

#include "llvm/Target/TargetData.h"


#include "llvm/Module.h"
#include "llvm/Function.h"
#include "llvm/BasicBlock.h"
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "llvm/Metadata.h"
#include "llvm/LLVMContext.h"
#include "llvm/InlineAsm.h"
#include "llvm/GlobalValue.h"
#include "llvm/CallingConv.h"
#include "llvm/Type.h"
#include "llvm/Argument.h"
#include "llvm/Attributes.h"
#include "llvm/DerivedTypes.h"



#endif /* INCLUDELLVM_H_ */
