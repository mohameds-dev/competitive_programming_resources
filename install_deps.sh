#!/usr/bin/env bash
#
# install_deps.sh
#
# Script to install all dependencies for competitive_programming_resources:
# - C++ compiler (g++ with C++17 support)
# - TeX Live & LaTeX packages (pdflatex, listings, amsmath, hyperref, etc.)
# - Python 3
# - curl
# - Catch2 v2 single-header test framework (utils/catch2.hpp)
#
# Usage:
#   sudo ./install_deps.sh       # Installs missing system dependencies
#   ./install_deps.sh --check    # Checks whether dependencies exist (no sudo needed)
#   ./install_deps.sh --help     # Shows help

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
CATCH2_URL="https://github.com/catchorg/Catch2/releases/download/v2.13.10/catch.hpp"
CATCH2_DEST="$SCRIPT_DIR/utils/catch2.hpp"

# Colors for terminal output
BOLD="\033[1m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"
RED="\033[0;31m"
BLUE="\033[0;34m"
RESET="\033[0m"

print_usage() {
    cat <<EOF
Usage: sudo ./install_deps.sh [OPTIONS]

Installs all prerequisites for the competitive_programming_resources repository:
  - C++ compiler with C++17 support (g++)
  - TeX Live / pdflatex and LaTeX packages (listings, amsmath, etc.)
  - Python 3
  - curl
  - Catch2 header (utils/catch2.hpp)

Options:
  --check       Check whether all dependencies are installed without installing
  -h, --help    Show this help message and exit

Examples:
  sudo ./install_deps.sh       # Install any missing dependencies
  ./install_deps.sh --check    # Check current status of dependencies
EOF
}

check_binary() {
    local cmd="$1"
    command -v "$cmd" >/dev/null 2>&1
}

check_latex_package() {
    local pkg="$1"
    if command -v kpsewhich >/dev/null 2>&1; then
        kpsewhich "$pkg" >/dev/null 2>&1
    else
        return 1
    fi
}

run_check_only() {
    echo -e "${BOLD}${BLUE}==> Checking competitive_programming_resources dependencies...${RESET}\n"
    local all_ok=true

    # 1. C++ compiler
    echo -n "Checking C++ compiler (g++): "
    if check_binary g++; then
        local gxx_ver
        gxx_ver=$(g++ --version | head -n1)
        echo -e "${GREEN}[OK]${RESET} ($gxx_ver)"
    else
        echo -e "${RED}[MISSING]${RESET}"
        all_ok=false
    fi

    # 2. Python 3
    echo -n "Checking Python 3 (python3): "
    if check_binary python3; then
        local py_ver
        py_ver=$(python3 --version 2>&1)
        echo -e "${GREEN}[OK]${RESET} ($py_ver)"
    else
        echo -e "${RED}[MISSING]${RESET}"
        all_ok=false
    fi

    # 3. curl
    echo -n "Checking curl: "
    if check_binary curl; then
        local curl_ver
        curl_ver=$(curl --version | head -n1)
        echo -e "${GREEN}[OK]${RESET} ($curl_ver)"
    else
        echo -e "${RED}[MISSING]${RESET}"
        all_ok=false
    fi

    # 4. TeX Live / pdflatex
    echo -n "Checking pdflatex: "
    if check_binary pdflatex; then
        local pdf_ver
        pdf_ver=$(pdflatex --version | head -n1)
        echo -e "${GREEN}[OK]${RESET} ($pdf_ver)"
    else
        echo -e "${RED}[MISSING]${RESET}"
        all_ok=false
    fi

    # 5. LaTeX listings package
    echo -n "Checking LaTeX listings package (listings.sty): "
    if check_latex_package listings.sty; then
        echo -e "${GREEN}[OK]${RESET}"
    else
        echo -e "${RED}[MISSING]${RESET}"
        all_ok=false
    fi

    # 6. Catch2 header
    echo -n "Checking Catch2 header ($CATCH2_DEST): "
    if [ -f "$CATCH2_DEST" ]; then
        echo -e "${GREEN}[OK]${RESET}"
    else
        echo -e "${RED}[MISSING]${RESET}"
        all_ok=false
    fi

    echo ""
    if [ "$all_ok" = true ]; then
        echo -e "${GREEN}${BOLD}All dependencies are satisfied!${RESET}"
        return 0
    else
        echo -e "${YELLOW}${BOLD}Some dependencies are missing. Run 'sudo ./install_deps.sh' to install them.${RESET}"
        return 1
    fi
}

detect_package_manager() {
    if command -v apt-get >/dev/null 2>&1; then
        echo "apt"
    elif command -v pacman >/dev/null 2>&1; then
        echo "pacman"
    elif command -v dnf >/dev/null 2>&1; then
        echo "dnf"
    elif command -v brew >/dev/null 2>&1; then
        echo "brew"
    else
        echo "unknown"
    fi
}

install_catch2_if_missing() {
    if [ -f "$CATCH2_DEST" ]; then
        echo -e "  ${GREEN}[✓] Catch2 header (${CATCH2_DEST}) is already present.${RESET}"
    else
        echo -e "  ${YELLOW}[-] Catch2 header missing. Downloading Catch2 v2.13.10...${RESET}"
        mkdir -p "$SCRIPT_DIR/utils"
        if ! curl -sSL "$CATCH2_URL" -o "$CATCH2_DEST"; then
            echo -e "  ${RED}[✗] Failed to download Catch2 from $CATCH2_URL${RESET}"
            return 1
        fi
        if [ -n "${SUDO_USER:-}" ]; then
            chown -R "$SUDO_USER:" "$SCRIPT_DIR/utils" 2>/dev/null || true
        fi
        echo -e "  ${GREEN}[✓] Downloaded Catch2 to ${CATCH2_DEST}.${RESET}"
    fi
}

# --- Parse arguments ---
CHECK_ONLY=false

while [ $# -gt 0 ]; do
    case "$1" in
        --check)
            CHECK_ONLY=true
            shift
            ;;
        -h|--help)
            print_usage
            exit 0
            ;;
        *)
            echo "Unknown option: $1"
            print_usage
            exit 1
            ;;
    esac
done

if [ "$CHECK_ONLY" = true ]; then
    run_check_only
    exit $?
fi

# --- Ensure root / sudo privileges ---
if [ "${EUID:-$(id -u)}" -ne 0 ]; then
    if command -v sudo >/dev/null 2>&1; then
        echo -e "${YELLOW}Elevated privileges required. Re-running with sudo...${RESET}"
        exec sudo bash "$0" "$@"
    else
        echo -e "${RED}Error: Root privileges are required to install system packages.${RESET}"
        echo "Please re-run this script with sudo or as root: sudo $0"
        exit 1
    fi
fi

PKG_MGR=$(detect_package_manager)
echo -e "${BOLD}${BLUE}==> Installing dependencies for competitive_programming_resources...${RESET}"
echo -e "Detected package manager: ${BOLD}$PKG_MGR${RESET}\n"

case "$PKG_MGR" in
    apt)
        APT_PKGS=(
            build-essential
            curl
            python3
            texlive-latex-base
            texlive-latex-recommended
            texlive-latex-extra
            texlive-fonts-recommended
        )

        MISSING_PKGS=()
        for pkg in "${APT_PKGS[@]}"; do
            if dpkg -s "$pkg" >/dev/null 2>&1; then
                echo -e "  ${GREEN}[✓] $pkg is already installed.${RESET}"
            else
                echo -e "  ${YELLOW}[-] $pkg is not installed.${RESET}"
                MISSING_PKGS+=("$pkg")
            fi
        done

        if [ ${#MISSING_PKGS[@]} -gt 0 ]; then
            echo -e "\n${BOLD}==> Updating apt repositories...${RESET}"
            apt-get update -y
            echo -e "\n${BOLD}==> Installing missing packages: ${MISSING_PKGS[*]}...${RESET}"
            DEBIAN_FRONTEND=noninteractive apt-get install -y "${MISSING_PKGS[@]}"
        else
            echo -e "\n${GREEN}All system apt packages are already installed.${RESET}"
        fi
        ;;

    pacman)
        PACMAN_PKGS=(
            base-devel
            curl
            python
            texlive-basic
            texlive-latexrecommended
            texlive-latexextra
            texlive-fontsrecommended
        )

        MISSING_PKGS=()
        for pkg in "${PACMAN_PKGS[@]}"; do
            if pacman -Qi "$pkg" >/dev/null 2>&1; then
                echo -e "  ${GREEN}[✓] $pkg is already installed.${RESET}"
            else
                echo -e "  ${YELLOW}[-] $pkg is not installed.${RESET}"
                MISSING_PKGS+=("$pkg")
            fi
        done

        if [ ${#MISSING_PKGS[@]} -gt 0 ]; then
            echo -e "\n${BOLD}==> Installing missing packages: ${MISSING_PKGS[*]}...${RESET}"
            pacman -Sy --noconfirm "${MISSING_PKGS[@]}"
        else
            echo -e "\n${GREEN}All system pacman packages are already installed.${RESET}"
        fi
        ;;

    dnf)
        DNF_PKGS=(
            gcc-c++
            make
            curl
            python3
            texlive-scheme-medium
        )

        MISSING_PKGS=()
        for pkg in "${DNF_PKGS[@]}"; do
            if rpm -q "$pkg" >/dev/null 2>&1; then
                echo -e "  ${GREEN}[✓] $pkg is already installed.${RESET}"
            else
                echo -e "  ${YELLOW}[-] $pkg is not installed.${RESET}"
                MISSING_PKGS+=("$pkg")
            fi
        done

        if [ ${#MISSING_PKGS[@]} -gt 0 ]; then
            echo -e "\n${BOLD}==> Installing missing packages: ${MISSING_PKGS[*]}...${RESET}"
            dnf install -y "${MISSING_PKGS[@]}"
        else
            echo -e "\n${GREEN}All system dnf packages are already installed.${RESET}"
        fi
        ;;

    brew)
        BREW_PKGS=(gcc curl python)
        for pkg in "${BREW_PKGS[@]}"; do
            if brew list "$pkg" >/dev/null 2>&1; then
                echo -e "  ${GREEN}[✓] $pkg is already installed.${RESET}"
            else
                echo -e "  ${YELLOW}[-] Installing $pkg...${RESET}"
                brew install "$pkg"
            fi
        done

        if check_binary pdflatex; then
            echo -e "  ${GREEN}[✓] pdflatex is already installed.${RESET}"
        else
            echo -e "  ${YELLOW}[-] Installing basictex cask...${RESET}"
            brew install --cask basictex
        fi
        ;;

    *)
        echo -e "${YELLOW}Warning: Unknown package manager.${RESET}"
        echo "Please install the following manually using your distribution's package manager:"
        echo "  - C++ compiler (g++)"
        echo "  - curl"
        echo "  - Python 3"
        echo "  - TeX Live (pdflatex, listings, amsmath, geometry, hyperref, xcolor)"
        ;;
esac

echo -e "\n${BOLD}==> Checking Catch2 test framework...${RESET}"
install_catch2_if_missing

echo -e "\n${GREEN}${BOLD}==> All dependencies are successfully installed and verified!${RESET}\n"
run_check_only
