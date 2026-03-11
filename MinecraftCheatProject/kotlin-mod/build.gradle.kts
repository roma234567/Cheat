plugins {
    id("fabric-loom") version "1.7-SNAPSHOT"
    kotlin("jvm") version "1.9.23"
}

version = property("mod_version") as String
group = property("maven_group") as String

repositories {
    maven("https://maven.fabricmc.net/")
    mavenCentral()
}

dependencies {
    minecraft("com.mojang:minecraft:${property("minecraft_version")}")
    mappings("net.fabricmc:yarn:${property("minecraft_version")}+build.1:v2")
    modImplementation("net.fabricmc:fabric-loader:${property("fabric_loader_version")}")
    modImplementation("net.fabricmc.fabric-api:fabric-api:${property("fabric_api_version")}")
    modImplementation("net.fabricmc:fabric-language-kotlin:1.11.0+kotlin.2.0.0")
}

loom {
    mixin {
        defaultRefmapName.set("cheat.refmap.json")
    }
}

tasks.withType<JavaCompile>().configureEach {
    options.release.set(21)
}

kotlin {
    jvmToolchain(21)
}
