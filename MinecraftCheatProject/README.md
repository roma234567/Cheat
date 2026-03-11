# Minecraft Cheat Project

> Educational multi-module project: Qt6 launcher (C++) + Fabric Kotlin mod skeleton for Minecraft 1.21.4.

## Overview
- **cpp-loader**: standalone desktop GUI launcher built with Qt6.
- **kotlin-mod**: Fabric Kotlin mod with module framework and mixin hooks.
- **build-scripts**: helper scripts to build both parts and collect artifacts.

## Screenshots
- Add your screenshots here (launcher UI / in-game HUD).

## Build
### 1) Build C++ loader
```bash
cd cpp-loader
cmake -S . -B build
cmake --build build --config Release
```

### 2) Build Kotlin mod
```bash
cd kotlin-mod
./gradlew build
```

### 3) Build all
- Linux/macOS: `./build-scripts/build_all.sh`
- Windows: `build-scripts\build_all.bat`

## Usage
1. Place resulting mod `.jar` into Minecraft `mods/` folder.
2. Run loader binary.
3. Choose nickname and game version.
4. Start game from loader.

## Disclaimer
Use responsibly and only where explicitly allowed.
