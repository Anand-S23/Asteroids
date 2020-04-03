@echo off

set DIRECT=..\Astriods\src
set TARGET=x64

:: SDL2 libraries and include paths 
set SDL2_LIB=..\SDL2
set SDL2_IMG=..\SDL2_image
set SDL2_MIX=..\SDL2_mixer
set SDL2_TTF=..\SDL2_ttf

set SDL2_LIBDIR=%SDL2_LIB%\lib\%TARGET%
set SDL2_IMGDIR=%SDL2_IMG%\lib\%TARGET%
set SDL2_MIXDIR=%SDL2_MIX%\lib\%TARGET%
set SDL2_TTFDIR=%SDL2_TTF%\lib\%TARGET%
set SDL2_LIBINC=%SDL2_LIB%\include
set SDL2_IMGINC=%SDL2_IMG%\include
set SDL2_MIXINC=%SDL2_MIX%\include
set SDL2_TTFINC=%SDL2_TTF%\include


if not exist ..\..\build mkdir ..\..\build
pushd ..\..\build

robocopy %SDL2_LIBDIR% . *.dll
robocopy %SDL2_IMGDIR% . *.dll
robocopy %SDL2_MIXDIR% . *.dll
robocopy %SDL2_TTFDIR% . *.dll

set FILES=%DIRECT%\main.c %DIRECT%\initalize.c %DIRECT%\render.c %DIRECT%\input.c %DIRECT%\asteroid.c %DIRECT%\math.c
set INC=-I%SDL2_LIBINC% -I%SDL2_IMGINC% -I%SDL2_MIXINC% -I%SDL2_TTFINC%
set DIR=%SDL2_LIBDIR%\SDL2.lib %SDL2_LIBDIR%\SDL2main.lib %SDL2_IMGDIR%\SDL2_image.lib  %SDL2_MIXDIR%\SDL2_mixer.lib  %SDL2_TTFDIR%\SDL2_ttf.lib

cl -Zi -FC -MD %FILES% %INC% %DIR% -link /machine:%TARGET% -subsystem:CONSOLE
popd
