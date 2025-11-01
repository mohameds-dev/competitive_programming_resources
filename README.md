# competitive_programming_resources
This is a repo for the competitive programming codes and resources.

## Project Structure

Each algorithm/data structure has its own directory with:
- `main.cpp` - The main implementation
- `tests.cpp` - Unit tests for the implementation
- `input.txt` - Sample input file
- `readme.md` - Documentation for the algorithm/data structure

## Usage

### Prerequisites
- C++ compiler with C++17 support (g++)
- Bash shell (Git Bash or WSL on Windows)

### Creating a New Directory

To create a new directory from the template:
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
- Create a new directory with the template structure
- Replace "Code Template" in readme.md with the formatted directory name

### Running Tests

Run tests for a specific directory:
```bash
./run_tests.sh directory_name
```

Run all tests:
```bash
./run_tests.sh
```

### Running Code

Run the main code with input.txt:
```bash
./run_code.sh directory_name
```

Example:
```bash
./run_code.sh segment_tree
```

## Notes for Windows Users

If you're on Windows, you can use:
- **Git Bash** - The scripts work directly
- **WSL** - Windows Subsystem for Linux
- **PowerShell** - You may need to use `bash ./script.sh` instead of `./script.sh`