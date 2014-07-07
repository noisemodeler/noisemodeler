@echo off
for /f "usebackq tokens=*" %%a in (`git describe --long --tags`) do set gitstring=%%a
set dottedstring=%gitstring:-=.%
echo %dottedstring:~0,-9%
