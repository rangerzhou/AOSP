// Generated Code - DO NOT EDIT !!
// generated by 'emugen'
#include <stdio.h>
#include <stdlib.h>
#include "foo_wrapper_context.h"

extern "C" {
	void fooAlphaFunc(FooInt func, FooFloat ref);
	FooBoolean fooIsBuffer(void* stuff);
	void fooUnsupported(void* params);
	void fooDoEncoderFlush(FooInt param);
	void fooTakeConstVoidPtrConstPtr(const void* const* param);
	void fooSetComplexStruct(const FooStruct* obj);
	void fooGetComplexStruct(FooStruct* obj);
	void fooInout(uint32_t* count);
};

#ifndef GET_CONTEXT
static foo_wrapper_context_t::CONTEXT_ACCESSOR_TYPE *getCurrentContext = NULL;
void foo_wrapper_context_t::setContextAccessor(CONTEXT_ACCESSOR_TYPE *f) { getCurrentContext = f; }
#define GET_CONTEXT foo_wrapper_context_t * ctx = getCurrentContext()
#endif

void fooAlphaFunc(FooInt func, FooFloat ref)
{
	GET_CONTEXT;
	ctx->fooAlphaFunc( func, ref);
}

FooBoolean fooIsBuffer(void* stuff)
{
	GET_CONTEXT;
	return ctx->fooIsBuffer( stuff);
}

void fooUnsupported(void* params)
{
	GET_CONTEXT;
	ctx->fooUnsupported( params);
}

void fooDoEncoderFlush(FooInt param)
{
	GET_CONTEXT;
	ctx->fooDoEncoderFlush( param);
}

void fooTakeConstVoidPtrConstPtr(const void* const* param)
{
	GET_CONTEXT;
	ctx->fooTakeConstVoidPtrConstPtr( param);
}

void fooSetComplexStruct(const FooStruct* obj)
{
	GET_CONTEXT;
	ctx->fooSetComplexStruct( obj);
}

void fooGetComplexStruct(FooStruct* obj)
{
	GET_CONTEXT;
	ctx->fooGetComplexStruct( obj);
}

void fooInout(uint32_t* count)
{
	GET_CONTEXT;
	ctx->fooInout( count);
}

