package com.yourname.cheat.modules

import net.minecraft.client.MinecraftClient

abstract class Module(
    val name: String,
    var keyBind: Int = -1
) {
    var enabled: Boolean = false
        private set

    protected val mc: MinecraftClient
        get() = MinecraftClient.getInstance()

    fun toggle() {
        enabled = !enabled
        if (enabled) onEnable() else onDisable()
    }

    open fun onEnable() {}
    open fun onDisable() {}
    open fun onTick() {}
    open fun onRender() {}
}
