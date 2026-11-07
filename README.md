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

### Prerequisites & Dependencies

The repository requires the following tools:

- **C++ Compiler**: `g++` with C++17 support (part of `build-essential`)
- **TeX Live & LaTeX**: `pdflatex` with packages `listings`, `amsmath`, `geometry`, `hyperref`, `xcolor` (for compiling `reference.tex` into a PDF cheatsheet)
- **Python 3**: `python3` (for Python template codes and scripts)
- **Download Utility**: `curl`
- **Unit Testing**: Catch2 v2 single-header (`utils/catch2.hpp`)
- **Shell**: Bash (Git Bash or WSL on Windows)

---

### Installation

You can either run the automated setup script or install all dependencies manually.

#### Option 1: Run the Automated Installation Script (Recommended)

A script (`install_deps.sh`) is provided that checks which dependencies are already installed and installs only the missing ones. It automatically detects your package manager (`apt`, `pacman`, `dnf`, or `brew`) and downloads Catch2 if `utils/catch2.hpp` is missing.

> **Note:** Because this script installs system packages via your package manager, it **requires sudo** privileges.

Run the script with `sudo`:

```bash
sudo ./install_deps.sh
```

*(If you run `./install_deps.sh` without `sudo`, it will prompt for elevated privileges automatically.)*

You can also check whether all dependencies are satisfied at any time **without sudo**:

```bash
./install_deps.sh --check
```

---

#### Option 2: Install All Dependencies Manually

If you prefer to install everything yourself, run the commands for your operating system:

##### Ubuntu / Debian / Linux Mint (APT)

```bash
# 1. Install system packages and TeX Live
sudo apt update
sudo apt install -y build-essential curl python3 texlive-latex-base texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended

# 2. Download Catch2 test framework
mkdir -p utils
curl -L https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -o utils/catch2.hpp
```

##### Arch Linux / Manjaro (Pacman)

```bash
# 1. Install system packages and TeX Live
sudo pacman -S --needed base-devel curl python texlive-basic texlive-latexrecommended texlive-latexextra texlive-fontsrecommended

# 2. Download Catch2 test framework
mkdir -p utils
curl -L https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -o utils/catch2.hpp
```

##### Fedora / RHEL (DNF)

```bash
# 1. Install system packages and TeX Live
sudo dnf install -y gcc-c++ make curl python3 texlive-scheme-medium

# 2. Download Catch2 test framework
mkdir -p utils
curl -L https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -o utils/catch2.hpp
```

##### macOS (Homebrew)

```bash
# 1. Install command line tools and basictex
brew install gcc curl python
brew install --cask basictex

# 2. Download Catch2 test framework
mkdir -p utils
curl -L https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp -o utils/catch2.hpp
```

---

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

### Generating PDF Reference Cheatsheet

Compile all algorithm implementations into a single printable PDF reference document using TeX Live:

```bash
./generate_latex.sh
```

The output PDF is saved to `latex_pdf_output/reference.pdf`.

## Notes for Windows Users

If you're on Windows, you can use:

- **Git Bash** - The scripts work directly
- **WSL** - Windows Subsystem for Linux
- **PowerShell** - You may need to use `bash ./script.sh` instead of `./script.sh`
