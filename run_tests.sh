#!/bin/bash

# Script to run tests
# Usage: ./run_tests.sh [directory_name]
#   If directory_name is provided, runs tests for that directory only
#   If not provided, runs tests for all directories

compile_and_run_test() {
    local dir="$1"
    local test_file="$dir/tests.cpp"
    
    if [ ! -f "$test_file" ]; then
        echo "Warning: No tests.cpp found in $dir"
        return 1
    fi
    
    echo "========================================="
    echo "Running tests for: $dir"
    echo "========================================="
    
    # Compile tests - errors will be shown automatically
    if ! g++ -std=c++17 -O2 -Wall -o "$dir/test_runner" "$test_file" 2>&1; then
        return 1
    fi
    
    # Run tests - output will show any errors
    if [ -f "$dir/test_runner" ]; then
        cd "$dir"
        ./test_runner
        cd ..
        rm -f "$dir/test_runner"
    fi
    
    return 0
}

if [ $# -eq 1 ]; then
    # Run tests for specific directory
    DIR_NAME="$1"
    
    if [ ! -d "$DIR_NAME" ]; then
        echo "Error: Directory '$DIR_NAME' not found"
        exit 1
    fi
    
    if compile_and_run_test "$DIR_NAME"; then
        exit 0
    else
        exit 1
    fi
else
    # Run tests for all directories
    echo "Running tests for all directories..."
    echo ""
    
    ERROR_DIRS=()
    
    for dir in */; do
        dir=${dir%/}
        
        # Skip if not a directory or doesn't have tests.cpp
        if [ ! -d "$dir" ] || [ ! -f "$dir/tests.cpp" ]; then
            continue
        fi
        
        if ! compile_and_run_test "$dir"; then
            ERROR_DIRS+=("$dir")
        fi
        
        echo ""
    done
    
    # Summary
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

