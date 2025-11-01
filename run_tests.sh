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
    
    # Compile tests
    if g++ -std=c++17 -O2 -Wall -o "$dir/test_runner" "$test_file"; then
        # Run tests
        if [ -f "$dir/test_runner" ]; then
            cd "$dir"
            ./test_runner
            TEST_STATUS=$?
            cd ..
            rm -f "$dir/test_runner"
            
            if [ $TEST_STATUS -eq 0 ]; then
                echo "✓ Tests passed for $dir"
                return 0
            else
                echo "✗ Tests failed for $dir"
                return 1
            fi
        fi
    else
        echo "✗ Compilation failed for $dir"
        return 1
    fi
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
    # Run tests for all directories (except template)
    echo "Running tests for all directories..."
    echo ""
    
    FAILED_DIRS=()
    PASSED_COUNT=0
    TOTAL_COUNT=0
    
    for dir in */; do
        dir=${dir%/}
        
        # Skip template directory
        if [ "$dir" = "template" ]; then
            continue
        fi
        
        # Skip if not a directory or doesn't have tests.cpp
        if [ ! -d "$dir" ] || [ ! -f "$dir/tests.cpp" ]; then
            continue
        fi
        
        TOTAL_COUNT=$((TOTAL_COUNT + 1))
        
        if compile_and_run_test "$dir"; then
            PASSED_COUNT=$((PASSED_COUNT + 1))
        else
            FAILED_DIRS+=("$dir")
        fi
        
        echo ""
    done
    
    # Summary
    echo "========================================="
    echo "Test Summary"
    echo "========================================="
    echo "Total directories tested: $TOTAL_COUNT"
    echo "Passed: $PASSED_COUNT"
    echo "Failed: ${#FAILED_DIRS[@]}"
    
    if [ ${#FAILED_DIRS[@]} -gt 0 ]; then
        echo ""
        echo "Failed directories:"
        for dir in "${FAILED_DIRS[@]}"; do
            echo "  - $dir"
        done
        exit 1
    else
        echo ""
        echo "All tests passed! ✓"
        exit 0
    fi
fi

