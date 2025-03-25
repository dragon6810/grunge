#!/usr/bin/env bash

mkdir -p build
cd build
emcmake cmake ..
if cmake --build .; then
cp grunge.js ../grunge.js
cp grunge.wasm ../grunge.wasm
cp grunge.html ../grunge.html
fi