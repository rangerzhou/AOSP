// Generated Code - DO NOT EDIT !!
// generated by 'emugen'

#ifndef GUARD_gles1_decoder_context_t
#define GUARD_gles1_decoder_context_t

#include "IOStream.h"
#include "ChecksumCalculator.h"
#include "gles1_server_context.h"



struct gles1_decoder_context_t : public gles1_server_context_t {

	size_t decode(void *buf, size_t bufsize, IOStream *stream, ChecksumCalculator* checksumCalc);

};

#endif  // GUARD_gles1_decoder_context_t
