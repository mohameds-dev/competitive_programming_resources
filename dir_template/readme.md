# Code Template

## File Structure

- **`code.hpp`**: Contains ONLY the algorithm/data structure implementation (no `main()` function)
- **`main.cpp`**: Includes `code.hpp` and runs the algorithm on `input.txt`
- **`tests.cpp`**: Includes `code.hpp` and contains unit tests for the algorithm

**Why separate `code.hpp`?** By keeping the implementation separate from `main()`, both `main.cpp` and `tests.cpp` can include it without causing duplicate `main()` function errors. This allows you to run the code on input files and test it separately.

## Description

TODO: Add description of the algorithm/data structure

## Complexity

- Time: TODO
- Space: TODO

## Usage

TODO: Add usage examples

## Examples

TODO: Add examples

## References

TODO: Add references
