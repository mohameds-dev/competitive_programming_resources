#!/bin/bash

# --- CONFIGURATION ---
CONTENT_FILE="content.tex"         # Temporary file to hold all code
MAIN_TEX_FILE="reference.tex"      # Your main LaTeX template
OUTPUT_DIR="latex_pdf_output"      # Folder for all generated files
OUTPUT_NAME="reference"            # The name of your final PDF

# --- List of directories to skip ---
SKIP_DIRS=("dir_template" "utils" "latex_pdf_output")
# ----------------------------------------

# 0. Remove the dir if it already exists
rm -rf "$OUTPUT_DIR"

# 1. Create the output directory
mkdir "$OUTPUT_DIR"

# 2. Generate the temporary content.tex file
> "$CONTENT_FILE"
echo "--- Generating LaTeX content ($CONTENT_FILE) ---"

# Loop through all subdirectories
for dir in */; do
    dirname=$(basename "$dir")
    
    # --- Extensible Skip Logic ---
    skip=false
    for skip_dir in "${SKIP_DIRS[@]}"; do
        if [ "$dirname" == "$skip_dir" ]; then
            skip=true
            break
        fi
    done
    
    if $skip; then
        echo "Skipping: $dirname"
        continue
    fi
    # --- End of Skip Logic ---

    README_FILE="$dir/readme.md"
    FILE_TO_USE=""
    LANGUAGE=""

    # Step 1: Check for code.cpp
    if [ -f "$dir/code.cpp" ]; then
        FILE_TO_USE="$dir/code.cpp"
        LANGUAGE="C++"
    # Step 2: If no code.cpp, check for main.cpp
    elif [ -f "$dir/main.cpp" ]; then
        FILE_TO_USE="$dir/main.cpp"
        LANGUAGE="C++"
    # Step 3: If no C++, check for main.py
    elif [ -f "$dir/main.py" ]; then
        FILE_TO_USE="$dir/main.py"
        LANGUAGE="Python"
    fi

    # Step 4: If a file was found, process it.
    if [ -n "$FILE_TO_USE" ]; then
        
        # Make a pretty name
        pretty_name=$(echo "$dirname" | sed -e 's/_/ /g' -e 's/\b\(.\)/\u\1/g')
        echo "Found: $pretty_name (using $FILE_TO_USE)"

        # 1. Add Section Title
        echo "\section*{$pretty_name}" >> "$CONTENT_FILE"
        echo "\addcontentsline{toc}{section}{$pretty_name}" >> "$CONTENT_FILE"
        echo "" >> "$CONTENT_FILE"

        
        # 2. Add the Code (now with language)
        echo "\lstinputlisting[language=$LANGUAGE]{$FILE_TO_USE}" >> "$CONTENT_FILE"
        echo "\clearpage" >> "$CONTENT_FILE" 
        echo "" >> "$CONTENT_FILE"
    
    else
        # echo "Skipping $dirname: No code file found"
        : 
    fi
done
echo "--- Content generation complete ---"

# 3. Compile the PDF 
echo "--- Compiling PDF (Pass 1) ---"
pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_TEX_FILE"

echo "--- Compiling PDF (Pass 2) ---"
pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_TEX_FILE"

# 4. Clean up 
echo "--- Cleaning up intermediate files ---"
rm "$CONTENT_FILE" 
rm "$OUTPUT_DIR/"*.aux
rm "$OUTPUT_DIR/"*.log
rm "$OUTPUT_DIR/"*.toc
rm "$OUTPUT_DIR/"*.out 

echo ""
echo "✅ PDF Build Complete!"
echo "Final PDF: $OUTPUT_DIR/$OUTPUT_NAME.pdf"