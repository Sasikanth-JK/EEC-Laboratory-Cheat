@echo off
setlocal enabledelayedexpansion

REM =====================================================================
REM  ANSI Color Setup for Windows 10/11
REM =====================================================================
for /F "delims=#" %%E in ('"prompt #$E# & for %%E in (1) do rem"') do set "ESC=%%E"
set "cTITLE=%ESC%[96m"    & REM Cyan
set "cSUCCESS=%ESC%[92m"  & REM Green
set "cWARN=%ESC%[93m"     & REM Yellow
set "cERROR=%ESC%[91m"    & REM Red
set "cPROMPT=%ESC%[95m"   & REM Magenta
set "cRESET=%ESC%[0m"     & REM Reset

REM =====================================================================
REM  EDIT THIS if your Turbo C BIN folder is somewhere else.
REM =====================================================================
set "MANUAL_DEFAULT=C:\TURBOC3\BIN"

REM ---- Use manual default if it exists, otherwise auto-detect common locations ----
set "DEFAULT_DEST="
if exist "%MANUAL_DEFAULT%" set "DEFAULT_DEST=%MANUAL_DEFAULT%"
if "!DEFAULT_DEST!"=="" if exist "C:\TURBOC3\BIN" set "DEFAULT_DEST=C:\TURBOC3\BIN"
if "!DEFAULT_DEST!"=="" if exist "C:\TC\BIN" set "DEFAULT_DEST=C:\TC\BIN"
if "!DEFAULT_DEST!"=="" if exist "C:\TURBOC\BIN" set "DEFAULT_DEST=C:\TURBOC\BIN"
if "!DEFAULT_DEST!"=="" if exist "D:\TURBOC3\BIN" set "DEFAULT_DEST=D:\TURBOC3\BIN"
if "!DEFAULT_DEST!"=="" if exist "D:\TC\BIN" set "DEFAULT_DEST=D:\TC\BIN"
if "!DEFAULT_DEST!"=="" set "DEFAULT_DEST=%MANUAL_DEFAULT%"

cls
echo %cTITLE%===================================================%cRESET%
echo %cTITLE%             Lab Program File Deployer             %cRESET%
echo %cTITLE%===================================================%cRESET%
echo.
echo %cWARN%Available Subjects:%cRESET%
echo.

set count=0
for /d %%D in (*) do (
    set /a count+=1
    set "folder!count!=%%D"
    echo   !count!. %%D
)

if %count%==0 (
    echo %cERROR%[!] No subject folders found in this directory.%cRESET%
    echo.
    pause
    exit /b
)

echo.
set /p subChoice="%cPROMPT%Enter the number of the subject to select:%cRESET% "

set "selectedFolder=!folder%subChoice%!"

if "!selectedFolder!"=="" (
    echo.
    echo %cERROR%[!] Invalid selection. Please run the script again.%cRESET%
    echo.
    pause
    exit /b
)

echo.
echo %cSUCCESS%[*] Selected Subject: !selectedFolder!%cRESET%
echo.

if "!DEFAULT_DEST!"=="" (
    echo %cWARN%Could not auto-detect a Turbo C BIN folder on this system.%cRESET%
    set /p destInput="%cPROMPT%Enter the FULL destination folder path:%cRESET% "
) else (
    echo Enter destination folder path.
    echo Enter %cTITLE%0%cRESET% to use the detected default: %cTITLE%!DEFAULT_DEST!%cRESET%
    set /p destInput="%cPROMPT%Destination [0 for default]:%cRESET% "
)

if "!destInput!"=="0" (
    if "!DEFAULT_DEST!"=="" (
        echo.
        echo %cERROR%[!] No default available. Please re-run and type a full path.%cRESET%
        echo.
        pause
        exit /b
    )
    set "destFolder=!DEFAULT_DEST!"
) else (
    set "destFolder=!destInput!"
)

if not exist "!destFolder!" (
    echo.
    echo %cWARN%Destination folder "!destFolder!" does not exist. Creating it...%cRESET%
    mkdir "!destFolder!"
)

echo.
echo %cWARN%Moving files from "!selectedFolder!" to "!destFolder!" ...%cRESET%

REM Check if the folder is empty before moving
dir /A-D /B "!selectedFolder!" >nul 2>&1
if errorlevel 1 (
    echo.
    echo %cERROR%[!] No files found in "!selectedFolder!". Nothing to move.%cRESET%
) else (
    move /Y "!selectedFolder!\*.*" "!destFolder!\" >nul
    echo.
    echo %cSUCCESS%[✓] Done. All files from "!selectedFolder!" have been deployed to "!destFolder!".%cRESET%
)

echo.
pause
