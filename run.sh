#!/usr/bin/env bash
set -e

CC=clang cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
./build/assembler ./Prog.asm
