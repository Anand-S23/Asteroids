#!/bin/bash

code="$PWD"
opts=-g
cd build > /dev/null
g++ $opts $code/x64 -o main.exe
cd $code > /dev/null
