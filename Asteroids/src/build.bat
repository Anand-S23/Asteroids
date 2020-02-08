@echo off

:: if not exist ..\..\build mkdir ..\..\build
:: pushd ..\..\build
:: cl -Zi ..\Astriods\src\main.c /I C:\Dev\include /link /LIBPATH:C:\Dev\lib SDL2.lib SDL2main.lib SDL2_image.lib /SUBSYSTEM:CONSOLE
:: cl -Zi ..\Astriods\src\main.c SDL2.lib SDL2main.lib SDL2_image.lib
:: popd


:: SETLOCAL

set DIRECT=..\Astriods\src
set TARGET=x64

:: SDL2 libraries and include paths 
set SDL2_LIB=..\SDL2
set SDL2_IMG=..\SDL2_image

set SDL2_LIBDIR=%SDL2_LIB%\lib\%TARGET%
set SDL2_IMGDIR=%SDL2_IMG%\lib\%TARGET%
set SDL2_LIBINC=%SDL2_LIB%\include
set SDL2_IMGINC=%SDL2_IMG%\include

if not exist ..\..\build mkdir ..\..\build
pushd ..\..\build

robocopy %SDL2_LIBDIR% . *.dll
robocopy %SDL2_IMGDIR% . *.dll

cl -Zi -FC -MD %DIRECT%\main.c %DIRECT%\initalize.c %DIRECT%\render.c %DIRECT%\input.c -I%SDL2_LIBINC% -I%SDL2_IMGINC% %SDL2_LIBDIR%\SDL2.lib %SDL2_LIBDIR%\SDL2main.lib %SDL2_IMGDIR%\SDL2_image.lib -link /machine:%TARGET% -subsystem:CONSOLE
popd
