// Generated Code - DO NOT EDIT !!
// generated by 'emugen'
#include <stdio.h>
#include <stdlib.h>
#include "foo_client_context.h"

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
static foo_client_context_t::CONTEXT_ACCESSOR_TYPE *getCurrentContext = NULL;
void foo_client_context_t::setContextAccessor(CONTEXT_ACCESSOR_TYPE *f) { getCurrentContext = f; }
#define GET_CONTEXT foo_client_context_t * ctx = getCurrentContext()
#endif

void fooAlphaFunc(FooInt func, FooFloat ref)
{
	GET_CONTEXT;
	ctx->fooAlphaFunc(ctx, func, ref);
}

FooBoolean fooIsBuffer(void* stuff)
{
	GET_CONTEXT;
	 if (n == NULL) { LOG(ERROR) << "NULL stuff"; return; }
	return ctx->fooIsBuffer(ctx, stuff);
}

void fooUnsupported(void* params)
{
	GET_CONTEXT;
	ctx->fooUnsupported(ctx, params);
}

void fooDoEncoderFlush(FooInt param)
{
	GET_CONTEXT;
	ctx->fooDoEncoderFlush(ctx, param);
}

void fooTakeConstVoidPtrConstPtr(const void* const* param)
{
	GET_CONTEXT;
	ctx->fooTakeConstVoidPtrConstPtr(ctx, param);
}

void fooSetComplexStruct(const FooStruct* obj)
{
	GET_CONTEXT;
	ctx->fooSetComplexStruct(ctx, obj);
}

void fooGetComplexStruct(FooStruct* obj)
{
	GET_CONTEXT;
	ctx->fooGetComplexStruct(ctx, obj);
}

void fooInout(uint32_t* count)
{
	GET_CONTEXT;
	ctx->fooInout(ctx, count);
}

