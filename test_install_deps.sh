#!/bin/bash
set -euo pipefail

SCRIPT_UNDER_TEST="./install_deps.sh"

echo "=== Running install_deps.sh tests ==="

# Test 1: File existence and executability
echo -n "Test 1: install_deps.sh exists and is executable... "
if [ ! -f "$SCRIPT_UNDER_TEST" ]; then
    echo "FAILED (file does not exist)"
    exit 1
fi
if [ ! -x "$SCRIPT_UNDER_TEST" ]; then
    echo "FAILED (file is not executable)"
    exit 1
fi
echo "PASSED"

# Test 2: Bash syntax check
echo -n "Test 2: Syntax check (bash -n)... "
if ! bash -n "$SCRIPT_UNDER_TEST"; then
    echo "FAILED (syntax errors found)"
    exit 1
fi
echo "PASSED"

# Test 3: Help flag works without sudo
echo -n "Test 3: --help flag exits cleanly... "
help_output=$("$SCRIPT_UNDER_TEST" --help 2>&1)
if [[ "$help_output" != *"Usage"* ]]; then
    echo "FAILED (missing Usage in output)"
    exit 1
fi
echo "PASSED"

# Test 4: -h short flag works
echo -n "Test 4: -h flag exits cleanly... "
help_output_short=$("$SCRIPT_UNDER_TEST" -h 2>&1)
if [[ "$help_output_short" != *"Usage"* ]]; then
    echo "FAILED (missing Usage in output)"
    exit 1
fi
echo "PASSED"

# Test 5: Unknown option triggers error and usage
echo -n "Test 5: Unknown flag exits with error... "
set +e
unknown_output=$("$SCRIPT_UNDER_TEST" --invalid-option 2>&1)
exit_code=$?
set -e
if [ $exit_code -eq 0 ] || [[ "$unknown_output" != *"Unknown option"* ]]; then
    echo "FAILED (expected non-zero exit and error message)"
    exit 1
fi
echo "PASSED"

# Test 6: --check flag checks dependencies without sudo
echo -n "Test 6: --check flag reports dependency status... "
check_output=$("$SCRIPT_UNDER_TEST" --check 2>&1)
if [[ "$check_output" != *"Checking"* ]] || [[ "$check_output" != *"All dependencies are satisfied"* ]]; then
    echo "FAILED (expected checking message and all satisfied)"
    exit 1
fi
echo "PASSED"

# Test 7: Package manager detection returns apt on this OS
echo -n "Test 7: detect_package_manager identifies apt... "
# Source only the detect function
eval "$(sed -n '/^detect_package_manager()/,/^}/p' "$SCRIPT_UNDER_TEST")"
detected_pkg=$(detect_package_manager)
if [ "$detected_pkg" != "apt" ]; then
    echo "FAILED (expected apt, got $detected_pkg)"
    exit 1
fi
echo "PASSED"

# Test 8: Catch2 installation logic when header is missing
echo -n "Test 8: Catch2 header download verification... "
GREEN="" YELLOW="" RED="" RESET=""
eval "$(sed -n '/^install_catch2_if_missing()/,/^}/p' "$SCRIPT_UNDER_TEST")"
TMP_DIR=$(mktemp -d)
SCRIPT_DIR="$TMP_DIR"
CATCH2_URL="https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp"
CATCH2_DEST="$TMP_DIR/utils/catch2.hpp"
# Verify initially missing
if [ -f "$CATCH2_DEST" ]; then
    echo "FAILED (file unexpectedly exists in temp dir)"
    rm -rf "$TMP_DIR"
    exit 1
fi
# Run install_catch2_if_missing
install_catch2_if_missing >/dev/null 2>&1
if [ ! -f "$CATCH2_DEST" ] || [ ! -s "$CATCH2_DEST" ]; then
    echo "FAILED (failed to download Catch2 header)"
    rm -rf "$TMP_DIR"
    exit 1
fi
rm -rf "$TMP_DIR"
echo "PASSED"

echo "=== All tests in test_install_deps.sh passed! ==="
