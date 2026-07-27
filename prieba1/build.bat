@echo off
cd /d "%~dp0"
gcc -Wall -Wextra -std=c99 -o terminal.exe pruena.c terminal.c destinos.c viajes.c
if errorlevel 1 (
    echo Error al compilar.
    pause
) else (
    echo Compilacion exitosa.
    echo Ejecutando programa...
    terminal.exe
)
