@echo off

:: IMPOSTAZIONE MOD DA SCARICARE

SET MOD_CODE="450814997"
SET MOD_NAME="cba_a3"

:: CONFIGURAZIONE CARTELLE

SET STEAMLOGIN=xyz abc
SET ServerPath="C:\GAME_SERVER\arma3server"
SET STEAMPATH="C:\GAME_SERVER\steamcmd"
SET steamcmdmodpath="C:\GAME_SERVER\steamcmd\steamapps\workshop\content\107410"

::-----------------------------------
:: NON MODIFICARE MAI DA QUA IN GIU'
::-----------------------------------

set Mods[0]=%MOD_CODE%

:: AVVIO DELLO SCRIPT

echo Questo script installa la mod %MOD_NAME% per Arma3 sul server
echo.
echo Author: {9GU}UncleBob
echo Mod Dir: %STEAMPATH%
echo 
echo.
echo     Key "ENTER" to procede
pause

:: Folder Mods => SteamCMD\steamapps\workshop\content\107410

set "x=0"

:SymLoop
if defined Mods[%x%] (
	call set list=%list% +"workshop_download_item 107410 %%Mods[%x%]%%" validate
    set /a "x+=1"
    GOTO :SymLoop
)
echo.
%STEAMPATH%\steamcmd.exe +login %STEAMLOGIN% %list% +quit

:: IMPOSTAZIONE DEL SIMLINK PER LA MOD

::0-0
MKLINK /J "%ServerPath%\keys" "%steamcmdmodpath%\keys"
::0
MKLINK /J "%ServerPath%\@%MOD_NAME%" "%steamcmdmodpath%\%MOD_CODE%"

robocopy %steamcmdmodpath% *.bikey %steamcmdmodpath%\keys\ *.pdf /S /R:1 /W:1 /NDL /XJD /XD OutputFolder /L

:: TERMINE

echo.
echo     La mod %MOD_NAME% aggiornata
echo     premi "ENTER" per chiudere
pause
