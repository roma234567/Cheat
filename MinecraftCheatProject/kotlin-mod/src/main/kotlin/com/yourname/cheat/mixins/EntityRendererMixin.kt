package com.yourname.cheat.mixins

import com.yourname.cheat.ModuleManager
import net.minecraft.client.render.entity.EntityRenderer
import net.minecraft.entity.Entity
import org.spongepowered.asm.mixin.Mixin
import org.spongepowered.asm.mixin.injection.At
import org.spongepowered.asm.mixin.injection.Inject
import org.spongepowered.asm.mixin.injection.callback.CallbackInfo

@Mixin(EntityRenderer::class)
class EntityRendererMixin {
    @Inject(method = ["render"], at = [At("TAIL")])
    private fun cheat$onRender(entity: Entity, yaw: Float, tickDelta: Float, ci: CallbackInfo) {
        ModuleManager.onRender()
    }
}
