package com.yourname.cheat.modules

class Flight : Module("Flight") {
    override fun onTick() {
        val player = mc.player ?: return
        player.abilities.allowFlying = true
        player.abilities.flying = true
        player.abilities.flySpeed = 0.08f
    }

    override fun onDisable() {
        val player = mc.player ?: return
        player.abilities.flying = false
    }
}
