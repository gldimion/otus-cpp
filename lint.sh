#!/usr/bin/env bash
# Formats sources and runs clang-tidy for the given homework dirs (all hw* by default).
set -euo pipefail
shopt -s nullglob
cd "$(dirname "$0")"

dirs=("$@")
if [ ${#dirs[@]} -eq 0 ]; then
    dirs=(hw*/)
fi

for dir in "${dirs[@]}"; do
    dir=${dir%/}
    echo "== $dir"

    clang-format -i "$dir"/*.cpp "$dir"/*.h

    cmake -S "$dir" -B "$dir/build" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON > /dev/null
    clang-tidy -p "$dir/build" --quiet "$dir"/*.cpp 2> >(grep -vE 'warnings generated|Processing file' >&2)
done
