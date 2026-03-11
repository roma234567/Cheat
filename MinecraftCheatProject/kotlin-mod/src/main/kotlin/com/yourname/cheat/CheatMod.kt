package com.yourname.cheat

import com.yourname.cheat.gui.ClickGUI
import net.fabricmc.api.ModInitializer
import net.fabricmc.fabric.api.client.event.lifecycle.v1.ClientTickEvents
import net.fabricmc.fabric.api.client.keybinding.v1.KeyBindingHelper
import net.minecraft.client.option.KeyBinding
import net.minecraft.client.util.InputUtil
import org.lwjgl.glfw.GLFW
import org.slf4j.LoggerFactory

@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.RUNTIME)
annotation class Mod(val value: String)

@Mod("cheat")
object CheatMod : ModInitializer {
    val LOGGER = LoggerFactory.getLogger("cheat")
    lateinit var openGuiKey: KeyBinding
        private set

    override fun onInitialize() {
        LOGGER.info("Initializing CheatMod...")
        ModuleManager.initializeDefaults()

        openGuiKey = KeyBindingHelper.registerKeyBinding(
            KeyBinding("key.cheat.open_gui", InputUtil.Type.KEYSYM, GLFW.GLFW_KEY_RIGHT_SHIFT, "category.cheat")
        )

        ClientTickEvents.END_CLIENT_TICK.register { client ->
            while (openGuiKey.wasPressed()) {
                client.setScreen(ClickGUI())
            }
            ModuleManager.onTick()
        }
    }
}
