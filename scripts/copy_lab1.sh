#!/usr/bin/env bash
# copy_lab1.sh — Copy your Lab 1 source files into this Lab 2.1 workspace.
#
# Usage: bash scripts/copy_lab1.sh <path-to-your-lab1-repo>
set -euo pipefail

LAB1_PATH="${1:-}"

if [[ -z "$LAB1_PATH" ]]; then
    echo "Usage: bash scripts/copy_lab1.sh <path-to-lab1-repo>"
    echo ""
    echo "  Example: bash scripts/copy_lab1.sh ../lab1-bare-metal-gpio-myuser"
    exit 1
fi

if [[ ! -d "$LAB1_PATH" ]]; then
    echo "ERROR: '$LAB1_PATH' is not a directory."
    exit 1
fi

if [[ ! -d "$LAB1_PATH/src" || ! -d "$LAB1_PATH/inc" ]]; then
    echo "ERROR: '$LAB1_PATH' does not look like a Lab 1 repo (missing src/ or inc/)."
    exit 1
fi

echo "Copying from $LAB1_PATH ..."
cp "$LAB1_PATH/src/main.c"  src/main.c
cp "$LAB1_PATH/src/gpio.c"  src/gpio.c
cp "$LAB1_PATH/inc/board.h" inc/board.h
cp "$LAB1_PATH/inc/rcc.h"   inc/rcc.h

echo "Done. Files copied:"
echo "  src/main.c   src/gpio.c"
echo "  inc/board.h  inc/rcc.h"
echo ""
echo "Your Lab 1 solution is now in place. Run 'make all' to verify it builds."
