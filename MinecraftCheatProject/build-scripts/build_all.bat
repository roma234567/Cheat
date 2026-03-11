@echo off
setlocal enabledelayedexpansion

set ROOT_DIR=%~dp0..
set DIST_DIR=%ROOT_DIR%\dist

if not exist "%DIST_DIR%" mkdir "%DIST_DIR%"

echo [1/3] Building C++ loader...
cmake -S "%ROOT_DIR%\cpp-loader" -B "%ROOT_DIR%\cpp-loader\build"
if errorlevel 1 exit /b 1
cmake --build "%ROOT_DIR%\cpp-loader\build" --config Release
if errorlevel 1 exit /b 1

echo [2/3] Building Kotlin mod...
cd /d "%ROOT_DIR%\kotlin-mod"
call gradlew.bat build
if errorlevel 1 exit /b 1

echo [3/3] Collecting artifacts...
copy /Y "%ROOT_DIR%\cpp-loader\build\Release\minecraft-cheat-loader.exe" "%DIST_DIR%\" >nul 2>nul
copy /Y "%ROOT_DIR%\kotlin-mod\build\libs\*.jar" "%DIST_DIR%\" >nul 2>nul

echo Done. Artifacts in: %DIST_DIR%
