ECHO off

CALL bin\build.bat

IF DEFINED MD_EMULATOR_PATH (
    ECHO Launching rom in %MD_EMULATOR_PATH%
     %MD_EMULATOR_PATH% .\out\rom.bin
)
ELSE (
    ECHO "Define MD_EMULATOR_PATH environment variable to launch the emulator"
)

exit /B 0