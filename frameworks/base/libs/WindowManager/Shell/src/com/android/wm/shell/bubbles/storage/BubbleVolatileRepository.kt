/*
 * Copyright (C) 2020 The Android Open Source Project
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
package com.android.wm.shell.bubbles.storage

import android.content.pm.LauncherApps
import android.os.UserHandle
import android.util.SparseArray
import com.android.internal.annotations.VisibleForTesting
import com.android.wm.shell.bubbles.ShortcutKey

private const val CAPACITY = 16

/**
 * BubbleVolatileRepository holds the most updated snapshot of list of bubbles for in-memory
 * manipulation.
 */
class BubbleVolatileRepository(private val launcherApps: LauncherApps) {

    /**
     * Set of bubbles per user. Each set of bubbles is ordered by recency.
     */
    private var entitiesByUser = SparseArray<MutableList<BubbleEntity>>()

    /**
     * The capacity of the cache.
     */
    @VisibleForTesting
    var capacity = CAPACITY

    /**
     * Returns a snapshot of all the bubbles, a map of the userId to bubble list.
     */
    val bubbles: SparseArray<List<BubbleEntity>>
        @Synchronized
        get() {
            val map = SparseArray<List<BubbleEntity>>()
            for (i in 0 until entitiesByUser.size()) {
                val k = entitiesByUser.keyAt(i)
                val v = entitiesByUser.valueAt(i)
                map.put(k, v.toList())
            }
            return map
        }

    /**
     * Returns the entity list of the provided user's bubbles or creates one if it doesn't exist.
     */
    @Synchronized
    fun getEntities(userId: Int): MutableList<BubbleEntity> {
        val entities = entitiesByUser.get(userId)
        return when (entities) {
            null -> mutableListOf<BubbleEntity>().also {
                entitiesByUser.put(userId, it)
            }
            else -> entities
        }
    }

    /**
     * Add the bubbles to memory and perform a de-duplication. In case a bubble already exists,
     * it will be moved to the last.
     */
    @Synchronized
    fun addBubbles(userId: Int, bubbles: List<BubbleEntity>) {
        if (bubbles.isEmpty()) return
        // Get the list for this user
        var entities = getEntities(userId)
        // Verify the size of given bubbles is within capacity, otherwise trim down to capacity
        val bubblesInRange = bubbles.takeLast(capacity)
        // To ensure natural ordering of the bubbles, removes bubbles which already exist
        val uniqueBubbles = bubblesInRange.filterNot { b: BubbleEntity ->
            entities.removeIf { e: BubbleEntity -> b.key == e.key } }
        val overflowCount = entities.size + bubblesInRange.size - capacity
        if (overflowCount > 0) {
            // Uncache ShortcutInfo of bubbles that will be removed due to capacity
            uncache(entities.take(overflowCount))
            entities = entities.drop(overflowCount).toMutableList()
        }
        entities.addAll(bubblesInRange)
        entitiesByUser.put(userId, entities)
        cache(uniqueBubbles)
    }

    @Synchronized
    fun removeBubbles(userId: Int, bubbles: List<BubbleEntity>) =
            uncache(bubbles.filter { b: BubbleEntity ->
                getEntities(userId).removeIf { e: BubbleEntity -> b.key == e.key } })

    private fun cache(bubbles: List<BubbleEntity>) {
        bubbles.groupBy { ShortcutKey(it.userId, it.packageName) }.forEach { (key, bubbles) ->
            launcherApps.cacheShortcuts(key.pkg, bubbles.map { it.shortcutId },
                    UserHandle.of(key.userId), LauncherApps.FLAG_CACHE_BUBBLE_SHORTCUTS)
        }
    }

    private fun uncache(bubbles: List<BubbleEntity>) {
        bubbles.groupBy { ShortcutKey(it.userId, it.packageName) }.forEach { (key, bubbles) ->
            launcherApps.uncacheShortcuts(key.pkg, bubbles.map { it.shortcutId },
                    UserHandle.of(key.userId), LauncherApps.FLAG_CACHE_BUBBLE_SHORTCUTS)
        }
    }
}
