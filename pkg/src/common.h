#ifndef _h_Rllvm_common_
#define _h_Rllvm_common_

#include <llvm-c/Core.h>
#include <Rinternals.h>

extern LLVMModuleRef mainModule;
extern SEXP RLLVM_ModuleTag;
extern SEXP RLLVM_TypeTag;
extern SEXP RLLVM_ValueTag;

SEXP ScalarPointer(void*ptr,SEXP tag,void (*fin)(SEXP));

#define MOD(X) ((LLVMModuleRef)R_ExternalPtrAddr(X))
#define TYP(X) ((LLVMTypeRef)R_ExternalPtrAddr(X))
#define VAL(X) ((LLVMValueRef)R_ExternalPtrAddr(X))

#endif