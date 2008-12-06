library(Rllvm)

m = .MainModule()

sxpinfo = llvm.struct(
	llvm.type(c(type="i5",obj="i1",named="i2",gp="i16",mark="i1",debug="i1",trace="i1",spare="i1",gcgen="i1",gccls="i3")))
voidptr = llvm.pointer(llvm.type("i8"));
sexprec = llvm.struct(list(sxp=sxpinfo,attr=voidptr,"next"=voidptr,prev=voidptr))


#Define types to match R SEXPs
type(m,"sexprec") = sexprec
printf = declare(m,"printf",llvm.fn(list(llvm.pointer(llvm.type("i8"))),llvm.type("i32"),var.args = TRUE))
printf
dump.module(m)