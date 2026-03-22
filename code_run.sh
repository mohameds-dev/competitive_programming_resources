#!/bin/bash

# Script to run code with input.txt
# Usage: ./run_code.sh directory_name

if [ $# -eq 0 ]; then
    echo "Error: Directory name required"
    echo "Usage: ./run_code.sh directory_name"
    exit 1
fi

DIR_NAME="$1"
MAIN_FILE="$DIR_NAME/main.cpp"
INPUT_FILE="$DIR_NAME/input.txt"

if [ ! -d "$DIR_NAME" ]; then
    echo "Error: Directory '$DIR_NAME' not found"
    exit 1
fi

if [ ! -f "$MAIN_FILE" ]; then
    echo "Error: main.cpp not found in '$DIR_NAME'"
    exit 1
fi

if [ ! -f "$INPUT_FILE" ]; then
    echo "Warning: input.txt not found in '$DIR_NAME'"
    echo "Running without input file..."
    INPUT_FILE="/dev/null"
fi

echo "Compiling $DIR_NAME/main.cpp..."
if g++ -std=c++17 -O2 -Wall -o "$DIR_NAME/runner" "$MAIN_FILE"; then
    echo "Running $DIR_NAME/main.cpp..."
    cd "$DIR_NAME"
    if [ -f input.txt ]; then
        ./runner < input.txt
    else
        ./runner
    fi
    cd ..
    rm -f "$DIR_NAME/runner"
else
    echo "Error: Compilation failed"
    exit 1
fi

