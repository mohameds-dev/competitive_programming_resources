#!/bin/bash

# Script to create a new directory from template
# Usage: ./create_new_dir.sh directory_name

if [ $# -eq 0 ]; then
    echo "Error: Directory name required"
    echo "Usage: ./create_new_dir.sh directory_name"
    exit 1
fi

DIR_NAME="$1"
TEMPLATE_DIR="template"

if [ ! -d "$TEMPLATE_DIR" ]; then
    echo "Error: Template directory '$TEMPLATE_DIR' not found"
    exit 1
fi

if [ -d "$DIR_NAME" ]; then
    echo "Error: Directory '$DIR_NAME' already exists"
    exit 1
fi

# Copy template directory
echo "Creating directory '$DIR_NAME' from template..."
cp -r "$TEMPLATE_DIR" "$DIR_NAME"

# Replace "Code Template" with directory name in readme.md
# Convert directory name to title case (e.g., "segment_tree" -> "Segment Tree")
FORMATTED_NAME=$(echo "$DIR_NAME" | sed 's/_/ /g' | awk '{for(i=1;i<=NF;i++){ $i=toupper(substr($i,1,1)) substr($i,2) }}1')


# Linux
sed -i "s/Code Template/$FORMATTED_NAME/g" "$DIR_NAME/readme.md"


# Update tests.cpp to use the new directory name
sed -i "s/Code Template/$FORMATTED_NAME/g" "$DIR_NAME/tests.cpp"

echo "Directory '$DIR_NAME' created successfully!"

