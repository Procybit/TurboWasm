@echo off
setlocal enabledelayedexpansion

call emsdk\emsdk_env

echo.
echo = BEGIN COMPILATION =
echo.

REM Loop through all .cpp files in the current directory
for %%f in (cpp\*.cpp) do (
    REM Extract the base name without the .cpp extension
    set "NAME=%%~nf"

    REM Compile the .cpp file to .wasm using em++
    call em++ "%%f" -o "wasm\!NAME!.wasm" -sSTANDALONE_WASM=1 -sINITIAL_HEAP=1gb -sABORTING_MALLOC=0 --no-entry -O3
    
    REM Check if the compilation was successful
    if errorlevel 1 (
        echo Failed to compile %%f
    ) else (
        echo Successfully compiled !NAME!.cpp to !NAME!.wasm
    )
)

echo.
echo All files have been processed.
pause