#! /bin/sh

echo "Building..."
g++ -o cpp_snake src/main.cpp
echo "Build finished!"

echo "Running..."
./cpp_snake 10 10
