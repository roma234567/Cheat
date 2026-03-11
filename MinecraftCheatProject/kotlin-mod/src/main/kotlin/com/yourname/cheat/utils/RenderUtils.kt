package com.yourname.cheat.utils

import com.mojang.blaze3d.systems.RenderSystem
import net.minecraft.util.math.Box

object RenderUtils {
    fun drawBox(box: Box, r: Float, g: Float, b: Float, a: Float) {
        RenderSystem.setShaderColor(r, g, b, a)
        // Placeholder: actual world-space rendering implementation goes here.
    }

    fun drawText(text: String, x: Float, y: Float, color: Int) {
        // Placeholder: UI text drawing helper.
    }

    fun drawLine(x1: Float, y1: Float, x2: Float, y2: Float, color: Int) {
        // Placeholder: 2D line drawing helper.
    }
}
