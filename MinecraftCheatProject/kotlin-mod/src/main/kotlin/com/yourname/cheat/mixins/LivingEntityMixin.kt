package com.yourname.cheat.mixins

import net.minecraft.entity.LivingEntity
import net.minecraft.entity.damage.DamageSource
import org.spongepowered.asm.mixin.Mixin
import org.spongepowered.asm.mixin.injection.At
import org.spongepowered.asm.mixin.injection.Inject
import org.spongepowered.asm.mixin.injection.callback.CallbackInfoReturnable

@Mixin(LivingEntity::class)
class LivingEntityMixin {
    @Inject(method = ["damage"], at = [At("HEAD")])
    private fun cheat$onDamage(source: DamageSource, amount: Float, cir: CallbackInfoReturnable<Boolean>) {
        // Hook point for future damage logic.
    }
}
