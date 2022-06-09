// Generated Code - DO NOT EDIT !!
// generated by 'emugen'
#ifndef __renderControl_client_ftable_t_h
#define __renderControl_client_ftable_t_h


static const struct _renderControl_funcs_by_name {
	const char *name;
	void *proc;
} renderControl_funcs_by_name[] = {
	{"rcGetRendererVersion", (void*)rcGetRendererVersion},
	{"rcGetEGLVersion", (void*)rcGetEGLVersion},
	{"rcQueryEGLString", (void*)rcQueryEGLString},
	{"rcGetGLString", (void*)rcGetGLString},
	{"rcGetNumConfigs", (void*)rcGetNumConfigs},
	{"rcGetConfigs", (void*)rcGetConfigs},
	{"rcChooseConfig", (void*)rcChooseConfig},
	{"rcGetFBParam", (void*)rcGetFBParam},
	{"rcCreateContext", (void*)rcCreateContext},
	{"rcDestroyContext", (void*)rcDestroyContext},
	{"rcCreateWindowSurface", (void*)rcCreateWindowSurface},
	{"rcDestroyWindowSurface", (void*)rcDestroyWindowSurface},
	{"rcCreateColorBuffer", (void*)rcCreateColorBuffer},
	{"rcOpenColorBuffer", (void*)rcOpenColorBuffer},
	{"rcCloseColorBuffer", (void*)rcCloseColorBuffer},
	{"rcSetWindowColorBuffer", (void*)rcSetWindowColorBuffer},
	{"rcFlushWindowColorBuffer", (void*)rcFlushWindowColorBuffer},
	{"rcMakeCurrent", (void*)rcMakeCurrent},
	{"rcFBPost", (void*)rcFBPost},
	{"rcFBSetSwapInterval", (void*)rcFBSetSwapInterval},
	{"rcBindTexture", (void*)rcBindTexture},
	{"rcBindRenderbuffer", (void*)rcBindRenderbuffer},
	{"rcColorBufferCacheFlush", (void*)rcColorBufferCacheFlush},
	{"rcReadColorBuffer", (void*)rcReadColorBuffer},
	{"rcUpdateColorBuffer", (void*)rcUpdateColorBuffer},
	{"rcOpenColorBuffer2", (void*)rcOpenColorBuffer2},
	{"rcCreateClientImage", (void*)rcCreateClientImage},
	{"rcDestroyClientImage", (void*)rcDestroyClientImage},
	{"rcSelectChecksumHelper", (void*)rcSelectChecksumHelper},
	{"rcCreateSyncKHR", (void*)rcCreateSyncKHR},
	{"rcClientWaitSyncKHR", (void*)rcClientWaitSyncKHR},
	{"rcFlushWindowColorBufferAsync", (void*)rcFlushWindowColorBufferAsync},
	{"rcDestroySyncKHR", (void*)rcDestroySyncKHR},
	{"rcSetPuid", (void*)rcSetPuid},
	{"rcUpdateColorBufferDMA", (void*)rcUpdateColorBufferDMA},
	{"rcCreateColorBufferDMA", (void*)rcCreateColorBufferDMA},
	{"rcWaitSyncKHR", (void*)rcWaitSyncKHR},
	{"rcCompose", (void*)rcCompose},
	{"rcCreateDisplay", (void*)rcCreateDisplay},
	{"rcDestroyDisplay", (void*)rcDestroyDisplay},
	{"rcSetDisplayColorBuffer", (void*)rcSetDisplayColorBuffer},
	{"rcGetDisplayColorBuffer", (void*)rcGetDisplayColorBuffer},
	{"rcGetColorBufferDisplay", (void*)rcGetColorBufferDisplay},
	{"rcGetDisplayPose", (void*)rcGetDisplayPose},
	{"rcSetDisplayPose", (void*)rcSetDisplayPose},
	{"rcSetColorBufferVulkanMode", (void*)rcSetColorBufferVulkanMode},
	{"rcReadColorBufferYUV", (void*)rcReadColorBufferYUV},
	{"rcIsSyncSignaled", (void*)rcIsSyncSignaled},
	{"rcCreateColorBufferWithHandle", (void*)rcCreateColorBufferWithHandle},
	{"rcCreateBuffer", (void*)rcCreateBuffer},
	{"rcCloseBuffer", (void*)rcCloseBuffer},
	{"rcSetColorBufferVulkanMode2", (void*)rcSetColorBufferVulkanMode2},
	{"rcMapGpaToBufferHandle", (void*)rcMapGpaToBufferHandle},
	{"rcCreateBuffer2", (void*)rcCreateBuffer2},
	{"rcMapGpaToBufferHandle2", (void*)rcMapGpaToBufferHandle2},
	{"rcFlushWindowColorBufferAsyncWithFrameNumber", (void*)rcFlushWindowColorBufferAsyncWithFrameNumber},
	{"rcSetTracingForPuid", (void*)rcSetTracingForPuid},
	{"rcMakeCurrentAsync", (void*)rcMakeCurrentAsync},
	{"rcComposeAsync", (void*)rcComposeAsync},
	{"rcDestroySyncKHRAsync", (void*)rcDestroySyncKHRAsync},
	{"rcComposeWithoutPost", (void*)rcComposeWithoutPost},
	{"rcComposeAsyncWithoutPost", (void*)rcComposeAsyncWithoutPost},
	{"rcCreateDisplayById", (void*)rcCreateDisplayById},
	{"rcSetDisplayPoseDpi", (void*)rcSetDisplayPoseDpi},
	{"rcReadColorBufferDMA", (void*)rcReadColorBufferDMA},
	{"rcGetFBDisplayConfigsCount", (void*)rcGetFBDisplayConfigsCount},
	{"rcGetFBDisplayConfigsParam", (void*)rcGetFBDisplayConfigsParam},
	{"rcGetFBDisplayActiveConfig", (void*)rcGetFBDisplayActiveConfig},
};
static const int renderControl_num_funcs = sizeof(renderControl_funcs_by_name) / sizeof(struct _renderControl_funcs_by_name);


#endif
