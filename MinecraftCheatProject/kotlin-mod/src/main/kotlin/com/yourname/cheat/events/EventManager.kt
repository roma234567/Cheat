package com.yourname.cheat.events

object EventManager {
    private val tickListeners = mutableListOf<() -> Unit>()

    fun onTick(listener: () -> Unit) {
        tickListeners += listener
    }

    fun emitTick() {
        tickListeners.forEach { it.invoke() }
    }

    // TODO: Add unsubscribe handles and render/input event channels.
}
