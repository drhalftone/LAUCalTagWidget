#!/bin/bash
# Generate CalTag patterns - macOS/Linux wrapper script
# Creates temporary virtual environment, installs dependencies, runs script, then cleans up

set -e  # Exit on any error

# Script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PYTHON_SCRIPT="$SCRIPT_DIR/calTagPatternGenerator.py"

# Check if Python script exists
if [ ! -f "$PYTHON_SCRIPT" ]; then
    echo "Error: calTagPatternGenerator.py not found in $SCRIPT_DIR"
    exit 1
fi

# Check for required arguments
if [ $# -lt 2 ]; then
    echo "Usage: $0 <width> <height> [additional_args...]"
    echo "Example: $0 95 47 -c -o mycaltag.pdf"
    exit 1
fi

# Create temporary directory for virtual environment
TEMP_DIR=$(mktemp -d)
VENV_DIR="$TEMP_DIR/caltag_venv"

echo "Setting up temporary environment in $TEMP_DIR"

# Function to cleanup on exit
cleanup() {
    echo "Cleaning up temporary files..."
    if [ -d "$TEMP_DIR" ]; then
        rm -rf "$TEMP_DIR"
    fi
    echo "Cleanup complete."
}

# Set trap to cleanup on script exit (success or failure)
trap cleanup EXIT

# Check if python3 is available
if ! command -v python3 &> /dev/null; then
    echo "Error: python3 is required but not installed"
    exit 1
fi

# Create virtual environment
echo "Creating virtual environment..."
python3 -m venv "$VENV_DIR"

# Activate virtual environment
source "$VENV_DIR/bin/activate"

# Upgrade pip
echo "Upgrading pip..."
pip install --upgrade pip --quiet

# Install required packages
echo "Installing required packages..."
pip install reportlab numpy --quiet

# Copy Python script to temp directory to avoid path issues
cp "$PYTHON_SCRIPT" "$TEMP_DIR/"

# Change to temp directory
cd "$TEMP_DIR"

# Run the Python script with all provided arguments
echo "Running CalTag generator..."
python calTagPatternGenerator.py "$@"

# Copy generated files back to original directory
echo "Copying generated files back..."
for file in *.pdf *.c; do
    if [ -f "$file" ]; then
        cp "$file" "$SCRIPT_DIR/"
        echo "Generated: $SCRIPT_DIR/$file"
    fi
done

echo "CalTag generation complete!"