#!/usr/bin/env bash
cd "$(dirname "$0")" || exit 1
cmake -B build && cmake --build build && ctest --test-dir build --output-on-failure
