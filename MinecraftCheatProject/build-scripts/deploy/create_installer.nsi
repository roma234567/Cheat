; NSIS installer template
Name "Minecraft Cheat Loader"
OutFile "MinecraftCheatSetup.exe"
InstallDir "$PROGRAMFILES\MinecraftCheat"

Section "Install"
  SetOutPath "$INSTDIR"
  File /r "..\..\dist\installer\*.*"
SectionEnd
