pushd %~dp0
pyinstaller --onefile DiscordNameClassGenerator.py
MOVE .\dist\DiscordNameClassGenerator.exe .\GenDiscordNameClass.exe
@RD /S /Q .\build
@RD /S /Q .\dist
DEL /S /F /Q .\DiscordNameClassGenerator.spec
PAUSE