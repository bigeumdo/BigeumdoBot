pushd %~dp0

GenProcedures.exe --path=../../BotServer/DB.xml --output=GenProcedures.h

IF ERRORLEVEL 1 PAUSE

XCOPY /Y GenProcedures.h "../../BotServer"

DEL /Q /F *.h

PAUSE