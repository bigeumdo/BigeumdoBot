pushd %~dp0

GenDiscordNameClass.exe --path=../../BotServer/Discord.xml --output=GenDiscordNameClass.h

IF ERRORLEVEL 1 PAUSE

XCOPY /Y GenDiscordNameClass.h "../../BotServer"

DEL /Q /F *.h

PAUSE