#!/bin/bash

# Script to compile and run Catch2 tests
# Usage: ./run_tests.sh [directory_name]
#   - If directory_name is provided, runs tests for that directory only
#   - If not provided, runs tests for all directories

compile_and_run_test() {
    local dir="$1"
    local test_file="$dir/tests.cpp"
    local binary="$dir/test_runner"
    local code_file="$dir/code.cpp"
    local catch2_file="utils/catch2.hpp"

    if [ ! -f "$test_file" ]; then
        echo "Warning: No tests.cpp found in $dir"
        return 1
    fi

    echo "========================================="
    echo "Running tests for: $dir"
    echo "========================================="

    # Determine if compilation is needed
    local needs_compile=true
    if [ -f "$binary" ]; then
        needs_compile=false
        # Recompile if any relevant file is newer than binary
        if [ "$test_file" -nt "$binary" ]; then needs_compile=true; fi
        if [ -f "$code_file" ] && [ "$code_file" -nt "$binary" ]; then needs_compile=true; fi
        if [ -f "$catch2_file" ] && [ "$catch2_file" -nt "$binary" ]; then needs_compile=true; fi
    fi

    if [ "$needs_compile" = true ]; then
        # Compile tests with Catch2
        if ! g++ -std=c++17 -O0 -Wall -o "$binary" "$test_file" 2>&1; then
            rm -f "$binary"
            return 1
        fi
    fi

    # Run the test binary
    if [ -f "$binary" ]; then
        (cd "$dir" && ./test_runner)
    fi

    return 0
}

# --------------------------------------------------
# Main
# --------------------------------------------------
if [ $# -eq 1 ]; then
    DIR_NAME="$1"
    if [ ! -d "$DIR_NAME" ]; then
        echo "Error: Directory '$DIR_NAME' not found"
        exit 1
    fi
    compile_and_run_test "$DIR_NAME"
    exit $?
else
    echo "Running tests for all directories..."
    echo ""
    ERROR_DIRS=()

    for dir in */; do
        dir=${dir%/}
        if [ ! -d "$dir" ] || [ ! -f "$dir/tests.cpp" ]; then
            continue
        fi
        if ! compile_and_run_test "$dir"; then
            ERROR_DIRS+=("$dir")
        fi
        echo ""
    done

    # Summary of errors
    if [ ${#ERROR_DIRS[@]} -gt 0 ]; then
        echo "========================================="
        echo "Directories with errors:"
        echo "========================================="
        for dir in "${ERROR_DIRS[@]}"; do
            echo "  - $dir"
        done
        exit 1
    fi
fi
