package com.yourname.cheat.utils

import net.minecraft.entity.Entity
import kotlin.math.atan2
import kotlin.math.sqrt

object RotationUtils {
    fun getRotationToEntity(entity: Entity): Pair<Float, Float> {
        val player = net.minecraft.client.MinecraftClient.getInstance().player ?: return 0f to 0f

        val dx = entity.x - player.x
        val dy = (entity.eyeY - player.eyeY)
        val dz = entity.z - player.z

        val dist = sqrt(dx * dx + dz * dz)
        val yaw = Math.toDegrees(atan2(dz, dx)).toFloat() - 90f
        val pitch = -Math.toDegrees(atan2(dy, dist)).toFloat()
        return yaw to pitch
    }

    fun smoothRotation(current: Float, target: Float, speed: Float): Float {
        val delta = (target - current).coerceIn(-speed, speed)
        return current + delta
    }
}
