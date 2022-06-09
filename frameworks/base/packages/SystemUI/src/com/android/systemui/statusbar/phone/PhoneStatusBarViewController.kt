/*
 * Copyright (C) 2021 The Android Open Source Project
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
package com.android.systemui.statusbar.phone

import android.graphics.Point
import android.view.View
import android.view.ViewGroup
import android.view.ViewTreeObserver
import com.android.systemui.R
import com.android.systemui.shared.animation.UnfoldMoveFromCenterAnimator
import com.android.systemui.unfold.SysUIUnfoldComponent
import com.android.systemui.unfold.UNFOLD_STATUS_BAR
import com.android.systemui.unfold.util.ScopedUnfoldTransitionProgressProvider
import com.android.systemui.util.ViewController
import com.android.systemui.util.kotlin.getOrNull
import java.util.Optional
import javax.inject.Inject
import javax.inject.Named

/** Controller for [PhoneStatusBarView].  */
class PhoneStatusBarViewController private constructor(
    view: PhoneStatusBarView,
    @Named(UNFOLD_STATUS_BAR) private val progressProvider: ScopedUnfoldTransitionProgressProvider?,
    private val moveFromCenterAnimationController: StatusBarMoveFromCenterAnimationController?,
    touchEventHandler: PhoneStatusBarView.TouchEventHandler
) : ViewController<PhoneStatusBarView>(view) {

    override fun onViewAttached() {
        moveFromCenterAnimationController?.let { animationController ->
            val statusBarLeftSide: View = mView.findViewById(R.id.status_bar_left_side)
            val systemIconArea: ViewGroup = mView.findViewById(R.id.system_icon_area)

            val viewsToAnimate = arrayOf(
                statusBarLeftSide,
                systemIconArea
            )

            mView.viewTreeObserver.addOnPreDrawListener(object :
                ViewTreeObserver.OnPreDrawListener {
                override fun onPreDraw(): Boolean {
                    animationController.onViewsReady(viewsToAnimate)
                    mView.viewTreeObserver.removeOnPreDrawListener(this)
                    return true
                }
            })

            mView.addOnLayoutChangeListener { _, left, _, right, _, oldLeft, _, oldRight, _ ->
                val widthChanged = right - left != oldRight - oldLeft
                if (widthChanged) {
                    moveFromCenterAnimationController.onStatusBarWidthChanged()
                }
            }
        }

        progressProvider?.setReadyToHandleTransition(true)
    }

    override fun onViewDetached() {
        progressProvider?.setReadyToHandleTransition(false)
        moveFromCenterAnimationController?.onViewDetached()
    }

    init {
        mView.setTouchEventHandler(touchEventHandler)
    }

    fun setImportantForAccessibility(mode: Int) {
        mView.importantForAccessibility = mode
    }

    class StatusBarViewsCenterProvider : UnfoldMoveFromCenterAnimator.ViewCenterProvider {
        override fun getViewCenter(view: View, outPoint: Point) =
            when (view.id) {
                R.id.status_bar_left_side -> {
                    // items aligned to the start, return start center point
                    getViewEdgeCenter(view, outPoint, isStart = true)
                }
                R.id.system_icon_area -> {
                    // items aligned to the end, return end center point
                    getViewEdgeCenter(view, outPoint, isStart = false)
                }
                else -> super.getViewCenter(view, outPoint)
            }

        /**
         * Returns start or end (based on [isStart]) center point of the view
         */
        private fun getViewEdgeCenter(view: View, outPoint: Point, isStart: Boolean) {
            val isRtl = view.resources.configuration.layoutDirection == View.LAYOUT_DIRECTION_RTL
            val isLeftEdge = isRtl xor isStart

            val viewLocation = IntArray(2)
            view.getLocationOnScreen(viewLocation)

            val viewX = viewLocation[0]
            val viewY = viewLocation[1]

            outPoint.x = viewX + if (isLeftEdge) view.height / 2 else view.width - view.height / 2
            outPoint.y = viewY + view.height / 2
        }
    }

    class Factory @Inject constructor(
        private val unfoldComponent: Optional<SysUIUnfoldComponent>,
        @Named(UNFOLD_STATUS_BAR)
        private val progressProvider: Optional<ScopedUnfoldTransitionProgressProvider>
    ) {
        fun create(
            view: PhoneStatusBarView,
            touchEventHandler: PhoneStatusBarView.TouchEventHandler
        ) =
            PhoneStatusBarViewController(
                view,
                progressProvider.getOrNull(),
                unfoldComponent.map {
                    it.getStatusBarMoveFromCenterAnimationController()
                }.getOrNull(),
                touchEventHandler
            )
    }
}
