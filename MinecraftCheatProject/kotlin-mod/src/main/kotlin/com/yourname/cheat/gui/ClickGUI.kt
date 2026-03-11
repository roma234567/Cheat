package com.yourname.cheat.gui

import com.yourname.cheat.ModuleManager
import net.minecraft.client.gui.DrawContext
import net.minecraft.client.gui.screen.Screen
import net.minecraft.text.Text

class ClickGUI : Screen(Text.literal("Cheat GUI")) {
    override fun render(context: DrawContext, mouseX: Int, mouseY: Int, delta: Float) {
        renderBackground(context, mouseX, mouseY, delta)

        context.drawText(textRenderer, "Modules", 20, 20, 0xFFFFFF, true)

        var y = 45
        ModuleManager.allModules().forEach { module ->
            val color = if (module.enabled) 0x00FF00 else 0xFF5555
            context.drawText(textRenderer, "[${if (module.enabled) "x" else " "}] ${module.name}", 20, y, color, true)
            y += 14
        }

        super.render(context, mouseX, mouseY, delta)
    }

    override fun mouseClicked(mouseX: Double, mouseY: Double, button: Int): Boolean {
        var y = 45
        ModuleManager.allModules().forEach { module ->
            val inRow = mouseX in 20.0..220.0 && mouseY in y.toDouble()..(y + 12).toDouble()
            if (inRow && button == 0) {
                module.toggle()
                return true
            }
            y += 14
        }
        return super.mouseClicked(mouseX, mouseY, button)
    }
}
