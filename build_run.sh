#! /bin/sh

echo "Building..."
make all
echo "Build finished!"

echo "Running..."
./cpp_snake 10 10
