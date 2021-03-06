/*
 ** Copyright 2007, The Android Open Source Project
 **
 ** Licensed under the Apache License, Version 2.0 (the "License");
 ** you may not use this file except in compliance with the License.
 ** You may obtain a copy of the License at
 **
 **     http://www.apache.org/licenses/LICENSE-2.0
 **
 ** Unless required by applicable law or agreed to in writing, software
 ** distributed under the License is distributed on an "AS IS" BASIS,
 ** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 ** See the License for the specific language governing permissions and
 ** limitations under the License.
 */

#ifndef ANDROID_EGL_OBJECT_H
#define ANDROID_EGL_OBJECT_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <log/log.h>
#include <stddef.h>
#include <stdint.h>
#include <system/window.h>

#include <atomic>
#include <string>
#include <vector>

#include "egl_display.h"

namespace android {

class egl_display_t;

class egl_object_t {
    egl_display_t* display;
    mutable std::atomic_size_t count;

protected:
    virtual ~egl_object_t();
    virtual void terminate();

public:
    explicit egl_object_t(egl_display_t* display);
    void destroy();

    inline void incRef() { count.fetch_add(1, std::memory_order_relaxed); }
    inline size_t decRef() { return count.fetch_sub(1, std::memory_order_acq_rel); }
    inline egl_display_t* getDisplay() const { return display; }

private:
    static bool get(egl_display_t const* display, egl_object_t* object);

public:
    template <typename N, typename T>
    class LocalRef {
        egl_object_t* ref;
        LocalRef() = delete;
        LocalRef(const LocalRef* rhs) = delete;

    public:
        ~LocalRef();
        explicit LocalRef(egl_object_t* rhs);
        explicit LocalRef(egl_display_t const* display, T o) : ref(nullptr) {
            egl_object_t* native = reinterpret_cast<N*>(o);
            if (o && egl_object_t::get(display, native)) {
                ref = native;
            }
        }
        inline N* get() { return static_cast<N*>(ref); }
        void acquire() const;
        void release() const;
        void terminate();
    };
    template <typename N, typename T>
    friend class LocalRef;
};

template <typename N, typename T>
egl_object_t::LocalRef<N, T>::LocalRef(egl_object_t* rhs) : ref(rhs) {
    if (ref) {
        ref->incRef();
    }
}

template <typename N, typename T>
egl_object_t::LocalRef<N, T>::~LocalRef() {
    if (ref) {
        ref->destroy();
    }
}

template <typename N, typename T>
void egl_object_t::LocalRef<N, T>::acquire() const {
    if (ref) {
        ref->incRef();
    }
}

template <typename N, typename T>
void egl_object_t::LocalRef<N, T>::release() const {
    if (ref) {
        if (ref->decRef() == 1) {
            // shouldn't happen because this is called from LocalRef
            ALOGE("LocalRef::release() removed the last reference!");
        }
    }
}

template <typename N, typename T>
void egl_object_t::LocalRef<N, T>::terminate() {
    if (ref) {
        ref->terminate();
    }
}

// ----------------------------------------------------------------------------

class egl_surface_t : public egl_object_t {
protected:
    ~egl_surface_t();
    void terminate() override;

public:
    typedef egl_object_t::LocalRef<egl_surface_t, EGLSurface> Ref;

    egl_surface_t(egl_display_t* dpy, EGLConfig config, EGLNativeWindowType win, EGLSurface surface,
                  EGLint colorSpace, egl_connection_t const* cnx);

    ANativeWindow* getNativeWindow() { return win; }
    ANativeWindow* getNativeWindow() const { return win; }
    EGLint getColorSpace() const { return colorSpace; }
    EGLBoolean setSmpte2086Attribute(EGLint attribute, EGLint value);
    EGLBoolean setCta8613Attribute(EGLint attribute, EGLint value);
    EGLBoolean getColorSpaceAttribute(EGLint attribute, EGLint* value) const;
    EGLBoolean getSmpte2086Attribute(EGLint attribute, EGLint* value) const;
    EGLBoolean getCta8613Attribute(EGLint attribute, EGLint* value) const;
    EGLBoolean getSmpte2086Metadata(android_smpte2086_metadata& smpte2086) const;
    EGLBoolean getCta8613Metadata(android_cta861_3_metadata& cta861_3) const;
    void resetSmpte2086Metadata() { egl_smpte2086_dirty = false; }
    void resetCta8613Metadata() { egl_cta861_3_dirty = false; }

    // Try to keep the order of these fields and size unchanged. It's not public API, but
    // it's not hard to imagine native games accessing them.
    EGLSurface surface;
    EGLConfig config;

private:
    ANativeWindow* win;

public:
    egl_connection_t const* cnx;

private:
    bool connected;
    void disconnect();
    EGLint colorSpace;

    struct egl_xy_color {
        EGLint x;
        EGLint y;
    };

    struct egl_smpte2086_metadata {
        struct egl_xy_color displayPrimaryRed;
        struct egl_xy_color displayPrimaryGreen;
        struct egl_xy_color displayPrimaryBlue;
        struct egl_xy_color whitePoint;
        EGLint maxLuminance;
        EGLint minLuminance;
    };

    struct egl_cta861_3_metadata {
        EGLint maxContentLightLevel;
        EGLint maxFrameAverageLightLevel;
    };

    bool egl_smpte2086_dirty;
    bool egl_cta861_3_dirty;

    egl_smpte2086_metadata egl_smpte2086_metadata;
    egl_cta861_3_metadata egl_cta861_3_metadata;
};

class egl_context_t : public egl_object_t {
protected:
    ~egl_context_t() {}

public:
    typedef egl_object_t::LocalRef<egl_context_t, EGLContext> Ref;

    egl_context_t(EGLDisplay dpy, EGLContext context, EGLConfig config, egl_connection_t const* cnx,
                  int version);

    void onLooseCurrent();
    void onMakeCurrent(EGLSurface draw, EGLSurface read);

    EGLDisplay dpy;
    EGLContext context;
    EGLConfig config;
    EGLSurface read;
    EGLSurface draw;
    egl_connection_t const* cnx;
    int version;
    std::string gl_extensions;
    std::vector<std::string> tokenized_gl_extensions;
};

typedef egl_surface_t::Ref SurfaceRef;
typedef egl_context_t::Ref ContextRef;

template <typename NATIVE, typename EGL>
static inline NATIVE* egl_to_native_cast(EGL arg) {
    return reinterpret_cast<NATIVE*>(arg);
}

static inline egl_surface_t* get_surface(EGLSurface surface) {
    return egl_to_native_cast<egl_surface_t>(surface);
}

static inline egl_context_t* get_context(EGLContext context) {
    return egl_to_native_cast<egl_context_t>(context);
}

}; // namespace android

#endif // ANDROID_EGL_OBJECT_H
