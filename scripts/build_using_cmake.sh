#!/bin/bash

mkdir build
cd build
cmake -G Ninja ..
ninja

echo -en "\e[32m✅ Built the project using CMake successfully.\e[0m\n"

exit $RESULT
