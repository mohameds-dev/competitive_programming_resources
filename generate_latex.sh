#!/bin/bash

# --- CONFIGURATION ---
CONTENT_FILE="content.tex"         # Temporary file to hold all code
MAIN_TEX_FILE="reference.tex"      # Your main LaTeX template
OUTPUT_DIR="latex_pdf_output"      # Folder for all generated files
OUTPUT_NAME="reference"            # The name of your final PDF

# 0. Remove the dir if it already exists
rm -rf "$OUTPUT_DIR"

# 1. Create the output directory if it doesn't exist
mkdir "$OUTPUT_DIR"

# 2. Generate the temporary content.tex file
> "$CONTENT_FILE"
echo "--- Generating LaTeX content ($CONTENT_FILE) ---"

# Loop through all subdirectories
for dir in */; do
    dirname=$(basename "$dir")
    README_FILE="$dir/readme.md"
    
    FILE_TO_USE="" # Will store the path to the code file

    # Priority 1: Check for code.cpp
    if [ -f "$dir/code.cpp" ]; then
        FILE_TO_USE="$dir/code.cpp"
    # Priority 2: If no code.cpp, check for main.cpp
    elif [ -f "$dir/main.cpp" ]; then
        FILE_TO_USE="$dir/main.cpp"
    fi

    # Priority 3: If a file was found (FILE_TO_USE is not empty), process it.
    if [ -n "$FILE_TO_USE" ]; then
        
        # Make a pretty name (e.g., "segment_tree" -> "Segment Tree")
        pretty_name=$(echo "$dirname" | sed -e 's/_/ /g' -e 's/\b\(.\)/\u\1/g')
        echo "Found: $pretty_name (using $FILE_TO_USE)"

        # 1. Add Section Title
        echo "\section*{$pretty_name}" >> "$CONTENT_FILE"
        echo "\addcontentsline{toc}{section}{$pretty_name}" >> "$CONTENT_FILE"
        echo "" >> "$CONTENT_FILE"

        # 2. Add README.md (converts Markdown to LaTeX)
        if [ -f "$README_FILE" ]; then
            pandoc "$README_FILE" -f markdown -t latex >> "$CONTENT_FILE"
            echo "\par" >> "$CONTENT_FILE"
        fi

        # 3. Add the C++ Code
        echo "\lstinputlisting{$FILE_TO_USE}" >> "$CONTENT_FILE"
        echo "\clearpage" >> "$CONTENT_FILE" # Start next algorithm on a new page
        echo "" >> "$CONTENT_FILE"
    
    else
        # Optional: Log the directories that are skipped
        # echo "Skipping: $dirname (no code.cpp or main.cpp found)"
        : # This colon is a 'do nothing' placeholder
    fi
done
echo "--- Content generation complete ---"

# 3. Compile the PDF (running twice for Table of Contents)
echo "--- Compiling PDF (Pass 1) ---"
pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_TEX_FILE"

echo "--- Compiling PDF (Pass 2) ---"
pdflatex -output-directory="$OUTPUT_DIR" "$MAIN_TEX_FILE"

# 4. Clean up all intermediate files
echo "--- Cleaning up intermediate files ---"
rm "$CONTENT_FILE" # Remove the temp file from the root
rm "$OUTPUT_DIR/"*.aux
rm "$OUTPUT_DIR/"*.log
rm "$OUTPUT_DIR/"*.toc

echo ""
echo "✅ PDF Build Complete!"
echo "Final PDF: $OUTPUT_DIR/$OUTPUT_NAME.pdf"