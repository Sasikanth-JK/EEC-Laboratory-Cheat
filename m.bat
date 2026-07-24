@echo off
setlocal enabledelayedexpansion

REM =====================================================================
REM  EDIT THIS if your Turbo C BIN folder is somewhere else.
REM  Leave as-is to let the script auto-detect common install locations.
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

echo ============================================
echo   Lab Program File Deployer
echo ============================================
echo.
echo Available Subjects:
echo.

set count=0
for /d %%D in (*) do (
    set /a count+=1
    set "folder!count!=%%D"
    echo   !count!. %%D
)

if %count%==0 (
    echo No subject folders found in this directory.
    pause
    exit /b
)

echo.
set /p subChoice=Enter the number of the subject to select: 

set "selectedFolder=!folder%subChoice%!"

if "!selectedFolder!"=="" (
    echo Invalid selection.
    pause
    exit /b
)

echo.
echo Selected Subject: !selectedFolder!
echo.

if "!DEFAULT_DEST!"=="" (
    echo Could not auto-detect a Turbo C BIN folder on this system.
    set /p destInput=Enter the FULL destination folder path: 
) else (
    echo Enter destination folder path.
    echo Enter 0 to use the detected default: !DEFAULT_DEST!
    set /p destInput=Destination [0 for default]: 
)

if "!destInput!"=="0" (
    if "!DEFAULT_DEST!"=="" (
        echo No default available. Please re-run and type a full path.
        pause
        exit /b
    )
    set "destFolder=!DEFAULT_DEST!"
) else (
    set "destFolder=!destInput!"
)

if not exist "!destFolder!" (
    echo Destination folder "!destFolder!" does not exist. Creating it...
    mkdir "!destFolder!"
)

echo.
echo Moving files from "!selectedFolder!" to "!destFolder!" ...
move /Y "!selectedFolder!\*.*" "!destFolder!\" >nul

echo.
echo Done. All files from "!selectedFolder!" have been moved to "!destFolder!".
pause
