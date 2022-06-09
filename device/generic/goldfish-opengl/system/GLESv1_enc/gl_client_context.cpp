// Generated Code - DO NOT EDIT !!
// generated by 'emugen'


#include <string.h>
#include "gl_client_context.h"


#include <stdio.h>

int gl_client_context_t::initDispatchByName(void *(*getProc)(const char *, void *userData), void *userData)
{
	glAlphaFunc = (glAlphaFunc_client_proc_t) getProc("glAlphaFunc", userData);
	glClearColor = (glClearColor_client_proc_t) getProc("glClearColor", userData);
	glClearDepthf = (glClearDepthf_client_proc_t) getProc("glClearDepthf", userData);
	glClipPlanef = (glClipPlanef_client_proc_t) getProc("glClipPlanef", userData);
	glColor4f = (glColor4f_client_proc_t) getProc("glColor4f", userData);
	glDepthRangef = (glDepthRangef_client_proc_t) getProc("glDepthRangef", userData);
	glFogf = (glFogf_client_proc_t) getProc("glFogf", userData);
	glFogfv = (glFogfv_client_proc_t) getProc("glFogfv", userData);
	glFrustumf = (glFrustumf_client_proc_t) getProc("glFrustumf", userData);
	glGetClipPlanef = (glGetClipPlanef_client_proc_t) getProc("glGetClipPlanef", userData);
	glGetFloatv = (glGetFloatv_client_proc_t) getProc("glGetFloatv", userData);
	glGetLightfv = (glGetLightfv_client_proc_t) getProc("glGetLightfv", userData);
	glGetMaterialfv = (glGetMaterialfv_client_proc_t) getProc("glGetMaterialfv", userData);
	glGetTexEnvfv = (glGetTexEnvfv_client_proc_t) getProc("glGetTexEnvfv", userData);
	glGetTexParameterfv = (glGetTexParameterfv_client_proc_t) getProc("glGetTexParameterfv", userData);
	glLightModelf = (glLightModelf_client_proc_t) getProc("glLightModelf", userData);
	glLightModelfv = (glLightModelfv_client_proc_t) getProc("glLightModelfv", userData);
	glLightf = (glLightf_client_proc_t) getProc("glLightf", userData);
	glLightfv = (glLightfv_client_proc_t) getProc("glLightfv", userData);
	glLineWidth = (glLineWidth_client_proc_t) getProc("glLineWidth", userData);
	glLoadMatrixf = (glLoadMatrixf_client_proc_t) getProc("glLoadMatrixf", userData);
	glMaterialf = (glMaterialf_client_proc_t) getProc("glMaterialf", userData);
	glMaterialfv = (glMaterialfv_client_proc_t) getProc("glMaterialfv", userData);
	glMultMatrixf = (glMultMatrixf_client_proc_t) getProc("glMultMatrixf", userData);
	glMultiTexCoord4f = (glMultiTexCoord4f_client_proc_t) getProc("glMultiTexCoord4f", userData);
	glNormal3f = (glNormal3f_client_proc_t) getProc("glNormal3f", userData);
	glOrthof = (glOrthof_client_proc_t) getProc("glOrthof", userData);
	glPointParameterf = (glPointParameterf_client_proc_t) getProc("glPointParameterf", userData);
	glPointParameterfv = (glPointParameterfv_client_proc_t) getProc("glPointParameterfv", userData);
	glPointSize = (glPointSize_client_proc_t) getProc("glPointSize", userData);
	glPolygonOffset = (glPolygonOffset_client_proc_t) getProc("glPolygonOffset", userData);
	glRotatef = (glRotatef_client_proc_t) getProc("glRotatef", userData);
	glScalef = (glScalef_client_proc_t) getProc("glScalef", userData);
	glTexEnvf = (glTexEnvf_client_proc_t) getProc("glTexEnvf", userData);
	glTexEnvfv = (glTexEnvfv_client_proc_t) getProc("glTexEnvfv", userData);
	glTexParameterf = (glTexParameterf_client_proc_t) getProc("glTexParameterf", userData);
	glTexParameterfv = (glTexParameterfv_client_proc_t) getProc("glTexParameterfv", userData);
	glTranslatef = (glTranslatef_client_proc_t) getProc("glTranslatef", userData);
	glActiveTexture = (glActiveTexture_client_proc_t) getProc("glActiveTexture", userData);
	glAlphaFuncx = (glAlphaFuncx_client_proc_t) getProc("glAlphaFuncx", userData);
	glBindBuffer = (glBindBuffer_client_proc_t) getProc("glBindBuffer", userData);
	glBindTexture = (glBindTexture_client_proc_t) getProc("glBindTexture", userData);
	glBlendFunc = (glBlendFunc_client_proc_t) getProc("glBlendFunc", userData);
	glBufferData = (glBufferData_client_proc_t) getProc("glBufferData", userData);
	glBufferSubData = (glBufferSubData_client_proc_t) getProc("glBufferSubData", userData);
	glClear = (glClear_client_proc_t) getProc("glClear", userData);
	glClearColorx = (glClearColorx_client_proc_t) getProc("glClearColorx", userData);
	glClearDepthx = (glClearDepthx_client_proc_t) getProc("glClearDepthx", userData);
	glClearStencil = (glClearStencil_client_proc_t) getProc("glClearStencil", userData);
	glClientActiveTexture = (glClientActiveTexture_client_proc_t) getProc("glClientActiveTexture", userData);
	glColor4ub = (glColor4ub_client_proc_t) getProc("glColor4ub", userData);
	glColor4x = (glColor4x_client_proc_t) getProc("glColor4x", userData);
	glColorMask = (glColorMask_client_proc_t) getProc("glColorMask", userData);
	glColorPointer = (glColorPointer_client_proc_t) getProc("glColorPointer", userData);
	glCompressedTexImage2D = (glCompressedTexImage2D_client_proc_t) getProc("glCompressedTexImage2D", userData);
	glCompressedTexSubImage2D = (glCompressedTexSubImage2D_client_proc_t) getProc("glCompressedTexSubImage2D", userData);
	glCopyTexImage2D = (glCopyTexImage2D_client_proc_t) getProc("glCopyTexImage2D", userData);
	glCopyTexSubImage2D = (glCopyTexSubImage2D_client_proc_t) getProc("glCopyTexSubImage2D", userData);
	glCullFace = (glCullFace_client_proc_t) getProc("glCullFace", userData);
	glDeleteBuffers = (glDeleteBuffers_client_proc_t) getProc("glDeleteBuffers", userData);
	glDeleteTextures = (glDeleteTextures_client_proc_t) getProc("glDeleteTextures", userData);
	glDepthFunc = (glDepthFunc_client_proc_t) getProc("glDepthFunc", userData);
	glDepthMask = (glDepthMask_client_proc_t) getProc("glDepthMask", userData);
	glDepthRangex = (glDepthRangex_client_proc_t) getProc("glDepthRangex", userData);
	glDisable = (glDisable_client_proc_t) getProc("glDisable", userData);
	glDisableClientState = (glDisableClientState_client_proc_t) getProc("glDisableClientState", userData);
	glDrawArrays = (glDrawArrays_client_proc_t) getProc("glDrawArrays", userData);
	glDrawElements = (glDrawElements_client_proc_t) getProc("glDrawElements", userData);
	glEnable = (glEnable_client_proc_t) getProc("glEnable", userData);
	glEnableClientState = (glEnableClientState_client_proc_t) getProc("glEnableClientState", userData);
	glFinish = (glFinish_client_proc_t) getProc("glFinish", userData);
	glFlush = (glFlush_client_proc_t) getProc("glFlush", userData);
	glFogx = (glFogx_client_proc_t) getProc("glFogx", userData);
	glFogxv = (glFogxv_client_proc_t) getProc("glFogxv", userData);
	glFrontFace = (glFrontFace_client_proc_t) getProc("glFrontFace", userData);
	glFrustumx = (glFrustumx_client_proc_t) getProc("glFrustumx", userData);
	glGetBooleanv = (glGetBooleanv_client_proc_t) getProc("glGetBooleanv", userData);
	glGetBufferParameteriv = (glGetBufferParameteriv_client_proc_t) getProc("glGetBufferParameteriv", userData);
	glClipPlanex = (glClipPlanex_client_proc_t) getProc("glClipPlanex", userData);
	glGenBuffers = (glGenBuffers_client_proc_t) getProc("glGenBuffers", userData);
	glGenTextures = (glGenTextures_client_proc_t) getProc("glGenTextures", userData);
	glGetError = (glGetError_client_proc_t) getProc("glGetError", userData);
	glGetFixedv = (glGetFixedv_client_proc_t) getProc("glGetFixedv", userData);
	glGetIntegerv = (glGetIntegerv_client_proc_t) getProc("glGetIntegerv", userData);
	glGetLightxv = (glGetLightxv_client_proc_t) getProc("glGetLightxv", userData);
	glGetMaterialxv = (glGetMaterialxv_client_proc_t) getProc("glGetMaterialxv", userData);
	glGetPointerv = (glGetPointerv_client_proc_t) getProc("glGetPointerv", userData);
	glGetString = (glGetString_client_proc_t) getProc("glGetString", userData);
	glGetTexEnviv = (glGetTexEnviv_client_proc_t) getProc("glGetTexEnviv", userData);
	glGetTexEnvxv = (glGetTexEnvxv_client_proc_t) getProc("glGetTexEnvxv", userData);
	glGetTexParameteriv = (glGetTexParameteriv_client_proc_t) getProc("glGetTexParameteriv", userData);
	glGetTexParameterxv = (glGetTexParameterxv_client_proc_t) getProc("glGetTexParameterxv", userData);
	glHint = (glHint_client_proc_t) getProc("glHint", userData);
	glIsBuffer = (glIsBuffer_client_proc_t) getProc("glIsBuffer", userData);
	glIsEnabled = (glIsEnabled_client_proc_t) getProc("glIsEnabled", userData);
	glIsTexture = (glIsTexture_client_proc_t) getProc("glIsTexture", userData);
	glLightModelx = (glLightModelx_client_proc_t) getProc("glLightModelx", userData);
	glLightModelxv = (glLightModelxv_client_proc_t) getProc("glLightModelxv", userData);
	glLightx = (glLightx_client_proc_t) getProc("glLightx", userData);
	glLightxv = (glLightxv_client_proc_t) getProc("glLightxv", userData);
	glLineWidthx = (glLineWidthx_client_proc_t) getProc("glLineWidthx", userData);
	glLoadIdentity = (glLoadIdentity_client_proc_t) getProc("glLoadIdentity", userData);
	glLoadMatrixx = (glLoadMatrixx_client_proc_t) getProc("glLoadMatrixx", userData);
	glLogicOp = (glLogicOp_client_proc_t) getProc("glLogicOp", userData);
	glMaterialx = (glMaterialx_client_proc_t) getProc("glMaterialx", userData);
	glMaterialxv = (glMaterialxv_client_proc_t) getProc("glMaterialxv", userData);
	glMatrixMode = (glMatrixMode_client_proc_t) getProc("glMatrixMode", userData);
	glMultMatrixx = (glMultMatrixx_client_proc_t) getProc("glMultMatrixx", userData);
	glMultiTexCoord4x = (glMultiTexCoord4x_client_proc_t) getProc("glMultiTexCoord4x", userData);
	glNormal3x = (glNormal3x_client_proc_t) getProc("glNormal3x", userData);
	glNormalPointer = (glNormalPointer_client_proc_t) getProc("glNormalPointer", userData);
	glOrthox = (glOrthox_client_proc_t) getProc("glOrthox", userData);
	glPixelStorei = (glPixelStorei_client_proc_t) getProc("glPixelStorei", userData);
	glPointParameterx = (glPointParameterx_client_proc_t) getProc("glPointParameterx", userData);
	glPointParameterxv = (glPointParameterxv_client_proc_t) getProc("glPointParameterxv", userData);
	glPointSizex = (glPointSizex_client_proc_t) getProc("glPointSizex", userData);
	glPolygonOffsetx = (glPolygonOffsetx_client_proc_t) getProc("glPolygonOffsetx", userData);
	glPopMatrix = (glPopMatrix_client_proc_t) getProc("glPopMatrix", userData);
	glPushMatrix = (glPushMatrix_client_proc_t) getProc("glPushMatrix", userData);
	glReadPixels = (glReadPixels_client_proc_t) getProc("glReadPixels", userData);
	glRotatex = (glRotatex_client_proc_t) getProc("glRotatex", userData);
	glSampleCoverage = (glSampleCoverage_client_proc_t) getProc("glSampleCoverage", userData);
	glSampleCoveragex = (glSampleCoveragex_client_proc_t) getProc("glSampleCoveragex", userData);
	glScalex = (glScalex_client_proc_t) getProc("glScalex", userData);
	glScissor = (glScissor_client_proc_t) getProc("glScissor", userData);
	glShadeModel = (glShadeModel_client_proc_t) getProc("glShadeModel", userData);
	glStencilFunc = (glStencilFunc_client_proc_t) getProc("glStencilFunc", userData);
	glStencilMask = (glStencilMask_client_proc_t) getProc("glStencilMask", userData);
	glStencilOp = (glStencilOp_client_proc_t) getProc("glStencilOp", userData);
	glTexCoordPointer = (glTexCoordPointer_client_proc_t) getProc("glTexCoordPointer", userData);
	glTexEnvi = (glTexEnvi_client_proc_t) getProc("glTexEnvi", userData);
	glTexEnvx = (glTexEnvx_client_proc_t) getProc("glTexEnvx", userData);
	glTexEnviv = (glTexEnviv_client_proc_t) getProc("glTexEnviv", userData);
	glTexEnvxv = (glTexEnvxv_client_proc_t) getProc("glTexEnvxv", userData);
	glTexImage2D = (glTexImage2D_client_proc_t) getProc("glTexImage2D", userData);
	glTexParameteri = (glTexParameteri_client_proc_t) getProc("glTexParameteri", userData);
	glTexParameterx = (glTexParameterx_client_proc_t) getProc("glTexParameterx", userData);
	glTexParameteriv = (glTexParameteriv_client_proc_t) getProc("glTexParameteriv", userData);
	glTexParameterxv = (glTexParameterxv_client_proc_t) getProc("glTexParameterxv", userData);
	glTexSubImage2D = (glTexSubImage2D_client_proc_t) getProc("glTexSubImage2D", userData);
	glTranslatex = (glTranslatex_client_proc_t) getProc("glTranslatex", userData);
	glVertexPointer = (glVertexPointer_client_proc_t) getProc("glVertexPointer", userData);
	glViewport = (glViewport_client_proc_t) getProc("glViewport", userData);
	glPointSizePointerOES = (glPointSizePointerOES_client_proc_t) getProc("glPointSizePointerOES", userData);
	glVertexPointerOffset = (glVertexPointerOffset_client_proc_t) getProc("glVertexPointerOffset", userData);
	glColorPointerOffset = (glColorPointerOffset_client_proc_t) getProc("glColorPointerOffset", userData);
	glNormalPointerOffset = (glNormalPointerOffset_client_proc_t) getProc("glNormalPointerOffset", userData);
	glPointSizePointerOffset = (glPointSizePointerOffset_client_proc_t) getProc("glPointSizePointerOffset", userData);
	glTexCoordPointerOffset = (glTexCoordPointerOffset_client_proc_t) getProc("glTexCoordPointerOffset", userData);
	glWeightPointerOffset = (glWeightPointerOffset_client_proc_t) getProc("glWeightPointerOffset", userData);
	glMatrixIndexPointerOffset = (glMatrixIndexPointerOffset_client_proc_t) getProc("glMatrixIndexPointerOffset", userData);
	glVertexPointerData = (glVertexPointerData_client_proc_t) getProc("glVertexPointerData", userData);
	glColorPointerData = (glColorPointerData_client_proc_t) getProc("glColorPointerData", userData);
	glNormalPointerData = (glNormalPointerData_client_proc_t) getProc("glNormalPointerData", userData);
	glTexCoordPointerData = (glTexCoordPointerData_client_proc_t) getProc("glTexCoordPointerData", userData);
	glPointSizePointerData = (glPointSizePointerData_client_proc_t) getProc("glPointSizePointerData", userData);
	glWeightPointerData = (glWeightPointerData_client_proc_t) getProc("glWeightPointerData", userData);
	glMatrixIndexPointerData = (glMatrixIndexPointerData_client_proc_t) getProc("glMatrixIndexPointerData", userData);
	glDrawElementsOffset = (glDrawElementsOffset_client_proc_t) getProc("glDrawElementsOffset", userData);
	glDrawElementsData = (glDrawElementsData_client_proc_t) getProc("glDrawElementsData", userData);
	glGetCompressedTextureFormats = (glGetCompressedTextureFormats_client_proc_t) getProc("glGetCompressedTextureFormats", userData);
	glFinishRoundTrip = (glFinishRoundTrip_client_proc_t) getProc("glFinishRoundTrip", userData);
	glBlendEquationSeparateOES = (glBlendEquationSeparateOES_client_proc_t) getProc("glBlendEquationSeparateOES", userData);
	glBlendFuncSeparateOES = (glBlendFuncSeparateOES_client_proc_t) getProc("glBlendFuncSeparateOES", userData);
	glBlendEquationOES = (glBlendEquationOES_client_proc_t) getProc("glBlendEquationOES", userData);
	glDrawTexsOES = (glDrawTexsOES_client_proc_t) getProc("glDrawTexsOES", userData);
	glDrawTexiOES = (glDrawTexiOES_client_proc_t) getProc("glDrawTexiOES", userData);
	glDrawTexxOES = (glDrawTexxOES_client_proc_t) getProc("glDrawTexxOES", userData);
	glDrawTexsvOES = (glDrawTexsvOES_client_proc_t) getProc("glDrawTexsvOES", userData);
	glDrawTexivOES = (glDrawTexivOES_client_proc_t) getProc("glDrawTexivOES", userData);
	glDrawTexxvOES = (glDrawTexxvOES_client_proc_t) getProc("glDrawTexxvOES", userData);
	glDrawTexfOES = (glDrawTexfOES_client_proc_t) getProc("glDrawTexfOES", userData);
	glDrawTexfvOES = (glDrawTexfvOES_client_proc_t) getProc("glDrawTexfvOES", userData);
	glEGLImageTargetTexture2DOES = (glEGLImageTargetTexture2DOES_client_proc_t) getProc("glEGLImageTargetTexture2DOES", userData);
	glEGLImageTargetRenderbufferStorageOES = (glEGLImageTargetRenderbufferStorageOES_client_proc_t) getProc("glEGLImageTargetRenderbufferStorageOES", userData);
	glAlphaFuncxOES = (glAlphaFuncxOES_client_proc_t) getProc("glAlphaFuncxOES", userData);
	glClearColorxOES = (glClearColorxOES_client_proc_t) getProc("glClearColorxOES", userData);
	glClearDepthxOES = (glClearDepthxOES_client_proc_t) getProc("glClearDepthxOES", userData);
	glClipPlanexOES = (glClipPlanexOES_client_proc_t) getProc("glClipPlanexOES", userData);
	glClipPlanexIMG = (glClipPlanexIMG_client_proc_t) getProc("glClipPlanexIMG", userData);
	glColor4xOES = (glColor4xOES_client_proc_t) getProc("glColor4xOES", userData);
	glDepthRangexOES = (glDepthRangexOES_client_proc_t) getProc("glDepthRangexOES", userData);
	glFogxOES = (glFogxOES_client_proc_t) getProc("glFogxOES", userData);
	glFogxvOES = (glFogxvOES_client_proc_t) getProc("glFogxvOES", userData);
	glFrustumxOES = (glFrustumxOES_client_proc_t) getProc("glFrustumxOES", userData);
	glGetClipPlanexOES = (glGetClipPlanexOES_client_proc_t) getProc("glGetClipPlanexOES", userData);
	glGetClipPlanex = (glGetClipPlanex_client_proc_t) getProc("glGetClipPlanex", userData);
	glGetFixedvOES = (glGetFixedvOES_client_proc_t) getProc("glGetFixedvOES", userData);
	glGetLightxvOES = (glGetLightxvOES_client_proc_t) getProc("glGetLightxvOES", userData);
	glGetMaterialxvOES = (glGetMaterialxvOES_client_proc_t) getProc("glGetMaterialxvOES", userData);
	glGetTexEnvxvOES = (glGetTexEnvxvOES_client_proc_t) getProc("glGetTexEnvxvOES", userData);
	glGetTexParameterxvOES = (glGetTexParameterxvOES_client_proc_t) getProc("glGetTexParameterxvOES", userData);
	glLightModelxOES = (glLightModelxOES_client_proc_t) getProc("glLightModelxOES", userData);
	glLightModelxvOES = (glLightModelxvOES_client_proc_t) getProc("glLightModelxvOES", userData);
	glLightxOES = (glLightxOES_client_proc_t) getProc("glLightxOES", userData);
	glLightxvOES = (glLightxvOES_client_proc_t) getProc("glLightxvOES", userData);
	glLineWidthxOES = (glLineWidthxOES_client_proc_t) getProc("glLineWidthxOES", userData);
	glLoadMatrixxOES = (glLoadMatrixxOES_client_proc_t) getProc("glLoadMatrixxOES", userData);
	glMaterialxOES = (glMaterialxOES_client_proc_t) getProc("glMaterialxOES", userData);
	glMaterialxvOES = (glMaterialxvOES_client_proc_t) getProc("glMaterialxvOES", userData);
	glMultMatrixxOES = (glMultMatrixxOES_client_proc_t) getProc("glMultMatrixxOES", userData);
	glMultiTexCoord4xOES = (glMultiTexCoord4xOES_client_proc_t) getProc("glMultiTexCoord4xOES", userData);
	glNormal3xOES = (glNormal3xOES_client_proc_t) getProc("glNormal3xOES", userData);
	glOrthoxOES = (glOrthoxOES_client_proc_t) getProc("glOrthoxOES", userData);
	glPointParameterxOES = (glPointParameterxOES_client_proc_t) getProc("glPointParameterxOES", userData);
	glPointParameterxvOES = (glPointParameterxvOES_client_proc_t) getProc("glPointParameterxvOES", userData);
	glPointSizexOES = (glPointSizexOES_client_proc_t) getProc("glPointSizexOES", userData);
	glPolygonOffsetxOES = (glPolygonOffsetxOES_client_proc_t) getProc("glPolygonOffsetxOES", userData);
	glRotatexOES = (glRotatexOES_client_proc_t) getProc("glRotatexOES", userData);
	glSampleCoveragexOES = (glSampleCoveragexOES_client_proc_t) getProc("glSampleCoveragexOES", userData);
	glScalexOES = (glScalexOES_client_proc_t) getProc("glScalexOES", userData);
	glTexEnvxOES = (glTexEnvxOES_client_proc_t) getProc("glTexEnvxOES", userData);
	glTexEnvxvOES = (glTexEnvxvOES_client_proc_t) getProc("glTexEnvxvOES", userData);
	glTexParameterxOES = (glTexParameterxOES_client_proc_t) getProc("glTexParameterxOES", userData);
	glTexParameterxvOES = (glTexParameterxvOES_client_proc_t) getProc("glTexParameterxvOES", userData);
	glTranslatexOES = (glTranslatexOES_client_proc_t) getProc("glTranslatexOES", userData);
	glIsRenderbufferOES = (glIsRenderbufferOES_client_proc_t) getProc("glIsRenderbufferOES", userData);
	glBindRenderbufferOES = (glBindRenderbufferOES_client_proc_t) getProc("glBindRenderbufferOES", userData);
	glDeleteRenderbuffersOES = (glDeleteRenderbuffersOES_client_proc_t) getProc("glDeleteRenderbuffersOES", userData);
	glGenRenderbuffersOES = (glGenRenderbuffersOES_client_proc_t) getProc("glGenRenderbuffersOES", userData);
	glRenderbufferStorageOES = (glRenderbufferStorageOES_client_proc_t) getProc("glRenderbufferStorageOES", userData);
	glGetRenderbufferParameterivOES = (glGetRenderbufferParameterivOES_client_proc_t) getProc("glGetRenderbufferParameterivOES", userData);
	glIsFramebufferOES = (glIsFramebufferOES_client_proc_t) getProc("glIsFramebufferOES", userData);
	glBindFramebufferOES = (glBindFramebufferOES_client_proc_t) getProc("glBindFramebufferOES", userData);
	glDeleteFramebuffersOES = (glDeleteFramebuffersOES_client_proc_t) getProc("glDeleteFramebuffersOES", userData);
	glGenFramebuffersOES = (glGenFramebuffersOES_client_proc_t) getProc("glGenFramebuffersOES", userData);
	glCheckFramebufferStatusOES = (glCheckFramebufferStatusOES_client_proc_t) getProc("glCheckFramebufferStatusOES", userData);
	glFramebufferRenderbufferOES = (glFramebufferRenderbufferOES_client_proc_t) getProc("glFramebufferRenderbufferOES", userData);
	glFramebufferTexture2DOES = (glFramebufferTexture2DOES_client_proc_t) getProc("glFramebufferTexture2DOES", userData);
	glGetFramebufferAttachmentParameterivOES = (glGetFramebufferAttachmentParameterivOES_client_proc_t) getProc("glGetFramebufferAttachmentParameterivOES", userData);
	glGenerateMipmapOES = (glGenerateMipmapOES_client_proc_t) getProc("glGenerateMipmapOES", userData);
	glMapBufferOES = (glMapBufferOES_client_proc_t) getProc("glMapBufferOES", userData);
	glUnmapBufferOES = (glUnmapBufferOES_client_proc_t) getProc("glUnmapBufferOES", userData);
	glGetBufferPointervOES = (glGetBufferPointervOES_client_proc_t) getProc("glGetBufferPointervOES", userData);
	glCurrentPaletteMatrixOES = (glCurrentPaletteMatrixOES_client_proc_t) getProc("glCurrentPaletteMatrixOES", userData);
	glLoadPaletteFromModelViewMatrixOES = (glLoadPaletteFromModelViewMatrixOES_client_proc_t) getProc("glLoadPaletteFromModelViewMatrixOES", userData);
	glMatrixIndexPointerOES = (glMatrixIndexPointerOES_client_proc_t) getProc("glMatrixIndexPointerOES", userData);
	glWeightPointerOES = (glWeightPointerOES_client_proc_t) getProc("glWeightPointerOES", userData);
	glQueryMatrixxOES = (glQueryMatrixxOES_client_proc_t) getProc("glQueryMatrixxOES", userData);
	glDepthRangefOES = (glDepthRangefOES_client_proc_t) getProc("glDepthRangefOES", userData);
	glFrustumfOES = (glFrustumfOES_client_proc_t) getProc("glFrustumfOES", userData);
	glOrthofOES = (glOrthofOES_client_proc_t) getProc("glOrthofOES", userData);
	glClipPlanefOES = (glClipPlanefOES_client_proc_t) getProc("glClipPlanefOES", userData);
	glClipPlanefIMG = (glClipPlanefIMG_client_proc_t) getProc("glClipPlanefIMG", userData);
	glGetClipPlanefOES = (glGetClipPlanefOES_client_proc_t) getProc("glGetClipPlanefOES", userData);
	glClearDepthfOES = (glClearDepthfOES_client_proc_t) getProc("glClearDepthfOES", userData);
	glTexGenfOES = (glTexGenfOES_client_proc_t) getProc("glTexGenfOES", userData);
	glTexGenfvOES = (glTexGenfvOES_client_proc_t) getProc("glTexGenfvOES", userData);
	glTexGeniOES = (glTexGeniOES_client_proc_t) getProc("glTexGeniOES", userData);
	glTexGenivOES = (glTexGenivOES_client_proc_t) getProc("glTexGenivOES", userData);
	glTexGenxOES = (glTexGenxOES_client_proc_t) getProc("glTexGenxOES", userData);
	glTexGenxvOES = (glTexGenxvOES_client_proc_t) getProc("glTexGenxvOES", userData);
	glGetTexGenfvOES = (glGetTexGenfvOES_client_proc_t) getProc("glGetTexGenfvOES", userData);
	glGetTexGenivOES = (glGetTexGenivOES_client_proc_t) getProc("glGetTexGenivOES", userData);
	glGetTexGenxvOES = (glGetTexGenxvOES_client_proc_t) getProc("glGetTexGenxvOES", userData);
	glBindVertexArrayOES = (glBindVertexArrayOES_client_proc_t) getProc("glBindVertexArrayOES", userData);
	glDeleteVertexArraysOES = (glDeleteVertexArraysOES_client_proc_t) getProc("glDeleteVertexArraysOES", userData);
	glGenVertexArraysOES = (glGenVertexArraysOES_client_proc_t) getProc("glGenVertexArraysOES", userData);
	glIsVertexArrayOES = (glIsVertexArrayOES_client_proc_t) getProc("glIsVertexArrayOES", userData);
	glDiscardFramebufferEXT = (glDiscardFramebufferEXT_client_proc_t) getProc("glDiscardFramebufferEXT", userData);
	glMultiDrawArraysEXT = (glMultiDrawArraysEXT_client_proc_t) getProc("glMultiDrawArraysEXT", userData);
	glMultiDrawElementsEXT = (glMultiDrawElementsEXT_client_proc_t) getProc("glMultiDrawElementsEXT", userData);
	glMultiDrawArraysSUN = (glMultiDrawArraysSUN_client_proc_t) getProc("glMultiDrawArraysSUN", userData);
	glMultiDrawElementsSUN = (glMultiDrawElementsSUN_client_proc_t) getProc("glMultiDrawElementsSUN", userData);
	glRenderbufferStorageMultisampleIMG = (glRenderbufferStorageMultisampleIMG_client_proc_t) getProc("glRenderbufferStorageMultisampleIMG", userData);
	glFramebufferTexture2DMultisampleIMG = (glFramebufferTexture2DMultisampleIMG_client_proc_t) getProc("glFramebufferTexture2DMultisampleIMG", userData);
	glDeleteFencesNV = (glDeleteFencesNV_client_proc_t) getProc("glDeleteFencesNV", userData);
	glGenFencesNV = (glGenFencesNV_client_proc_t) getProc("glGenFencesNV", userData);
	glIsFenceNV = (glIsFenceNV_client_proc_t) getProc("glIsFenceNV", userData);
	glTestFenceNV = (glTestFenceNV_client_proc_t) getProc("glTestFenceNV", userData);
	glGetFenceivNV = (glGetFenceivNV_client_proc_t) getProc("glGetFenceivNV", userData);
	glFinishFenceNV = (glFinishFenceNV_client_proc_t) getProc("glFinishFenceNV", userData);
	glSetFenceNV = (glSetFenceNV_client_proc_t) getProc("glSetFenceNV", userData);
	glGetDriverControlsQCOM = (glGetDriverControlsQCOM_client_proc_t) getProc("glGetDriverControlsQCOM", userData);
	glGetDriverControlStringQCOM = (glGetDriverControlStringQCOM_client_proc_t) getProc("glGetDriverControlStringQCOM", userData);
	glEnableDriverControlQCOM = (glEnableDriverControlQCOM_client_proc_t) getProc("glEnableDriverControlQCOM", userData);
	glDisableDriverControlQCOM = (glDisableDriverControlQCOM_client_proc_t) getProc("glDisableDriverControlQCOM", userData);
	glExtGetTexturesQCOM = (glExtGetTexturesQCOM_client_proc_t) getProc("glExtGetTexturesQCOM", userData);
	glExtGetBuffersQCOM = (glExtGetBuffersQCOM_client_proc_t) getProc("glExtGetBuffersQCOM", userData);
	glExtGetRenderbuffersQCOM = (glExtGetRenderbuffersQCOM_client_proc_t) getProc("glExtGetRenderbuffersQCOM", userData);
	glExtGetFramebuffersQCOM = (glExtGetFramebuffersQCOM_client_proc_t) getProc("glExtGetFramebuffersQCOM", userData);
	glExtGetTexLevelParameterivQCOM = (glExtGetTexLevelParameterivQCOM_client_proc_t) getProc("glExtGetTexLevelParameterivQCOM", userData);
	glExtTexObjectStateOverrideiQCOM = (glExtTexObjectStateOverrideiQCOM_client_proc_t) getProc("glExtTexObjectStateOverrideiQCOM", userData);
	glExtGetTexSubImageQCOM = (glExtGetTexSubImageQCOM_client_proc_t) getProc("glExtGetTexSubImageQCOM", userData);
	glExtGetBufferPointervQCOM = (glExtGetBufferPointervQCOM_client_proc_t) getProc("glExtGetBufferPointervQCOM", userData);
	glExtGetShadersQCOM = (glExtGetShadersQCOM_client_proc_t) getProc("glExtGetShadersQCOM", userData);
	glExtGetProgramsQCOM = (glExtGetProgramsQCOM_client_proc_t) getProc("glExtGetProgramsQCOM", userData);
	glExtIsProgramBinaryQCOM = (glExtIsProgramBinaryQCOM_client_proc_t) getProc("glExtIsProgramBinaryQCOM", userData);
	glExtGetProgramBinarySourceQCOM = (glExtGetProgramBinarySourceQCOM_client_proc_t) getProc("glExtGetProgramBinarySourceQCOM", userData);
	glStartTilingQCOM = (glStartTilingQCOM_client_proc_t) getProc("glStartTilingQCOM", userData);
	glEndTilingQCOM = (glEndTilingQCOM_client_proc_t) getProc("glEndTilingQCOM", userData);
	glGetGraphicsResetStatusEXT = (glGetGraphicsResetStatusEXT_client_proc_t) getProc("glGetGraphicsResetStatusEXT", userData);
	glReadnPixelsEXT = (glReadnPixelsEXT_client_proc_t) getProc("glReadnPixelsEXT", userData);
	return 0;
}

