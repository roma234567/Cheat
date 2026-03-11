package com.yourname.cheat.gui

import com.yourname.cheat.ModuleManager
import net.minecraft.client.MinecraftClient
import net.minecraft.client.gui.DrawContext

object Hud {
    fun render(context: DrawContext) {
        val mc = MinecraftClient.getInstance()
        val tr = mc.textRenderer

        context.drawText(tr, "CHEAT LOADER", 8, 8, 0x00FFFF, true)

        var y = 24
        ModuleManager.activeModules().forEach { module ->
            context.drawText(tr, module.name, 8, y, 0xFFFFFF, true)
            y += 12
        }
    }
}
