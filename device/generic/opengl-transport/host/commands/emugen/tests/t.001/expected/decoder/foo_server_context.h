// Generated Code - DO NOT EDIT !!
// generated by 'emugen'
#ifndef __foo_server_context_t_h
#define __foo_server_context_t_h

#include "foo_server_proc.h"

#include "foo_types.h"


struct foo_server_context_t {

	fooAlphaFunc_server_proc_t fooAlphaFunc;
	fooIsBuffer_server_proc_t fooIsBuffer;
	fooUnsupported_server_proc_t fooUnsupported;
	fooDoEncoderFlush_server_proc_t fooDoEncoderFlush;
	fooTakeConstVoidPtrConstPtr_server_proc_t fooTakeConstVoidPtrConstPtr;
	fooSetComplexStruct_server_proc_t fooSetComplexStruct;
	fooGetComplexStruct_server_proc_t fooGetComplexStruct;
	fooInout_server_proc_t fooInout;
	virtual ~foo_server_context_t() {}
	int initDispatchByName( void *(*getProc)(const char *name, void *userData), void *userData);
};

#endif
