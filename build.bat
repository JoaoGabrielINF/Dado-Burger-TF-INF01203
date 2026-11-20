@echo off
rem ****************************************************************************
rem  Compila o Dado Burger usando a toolchain portatil de tools\w64devkit.
rem  Equivale a rodar "make" com o gcc/make do projeto no PATH.
rem ****************************************************************************
setlocal
cd /d "%~dp0"

if not exist tools\w64devkit\bin\gcc.exe (
    echo Toolchain nao encontrada. Rode tools\setup_tools.bat primeiro.
    exit /b 1
)

set "PATH=%cd%\tools\w64devkit\bin;%PATH%"
make %*
exit /b %errorlevel%
