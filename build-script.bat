::C:\Program Files\Epic Games\UE_5.5\Engine\Build\BatchFiles\RunUAT.bat

:: "C:/Program Files/Epic Games/UE_5.5/Engine/Build/BatchFiles/RunUAT.bat"  -ScriptsForProject="C:/Users/Selsy/Documents/Unreal Projects/MenuSubsystemSteam/MenuSubsystemSteam.uproject" Turnkey -utf8output -WaitForUATMutex -command=VerifySdk -ReportFilename="C:/Users/Selsy/Documents/Unreal Projects/MenuSubsystemSteam/Intermediate/TurnkeyReport_1.log" -log="C:/Users/Selsy/Documents/Unreal Projects/MenuSubsystemSteam/Intermediate/TurnkeyLog_1.log" -project="C:/Users/Selsy/Documents/Unreal Projects/MenuSubsystemSteam/MenuSubsystemSteam.uproject"  -Device=Win64@RROUJOUE" -nocompile -nocompileuat 

set projectFile="C:/Users/Selsy/Documents/Unreal Projects/MenuSubsystemSteam/MenuSubsystemSteam.uproject"
set unrealCmd="C:\Program Files\Epic Games\UE_5.5\Engine\Binaries\Win64\UnrealEditor-Cmd.exe"
set buildDir="C:/Users/Selsy/Documents/Unreal Projects/MenuSubsystemSteam/Build/Windows"
set unrealUAT="C:/Program Files/Epic Games/UE_5.5/Engine/Build/BatchFiles/RunUAT.bat" 

%unrealUAT% -ScriptsForProject=%projectFile% Turnkey -command=VerifySdk -platform=Win64 -UpdateIfNeeded -EditorIO -EditorIOPort=50963  -project=%projectFile% BuildCookRun -nop4 -utf8output -nocompileeditor -skipbuildeditor -cook  -project=%projectFile% -target=MenuSubsystemSteam  -unrealexe=%unrealCmd% -platform=Win64 -installed -skipstage"

%unrealUAT% -ScriptsForProject=%projectFile% Turnkey -command=VerifySdk -platform=Win64 -UpdateIfNeeded -EditorIO -EditorIOPort=50963  -project=%projectFile% BuildCookRun -nop4 -utf8output -nocompileeditor -skipbuildeditor -cook  -project=%projectFile% -target=MenuSubsystemSteam   -unrealexe=%unrealCmd% -platform=Win64 -installed -stage -archive -package -build -clean -pak -iostore -compressed -prereqs -archivedirectory=%buildDir% -clientconfig=Development" -nocompile -nocompileua

pause