@echo off
setlocal

set ROOT_DIR=%~dp0\..\..
set DIST_DIR=%ROOT_DIR%\dist\installer

if not exist "%DIST_DIR%" mkdir "%DIST_DIR%"
if not exist "%DIST_DIR%\loader" mkdir "%DIST_DIR%\loader"
if not exist "%DIST_DIR%\mod" mkdir "%DIST_DIR%\mod"

copy /Y "%ROOT_DIR%\cpp-loader\build\Release\minecraft-cheat-loader.exe" "%DIST_DIR%\loader\" >nul 2>nul
copy /Y "%ROOT_DIR%\kotlin-mod\build\libs\*.jar" "%DIST_DIR%\mod\" >nul 2>nul

echo Files copied to %DIST_DIR%
