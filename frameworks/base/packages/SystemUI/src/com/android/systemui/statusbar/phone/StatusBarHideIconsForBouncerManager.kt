package com.android.systemui.statusbar.phone

import com.android.systemui.Dumpable
import com.android.systemui.dagger.SysUISingleton
import com.android.systemui.dagger.qualifiers.Main
import com.android.systemui.dump.DumpManager
import com.android.systemui.statusbar.CommandQueue
import com.android.systemui.util.concurrency.DelayableExecutor
import java.io.FileDescriptor
import java.io.PrintWriter
import javax.inject.Inject

/**
 * A class that manages if the status bar (clock + notifications + signal cluster) should be visible
 * or not when showing the bouncer.
 *
 * We want to hide it when:
 * • User swipes up on the keyguard
 * • Locked activity that doesn't show a status bar requests the bouncer.
 *
 * [getShouldHideStatusBarIconsForBouncer] is the main exported method for this class. The other
 * methods set state variables that are used in the calculation or manually trigger an update.
 */
@SysUISingleton
class StatusBarHideIconsForBouncerManager @Inject constructor(
    private val commandQueue: CommandQueue,
    @Main private val mainExecutor: DelayableExecutor,
    dumpManager: DumpManager
) : Dumpable {
    // State variables set by external classes.
    private var panelExpanded: Boolean = false
    private var isOccluded: Boolean = false
    private var bouncerShowing: Boolean = false
    private var topAppHidesStatusBar: Boolean = false
    private var statusBarWindowHidden: Boolean = false
    private var displayId: Int = 0

    // State variables calculated internally.
    private var hideIconsForBouncer: Boolean = false
    private var bouncerWasShowingWhenHidden: Boolean = false
    private var wereIconsJustHidden: Boolean = false

    init {
        dumpManager.registerDumpable(this)
    }

    /** Returns true if the status bar icons should be hidden in the bouncer. */
    fun getShouldHideStatusBarIconsForBouncer(): Boolean {
        return hideIconsForBouncer || wereIconsJustHidden
    }

    fun setStatusBarWindowHidden(statusBarWindowHidden: Boolean) {
        this.statusBarWindowHidden = statusBarWindowHidden
    }

    fun setDisplayId(displayId: Int) {
        this.displayId = displayId
    }

    fun setPanelExpandedAndTriggerUpdate(panelExpanded: Boolean) {
        this.panelExpanded = panelExpanded
        updateHideIconsForBouncer(animate = false)
    }

    fun setIsOccludedAndTriggerUpdate(isOccluded: Boolean) {
        this.isOccluded = isOccluded
        updateHideIconsForBouncer(animate = false)
    }

    fun setBouncerShowingAndTriggerUpdate(bouncerShowing: Boolean) {
        this.bouncerShowing = bouncerShowing
        updateHideIconsForBouncer(animate = true)
    }

    fun setTopAppHidesStatusBarAndTriggerUpdate(topAppHidesStatusBar: Boolean) {
        this.topAppHidesStatusBar = topAppHidesStatusBar
        if (!topAppHidesStatusBar && wereIconsJustHidden) {
            // Immediately update the icon hidden state, since that should only apply if we're
            // staying fullscreen.
            wereIconsJustHidden = false
            commandQueue.recomputeDisableFlags(displayId, /* animate= */ true)
        }
        updateHideIconsForBouncer(animate = true)
    }

    /**
     * Updates whether the status bar icons should be hidden in the bouncer. May trigger
     * [commandQueue.recomputeDisableFlags] if the icon visibility status changes.
     */
    fun updateHideIconsForBouncer(animate: Boolean) {
        val hideBecauseApp =
            topAppHidesStatusBar &&
                    isOccluded &&
                    (statusBarWindowHidden || bouncerShowing)
        val hideBecauseKeyguard = !panelExpanded && !isOccluded && bouncerShowing
        val shouldHideIconsForBouncer = hideBecauseApp || hideBecauseKeyguard
        if (hideIconsForBouncer != shouldHideIconsForBouncer) {
            hideIconsForBouncer = shouldHideIconsForBouncer
            if (!shouldHideIconsForBouncer && bouncerWasShowingWhenHidden) {
                // We're delaying the showing, since most of the time the fullscreen app will
                // hide the icons again and we don't want them to fade in and out immediately again.
                wereIconsJustHidden = true
                mainExecutor.executeDelayed(
                    {
                        wereIconsJustHidden = false
                        commandQueue.recomputeDisableFlags(displayId, true)
                    },
                    500
                )
            } else {
                commandQueue.recomputeDisableFlags(displayId, animate)
            }
        }
        if (shouldHideIconsForBouncer) {
            bouncerWasShowingWhenHidden = bouncerShowing
        }
    }

    override fun dump(fd: FileDescriptor, pw: PrintWriter, args: Array<out String>) {
        pw.println("---- State variables set externally ----")
        pw.println("panelExpanded=$panelExpanded")
        pw.println("isOccluded=$isOccluded")
        pw.println("bouncerShowing=$bouncerShowing")
        pw.println("topAppHideStatusBar=$topAppHidesStatusBar")
        pw.println("statusBarWindowHidden=$statusBarWindowHidden")
        pw.println("displayId=$displayId")

        pw.println("---- State variables calculated internally ----")
        pw.println("hideIconsForBouncer=$hideIconsForBouncer")
        pw.println("bouncerWasShowingWhenHidden=$bouncerWasShowingWhenHidden")
        pw.println("wereIconsJustHidden=$wereIconsJustHidden")
    }
}
