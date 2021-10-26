#!/usr/bin/env bash
set -o errexit
mkdir -p build
cd build
cmake ../ -DCMAKE_BUILD_TYPE=RELEASE
make
cd ..
rm -f libyara_elixir.so
ln -s build/libyara_elixir.so
mix test --trace
