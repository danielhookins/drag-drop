@echo off

if not exist build mkdir build
cd build

cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release

copy ..\lib\SDL2-VC\lib\x64\SDL2.dll .

cd ..
