/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License
 */

package com.android.settings.accessibility;

import android.content.Context;
import android.graphics.SurfaceTexture;
import android.media.MediaPlayer;
import android.view.Surface;
import android.view.TextureView;
import android.view.TextureView.SurfaceTextureListener;

import androidx.annotation.GuardedBy;
import androidx.annotation.RawRes;
import androidx.annotation.VisibleForTesting;

/**
 * Plays the video by {@link MediaPlayer} on {@link TextureView}, calls {@link #create(Context, int,
 * TextureView)} to setup the listener for TextureView and start to play the video. Once this player
 * is no longer used, call {@link #release()} so that MediaPlayer object can be released.
 */
public class VideoPlayer implements SurfaceTextureListener {
    private final Context mContext;
    private final Object mMediaPlayerLock = new Object();
    // Media player object can't be used after it has been released, so it will be set to null. But
    // VideoPlayer is asynchronized, media player object might be paused or resumed again before
    // released media player is set to null. Therefore, lock mediaPlayer and mediaPlayerState by
    // mediaPlayerLock keep their states consistent.
    @VisibleForTesting
    @GuardedBy("mediaPlayerLock")
    MediaPlayer mMediaPlayer;

    @VisibleForTesting
    @GuardedBy("mediaPlayerLock")
    State mMediaPlayerState = State.NONE;

    @RawRes
    private final int mVideoRes;

    @VisibleForTesting
    Surface mAnimationSurface;


    /**
     * Creates a {@link MediaPlayer} for a given resource id and starts playback when the surface
     * for
     * a given {@link TextureView} is ready.
     */
    public static VideoPlayer create(Context context, @RawRes int videoRes,
            TextureView textureView) {
        return new VideoPlayer(context, videoRes, textureView);
    }

    private VideoPlayer(Context context, @RawRes int videoRes, TextureView textureView) {
        this.mContext = context;
        this.mVideoRes = videoRes;
        textureView.setSurfaceTextureListener(this);
    }

    public void pause() {
        synchronized (mMediaPlayerLock) {
            if (mMediaPlayerState == State.STARTED) {
                mMediaPlayerState = State.PAUSED;
                mMediaPlayer.pause();
            }
        }
    }

    public void resume() {
        synchronized (mMediaPlayerLock) {
            if (mMediaPlayerState == State.PAUSED) {
                mMediaPlayer.start();
                mMediaPlayerState = State.STARTED;
            }
        }
    }

    /** Release media player when it's no longer needed. */
    public void release() {
        synchronized (mMediaPlayerLock) {
            if (mMediaPlayerState != State.NONE && mMediaPlayerState != State.END) {
                mMediaPlayerState = State.END;
                mMediaPlayer.release();
                mMediaPlayer = null;
            }
        }
        if (mAnimationSurface != null) {
            mAnimationSurface.release();
            mAnimationSurface = null;
        }
    }

    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surface, int width, int height) {
        mAnimationSurface = new Surface(surface);
        synchronized (mMediaPlayerLock) {
            mMediaPlayer = MediaPlayer.create(mContext, mVideoRes);
            mMediaPlayerState = State.PREPARED;
            mMediaPlayer.setSurface(mAnimationSurface);
            mMediaPlayer.setLooping(true);
            mMediaPlayer.start();
            mMediaPlayerState = State.STARTED;
        }
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height) {
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface) {
        release();
        return false;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface) {
    }

    /**
     * The state of MediaPlayer object. Refer to
     * https://developer.android.com/reference/android/media/MediaPlayer#StateDiagram.
     */
    public enum State {
        /** MediaPlayer objects has not be created. */
        NONE,
        /** MediaPlayer objects is created by create() method. */
        PREPARED,
        /** MediaPlayer is started. It can be paused by pause() method. */
        STARTED,
        /** MediaPlayer object is paused. Calling start() to resume it. */
        PAUSED,
        /**
         * MediaPlayer object is stopped and cannot be started until calling prepare() or
         * prepareAsync()
         * methods.
         */
        STOPPED,
        /** MediaPlayer object is released. It cannot be used again. */
        END
    }
}

