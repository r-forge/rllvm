#include "common.h"
#include <stdlib.h>
#include <string.h>

LLVMTypeRef rllvm_core_type(const char *type) {
	char *tmp;
	
	if(type[0] == 'i') {
		int bits = 32;
		type++;
		if(type[0] >= '0' && type[0] <= '9')
			bits = strtol(type,&tmp,10);
		return LLVMIntType(bits);
	} else if(type[0] == 'f') {
		if(type[1] == '\0') return LLVMFloatType();
		if(strcmp(type,"fp128") == 0)
			return LLVMFP128Type();
		else if(strcmp(type,"fp80") == 0)
			return LLVMX86FP80Type();		
		else if(strcmp(type,"fp128ppc") == 0)
			return LLVMPPCFP128Type();
	} 
	switch(type[0]) {
		case 'd': return LLVMDoubleType();
		case 'v': return LLVMVoidType();
		case 'O': return LLVMOpaqueType();
	}
	error("Unknown llvm core type: %s",type);
}


SEXP RLLVM_CoreType1(const char *type) {
	SEXP ret;
	PROTECT(ret = ScalarPointer(rllvm_core_type(type),RLLVM_TypeTag,NULL));
	setAttrib(ret,R_ClassSymbol,ScalarString(mkChar("LLVMType")));
	UNPROTECT(1);
	return ret;
}

SEXP RLLVM_CoreType(SEXP type) {
	if(length(type) == 1) {
		return RLLVM_CoreType1(CHAR(STRING_ELT(type,0)));
	} else {
		SEXP ret;int i;
		PROTECT(ret = allocVector(VECSXP,length(type)));
		for(i=0;i<length(type);i++)
			SET_VECTOR_ELT(ret,i,RLLVM_CoreType1(CHAR(STRING_ELT(type,i))));
		UNPROTECT(1);
		return ret;
	}
}

SEXP RLLVM_PointerType(SEXP type) {
	return ScalarPointer(LLVMPointerType(TYP(type),0),RLLVM_TypeTag,NULL);
}

SEXP RLLVM_ArrayType(SEXP type,SEXP n) {
	return ScalarPointer(LLVMArrayType(TYP(type),INTEGER(n)[0]),RLLVM_TypeTag,NULL);
}

SEXP RLLVM_StructType(SEXP types,SEXP packed) {
	int i;
	LLVMTypeRef *t = (LLVMTypeRef*)R_alloc(sizeof(LLVMTypeRef),length(types));
	for(i=0;i<length(types);i++)
		t[i] = TYP(VECTOR_ELT(types,i));
	return ScalarPointer(LLVMStructType(t,length(types),LOGICAL(packed)[0]),RLLVM_TypeTag,NULL);
}

SEXP RLLVM_FunctionType(SEXP types,SEXP ret,SEXP var_args) {
	int i;
	LLVMTypeRef *a = (LLVMTypeRef*)R_alloc(sizeof(LLVMTypeRef),length(types));
	for(i=0;i<length(types);i++)
		a[i] = TYP(VECTOR_ELT(types,i));
	return ScalarPointer(LLVMFunctionType(TYP(ret),a,length(types),LOGICAL(var_args)[0]),RLLVM_TypeTag,NULL);
}

SEXP rllvm_decode_function(LLVMTypeRef type) {
	
}

SEXP rllvm_decode_pointer(LLVMTypeRef type) {
	
}
SEXP rllvm_decode_array(LLVMTypeRef type) {
	
}
SEXP rllvm_decode_struct(LLVMTypeRef type) {
	
}

SEXP rllvm_decode_type(LLVMTypeRef type) {
	char temp[14];
/*	switch(type) {
		case LLVMVoidTypeKind: return ScalarString(mkChar("v"));
		case LLVMFloatTypeKind: return ScalarString(mkChar("f"));
		case LLVMDoubleTypeKind: return ScalarString(mkChar("d"));
		case LLVMX86_FP80TypeKind: return ScalarString(mkChar("fp80"));
		case LLVMFP128TypeKind: return ScalarString(mkChar("fp128"));
		case LLVMPPC_FP128TypeKind: return ScalarString(mkChar("fp128ppc"));
		case LLVMIntegerTypeKind: 
		sprintf(temp,"i%d",LLVMGetIntTypeWidth(type));
		return ScalarString(mkChar(temp));
		case LLVMPointerTypeKind: return rllvm_decode_pointer(type);
	}*/
}

SEXP RLLVM_DecodeStruct(SEXP type) {
	SEXP ret;
	LLVMTypeRef  T = TYP(type);
	unsigned int n = LLVMCountStructElementTypes(T);
	PROTECT(ret = allocVector(VECSXP,n));
	
	
	
	UNPROTECT(1);
	return ret;
}



SEXP RLLVM_DecodeType(SEXP type) {
	switch(LLVMGetTypeKind(TYP(type))) {
		case LLVMVoidTypeKind:
		break;
		case LLVMFloatTypeKind:
		break;
		case LLVMDoubleTypeKind:
		break;
		case LLVMX86_FP80TypeKind:
		break;
		case LLVMFP128TypeKind:
		break;
		case LLVMPPC_FP128TypeKind:
		break;
		case LLVMLabelTypeKind:
		break;
		case LLVMIntegerTypeKind:
		break;
		case LLVMFunctionTypeKind:
		break;
		case LLVMStructTypeKind: return RLLVM_DecodeStruct(type);
	}
	return R_NilValue;
}

