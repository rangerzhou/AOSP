// Generated Code - DO NOT EDIT !!
// generated by 'emugen'


#include <string.h>
#include "gles1_server_context.h"


#include <stdio.h>

int gles1_server_context_t::initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData)
{
	glAlphaFunc = (glAlphaFunc_server_proc_t) getProc("glAlphaFunc", userData);
	glClearColor = (glClearColor_server_proc_t) getProc("glClearColor", userData);
	glClearDepthf = (glClearDepthf_server_proc_t) getProc("glClearDepthf", userData);
	glClipPlanef = (glClipPlanef_server_proc_t) getProc("glClipPlanef", userData);
	glColor4f = (glColor4f_server_proc_t) getProc("glColor4f", userData);
	glDepthRangef = (glDepthRangef_server_proc_t) getProc("glDepthRangef", userData);
	glFogf = (glFogf_server_proc_t) getProc("glFogf", userData);
	glFogfv = (glFogfv_server_proc_t) getProc("glFogfv", userData);
	glFrustumf = (glFrustumf_server_proc_t) getProc("glFrustumf", userData);
	glGetClipPlanef = (glGetClipPlanef_server_proc_t) getProc("glGetClipPlanef", userData);
	glGetFloatv = (glGetFloatv_server_proc_t) getProc("glGetFloatv", userData);
	glGetLightfv = (glGetLightfv_server_proc_t) getProc("glGetLightfv", userData);
	glGetMaterialfv = (glGetMaterialfv_server_proc_t) getProc("glGetMaterialfv", userData);
	glGetTexEnvfv = (glGetTexEnvfv_server_proc_t) getProc("glGetTexEnvfv", userData);
	glGetTexParameterfv = (glGetTexParameterfv_server_proc_t) getProc("glGetTexParameterfv", userData);
	glLightModelf = (glLightModelf_server_proc_t) getProc("glLightModelf", userData);
	glLightModelfv = (glLightModelfv_server_proc_t) getProc("glLightModelfv", userData);
	glLightf = (glLightf_server_proc_t) getProc("glLightf", userData);
	glLightfv = (glLightfv_server_proc_t) getProc("glLightfv", userData);
	glLineWidth = (glLineWidth_server_proc_t) getProc("glLineWidth", userData);
	glLoadMatrixf = (glLoadMatrixf_server_proc_t) getProc("glLoadMatrixf", userData);
	glMaterialf = (glMaterialf_server_proc_t) getProc("glMaterialf", userData);
	glMaterialfv = (glMaterialfv_server_proc_t) getProc("glMaterialfv", userData);
	glMultMatrixf = (glMultMatrixf_server_proc_t) getProc("glMultMatrixf", userData);
	glMultiTexCoord4f = (glMultiTexCoord4f_server_proc_t) getProc("glMultiTexCoord4f", userData);
	glNormal3f = (glNormal3f_server_proc_t) getProc("glNormal3f", userData);
	glOrthof = (glOrthof_server_proc_t) getProc("glOrthof", userData);
	glPointParameterf = (glPointParameterf_server_proc_t) getProc("glPointParameterf", userData);
	glPointParameterfv = (glPointParameterfv_server_proc_t) getProc("glPointParameterfv", userData);
	glPointSize = (glPointSize_server_proc_t) getProc("glPointSize", userData);
	glPolygonOffset = (glPolygonOffset_server_proc_t) getProc("glPolygonOffset", userData);
	glRotatef = (glRotatef_server_proc_t) getProc("glRotatef", userData);
	glScalef = (glScalef_server_proc_t) getProc("glScalef", userData);
	glTexEnvf = (glTexEnvf_server_proc_t) getProc("glTexEnvf", userData);
	glTexEnvfv = (glTexEnvfv_server_proc_t) getProc("glTexEnvfv", userData);
	glTexParameterf = (glTexParameterf_server_proc_t) getProc("glTexParameterf", userData);
	glTexParameterfv = (glTexParameterfv_server_proc_t) getProc("glTexParameterfv", userData);
	glTranslatef = (glTranslatef_server_proc_t) getProc("glTranslatef", userData);
	glActiveTexture = (glActiveTexture_server_proc_t) getProc("glActiveTexture", userData);
	glAlphaFuncx = (glAlphaFuncx_server_proc_t) getProc("glAlphaFuncx", userData);
	glBindBuffer = (glBindBuffer_server_proc_t) getProc("glBindBuffer", userData);
	glBindTexture = (glBindTexture_server_proc_t) getProc("glBindTexture", userData);
	glBlendFunc = (glBlendFunc_server_proc_t) getProc("glBlendFunc", userData);
	glBufferData = (glBufferData_server_proc_t) getProc("glBufferData", userData);
	glBufferSubData = (glBufferSubData_server_proc_t) getProc("glBufferSubData", userData);
	glClear = (glClear_server_proc_t) getProc("glClear", userData);
	glClearColorx = (glClearColorx_server_proc_t) getProc("glClearColorx", userData);
	glClearDepthx = (glClearDepthx_server_proc_t) getProc("glClearDepthx", userData);
	glClearStencil = (glClearStencil_server_proc_t) getProc("glClearStencil", userData);
	glClientActiveTexture = (glClientActiveTexture_server_proc_t) getProc("glClientActiveTexture", userData);
	glColor4ub = (glColor4ub_server_proc_t) getProc("glColor4ub", userData);
	glColor4x = (glColor4x_server_proc_t) getProc("glColor4x", userData);
	glColorMask = (glColorMask_server_proc_t) getProc("glColorMask", userData);
	glColorPointer = (glColorPointer_server_proc_t) getProc("glColorPointer", userData);
	glCompressedTexImage2D = (glCompressedTexImage2D_server_proc_t) getProc("glCompressedTexImage2D", userData);
	glCompressedTexSubImage2D = (glCompressedTexSubImage2D_server_proc_t) getProc("glCompressedTexSubImage2D", userData);
	glCopyTexImage2D = (glCopyTexImage2D_server_proc_t) getProc("glCopyTexImage2D", userData);
	glCopyTexSubImage2D = (glCopyTexSubImage2D_server_proc_t) getProc("glCopyTexSubImage2D", userData);
	glCullFace = (glCullFace_server_proc_t) getProc("glCullFace", userData);
	glDeleteBuffers = (glDeleteBuffers_dec_server_proc_t) getProc("glDeleteBuffers", userData);
	glDeleteTextures = (glDeleteTextures_dec_server_proc_t) getProc("glDeleteTextures", userData);
	glDepthFunc = (glDepthFunc_server_proc_t) getProc("glDepthFunc", userData);
	glDepthMask = (glDepthMask_server_proc_t) getProc("glDepthMask", userData);
	glDepthRangex = (glDepthRangex_server_proc_t) getProc("glDepthRangex", userData);
	glDisable = (glDisable_server_proc_t) getProc("glDisable", userData);
	glDisableClientState = (glDisableClientState_server_proc_t) getProc("glDisableClientState", userData);
	glDrawArrays = (glDrawArrays_server_proc_t) getProc("glDrawArrays", userData);
	glDrawElements = (glDrawElements_server_proc_t) getProc("glDrawElements", userData);
	glEnable = (glEnable_server_proc_t) getProc("glEnable", userData);
	glEnableClientState = (glEnableClientState_server_proc_t) getProc("glEnableClientState", userData);
	glFinish = (glFinish_server_proc_t) getProc("glFinish", userData);
	glFlush = (glFlush_server_proc_t) getProc("glFlush", userData);
	glFogx = (glFogx_server_proc_t) getProc("glFogx", userData);
	glFogxv = (glFogxv_server_proc_t) getProc("glFogxv", userData);
	glFrontFace = (glFrontFace_server_proc_t) getProc("glFrontFace", userData);
	glFrustumx = (glFrustumx_server_proc_t) getProc("glFrustumx", userData);
	glGetBooleanv = (glGetBooleanv_server_proc_t) getProc("glGetBooleanv", userData);
	glGetBufferParameteriv = (glGetBufferParameteriv_server_proc_t) getProc("glGetBufferParameteriv", userData);
	glClipPlanex = (glClipPlanex_server_proc_t) getProc("glClipPlanex", userData);
	glGenBuffers = (glGenBuffers_dec_server_proc_t) getProc("glGenBuffers", userData);
	glGenTextures = (glGenTextures_dec_server_proc_t) getProc("glGenTextures", userData);
	glGetError = (glGetError_server_proc_t) getProc("glGetError", userData);
	glGetFixedv = (glGetFixedv_server_proc_t) getProc("glGetFixedv", userData);
	glGetIntegerv = (glGetIntegerv_server_proc_t) getProc("glGetIntegerv", userData);
	glGetLightxv = (glGetLightxv_server_proc_t) getProc("glGetLightxv", userData);
	glGetMaterialxv = (glGetMaterialxv_server_proc_t) getProc("glGetMaterialxv", userData);
	glGetPointerv = (glGetPointerv_server_proc_t) getProc("glGetPointerv", userData);
	glGetString = (glGetString_server_proc_t) getProc("glGetString", userData);
	glGetTexEnviv = (glGetTexEnviv_server_proc_t) getProc("glGetTexEnviv", userData);
	glGetTexEnvxv = (glGetTexEnvxv_server_proc_t) getProc("glGetTexEnvxv", userData);
	glGetTexParameteriv = (glGetTexParameteriv_server_proc_t) getProc("glGetTexParameteriv", userData);
	glGetTexParameterxv = (glGetTexParameterxv_server_proc_t) getProc("glGetTexParameterxv", userData);
	glHint = (glHint_server_proc_t) getProc("glHint", userData);
	glIsBuffer = (glIsBuffer_server_proc_t) getProc("glIsBuffer", userData);
	glIsEnabled = (glIsEnabled_server_proc_t) getProc("glIsEnabled", userData);
	glIsTexture = (glIsTexture_server_proc_t) getProc("glIsTexture", userData);
	glLightModelx = (glLightModelx_server_proc_t) getProc("glLightModelx", userData);
	glLightModelxv = (glLightModelxv_server_proc_t) getProc("glLightModelxv", userData);
	glLightx = (glLightx_server_proc_t) getProc("glLightx", userData);
	glLightxv = (glLightxv_server_proc_t) getProc("glLightxv", userData);
	glLineWidthx = (glLineWidthx_server_proc_t) getProc("glLineWidthx", userData);
	glLoadIdentity = (glLoadIdentity_server_proc_t) getProc("glLoadIdentity", userData);
	glLoadMatrixx = (glLoadMatrixx_server_proc_t) getProc("glLoadMatrixx", userData);
	glLogicOp = (glLogicOp_server_proc_t) getProc("glLogicOp", userData);
	glMaterialx = (glMaterialx_server_proc_t) getProc("glMaterialx", userData);
	glMaterialxv = (glMaterialxv_server_proc_t) getProc("glMaterialxv", userData);
	glMatrixMode = (glMatrixMode_server_proc_t) getProc("glMatrixMode", userData);
	glMultMatrixx = (glMultMatrixx_server_proc_t) getProc("glMultMatrixx", userData);
	glMultiTexCoord4x = (glMultiTexCoord4x_server_proc_t) getProc("glMultiTexCoord4x", userData);
	glNormal3x = (glNormal3x_server_proc_t) getProc("glNormal3x", userData);
	glNormalPointer = (glNormalPointer_server_proc_t) getProc("glNormalPointer", userData);
	glOrthox = (glOrthox_server_proc_t) getProc("glOrthox", userData);
	glPixelStorei = (glPixelStorei_server_proc_t) getProc("glPixelStorei", userData);
	glPointParameterx = (glPointParameterx_server_proc_t) getProc("glPointParameterx", userData);
	glPointParameterxv = (glPointParameterxv_server_proc_t) getProc("glPointParameterxv", userData);
	glPointSizex = (glPointSizex_server_proc_t) getProc("glPointSizex", userData);
	glPolygonOffsetx = (glPolygonOffsetx_server_proc_t) getProc("glPolygonOffsetx", userData);
	glPopMatrix = (glPopMatrix_server_proc_t) getProc("glPopMatrix", userData);
	glPushMatrix = (glPushMatrix_server_proc_t) getProc("glPushMatrix", userData);
	glReadPixels = (glReadPixels_server_proc_t) getProc("glReadPixels", userData);
	glRotatex = (glRotatex_server_proc_t) getProc("glRotatex", userData);
	glSampleCoverage = (glSampleCoverage_server_proc_t) getProc("glSampleCoverage", userData);
	glSampleCoveragex = (glSampleCoveragex_server_proc_t) getProc("glSampleCoveragex", userData);
	glScalex = (glScalex_server_proc_t) getProc("glScalex", userData);
	glScissor = (glScissor_server_proc_t) getProc("glScissor", userData);
	glShadeModel = (glShadeModel_server_proc_t) getProc("glShadeModel", userData);
	glStencilFunc = (glStencilFunc_server_proc_t) getProc("glStencilFunc", userData);
	glStencilMask = (glStencilMask_server_proc_t) getProc("glStencilMask", userData);
	glStencilOp = (glStencilOp_server_proc_t) getProc("glStencilOp", userData);
	glTexCoordPointer = (glTexCoordPointer_server_proc_t) getProc("glTexCoordPointer", userData);
	glTexEnvi = (glTexEnvi_server_proc_t) getProc("glTexEnvi", userData);
	glTexEnvx = (glTexEnvx_server_proc_t) getProc("glTexEnvx", userData);
	glTexEnviv = (glTexEnviv_server_proc_t) getProc("glTexEnviv", userData);
	glTexEnvxv = (glTexEnvxv_server_proc_t) getProc("glTexEnvxv", userData);
	glTexImage2D = (glTexImage2D_server_proc_t) getProc("glTexImage2D", userData);
	glTexParameteri = (glTexParameteri_server_proc_t) getProc("glTexParameteri", userData);
	glTexParameterx = (glTexParameterx_server_proc_t) getProc("glTexParameterx", userData);
	glTexParameteriv = (glTexParameteriv_server_proc_t) getProc("glTexParameteriv", userData);
	glTexParameterxv = (glTexParameterxv_server_proc_t) getProc("glTexParameterxv", userData);
	glTexSubImage2D = (glTexSubImage2D_server_proc_t) getProc("glTexSubImage2D", userData);
	glTranslatex = (glTranslatex_server_proc_t) getProc("glTranslatex", userData);
	glVertexPointer = (glVertexPointer_server_proc_t) getProc("glVertexPointer", userData);
	glViewport = (glViewport_server_proc_t) getProc("glViewport", userData);
	glPointSizePointerOES = (glPointSizePointerOES_server_proc_t) getProc("glPointSizePointerOES", userData);
	glVertexPointerOffset = (glVertexPointerOffset_server_proc_t) getProc("glVertexPointerOffset", userData);
	glColorPointerOffset = (glColorPointerOffset_server_proc_t) getProc("glColorPointerOffset", userData);
	glNormalPointerOffset = (glNormalPointerOffset_server_proc_t) getProc("glNormalPointerOffset", userData);
	glPointSizePointerOffset = (glPointSizePointerOffset_server_proc_t) getProc("glPointSizePointerOffset", userData);
	glTexCoordPointerOffset = (glTexCoordPointerOffset_server_proc_t) getProc("glTexCoordPointerOffset", userData);
	glWeightPointerOffset = (glWeightPointerOffset_server_proc_t) getProc("glWeightPointerOffset", userData);
	glMatrixIndexPointerOffset = (glMatrixIndexPointerOffset_server_proc_t) getProc("glMatrixIndexPointerOffset", userData);
	glVertexPointerData = (glVertexPointerData_server_proc_t) getProc("glVertexPointerData", userData);
	glColorPointerData = (glColorPointerData_server_proc_t) getProc("glColorPointerData", userData);
	glNormalPointerData = (glNormalPointerData_server_proc_t) getProc("glNormalPointerData", userData);
	glTexCoordPointerData = (glTexCoordPointerData_server_proc_t) getProc("glTexCoordPointerData", userData);
	glPointSizePointerData = (glPointSizePointerData_server_proc_t) getProc("glPointSizePointerData", userData);
	glWeightPointerData = (glWeightPointerData_server_proc_t) getProc("glWeightPointerData", userData);
	glMatrixIndexPointerData = (glMatrixIndexPointerData_server_proc_t) getProc("glMatrixIndexPointerData", userData);
	glDrawElementsOffset = (glDrawElementsOffset_server_proc_t) getProc("glDrawElementsOffset", userData);
	glDrawElementsData = (glDrawElementsData_server_proc_t) getProc("glDrawElementsData", userData);
	glGetCompressedTextureFormats = (glGetCompressedTextureFormats_server_proc_t) getProc("glGetCompressedTextureFormats", userData);
	glFinishRoundTrip = (glFinishRoundTrip_server_proc_t) getProc("glFinishRoundTrip", userData);
	glBlendEquationSeparateOES = (glBlendEquationSeparateOES_server_proc_t) getProc("glBlendEquationSeparateOES", userData);
	glBlendFuncSeparateOES = (glBlendFuncSeparateOES_server_proc_t) getProc("glBlendFuncSeparateOES", userData);
	glBlendEquationOES = (glBlendEquationOES_server_proc_t) getProc("glBlendEquationOES", userData);
	glDrawTexsOES = (glDrawTexsOES_server_proc_t) getProc("glDrawTexsOES", userData);
	glDrawTexiOES = (glDrawTexiOES_server_proc_t) getProc("glDrawTexiOES", userData);
	glDrawTexxOES = (glDrawTexxOES_server_proc_t) getProc("glDrawTexxOES", userData);
	glDrawTexsvOES = (glDrawTexsvOES_server_proc_t) getProc("glDrawTexsvOES", userData);
	glDrawTexivOES = (glDrawTexivOES_server_proc_t) getProc("glDrawTexivOES", userData);
	glDrawTexxvOES = (glDrawTexxvOES_server_proc_t) getProc("glDrawTexxvOES", userData);
	glDrawTexfOES = (glDrawTexfOES_server_proc_t) getProc("glDrawTexfOES", userData);
	glDrawTexfvOES = (glDrawTexfvOES_server_proc_t) getProc("glDrawTexfvOES", userData);
	glEGLImageTargetTexture2DOES = (glEGLImageTargetTexture2DOES_server_proc_t) getProc("glEGLImageTargetTexture2DOES", userData);
	glEGLImageTargetRenderbufferStorageOES = (glEGLImageTargetRenderbufferStorageOES_server_proc_t) getProc("glEGLImageTargetRenderbufferStorageOES", userData);
	glAlphaFuncxOES = (glAlphaFuncxOES_server_proc_t) getProc("glAlphaFuncxOES", userData);
	glClearColorxOES = (glClearColorxOES_server_proc_t) getProc("glClearColorxOES", userData);
	glClearDepthxOES = (glClearDepthxOES_server_proc_t) getProc("glClearDepthxOES", userData);
	glClipPlanexOES = (glClipPlanexOES_server_proc_t) getProc("glClipPlanexOES", userData);
	glClipPlanexIMG = (glClipPlanexIMG_server_proc_t) getProc("glClipPlanexIMG", userData);
	glColor4xOES = (glColor4xOES_server_proc_t) getProc("glColor4xOES", userData);
	glDepthRangexOES = (glDepthRangexOES_server_proc_t) getProc("glDepthRangexOES", userData);
	glFogxOES = (glFogxOES_server_proc_t) getProc("glFogxOES", userData);
	glFogxvOES = (glFogxvOES_server_proc_t) getProc("glFogxvOES", userData);
	glFrustumxOES = (glFrustumxOES_server_proc_t) getProc("glFrustumxOES", userData);
	glGetClipPlanexOES = (glGetClipPlanexOES_server_proc_t) getProc("glGetClipPlanexOES", userData);
	glGetClipPlanex = (glGetClipPlanex_server_proc_t) getProc("glGetClipPlanex", userData);
	glGetFixedvOES = (glGetFixedvOES_server_proc_t) getProc("glGetFixedvOES", userData);
	glGetLightxvOES = (glGetLightxvOES_server_proc_t) getProc("glGetLightxvOES", userData);
	glGetMaterialxvOES = (glGetMaterialxvOES_server_proc_t) getProc("glGetMaterialxvOES", userData);
	glGetTexEnvxvOES = (glGetTexEnvxvOES_server_proc_t) getProc("glGetTexEnvxvOES", userData);
	glGetTexParameterxvOES = (glGetTexParameterxvOES_server_proc_t) getProc("glGetTexParameterxvOES", userData);
	glLightModelxOES = (glLightModelxOES_server_proc_t) getProc("glLightModelxOES", userData);
	glLightModelxvOES = (glLightModelxvOES_server_proc_t) getProc("glLightModelxvOES", userData);
	glLightxOES = (glLightxOES_server_proc_t) getProc("glLightxOES", userData);
	glLightxvOES = (glLightxvOES_server_proc_t) getProc("glLightxvOES", userData);
	glLineWidthxOES = (glLineWidthxOES_server_proc_t) getProc("glLineWidthxOES", userData);
	glLoadMatrixxOES = (glLoadMatrixxOES_server_proc_t) getProc("glLoadMatrixxOES", userData);
	glMaterialxOES = (glMaterialxOES_server_proc_t) getProc("glMaterialxOES", userData);
	glMaterialxvOES = (glMaterialxvOES_server_proc_t) getProc("glMaterialxvOES", userData);
	glMultMatrixxOES = (glMultMatrixxOES_server_proc_t) getProc("glMultMatrixxOES", userData);
	glMultiTexCoord4xOES = (glMultiTexCoord4xOES_server_proc_t) getProc("glMultiTexCoord4xOES", userData);
	glNormal3xOES = (glNormal3xOES_server_proc_t) getProc("glNormal3xOES", userData);
	glOrthoxOES = (glOrthoxOES_server_proc_t) getProc("glOrthoxOES", userData);
	glPointParameterxOES = (glPointParameterxOES_server_proc_t) getProc("glPointParameterxOES", userData);
	glPointParameterxvOES = (glPointParameterxvOES_server_proc_t) getProc("glPointParameterxvOES", userData);
	glPointSizexOES = (glPointSizexOES_server_proc_t) getProc("glPointSizexOES", userData);
	glPolygonOffsetxOES = (glPolygonOffsetxOES_server_proc_t) getProc("glPolygonOffsetxOES", userData);
	glRotatexOES = (glRotatexOES_server_proc_t) getProc("glRotatexOES", userData);
	glSampleCoveragexOES = (glSampleCoveragexOES_server_proc_t) getProc("glSampleCoveragexOES", userData);
	glScalexOES = (glScalexOES_server_proc_t) getProc("glScalexOES", userData);
	glTexEnvxOES = (glTexEnvxOES_server_proc_t) getProc("glTexEnvxOES", userData);
	glTexEnvxvOES = (glTexEnvxvOES_server_proc_t) getProc("glTexEnvxvOES", userData);
	glTexParameterxOES = (glTexParameterxOES_server_proc_t) getProc("glTexParameterxOES", userData);
	glTexParameterxvOES = (glTexParameterxvOES_server_proc_t) getProc("glTexParameterxvOES", userData);
	glTranslatexOES = (glTranslatexOES_server_proc_t) getProc("glTranslatexOES", userData);
	glIsRenderbufferOES = (glIsRenderbufferOES_server_proc_t) getProc("glIsRenderbufferOES", userData);
	glBindRenderbufferOES = (glBindRenderbufferOES_server_proc_t) getProc("glBindRenderbufferOES", userData);
	glDeleteRenderbuffersOES = (glDeleteRenderbuffersOES_dec_server_proc_t) getProc("glDeleteRenderbuffersOES", userData);
	glGenRenderbuffersOES = (glGenRenderbuffersOES_dec_server_proc_t) getProc("glGenRenderbuffersOES", userData);
	glRenderbufferStorageOES = (glRenderbufferStorageOES_server_proc_t) getProc("glRenderbufferStorageOES", userData);
	glGetRenderbufferParameterivOES = (glGetRenderbufferParameterivOES_server_proc_t) getProc("glGetRenderbufferParameterivOES", userData);
	glIsFramebufferOES = (glIsFramebufferOES_server_proc_t) getProc("glIsFramebufferOES", userData);
	glBindFramebufferOES = (glBindFramebufferOES_server_proc_t) getProc("glBindFramebufferOES", userData);
	glDeleteFramebuffersOES = (glDeleteFramebuffersOES_dec_server_proc_t) getProc("glDeleteFramebuffersOES", userData);
	glGenFramebuffersOES = (glGenFramebuffersOES_dec_server_proc_t) getProc("glGenFramebuffersOES", userData);
	glCheckFramebufferStatusOES = (glCheckFramebufferStatusOES_server_proc_t) getProc("glCheckFramebufferStatusOES", userData);
	glFramebufferRenderbufferOES = (glFramebufferRenderbufferOES_server_proc_t) getProc("glFramebufferRenderbufferOES", userData);
	glFramebufferTexture2DOES = (glFramebufferTexture2DOES_server_proc_t) getProc("glFramebufferTexture2DOES", userData);
	glGetFramebufferAttachmentParameterivOES = (glGetFramebufferAttachmentParameterivOES_server_proc_t) getProc("glGetFramebufferAttachmentParameterivOES", userData);
	glGenerateMipmapOES = (glGenerateMipmapOES_server_proc_t) getProc("glGenerateMipmapOES", userData);
	glMapBufferOES = (glMapBufferOES_server_proc_t) getProc("glMapBufferOES", userData);
	glUnmapBufferOES = (glUnmapBufferOES_server_proc_t) getProc("glUnmapBufferOES", userData);
	glGetBufferPointervOES = (glGetBufferPointervOES_server_proc_t) getProc("glGetBufferPointervOES", userData);
	glCurrentPaletteMatrixOES = (glCurrentPaletteMatrixOES_server_proc_t) getProc("glCurrentPaletteMatrixOES", userData);
	glLoadPaletteFromModelViewMatrixOES = (glLoadPaletteFromModelViewMatrixOES_server_proc_t) getProc("glLoadPaletteFromModelViewMatrixOES", userData);
	glMatrixIndexPointerOES = (glMatrixIndexPointerOES_server_proc_t) getProc("glMatrixIndexPointerOES", userData);
	glWeightPointerOES = (glWeightPointerOES_server_proc_t) getProc("glWeightPointerOES", userData);
	glQueryMatrixxOES = (glQueryMatrixxOES_server_proc_t) getProc("glQueryMatrixxOES", userData);
	glDepthRangefOES = (glDepthRangefOES_server_proc_t) getProc("glDepthRangefOES", userData);
	glFrustumfOES = (glFrustumfOES_server_proc_t) getProc("glFrustumfOES", userData);
	glOrthofOES = (glOrthofOES_server_proc_t) getProc("glOrthofOES", userData);
	glClipPlanefOES = (glClipPlanefOES_server_proc_t) getProc("glClipPlanefOES", userData);
	glClipPlanefIMG = (glClipPlanefIMG_server_proc_t) getProc("glClipPlanefIMG", userData);
	glGetClipPlanefOES = (glGetClipPlanefOES_server_proc_t) getProc("glGetClipPlanefOES", userData);
	glClearDepthfOES = (glClearDepthfOES_server_proc_t) getProc("glClearDepthfOES", userData);
	glTexGenfOES = (glTexGenfOES_server_proc_t) getProc("glTexGenfOES", userData);
	glTexGenfvOES = (glTexGenfvOES_server_proc_t) getProc("glTexGenfvOES", userData);
	glTexGeniOES = (glTexGeniOES_server_proc_t) getProc("glTexGeniOES", userData);
	glTexGenivOES = (glTexGenivOES_server_proc_t) getProc("glTexGenivOES", userData);
	glTexGenxOES = (glTexGenxOES_server_proc_t) getProc("glTexGenxOES", userData);
	glTexGenxvOES = (glTexGenxvOES_server_proc_t) getProc("glTexGenxvOES", userData);
	glGetTexGenfvOES = (glGetTexGenfvOES_server_proc_t) getProc("glGetTexGenfvOES", userData);
	glGetTexGenivOES = (glGetTexGenivOES_server_proc_t) getProc("glGetTexGenivOES", userData);
	glGetTexGenxvOES = (glGetTexGenxvOES_server_proc_t) getProc("glGetTexGenxvOES", userData);
	glBindVertexArrayOES = (glBindVertexArrayOES_server_proc_t) getProc("glBindVertexArrayOES", userData);
	glDeleteVertexArraysOES = (glDeleteVertexArraysOES_dec_server_proc_t) getProc("glDeleteVertexArraysOES", userData);
	glGenVertexArraysOES = (glGenVertexArraysOES_dec_server_proc_t) getProc("glGenVertexArraysOES", userData);
	glIsVertexArrayOES = (glIsVertexArrayOES_server_proc_t) getProc("glIsVertexArrayOES", userData);
	glDiscardFramebufferEXT = (glDiscardFramebufferEXT_server_proc_t) getProc("glDiscardFramebufferEXT", userData);
	glMultiDrawArraysEXT = (glMultiDrawArraysEXT_server_proc_t) getProc("glMultiDrawArraysEXT", userData);
	glMultiDrawElementsEXT = (glMultiDrawElementsEXT_server_proc_t) getProc("glMultiDrawElementsEXT", userData);
	glMultiDrawArraysSUN = (glMultiDrawArraysSUN_server_proc_t) getProc("glMultiDrawArraysSUN", userData);
	glMultiDrawElementsSUN = (glMultiDrawElementsSUN_server_proc_t) getProc("glMultiDrawElementsSUN", userData);
	glRenderbufferStorageMultisampleIMG = (glRenderbufferStorageMultisampleIMG_server_proc_t) getProc("glRenderbufferStorageMultisampleIMG", userData);
	glFramebufferTexture2DMultisampleIMG = (glFramebufferTexture2DMultisampleIMG_server_proc_t) getProc("glFramebufferTexture2DMultisampleIMG", userData);
	glDeleteFencesNV = (glDeleteFencesNV_server_proc_t) getProc("glDeleteFencesNV", userData);
	glGenFencesNV = (glGenFencesNV_server_proc_t) getProc("glGenFencesNV", userData);
	glIsFenceNV = (glIsFenceNV_server_proc_t) getProc("glIsFenceNV", userData);
	glTestFenceNV = (glTestFenceNV_server_proc_t) getProc("glTestFenceNV", userData);
	glGetFenceivNV = (glGetFenceivNV_server_proc_t) getProc("glGetFenceivNV", userData);
	glFinishFenceNV = (glFinishFenceNV_server_proc_t) getProc("glFinishFenceNV", userData);
	glSetFenceNV = (glSetFenceNV_server_proc_t) getProc("glSetFenceNV", userData);
	glGetDriverControlsQCOM = (glGetDriverControlsQCOM_server_proc_t) getProc("glGetDriverControlsQCOM", userData);
	glGetDriverControlStringQCOM = (glGetDriverControlStringQCOM_server_proc_t) getProc("glGetDriverControlStringQCOM", userData);
	glEnableDriverControlQCOM = (glEnableDriverControlQCOM_server_proc_t) getProc("glEnableDriverControlQCOM", userData);
	glDisableDriverControlQCOM = (glDisableDriverControlQCOM_server_proc_t) getProc("glDisableDriverControlQCOM", userData);
	glExtGetTexturesQCOM = (glExtGetTexturesQCOM_server_proc_t) getProc("glExtGetTexturesQCOM", userData);
	glExtGetBuffersQCOM = (glExtGetBuffersQCOM_server_proc_t) getProc("glExtGetBuffersQCOM", userData);
	glExtGetRenderbuffersQCOM = (glExtGetRenderbuffersQCOM_server_proc_t) getProc("glExtGetRenderbuffersQCOM", userData);
	glExtGetFramebuffersQCOM = (glExtGetFramebuffersQCOM_server_proc_t) getProc("glExtGetFramebuffersQCOM", userData);
	glExtGetTexLevelParameterivQCOM = (glExtGetTexLevelParameterivQCOM_server_proc_t) getProc("glExtGetTexLevelParameterivQCOM", userData);
	glExtTexObjectStateOverrideiQCOM = (glExtTexObjectStateOverrideiQCOM_server_proc_t) getProc("glExtTexObjectStateOverrideiQCOM", userData);
	glExtGetTexSubImageQCOM = (glExtGetTexSubImageQCOM_server_proc_t) getProc("glExtGetTexSubImageQCOM", userData);
	glExtGetBufferPointervQCOM = (glExtGetBufferPointervQCOM_server_proc_t) getProc("glExtGetBufferPointervQCOM", userData);
	glExtGetShadersQCOM = (glExtGetShadersQCOM_server_proc_t) getProc("glExtGetShadersQCOM", userData);
	glExtGetProgramsQCOM = (glExtGetProgramsQCOM_server_proc_t) getProc("glExtGetProgramsQCOM", userData);
	glExtIsProgramBinaryQCOM = (glExtIsProgramBinaryQCOM_server_proc_t) getProc("glExtIsProgramBinaryQCOM", userData);
	glExtGetProgramBinarySourceQCOM = (glExtGetProgramBinarySourceQCOM_server_proc_t) getProc("glExtGetProgramBinarySourceQCOM", userData);
	glStartTilingQCOM = (glStartTilingQCOM_server_proc_t) getProc("glStartTilingQCOM", userData);
	glEndTilingQCOM = (glEndTilingQCOM_server_proc_t) getProc("glEndTilingQCOM", userData);
	glGetGraphicsResetStatusEXT = (glGetGraphicsResetStatusEXT_server_proc_t) getProc("glGetGraphicsResetStatusEXT", userData);
	glReadnPixelsEXT = (glReadnPixelsEXT_server_proc_t) getProc("glReadnPixelsEXT", userData);
	return 0;
}

