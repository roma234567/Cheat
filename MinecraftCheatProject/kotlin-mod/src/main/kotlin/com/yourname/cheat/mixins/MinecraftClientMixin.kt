package com.yourname.cheat.mixins

import com.yourname.cheat.ModuleManager
import net.minecraft.client.MinecraftClient
import org.spongepowered.asm.mixin.Mixin
import org.spongepowered.asm.mixin.injection.At
import org.spongepowered.asm.mixin.injection.Inject
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo

@Mixin(MinecraftClient::class)
class MinecraftClientMixin {
    @Inject(method = ["tick"], at = [At("TAIL")])
    private fun cheat$onTick(ci: CallbackInfo) {
        ModuleManager.onTick()
    }
}
