// Generated Code - DO NOT EDIT !!
// generated by 'emugen'


#include <string.h>
#include "foo_server_context.h"


#include <stdio.h>

int foo_server_context_t::initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData)
{
	fooAlphaFunc = (fooAlphaFunc_server_proc_t) getProc("fooAlphaFunc", userData);
	fooIsBuffer = (fooIsBuffer_server_proc_t) getProc("fooIsBuffer", userData);
	fooUnsupported = (fooUnsupported_server_proc_t) getProc("fooUnsupported", userData);
	fooDoEncoderFlush = (fooDoEncoderFlush_server_proc_t) getProc("fooDoEncoderFlush", userData);
	fooTakeConstVoidPtrConstPtr = (fooTakeConstVoidPtrConstPtr_server_proc_t) getProc("fooTakeConstVoidPtrConstPtr", userData);
	fooSetComplexStruct = (fooSetComplexStruct_server_proc_t) getProc("fooSetComplexStruct", userData);
	fooGetComplexStruct = (fooGetComplexStruct_server_proc_t) getProc("fooGetComplexStruct", userData);
	fooInout = (fooInout_server_proc_t) getProc("fooInout", userData);
	return 0;
}

