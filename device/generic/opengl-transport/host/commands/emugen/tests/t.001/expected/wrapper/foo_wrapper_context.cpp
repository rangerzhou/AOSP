// Generated Code - DO NOT EDIT !!
// generated by 'emugen'


#include <string.h>
#include "foo_wrapper_context.h"


#include <stdio.h>

int foo_wrapper_context_t::initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData)
{
	fooAlphaFunc = (fooAlphaFunc_wrapper_proc_t) getProc("fooAlphaFunc", userData);
	fooIsBuffer = (fooIsBuffer_wrapper_proc_t) getProc("fooIsBuffer", userData);
	fooUnsupported = (fooUnsupported_wrapper_proc_t) getProc("fooUnsupported", userData);
	fooDoEncoderFlush = (fooDoEncoderFlush_wrapper_proc_t) getProc("fooDoEncoderFlush", userData);
	fooTakeConstVoidPtrConstPtr = (fooTakeConstVoidPtrConstPtr_wrapper_proc_t) getProc("fooTakeConstVoidPtrConstPtr", userData);
	fooSetComplexStruct = (fooSetComplexStruct_wrapper_proc_t) getProc("fooSetComplexStruct", userData);
	fooGetComplexStruct = (fooGetComplexStruct_wrapper_proc_t) getProc("fooGetComplexStruct", userData);
	fooInout = (fooInout_wrapper_proc_t) getProc("fooInout", userData);
	return 0;
}

