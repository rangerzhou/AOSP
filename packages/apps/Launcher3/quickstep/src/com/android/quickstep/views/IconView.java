/*
 * Copyright (C) 2018 The Android Open Source Project
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
 * limitations under the License.
 */
package com.android.quickstep.views;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.View;

import androidx.annotation.Nullable;

import com.android.launcher3.Utilities;

/**
 * A view which draws a drawable stretched to fit its size. Unlike ImageView, it avoids relayout
 * when the drawable changes.
 */
public class IconView extends View {

    @Nullable
    private Drawable mDrawable;
    private int mDrawableWidth, mDrawableHeight;

    public IconView(Context context) {
        super(context);
    }

    public IconView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public IconView(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    /**
     * Sets a {@link Drawable} to be displayed.
     */
    public void setDrawable(@Nullable Drawable d) {
        if (mDrawable != null) {
            mDrawable.setCallback(null);
        }
        mDrawable = d;
        if (mDrawable != null) {
            mDrawable.setCallback(this);
            setDrawableSizeInternal(getWidth(), getHeight());
        }
        invalidate();
    }

    /**
     * Sets the size of the icon drawable.
     */
    public void setDrawableSize(int iconWidth, int iconHeight) {
        mDrawableWidth = iconWidth;
        mDrawableHeight = iconHeight;
        if (mDrawable != null) {
            setDrawableSizeInternal(getWidth(), getHeight());
        }
    }

    private void setDrawableSizeInternal(int selfWidth, int selfHeight) {
        Rect selfRect = new Rect(0, 0, selfWidth, selfHeight);
        Rect drawableRect = new Rect();
        Gravity.apply(Gravity.CENTER, mDrawableWidth, mDrawableHeight, selfRect, drawableRect);
        mDrawable.setBounds(drawableRect);
    }

    @Nullable
    public Drawable getDrawable() {
        return mDrawable;
    }

    public int getDrawableWidth() {
        return mDrawableWidth;
    }

    public int getDrawableHeight() {
        return mDrawableHeight;
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {
        super.onSizeChanged(w, h, oldw, oldh);
        if (mDrawable != null) {
            setDrawableSizeInternal(w, h);
        }
    }

    @Override
    protected boolean verifyDrawable(Drawable who) {
        return super.verifyDrawable(who) || who == mDrawable;
    }

    @Override
    protected void drawableStateChanged() {
        super.drawableStateChanged();

        final Drawable drawable = mDrawable;
        if (drawable != null && drawable.isStateful()
                && drawable.setState(getDrawableState())) {
            invalidateDrawable(drawable);
        }
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (mDrawable != null) {
            mDrawable.draw(canvas);
        }
    }

    @Override
    public boolean hasOverlappingRendering() {
        return false;
    }

    @Override
    public void setAlpha(float alpha) {
        super.setAlpha(alpha);
        if (alpha > 0) {
            setVisibility(VISIBLE);
        } else {
            setVisibility(INVISIBLE);
        }
    }

    /**
     * Set the tint color of the icon, useful for scrimming or dimming.
     *
     * @param color to blend in.
     * @param amount [0,1] 0 no tint, 1 full tint
     */
    public void setIconColorTint(int color, float amount) {
        if (mDrawable != null) {
            mDrawable.setColorFilter(Utilities.makeColorTintingColorFilter(color, amount));
        }
    }
}
