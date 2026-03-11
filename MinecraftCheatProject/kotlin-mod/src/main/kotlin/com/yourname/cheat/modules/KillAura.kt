package com.yourname.cheat.modules

import com.yourname.cheat.utils.RotationUtils
import net.minecraft.entity.LivingEntity

class KillAura : Module("KillAura") {
    var range: Double = 4.0
    var cps: Int = 8
    var throughWalls: Boolean = false

    private var lastAttackMs: Long = 0

    override fun onTick() {
        val player = mc.player ?: return
        val world = mc.world ?: return

        val target = world.entities
            .filterIsInstance<LivingEntity>()
            .filter { it != player && it.isAlive }
            .filter { player.distanceTo(it) <= range }
            .minByOrNull { player.squaredDistanceTo(it) }
            ?: return

        if (!throughWalls && !player.canSee(target)) return

        val now = System.currentTimeMillis()
        val delay = 1000L / cps.coerceAtLeast(1)
        if (now - lastAttackMs < delay) return

        val (yaw, pitch) = RotationUtils.getRotationToEntity(target)
        player.yaw = yaw
        player.pitch = pitch

        mc.interactionManager?.attackEntity(player, target)
        player.swingHand(player.activeHand)
        lastAttackMs = now
    }
}
