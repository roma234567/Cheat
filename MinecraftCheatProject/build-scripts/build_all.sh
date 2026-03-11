#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
DIST_DIR="$ROOT_DIR/dist"

mkdir -p "$DIST_DIR"

echo "[1/3] Building C++ loader..."
cmake -S "$ROOT_DIR/cpp-loader" -B "$ROOT_DIR/cpp-loader/build"
cmake --build "$ROOT_DIR/cpp-loader/build" --config Release

echo "[2/3] Building Kotlin mod..."
(cd "$ROOT_DIR/kotlin-mod" && ./gradlew build)

echo "[3/3] Collecting artifacts..."
cp -f "$ROOT_DIR/cpp-loader/build/minecraft-cheat-loader" "$DIST_DIR/" 2>/dev/null || true
cp -f "$ROOT_DIR/kotlin-mod/build/libs"/*.jar "$DIST_DIR/" 2>/dev/null || true

echo "Done. Artifacts in: $DIST_DIR"
