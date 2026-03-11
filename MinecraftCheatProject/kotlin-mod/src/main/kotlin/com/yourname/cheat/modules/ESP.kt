package com.yourname.cheat.modules

import com.yourname.cheat.utils.RenderUtils
import net.minecraft.client.render.VertexConsumerProvider

class ESP : Module("ESP") {
    override fun onRender() {
        val world = mc.world ?: return
        val player = mc.player ?: return

        world.players
            .filter { it != player }
            .forEach { target ->
                RenderUtils.drawBox(target.boundingBox, 0f, 1f, 1f, 0.35f)
            }
    }
}
