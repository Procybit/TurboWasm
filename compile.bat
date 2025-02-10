@echo off
setlocal enabledelayedexpansion

call emsdk\emsdk_env

echo.
echo = BEGIN COMPILATION =
echo.

for %%f in (cpp\*.c) do (
    set "NAME=%%~nf"
    call emcc "%%f" -o "wasm\!NAME!.wasm" -Os -g3 -gsource-map --source-map-base http://localhost:8000/wasm/ -sSTANDALONE_WASM=1 -sINITIAL_HEAP=256mb -sABORTING_MALLOC=0 --no-entry

    if errorlevel 1 (
        echo Failed to compile %%f
    ) else (
        echo Successfully compiled !NAME!.c to !NAME!.wasm
    )
)

echo.
echo All files have been processed.
pause