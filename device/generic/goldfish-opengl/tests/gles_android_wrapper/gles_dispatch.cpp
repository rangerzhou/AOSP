/*
* Copyright (C) 2011 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#include "gles_dispatch.h"
#include <stdio.h>
#include <dlfcn.h>

gles_dispatch *create_gles_dispatch(void *gles_android)
{
        gles_dispatch *disp = new gles_dispatch;

    void *ptr;
    ptr = dlsym(gles_android,"glAlphaFunc"); disp->set_glAlphaFunc((glAlphaFunc_t)ptr);
    ptr = dlsym(gles_android,"glClearColor"); disp->set_glClearColor((glClearColor_t)ptr);
    ptr = dlsym(gles_android,"glClearDepthf"); disp->set_glClearDepthf((glClearDepthf_t)ptr);
    ptr = dlsym(gles_android,"glClipPlanef"); disp->set_glClipPlanef((glClipPlanef_t)ptr);
    ptr = dlsym(gles_android,"glColor4f"); disp->set_glColor4f((glColor4f_t)ptr);
    ptr = dlsym(gles_android,"glDepthRangef"); disp->set_glDepthRangef((glDepthRangef_t)ptr);
    ptr = dlsym(gles_android,"glFogf"); disp->set_glFogf((glFogf_t)ptr);
    ptr = dlsym(gles_android,"glFogfv"); disp->set_glFogfv((glFogfv_t)ptr);
    ptr = dlsym(gles_android,"glFrustumf"); disp->set_glFrustumf((glFrustumf_t)ptr);
    ptr = dlsym(gles_android,"glGetClipPlanef"); disp->set_glGetClipPlanef((glGetClipPlanef_t)ptr);
    ptr = dlsym(gles_android,"glGetFloatv"); disp->set_glGetFloatv((glGetFloatv_t)ptr);
    ptr = dlsym(gles_android,"glGetLightfv"); disp->set_glGetLightfv((glGetLightfv_t)ptr);
    ptr = dlsym(gles_android,"glGetMaterialfv"); disp->set_glGetMaterialfv((glGetMaterialfv_t)ptr);
    ptr = dlsym(gles_android,"glGetTexEnvfv"); disp->set_glGetTexEnvfv((glGetTexEnvfv_t)ptr);
    ptr = dlsym(gles_android,"glGetTexParameterfv"); disp->set_glGetTexParameterfv((glGetTexParameterfv_t)ptr);
    ptr = dlsym(gles_android,"glLightModelf"); disp->set_glLightModelf((glLightModelf_t)ptr);
    ptr = dlsym(gles_android,"glLightModelfv"); disp->set_glLightModelfv((glLightModelfv_t)ptr);
    ptr = dlsym(gles_android,"glLightf"); disp->set_glLightf((glLightf_t)ptr);
    ptr = dlsym(gles_android,"glLightfv"); disp->set_glLightfv((glLightfv_t)ptr);
    ptr = dlsym(gles_android,"glLineWidth"); disp->set_glLineWidth((glLineWidth_t)ptr);
    ptr = dlsym(gles_android,"glLoadMatrixf"); disp->set_glLoadMatrixf((glLoadMatrixf_t)ptr);
    ptr = dlsym(gles_android,"glMaterialf"); disp->set_glMaterialf((glMaterialf_t)ptr);
    ptr = dlsym(gles_android,"glMaterialfv"); disp->set_glMaterialfv((glMaterialfv_t)ptr);
    ptr = dlsym(gles_android,"glMultMatrixf"); disp->set_glMultMatrixf((glMultMatrixf_t)ptr);
    ptr = dlsym(gles_android,"glMultiTexCoord4f"); disp->set_glMultiTexCoord4f((glMultiTexCoord4f_t)ptr);
    ptr = dlsym(gles_android,"glNormal3f"); disp->set_glNormal3f((glNormal3f_t)ptr);
    ptr = dlsym(gles_android,"glOrthof"); disp->set_glOrthof((glOrthof_t)ptr);
    ptr = dlsym(gles_android,"glPointParameterf"); disp->set_glPointParameterf((glPointParameterf_t)ptr);
    ptr = dlsym(gles_android,"glPointParameterfv"); disp->set_glPointParameterfv((glPointParameterfv_t)ptr);
    ptr = dlsym(gles_android,"glPointSize"); disp->set_glPointSize((glPointSize_t)ptr);
    ptr = dlsym(gles_android,"glPolygonOffset"); disp->set_glPolygonOffset((glPolygonOffset_t)ptr);
    ptr = dlsym(gles_android,"glRotatef"); disp->set_glRotatef((glRotatef_t)ptr);
    ptr = dlsym(gles_android,"glScalef"); disp->set_glScalef((glScalef_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvf"); disp->set_glTexEnvf((glTexEnvf_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvfv"); disp->set_glTexEnvfv((glTexEnvfv_t)ptr);
    ptr = dlsym(gles_android,"glTexParameterf"); disp->set_glTexParameterf((glTexParameterf_t)ptr);
    ptr = dlsym(gles_android,"glTexParameterfv"); disp->set_glTexParameterfv((glTexParameterfv_t)ptr);
    ptr = dlsym(gles_android,"glTranslatef"); disp->set_glTranslatef((glTranslatef_t)ptr);
    ptr = dlsym(gles_android,"glActiveTexture"); disp->set_glActiveTexture((glActiveTexture_t)ptr);
    ptr = dlsym(gles_android,"glAlphaFuncx"); disp->set_glAlphaFuncx((glAlphaFuncx_t)ptr);
    ptr = dlsym(gles_android,"glBindBuffer"); disp->set_glBindBuffer((glBindBuffer_t)ptr);
    ptr = dlsym(gles_android,"glBindTexture"); disp->set_glBindTexture((glBindTexture_t)ptr);
    ptr = dlsym(gles_android,"glBlendFunc"); disp->set_glBlendFunc((glBlendFunc_t)ptr);
    ptr = dlsym(gles_android,"glBufferData"); disp->set_glBufferData((glBufferData_t)ptr);
    ptr = dlsym(gles_android,"glBufferSubData"); disp->set_glBufferSubData((glBufferSubData_t)ptr);
    ptr = dlsym(gles_android,"glClear"); disp->set_glClear((glClear_t)ptr);
    ptr = dlsym(gles_android,"glClearColorx"); disp->set_glClearColorx((glClearColorx_t)ptr);
    ptr = dlsym(gles_android,"glClearDepthx"); disp->set_glClearDepthx((glClearDepthx_t)ptr);
    ptr = dlsym(gles_android,"glClearStencil"); disp->set_glClearStencil((glClearStencil_t)ptr);
    ptr = dlsym(gles_android,"glClientActiveTexture"); disp->set_glClientActiveTexture((glClientActiveTexture_t)ptr);
    ptr = dlsym(gles_android,"glClipPlanex"); disp->set_glClipPlanex((glClipPlanex_t)ptr);
    ptr = dlsym(gles_android,"glColor4ub"); disp->set_glColor4ub((glColor4ub_t)ptr);
    ptr = dlsym(gles_android,"glColor4x"); disp->set_glColor4x((glColor4x_t)ptr);
    ptr = dlsym(gles_android,"glColorMask"); disp->set_glColorMask((glColorMask_t)ptr);
    ptr = dlsym(gles_android,"glColorPointer"); disp->set_glColorPointer((glColorPointer_t)ptr);
    ptr = dlsym(gles_android,"glCompressedTexImage2D"); disp->set_glCompressedTexImage2D((glCompressedTexImage2D_t)ptr);
    ptr = dlsym(gles_android,"glCompressedTexSubImage2D"); disp->set_glCompressedTexSubImage2D((glCompressedTexSubImage2D_t)ptr);
    ptr = dlsym(gles_android,"glCopyTexImage2D"); disp->set_glCopyTexImage2D((glCopyTexImage2D_t)ptr);
    ptr = dlsym(gles_android,"glCopyTexSubImage2D"); disp->set_glCopyTexSubImage2D((glCopyTexSubImage2D_t)ptr);
    ptr = dlsym(gles_android,"glCullFace"); disp->set_glCullFace((glCullFace_t)ptr);
    ptr = dlsym(gles_android,"glDeleteBuffers"); disp->set_glDeleteBuffers((glDeleteBuffers_t)ptr);
    ptr = dlsym(gles_android,"glDeleteTextures"); disp->set_glDeleteTextures((glDeleteTextures_t)ptr);
    ptr = dlsym(gles_android,"glDepthFunc"); disp->set_glDepthFunc((glDepthFunc_t)ptr);
    ptr = dlsym(gles_android,"glDepthMask"); disp->set_glDepthMask((glDepthMask_t)ptr);
    ptr = dlsym(gles_android,"glDepthRangex"); disp->set_glDepthRangex((glDepthRangex_t)ptr);
    ptr = dlsym(gles_android,"glDisable"); disp->set_glDisable((glDisable_t)ptr);
    ptr = dlsym(gles_android,"glDisableClientState"); disp->set_glDisableClientState((glDisableClientState_t)ptr);
    ptr = dlsym(gles_android,"glDrawArrays"); disp->set_glDrawArrays((glDrawArrays_t)ptr);
    ptr = dlsym(gles_android,"glDrawElements"); disp->set_glDrawElements((glDrawElements_t)ptr);
    ptr = dlsym(gles_android,"glEnable"); disp->set_glEnable((glEnable_t)ptr);
    ptr = dlsym(gles_android,"glEnableClientState"); disp->set_glEnableClientState((glEnableClientState_t)ptr);
    ptr = dlsym(gles_android,"glFinish"); disp->set_glFinish((glFinish_t)ptr);
    ptr = dlsym(gles_android,"glFlush"); disp->set_glFlush((glFlush_t)ptr);
    ptr = dlsym(gles_android,"glFogx"); disp->set_glFogx((glFogx_t)ptr);
    ptr = dlsym(gles_android,"glFogxv"); disp->set_glFogxv((glFogxv_t)ptr);
    ptr = dlsym(gles_android,"glFrontFace"); disp->set_glFrontFace((glFrontFace_t)ptr);
    ptr = dlsym(gles_android,"glFrustumx"); disp->set_glFrustumx((glFrustumx_t)ptr);
    ptr = dlsym(gles_android,"glGetBooleanv"); disp->set_glGetBooleanv((glGetBooleanv_t)ptr);
    ptr = dlsym(gles_android,"glGetBufferParameteriv"); disp->set_glGetBufferParameteriv((glGetBufferParameteriv_t)ptr);
    ptr = dlsym(gles_android,"glGetClipPlanex"); disp->set_glGetClipPlanex((glGetClipPlanex_t)ptr);
    ptr = dlsym(gles_android,"glGenBuffers"); disp->set_glGenBuffers((glGenBuffers_t)ptr);
    ptr = dlsym(gles_android,"glGenTextures"); disp->set_glGenTextures((glGenTextures_t)ptr);
    ptr = dlsym(gles_android,"glGetError"); disp->set_glGetError((glGetError_t)ptr);
    ptr = dlsym(gles_android,"glGetFixedv"); disp->set_glGetFixedv((glGetFixedv_t)ptr);
    ptr = dlsym(gles_android,"glGetIntegerv"); disp->set_glGetIntegerv((glGetIntegerv_t)ptr);
    ptr = dlsym(gles_android,"glGetLightxv"); disp->set_glGetLightxv((glGetLightxv_t)ptr);
    ptr = dlsym(gles_android,"glGetMaterialxv"); disp->set_glGetMaterialxv((glGetMaterialxv_t)ptr);
    ptr = dlsym(gles_android,"glGetPointerv"); disp->set_glGetPointerv((glGetPointerv_t)ptr);
    ptr = dlsym(gles_android,"glGetString"); disp->set_glGetString((glGetString_t)ptr);
    ptr = dlsym(gles_android,"glGetTexEnviv"); disp->set_glGetTexEnviv((glGetTexEnviv_t)ptr);
    ptr = dlsym(gles_android,"glGetTexEnvxv"); disp->set_glGetTexEnvxv((glGetTexEnvxv_t)ptr);
    ptr = dlsym(gles_android,"glGetTexParameteriv"); disp->set_glGetTexParameteriv((glGetTexParameteriv_t)ptr);
    ptr = dlsym(gles_android,"glGetTexParameterxv"); disp->set_glGetTexParameterxv((glGetTexParameterxv_t)ptr);
    ptr = dlsym(gles_android,"glHint"); disp->set_glHint((glHint_t)ptr);
    ptr = dlsym(gles_android,"glIsBuffer"); disp->set_glIsBuffer((glIsBuffer_t)ptr);
    ptr = dlsym(gles_android,"glIsEnabled"); disp->set_glIsEnabled((glIsEnabled_t)ptr);
    ptr = dlsym(gles_android,"glIsTexture"); disp->set_glIsTexture((glIsTexture_t)ptr);
    ptr = dlsym(gles_android,"glLightModelx"); disp->set_glLightModelx((glLightModelx_t)ptr);
    ptr = dlsym(gles_android,"glLightModelxv"); disp->set_glLightModelxv((glLightModelxv_t)ptr);
    ptr = dlsym(gles_android,"glLightx"); disp->set_glLightx((glLightx_t)ptr);
    ptr = dlsym(gles_android,"glLightxv"); disp->set_glLightxv((glLightxv_t)ptr);
    ptr = dlsym(gles_android,"glLineWidthx"); disp->set_glLineWidthx((glLineWidthx_t)ptr);
    ptr = dlsym(gles_android,"glLoadIdentity"); disp->set_glLoadIdentity((glLoadIdentity_t)ptr);
    ptr = dlsym(gles_android,"glLoadMatrixx"); disp->set_glLoadMatrixx((glLoadMatrixx_t)ptr);
    ptr = dlsym(gles_android,"glLogicOp"); disp->set_glLogicOp((glLogicOp_t)ptr);
    ptr = dlsym(gles_android,"glMaterialx"); disp->set_glMaterialx((glMaterialx_t)ptr);
    ptr = dlsym(gles_android,"glMaterialxv"); disp->set_glMaterialxv((glMaterialxv_t)ptr);
    ptr = dlsym(gles_android,"glMatrixMode"); disp->set_glMatrixMode((glMatrixMode_t)ptr);
    ptr = dlsym(gles_android,"glMultMatrixx"); disp->set_glMultMatrixx((glMultMatrixx_t)ptr);
    ptr = dlsym(gles_android,"glMultiTexCoord4x"); disp->set_glMultiTexCoord4x((glMultiTexCoord4x_t)ptr);
    ptr = dlsym(gles_android,"glNormal3x"); disp->set_glNormal3x((glNormal3x_t)ptr);
    ptr = dlsym(gles_android,"glNormalPointer"); disp->set_glNormalPointer((glNormalPointer_t)ptr);
    ptr = dlsym(gles_android,"glOrthox"); disp->set_glOrthox((glOrthox_t)ptr);
    ptr = dlsym(gles_android,"glPixelStorei"); disp->set_glPixelStorei((glPixelStorei_t)ptr);
    ptr = dlsym(gles_android,"glPointParameterx"); disp->set_glPointParameterx((glPointParameterx_t)ptr);
    ptr = dlsym(gles_android,"glPointParameterxv"); disp->set_glPointParameterxv((glPointParameterxv_t)ptr);
    ptr = dlsym(gles_android,"glPointSizex"); disp->set_glPointSizex((glPointSizex_t)ptr);
    ptr = dlsym(gles_android,"glPolygonOffsetx"); disp->set_glPolygonOffsetx((glPolygonOffsetx_t)ptr);
    ptr = dlsym(gles_android,"glPopMatrix"); disp->set_glPopMatrix((glPopMatrix_t)ptr);
    ptr = dlsym(gles_android,"glPushMatrix"); disp->set_glPushMatrix((glPushMatrix_t)ptr);
    ptr = dlsym(gles_android,"glReadPixels"); disp->set_glReadPixels((glReadPixels_t)ptr);
    ptr = dlsym(gles_android,"glRotatex"); disp->set_glRotatex((glRotatex_t)ptr);
    ptr = dlsym(gles_android,"glSampleCoverage"); disp->set_glSampleCoverage((glSampleCoverage_t)ptr);
    ptr = dlsym(gles_android,"glSampleCoveragex"); disp->set_glSampleCoveragex((glSampleCoveragex_t)ptr);
    ptr = dlsym(gles_android,"glScalex"); disp->set_glScalex((glScalex_t)ptr);
    ptr = dlsym(gles_android,"glScissor"); disp->set_glScissor((glScissor_t)ptr);
    ptr = dlsym(gles_android,"glShadeModel"); disp->set_glShadeModel((glShadeModel_t)ptr);
    ptr = dlsym(gles_android,"glStencilFunc"); disp->set_glStencilFunc((glStencilFunc_t)ptr);
    ptr = dlsym(gles_android,"glStencilMask"); disp->set_glStencilMask((glStencilMask_t)ptr);
    ptr = dlsym(gles_android,"glStencilOp"); disp->set_glStencilOp((glStencilOp_t)ptr);
    ptr = dlsym(gles_android,"glTexCoordPointer"); disp->set_glTexCoordPointer((glTexCoordPointer_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvi"); disp->set_glTexEnvi((glTexEnvi_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvx"); disp->set_glTexEnvx((glTexEnvx_t)ptr);
    ptr = dlsym(gles_android,"glTexEnviv"); disp->set_glTexEnviv((glTexEnviv_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvxv"); disp->set_glTexEnvxv((glTexEnvxv_t)ptr);
    ptr = dlsym(gles_android,"glTexImage2D"); disp->set_glTexImage2D((glTexImage2D_t)ptr);
    ptr = dlsym(gles_android,"glTexParameteri"); disp->set_glTexParameteri((glTexParameteri_t)ptr);
    ptr = dlsym(gles_android,"glTexParameterx"); disp->set_glTexParameterx((glTexParameterx_t)ptr);
    ptr = dlsym(gles_android,"glTexParameteriv"); disp->set_glTexParameteriv((glTexParameteriv_t)ptr);
    ptr = dlsym(gles_android,"glTexParameterxv"); disp->set_glTexParameterxv((glTexParameterxv_t)ptr);
    ptr = dlsym(gles_android,"glTexSubImage2D"); disp->set_glTexSubImage2D((glTexSubImage2D_t)ptr);
    ptr = dlsym(gles_android,"glTranslatex"); disp->set_glTranslatex((glTranslatex_t)ptr);
    ptr = dlsym(gles_android,"glVertexPointer"); disp->set_glVertexPointer((glVertexPointer_t)ptr);
    ptr = dlsym(gles_android,"glViewport"); disp->set_glViewport((glViewport_t)ptr);
    ptr = dlsym(gles_android,"glPointSizePointerOES"); disp->set_glPointSizePointerOES((glPointSizePointerOES_t)ptr);
    ptr = dlsym(gles_android,"glBlendEquationSeparateOES"); disp->set_glBlendEquationSeparateOES((glBlendEquationSeparateOES_t)ptr);
    ptr = dlsym(gles_android,"glBlendFuncSeparateOES"); disp->set_glBlendFuncSeparateOES((glBlendFuncSeparateOES_t)ptr);
    ptr = dlsym(gles_android,"glBlendEquationOES"); disp->set_glBlendEquationOES((glBlendEquationOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexsOES"); disp->set_glDrawTexsOES((glDrawTexsOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexiOES"); disp->set_glDrawTexiOES((glDrawTexiOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexxOES"); disp->set_glDrawTexxOES((glDrawTexxOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexsvOES"); disp->set_glDrawTexsvOES((glDrawTexsvOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexivOES"); disp->set_glDrawTexivOES((glDrawTexivOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexxvOES"); disp->set_glDrawTexxvOES((glDrawTexxvOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexfOES"); disp->set_glDrawTexfOES((glDrawTexfOES_t)ptr);
    ptr = dlsym(gles_android,"glDrawTexfvOES"); disp->set_glDrawTexfvOES((glDrawTexfvOES_t)ptr);
    ptr = dlsym(gles_android,"glEGLImageTargetTexture2DOES"); disp->set_glEGLImageTargetTexture2DOES((glEGLImageTargetTexture2DOES_t)ptr);
    ptr = dlsym(gles_android,"glEGLImageTargetRenderbufferStorageOES"); disp->set_glEGLImageTargetRenderbufferStorageOES((glEGLImageTargetRenderbufferStorageOES_t)ptr);
    ptr = dlsym(gles_android,"glAlphaFuncxOES"); disp->set_glAlphaFuncxOES((glAlphaFuncxOES_t)ptr);
    ptr = dlsym(gles_android,"glClearColorxOES"); disp->set_glClearColorxOES((glClearColorxOES_t)ptr);
    ptr = dlsym(gles_android,"glClearDepthxOES"); disp->set_glClearDepthxOES((glClearDepthxOES_t)ptr);
    ptr = dlsym(gles_android,"glClipPlanexOES"); disp->set_glClipPlanexOES((glClipPlanexOES_t)ptr);
    ptr = dlsym(gles_android,"glColor4xOES"); disp->set_glColor4xOES((glColor4xOES_t)ptr);
    ptr = dlsym(gles_android,"glDepthRangexOES"); disp->set_glDepthRangexOES((glDepthRangexOES_t)ptr);
    ptr = dlsym(gles_android,"glFogxOES"); disp->set_glFogxOES((glFogxOES_t)ptr);
    ptr = dlsym(gles_android,"glFogxvOES"); disp->set_glFogxvOES((glFogxvOES_t)ptr);
    ptr = dlsym(gles_android,"glFrustumxOES"); disp->set_glFrustumxOES((glFrustumxOES_t)ptr);
    ptr = dlsym(gles_android,"glGetClipPlanexOES"); disp->set_glGetClipPlanexOES((glGetClipPlanexOES_t)ptr);
    ptr = dlsym(gles_android,"glGetFixedvOES"); disp->set_glGetFixedvOES((glGetFixedvOES_t)ptr);
    ptr = dlsym(gles_android,"glGetLightxvOES"); disp->set_glGetLightxvOES((glGetLightxvOES_t)ptr);
    ptr = dlsym(gles_android,"glGetMaterialxvOES"); disp->set_glGetMaterialxvOES((glGetMaterialxvOES_t)ptr);
    ptr = dlsym(gles_android,"glGetTexEnvxvOES"); disp->set_glGetTexEnvxvOES((glGetTexEnvxvOES_t)ptr);
    ptr = dlsym(gles_android,"glGetTexParameterxvOES"); disp->set_glGetTexParameterxvOES((glGetTexParameterxvOES_t)ptr);
    ptr = dlsym(gles_android,"glLightModelxOES"); disp->set_glLightModelxOES((glLightModelxOES_t)ptr);
    ptr = dlsym(gles_android,"glLightModelxvOES"); disp->set_glLightModelxvOES((glLightModelxvOES_t)ptr);
    ptr = dlsym(gles_android,"glLightxOES"); disp->set_glLightxOES((glLightxOES_t)ptr);
    ptr = dlsym(gles_android,"glLightxvOES"); disp->set_glLightxvOES((glLightxvOES_t)ptr);
    ptr = dlsym(gles_android,"glLineWidthxOES"); disp->set_glLineWidthxOES((glLineWidthxOES_t)ptr);
    ptr = dlsym(gles_android,"glLoadMatrixxOES"); disp->set_glLoadMatrixxOES((glLoadMatrixxOES_t)ptr);
    ptr = dlsym(gles_android,"glMaterialxOES"); disp->set_glMaterialxOES((glMaterialxOES_t)ptr);
    ptr = dlsym(gles_android,"glMaterialxvOES"); disp->set_glMaterialxvOES((glMaterialxvOES_t)ptr);
    ptr = dlsym(gles_android,"glMultMatrixxOES"); disp->set_glMultMatrixxOES((glMultMatrixxOES_t)ptr);
    ptr = dlsym(gles_android,"glMultiTexCoord4xOES"); disp->set_glMultiTexCoord4xOES((glMultiTexCoord4xOES_t)ptr);
    ptr = dlsym(gles_android,"glNormal3xOES"); disp->set_glNormal3xOES((glNormal3xOES_t)ptr);
    ptr = dlsym(gles_android,"glOrthoxOES"); disp->set_glOrthoxOES((glOrthoxOES_t)ptr);
    ptr = dlsym(gles_android,"glPointParameterxOES"); disp->set_glPointParameterxOES((glPointParameterxOES_t)ptr);
    ptr = dlsym(gles_android,"glPointParameterxvOES"); disp->set_glPointParameterxvOES((glPointParameterxvOES_t)ptr);
    ptr = dlsym(gles_android,"glPointSizexOES"); disp->set_glPointSizexOES((glPointSizexOES_t)ptr);
    ptr = dlsym(gles_android,"glPolygonOffsetxOES"); disp->set_glPolygonOffsetxOES((glPolygonOffsetxOES_t)ptr);
    ptr = dlsym(gles_android,"glRotatexOES"); disp->set_glRotatexOES((glRotatexOES_t)ptr);
    ptr = dlsym(gles_android,"glSampleCoveragexOES"); disp->set_glSampleCoveragexOES((glSampleCoveragexOES_t)ptr);
    ptr = dlsym(gles_android,"glScalexOES"); disp->set_glScalexOES((glScalexOES_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvxOES"); disp->set_glTexEnvxOES((glTexEnvxOES_t)ptr);
    ptr = dlsym(gles_android,"glTexEnvxvOES"); disp->set_glTexEnvxvOES((glTexEnvxvOES_t)ptr);
    ptr = dlsym(gles_android,"glTexParameterxOES"); disp->set_glTexParameterxOES((glTexParameterxOES_t)ptr);
    ptr = dlsym(gles_android,"glTexParameterxvOES"); disp->set_glTexParameterxvOES((glTexParameterxvOES_t)ptr);
    ptr = dlsym(gles_android,"glTranslatexOES"); disp->set_glTranslatexOES((glTranslatexOES_t)ptr);
    ptr = dlsym(gles_android,"glIsRenderbufferOES"); disp->set_glIsRenderbufferOES((glIsRenderbufferOES_t)ptr);
    ptr = dlsym(gles_android,"glBindRenderbufferOES"); disp->set_glBindRenderbufferOES((glBindRenderbufferOES_t)ptr);
    ptr = dlsym(gles_android,"glDeleteRenderbuffersOES"); disp->set_glDeleteRenderbuffersOES((glDeleteRenderbuffersOES_t)ptr);
    ptr = dlsym(gles_android,"glGenRenderbuffersOES"); disp->set_glGenRenderbuffersOES((glGenRenderbuffersOES_t)ptr);
    ptr = dlsym(gles_android,"glRenderbufferStorageOES"); disp->set_glRenderbufferStorageOES((glRenderbufferStorageOES_t)ptr);
    ptr = dlsym(gles_android,"glGetRenderbufferParameterivOES"); disp->set_glGetRenderbufferParameterivOES((glGetRenderbufferParameterivOES_t)ptr);
    ptr = dlsym(gles_android,"glIsFramebufferOES"); disp->set_glIsFramebufferOES((glIsFramebufferOES_t)ptr);
    ptr = dlsym(gles_android,"glBindFramebufferOES"); disp->set_glBindFramebufferOES((glBindFramebufferOES_t)ptr);
    ptr = dlsym(gles_android,"glDeleteFramebuffersOES"); disp->set_glDeleteFramebuffersOES((glDeleteFramebuffersOES_t)ptr);
    ptr = dlsym(gles_android,"glGenFramebuffersOES"); disp->set_glGenFramebuffersOES((glGenFramebuffersOES_t)ptr);
    ptr = dlsym(gles_android,"glCheckFramebufferStatusOES"); disp->set_glCheckFramebufferStatusOES((glCheckFramebufferStatusOES_t)ptr);
    ptr = dlsym(gles_android,"glFramebufferRenderbufferOES"); disp->set_glFramebufferRenderbufferOES((glFramebufferRenderbufferOES_t)ptr);
    ptr = dlsym(gles_android,"glFramebufferTexture2DOES"); disp->set_glFramebufferTexture2DOES((glFramebufferTexture2DOES_t)ptr);
    ptr = dlsym(gles_android,"glGetFramebufferAttachmentParameterivOES"); disp->set_glGetFramebufferAttachmentParameterivOES((glGetFramebufferAttachmentParameterivOES_t)ptr);
    ptr = dlsym(gles_android,"glGenerateMipmapOES"); disp->set_glGenerateMipmapOES((glGenerateMipmapOES_t)ptr);
    ptr = dlsym(gles_android,"glMapBufferOES"); disp->set_glMapBufferOES((glMapBufferOES_t)ptr);
    ptr = dlsym(gles_android,"glUnmapBufferOES"); disp->set_glUnmapBufferOES((glUnmapBufferOES_t)ptr);
    ptr = dlsym(gles_android,"glGetBufferPointervOES"); disp->set_glGetBufferPointervOES((glGetBufferPointervOES_t)ptr);
    ptr = dlsym(gles_android,"glCurrentPaletteMatrixOES"); disp->set_glCurrentPaletteMatrixOES((glCurrentPaletteMatrixOES_t)ptr);
    ptr = dlsym(gles_android,"glLoadPaletteFromModelViewMatrixOES"); disp->set_glLoadPaletteFromModelViewMatrixOES((glLoadPaletteFromModelViewMatrixOES_t)ptr);
    ptr = dlsym(gles_android,"glMatrixIndexPointerOES"); disp->set_glMatrixIndexPointerOES((glMatrixIndexPointerOES_t)ptr);
    ptr = dlsym(gles_android,"glWeightPointerOES"); disp->set_glWeightPointerOES((glWeightPointerOES_t)ptr);
    ptr = dlsym(gles_android,"glQueryMatrixxOES"); disp->set_glQueryMatrixxOES((glQueryMatrixxOES_t)ptr);
    ptr = dlsym(gles_android,"glDepthRangefOES"); disp->set_glDepthRangefOES((glDepthRangefOES_t)ptr);
    ptr = dlsym(gles_android,"glFrustumfOES"); disp->set_glFrustumfOES((glFrustumfOES_t)ptr);
    ptr = dlsym(gles_android,"glOrthofOES"); disp->set_glOrthofOES((glOrthofOES_t)ptr);
    ptr = dlsym(gles_android,"glClipPlanefOES"); disp->set_glClipPlanefOES((glClipPlanefOES_t)ptr);
    ptr = dlsym(gles_android,"glGetClipPlanefOES"); disp->set_glGetClipPlanefOES((glGetClipPlanefOES_t)ptr);
    ptr = dlsym(gles_android,"glClearDepthfOES"); disp->set_glClearDepthfOES((glClearDepthfOES_t)ptr);
    ptr = dlsym(gles_android,"glTexGenfOES"); disp->set_glTexGenfOES((glTexGenfOES_t)ptr);
    ptr = dlsym(gles_android,"glTexGenfvOES"); disp->set_glTexGenfvOES((glTexGenfvOES_t)ptr);
    ptr = dlsym(gles_android,"glTexGeniOES"); disp->set_glTexGeniOES((glTexGeniOES_t)ptr);
    ptr = dlsym(gles_android,"glTexGenivOES"); disp->set_glTexGenivOES((glTexGenivOES_t)ptr);
    ptr = dlsym(gles_android,"glTexGenxOES"); disp->set_glTexGenxOES((glTexGenxOES_t)ptr);
    ptr = dlsym(gles_android,"glTexGenxvOES"); disp->set_glTexGenxvOES((glTexGenxvOES_t)ptr);
    ptr = dlsym(gles_android,"glGetTexGenfvOES"); disp->set_glGetTexGenfvOES((glGetTexGenfvOES_t)ptr);
    ptr = dlsym(gles_android,"glGetTexGenivOES"); disp->set_glGetTexGenivOES((glGetTexGenivOES_t)ptr);
    ptr = dlsym(gles_android,"glGetTexGenxvOES"); disp->set_glGetTexGenxvOES((glGetTexGenxvOES_t)ptr);
    ptr = dlsym(gles_android,"glBindVertexArrayOES"); disp->set_glBindVertexArrayOES((glBindVertexArrayOES_t)ptr);
    ptr = dlsym(gles_android,"glDeleteVertexArraysOES"); disp->set_glDeleteVertexArraysOES((glDeleteVertexArraysOES_t)ptr);
    ptr = dlsym(gles_android,"glGenVertexArraysOES"); disp->set_glGenVertexArraysOES((glGenVertexArraysOES_t)ptr);
    ptr = dlsym(gles_android,"glIsVertexArrayOES"); disp->set_glIsVertexArrayOES((glIsVertexArrayOES_t)ptr);
    ptr = dlsym(gles_android,"glDiscardFramebufferEXT"); disp->set_glDiscardFramebufferEXT((glDiscardFramebufferEXT_t)ptr);
    ptr = dlsym(gles_android,"glMultiDrawArraysEXT"); disp->set_glMultiDrawArraysEXT((glMultiDrawArraysEXT_t)ptr);
    ptr = dlsym(gles_android,"glMultiDrawElementsEXT"); disp->set_glMultiDrawElementsEXT((glMultiDrawElementsEXT_t)ptr);
    ptr = dlsym(gles_android,"glClipPlanefIMG"); disp->set_glClipPlanefIMG((glClipPlanefIMG_t)ptr);
    ptr = dlsym(gles_android,"glClipPlanexIMG"); disp->set_glClipPlanexIMG((glClipPlanexIMG_t)ptr);
    ptr = dlsym(gles_android,"glRenderbufferStorageMultisampleIMG"); disp->set_glRenderbufferStorageMultisampleIMG((glRenderbufferStorageMultisampleIMG_t)ptr);
    ptr = dlsym(gles_android,"glFramebufferTexture2DMultisampleIMG"); disp->set_glFramebufferTexture2DMultisampleIMG((glFramebufferTexture2DMultisampleIMG_t)ptr);
    ptr = dlsym(gles_android,"glDeleteFencesNV"); disp->set_glDeleteFencesNV((glDeleteFencesNV_t)ptr);
    ptr = dlsym(gles_android,"glGenFencesNV"); disp->set_glGenFencesNV((glGenFencesNV_t)ptr);
    ptr = dlsym(gles_android,"glIsFenceNV"); disp->set_glIsFenceNV((glIsFenceNV_t)ptr);
    ptr = dlsym(gles_android,"glTestFenceNV"); disp->set_glTestFenceNV((glTestFenceNV_t)ptr);
    ptr = dlsym(gles_android,"glGetFenceivNV"); disp->set_glGetFenceivNV((glGetFenceivNV_t)ptr);
    ptr = dlsym(gles_android,"glFinishFenceNV"); disp->set_glFinishFenceNV((glFinishFenceNV_t)ptr);
    ptr = dlsym(gles_android,"glSetFenceNV"); disp->set_glSetFenceNV((glSetFenceNV_t)ptr);
    ptr = dlsym(gles_android,"glGetDriverControlsQCOM"); disp->set_glGetDriverControlsQCOM((glGetDriverControlsQCOM_t)ptr);
    ptr = dlsym(gles_android,"glGetDriverControlStringQCOM"); disp->set_glGetDriverControlStringQCOM((glGetDriverControlStringQCOM_t)ptr);
    ptr = dlsym(gles_android,"glEnableDriverControlQCOM"); disp->set_glEnableDriverControlQCOM((glEnableDriverControlQCOM_t)ptr);
    ptr = dlsym(gles_android,"glDisableDriverControlQCOM"); disp->set_glDisableDriverControlQCOM((glDisableDriverControlQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetTexturesQCOM"); disp->set_glExtGetTexturesQCOM((glExtGetTexturesQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetBuffersQCOM"); disp->set_glExtGetBuffersQCOM((glExtGetBuffersQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetRenderbuffersQCOM"); disp->set_glExtGetRenderbuffersQCOM((glExtGetRenderbuffersQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetFramebuffersQCOM"); disp->set_glExtGetFramebuffersQCOM((glExtGetFramebuffersQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetTexLevelParameterivQCOM"); disp->set_glExtGetTexLevelParameterivQCOM((glExtGetTexLevelParameterivQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtTexObjectStateOverrideiQCOM"); disp->set_glExtTexObjectStateOverrideiQCOM((glExtTexObjectStateOverrideiQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetTexSubImageQCOM"); disp->set_glExtGetTexSubImageQCOM((glExtGetTexSubImageQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetBufferPointervQCOM"); disp->set_glExtGetBufferPointervQCOM((glExtGetBufferPointervQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetShadersQCOM"); disp->set_glExtGetShadersQCOM((glExtGetShadersQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetProgramsQCOM"); disp->set_glExtGetProgramsQCOM((glExtGetProgramsQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtIsProgramBinaryQCOM"); disp->set_glExtIsProgramBinaryQCOM((glExtIsProgramBinaryQCOM_t)ptr);
    ptr = dlsym(gles_android,"glExtGetProgramBinarySourceQCOM"); disp->set_glExtGetProgramBinarySourceQCOM((glExtGetProgramBinarySourceQCOM_t)ptr);
    ptr = dlsym(gles_android,"glStartTilingQCOM"); disp->set_glStartTilingQCOM((glStartTilingQCOM_t)ptr);
    ptr = dlsym(gles_android,"glEndTilingQCOM"); disp->set_glEndTilingQCOM((glEndTilingQCOM_t)ptr);

        return disp;
}
