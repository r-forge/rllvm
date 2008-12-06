#include "common.h"
#include <R_ext/Rdynload.h>

SEXP ScalarPointer(void*ptr,SEXP tag,void (*fin)(SEXP)) {
	SEXP ret = R_MakeExternalPtr(ptr,tag,R_NilValue);
	if(fin != NULL)
		R_RegisterCFinalizerEx(ret,fin,1);
	return ret;
}

LLVMModuleRef mainModule;
SEXP RLLVM_ModuleTag;
SEXP RLLVM_TypeTag;
SEXP RLLVM_ValueTag;

void R_init_Rllvm(DllInfo *dll) {
	RLLVM_ModuleTag = install("LLVMModuleRef");
	RLLVM_TypeTag   = install("LLVMTypeRef");
	RLLVM_ValueTag  = install("LLVMValueRef");
	mainModule = LLVMModuleCreateWithName("R Default Module");
}