@echo off
rem call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
set path=m:\MyFirstWindowsProject\misc\;%path%

"C:\Users\thesp\Desktop\emacs-27.2-x86_64\bin\emacs-27.2.exe" -q -l "m:\MyFirstWindowsProject\misc\.emacs
