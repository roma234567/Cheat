package com.yourname.cheat.modules

import net.minecraft.util.math.Vec3d

class Speed : Module("Speed") {
    private val multiplier = 1.35

    override fun onTick() {
        val player = mc.player ?: return
        if (!player.isOnGround) return

        val v = player.velocity
        player.velocity = Vec3d(v.x * multiplier, v.y, v.z * multiplier)
    }
}
