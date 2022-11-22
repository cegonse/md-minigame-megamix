ECHO off

IF DEFINED SGDK_PATH (
    ECHO Using %SGDK_PATH% as SGDK path
) ELSE (
    ECHO SGDK_PATH environment variable must be defined
    EXIT /B 0
)

SET "GDK_WIN=%SGDK_PATH%"
SET "XGCC_WIN=%GDK_WIN%\x68k-gcc\bin"
SET "PATH=%GDK_WIN%\bin;%XGCC_WIN%;%PATH%"

%GDK_WIN%\bin\make -C . release -f %GDK_WIN%\makefile.gen

ECHO BUILD COMPLETED!

IF DEFINED MD_EMULATOR_PATH (
    ECHO Launching rom in %MD_EMULATOR_PATH%
     %MD_EMULATOR_PATH% .\out\rom.bin
)

exit /B 0