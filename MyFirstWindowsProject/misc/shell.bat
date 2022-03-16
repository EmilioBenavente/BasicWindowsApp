@echo off
rem call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
set path=m:\MyFirstWindowsProject\misc\;%path%

"z:\bin\emacs.exe" -q -l "m:\MyFirstWindowsProject\misc\.emacs
