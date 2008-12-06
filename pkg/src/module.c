#include "common.h"
#include <string.h>

void rllvm_module_fin(SEXP ptr) {
	LLVMModuleRef mod = (LLVMModuleRef)R_ExternalPtrAddr(ptr);
	if(NULL != mod) {
		LLVMDisposeModule(mod);
		R_SetExternalPtrAddr(ptr,NULL);
	}
}

SEXP rllvm_module(LLVMModuleRef module,int finalize) {
	return ScalarPointer(module,RLLVM_ModuleTag,finalize ? rllvm_module_fin : NULL);
}

SEXP RLLVM_MainModule() { return rllvm_module(mainModule,0); }
SEXP RLLVM_CreateModule(SEXP name) {
	return rllvm_module(LLVMModuleCreateWithName(CHAR(STRING_ELT(name,0))),1);
}

SEXP RLLVM_GetDataLayout(SEXP module) {
	const char *layout = LLVMGetDataLayout(MOD(module));
	return layout == NULL ? R_NilValue : ScalarString(mkChar(layout));
}
SEXP RLLVM_SetDataLayout(SEXP module,SEXP layout) {
	LLVMSetDataLayout(MOD(module),CHAR(STRING_ELT(layout,0)));
	return module;
}

SEXP RLLVM_GetTarget(SEXP module) {
	const char *target = LLVMGetTarget(MOD(module));
	return target == NULL ? R_NilValue : ScalarString(mkChar(target));
}
SEXP RLLVM_SetTarget(SEXP module,SEXP target) {
	LLVMSetTarget(MOD(module),CHAR(STRING_ELT(target,0)));
	return module;
}

SEXP RLLVM_SetType(SEXP module,SEXP name,SEXP type) {
	const char *typnam = CHAR(STRING_ELT(name,0));
	if(type == R_NilValue)
		LLVMDeleteTypeName(MOD(module),typnam);
	else
		LLVMAddTypeName(MOD(module),typnam,TYP(type));
	return module;
}

void rllvm_set_attributes(LLVMValueRef fn,SEXP attr) {
	int i;	
	if(length(attr) == 0 || attr == R_NilValue) return;
	
	for(i=0;i<length(attr);i++) {
		const char *tmp = CHAR(STRING_ELT(attr,i));
		if(strcmp(tmp,"zext") == 0)
			LLVMAddAttribute(fn,LLVMZExtAttribute);
		else if(strcmp(tmp,"sext") == 0)
			LLVMAddAttribute(fn,LLVMSExtAttribute);
		else if(strcmp(tmp,"noreturn") == 0)
			LLVMAddAttribute(fn,LLVMNoReturnAttribute);
		else if(strcmp(tmp,"inreg") == 0)
			LLVMAddAttribute(fn,LLVMInRegAttribute);
		else if(strcmp(tmp,"structret") == 0)
			LLVMAddAttribute(fn,LLVMStructRetAttribute);
		else if(strcmp(tmp,"nounwind") == 0)
			LLVMAddAttribute(fn,LLVMNoUnwindAttribute);
		else if(strcmp(tmp,"noalias") == 0)
			LLVMAddAttribute(fn,LLVMNoAliasAttribute);
		else if(strcmp(tmp,"byval") == 0)
			LLVMAddAttribute(fn,LLVMByValAttribute);
		else if(strcmp(tmp,"nest") == 0)
			LLVMAddAttribute(fn,LLVMNestAttribute);
		else if(strcmp(tmp,"readnone") == 0)
			LLVMAddAttribute(fn,LLVMReadNoneAttribute);
		else if(strcmp(tmp,"readonly") == 0)
			LLVMAddAttribute(fn,LLVMReadOnlyAttribute);
	}
}

SEXP RLLVM_DeclareFunction(SEXP module,SEXP name,SEXP type,SEXP attr) {

	const char *decl = CHAR(STRING_ELT(name,0));
	LLVMValueRef fn  = LLVMAddFunction(MOD(module),decl,TYP(type));
	rllvm_set_attributes(fn,attr);
	return ScalarPointer(fn,RLLVM_ValueTag,NULL);
}



SEXP RLLVM_DumpModule(SEXP module) {
	LLVMDumpModule(MOD(module));
	return R_NilValue;
}
