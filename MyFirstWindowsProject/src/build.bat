@echo off

set CommonCompilerFlags=-nologo -Zi

set CommonLinkerFlags=-opt:ref user32.lib gdi32.lib winmm.lib Ole32.lib

REM TODO - can we just build both with one exe?

IF NOT EXIST ..\..\build mkdir ..\..\build
pushd ..\..\build

REM 32-bit Build
rem cl  %CommonCompilerFlags% ..\MyFirstWindowsProject\src\Win32_MainAppWindow.cpp /link -subsystem:windows,5.1 %CommonLinkerFlags%

REM 64-bit Build
cl  %CommonCompilerFlags% ..\MyFirstWindowsProject\src\Win32_MainAppWindow.cpp /link %CommonLinkerFlags%
popd

