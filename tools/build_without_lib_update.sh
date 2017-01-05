#!/usr/bin/env bash

set -e
script=$(readlink -f "$0")
route=$(dirname "$script")

which cmake >/dev/null 2>&1 || { echo "build requires cmake but nothing is found"; exit 1; }

if [ -d "$route"/../build ]; then
    rm -rf "$route"/../build
fi

mkdir -p "$route"/../build || exit 2
cd "$route"/../build
cmake .. -G "Unix Makefiles"
make -j1
