package com.yourname.cheat

import com.yourname.cheat.modules.ESP
import com.yourname.cheat.modules.Flight
import com.yourname.cheat.modules.KillAura
import com.yourname.cheat.modules.Module
import com.yourname.cheat.modules.Speed

object ModuleManager {
    private val modules = mutableListOf<Module>()

    fun initializeDefaults() {
        if (modules.isNotEmpty()) return
        registerModule(KillAura())
        registerModule(ESP())
        registerModule(Flight())
        registerModule(Speed())
    }

    fun registerModule(module: Module) {
        modules += module
    }

    fun getModule(name: String): Module? = modules.firstOrNull { it.name.equals(name, ignoreCase = true) }

    fun toggleModule(name: String) {
        getModule(name)?.toggle()
    }

    fun allModules(): List<Module> = modules.toList()

    fun activeModules(): List<Module> = modules.filter { it.enabled }

    fun onTick() {
        modules.filter { it.enabled }.forEach { it.onTick() }
    }

    fun onRender() {
        modules.filter { it.enabled }.forEach { it.onRender() }
    }
}
