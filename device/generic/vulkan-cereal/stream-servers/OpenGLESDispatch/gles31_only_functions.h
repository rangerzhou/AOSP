// Auto-generated with: android/scripts/gen-entries.py --mode=funcargs android/android-emugl/host/libs/libOpenGLESDispatch/gles31_only.entries --output=android/android-emugl/host/include/OpenGLESDispatch/gles31_only_functions.h
// DO NOT EDIT THIS FILE

#ifndef GLES31_ONLY_FUNCTIONS_H
#define GLES31_ONLY_FUNCTIONS_H

#include <GLES/gl.h>
#include <GLES3/gl3.h>
#include <GLES3/gl31.h>
#define LIST_GLES31_ONLY_FUNCTIONS(X) \
  X(void, glGetBooleani_v, (GLenum target, GLuint index, GLboolean * data), (target, index, data)) \
  X(void, glMemoryBarrier, (GLbitfield barriers), (barriers)) \
  X(void, glMemoryBarrierByRegion, (GLbitfield barriers), (barriers)) \
  X(void, glGenProgramPipelines, (GLsizei n, GLuint * pipelines), (n, pipelines)) \
  X(void, glDeleteProgramPipelines, (GLsizei n, const GLuint * pipelines), (n, pipelines)) \
  X(void, glBindProgramPipeline, (GLuint pipeline), (pipeline)) \
  X(void, glGetProgramPipelineiv, (GLuint pipeline, GLenum pname, GLint * params), (pipeline, pname, params)) \
  X(void, glGetProgramPipelineInfoLog, (GLuint pipeline, GLsizei bufSize, GLsizei * length, GLchar * infoLog), (pipeline, bufSize, length, infoLog)) \
  X(void, glValidateProgramPipeline, (GLuint pipeline), (pipeline)) \
  X(GLboolean, glIsProgramPipeline, (GLuint pipeline), (pipeline)) \
  X(void, glUseProgramStages, (GLuint pipeline, GLbitfield stages, GLuint program), (pipeline, stages, program)) \
  X(void, glActiveShaderProgram, (GLuint pipeline, GLuint program), (pipeline, program)) \
  X(GLuint, glCreateShaderProgramv, (GLenum type, GLsizei count, const char ** strings), (type, count, strings)) \
  X(void, glProgramUniform1f, (GLuint program, GLint location, GLfloat v0), (program, location, v0)) \
  X(void, glProgramUniform2f, (GLuint program, GLint location, GLfloat v0, GLfloat v1), (program, location, v0, v1)) \
  X(void, glProgramUniform3f, (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2), (program, location, v0, v1, v2)) \
  X(void, glProgramUniform4f, (GLuint program, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3), (program, location, v0, v1, v2, v3)) \
  X(void, glProgramUniform1i, (GLuint program, GLint location, GLint v0), (program, location, v0)) \
  X(void, glProgramUniform2i, (GLuint program, GLint location, GLint v0, GLint v1), (program, location, v0, v1)) \
  X(void, glProgramUniform3i, (GLuint program, GLint location, GLint v0, GLint v1, GLint v2), (program, location, v0, v1, v2)) \
  X(void, glProgramUniform4i, (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLint v3), (program, location, v0, v1, v2, v3)) \
  X(void, glProgramUniform1ui, (GLuint program, GLint location, GLuint v0), (program, location, v0)) \
  X(void, glProgramUniform2ui, (GLuint program, GLint location, GLint v0, GLuint v1), (program, location, v0, v1)) \
  X(void, glProgramUniform3ui, (GLuint program, GLint location, GLint v0, GLint v1, GLuint v2), (program, location, v0, v1, v2)) \
  X(void, glProgramUniform4ui, (GLuint program, GLint location, GLint v0, GLint v1, GLint v2, GLuint v3), (program, location, v0, v1, v2, v3)) \
  X(void, glProgramUniform1fv, (GLuint program, GLint location, GLsizei count, const GLfloat * value), (program, location, count, value)) \
  X(void, glProgramUniform2fv, (GLuint program, GLint location, GLsizei count, const GLfloat * value), (program, location, count, value)) \
  X(void, glProgramUniform3fv, (GLuint program, GLint location, GLsizei count, const GLfloat * value), (program, location, count, value)) \
  X(void, glProgramUniform4fv, (GLuint program, GLint location, GLsizei count, const GLfloat * value), (program, location, count, value)) \
  X(void, glProgramUniform1iv, (GLuint program, GLint location, GLsizei count, const GLint * value), (program, location, count, value)) \
  X(void, glProgramUniform2iv, (GLuint program, GLint location, GLsizei count, const GLint * value), (program, location, count, value)) \
  X(void, glProgramUniform3iv, (GLuint program, GLint location, GLsizei count, const GLint * value), (program, location, count, value)) \
  X(void, glProgramUniform4iv, (GLuint program, GLint location, GLsizei count, const GLint * value), (program, location, count, value)) \
  X(void, glProgramUniform1uiv, (GLuint program, GLint location, GLsizei count, const GLuint * value), (program, location, count, value)) \
  X(void, glProgramUniform2uiv, (GLuint program, GLint location, GLsizei count, const GLuint * value), (program, location, count, value)) \
  X(void, glProgramUniform3uiv, (GLuint program, GLint location, GLsizei count, const GLuint * value), (program, location, count, value)) \
  X(void, glProgramUniform4uiv, (GLuint program, GLint location, GLsizei count, const GLuint * value), (program, location, count, value)) \
  X(void, glProgramUniformMatrix2fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix3fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix4fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix2x3fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix3x2fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix2x4fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix4x2fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix3x4fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glProgramUniformMatrix4x3fv, (GLuint program, GLint location, GLsizei count, GLboolean transpose, const GLfloat * value), (program, location, count, transpose, value)) \
  X(void, glGetProgramInterfaceiv, (GLuint program, GLenum programInterface, GLenum pname, GLint * params), (program, programInterface, pname, params)) \
  X(void, glGetProgramResourceiv, (GLuint program, GLenum programInterface, GLuint index, GLsizei propCount, const GLenum * props, GLsizei bufSize, GLsizei * length, GLint * params), (program, programInterface, index, propCount, props, bufSize, length, params)) \
  X(GLuint, glGetProgramResourceIndex, (GLuint program, GLenum programInterface, const char * name), (program, programInterface, name)) \
  X(GLint, glGetProgramResourceLocation, (GLuint program, GLenum programInterface, const char * name), (program, programInterface, name)) \
  X(void, glGetProgramResourceName, (GLuint program, GLenum programInterface, GLuint index, GLsizei bufSize, GLsizei * length, char * name), (program, programInterface, index, bufSize, length, name)) \
  X(void, glBindImageTexture, (GLuint unit, GLuint texture, GLint level, GLboolean layered, GLint layer, GLenum access, GLenum format), (unit, texture, level, layered, layer, access, format)) \
  X(void, glDispatchCompute, (GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z), (num_groups_x, num_groups_y, num_groups_z)) \
  X(void, glDispatchComputeIndirect, (GLintptr indirect), (indirect)) \
  X(void, glBindVertexBuffer, (GLuint bindingindex, GLuint buffer, GLintptr offset, GLintptr stride), (bindingindex, buffer, offset, stride)) \
  X(void, glVertexAttribBinding, (GLuint attribindex, GLuint bindingindex), (attribindex, bindingindex)) \
  X(void, glVertexAttribFormat, (GLuint attribindex, GLint size, GLenum type, GLboolean normalized, GLuint relativeoffset), (attribindex, size, type, normalized, relativeoffset)) \
  X(void, glVertexAttribIFormat, (GLuint attribindex, GLint size, GLenum type, GLuint relativeoffset), (attribindex, size, type, relativeoffset)) \
  X(void, glVertexBindingDivisor, (GLuint bindingindex, GLuint divisor), (bindingindex, divisor)) \
  X(void, glDrawArraysIndirect, (GLenum mode, const void * indirect), (mode, indirect)) \
  X(void, glDrawElementsIndirect, (GLenum mode, GLenum type, const void * indirect), (mode, type, indirect)) \
  X(void, glTexStorage2DMultisample, (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations), (target, samples, internalformat, width, height, fixedsamplelocations)) \
  X(void, glSampleMaski, (GLuint maskNumber, GLbitfield mask), (maskNumber, mask)) \
  X(void, glGetMultisamplefv, (GLenum pname, GLuint index, GLfloat * val), (pname, index, val)) \
  X(void, glFramebufferParameteri, (GLenum target, GLenum pname, GLint param), (target, pname, param)) \
  X(void, glGetFramebufferParameteriv, (GLenum target, GLenum pname, GLint * params), (target, pname, params)) \


#endif  // GLES31_ONLY_FUNCTIONS_H
