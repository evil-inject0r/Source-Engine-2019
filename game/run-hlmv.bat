@echo off

set cmdLine=-game mod_hl2

start "" bin\win32\hlmv.exe %cmdLine%
echo bin\win32\hlmv.exe %cmdLine%

timeout 5