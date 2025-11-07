# competitive_programming_resources

This is a repo for the competitive programming codes and resources.

## Project Structure

Each algorithm/data structure has its own directory with:

- `code.hpp` - Contains ONLY the algorithm/data structure implementation (no `main()` function)
- `main.cpp` - Includes `code.hpp` and runs the algorithm on `input.txt`
- `tests.cpp` - Includes `code.hpp` and contains unit tests using Catch2
- `input.txt` - Sample input file
- `readme.md` - Documentation for the algorithm/data structure

**Why separate `code.hpp`?** By keeping the implementation separate from `main()`, both `main.cpp` and `tests.cpp` can include it without causing duplicate `main()` function errors. This allows you to run the code on input files and test it separately.

## Usage

### Prerequisites

- C++ compiler with C++17 support (g++)
- Bash shell (Git Bash or WSL on Windows)

### Setup

#### Download Catch2

Tests use Catch2 for unit testing. Download the single-header version:

```bash
curl -L https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -o utils/catch2.hpp
```

Or download manually from [Catch2 releases](https://github.com/catchorg/Catch2/releases) and place it in `utils/catch2.hpp`.

### Creating a New Directory

To create a new directory from the dir_template:

```bash
./create_new_dir.sh directory_name
```

Example:

```bash
./create_new_dir.sh segment_tree
./create_new_dir.sh dijkstra
./create_new_dir.sh sparse_table
```

This will:

- Create a new directory with the dir_template structure
- Replace "Code Template" in readme.md with the formatted directory name

### Running Tests

Run tests for a specific directory:

```bash
./tests_run.sh directory_name
```

Run all tests:

```bash
./tests_run.sh
```

**Note:** The test script uses incremental compilation - it only recompiles if source files have changed, making subsequent test runs very fast.

### Running Code

Run the main code with input.txt:

```bash
./code_run.sh directory_name
```

Example:

```bash
./code_run.sh segment_tree
```

## Notes for Windows Users

If you're on Windows, you can use:

- **Git Bash** - The scripts work directly
- **WSL** - Windows Subsystem for Linux
- **PowerShell** - You may need to use `bash ./script.sh` instead of `./script.sh`
