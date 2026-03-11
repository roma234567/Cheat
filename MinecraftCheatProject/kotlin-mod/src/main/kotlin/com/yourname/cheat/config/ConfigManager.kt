package com.yourname.cheat.config

object ConfigManager {
    private val values = mutableMapOf<String, String>()

    fun get(key: String, default: String = ""): String = values[key] ?: default

    fun set(key: String, value: String) {
        values[key] = value
    }

    // TODO: Persist config to disk using Gson/Kotlinx serialization.
}
