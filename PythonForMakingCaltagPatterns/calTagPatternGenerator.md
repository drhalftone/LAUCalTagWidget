# CalTag Pattern Generator

A comprehensive toolkit for generating CalTag calibration patterns with unique 4×4 binary codes embedded in checkerboard squares. These patterns are ideal for camera calibration, pose estimation, and computer vision applications.

## Overview

CalTag (Calibration Tag) is an enhanced fiducial marker system that combines traditional checkerboard patterns with unique binary identifiers. Each square in the checkerboard contains a rotationally-unique 4×4 binary pattern in its center, enabling robust detection and identification of individual squares.

### Key Features

- **16,102 Unique Patterns**: Generates all possible rotationally-distinct 4×4 binary patterns with 4-12 white squares
- **Balanced Pattern Selection**: Prioritizes patterns with equal numbers of 1s and 0s for optimal detection
- **Randomized Placement**: Shuffles pattern locations while maintaining quality preference
- **Perfect Scaling**: Generates 1" × 1" squares for precise physical measurements
- **Border Support**: Half-square borders provide corner visibility for edge detection
- **Lookup Table Generation**: Creates C code for fast pattern-to-coordinate mapping
- **Cross-Platform**: Works on macOS, Linux, and Windows

## Files Overview

| File | Description |
|------|-------------|
| `calTagPatternGenerator.py` | Main Python script for pattern generation |
| `calTagPatternGenerator.sh` | macOS/Linux wrapper with automatic environment setup |
| `calTagPatternGenerator.bat` | Windows wrapper with automatic environment setup |
| `calTagPatternGenerator.md` | This documentation file |

## Installation & Usage

### Quick Start (No Installation Required)

The wrapper scripts automatically handle all dependencies:

**macOS/Linux:**
```bash
./calTagPatternGenerator.sh <width> <height> [options]
```

**Windows:**
```cmd
calTagPatternGenerator.bat <width> <height> [options]
```

### Direct Python Usage

If you prefer to manage dependencies yourself:

```bash
pip install reportlab numpy
python calTagPatternGenerator.py <width> <height> [options]
```

## Command Line Options

| Option | Description | Default |
|--------|-------------|---------|
| `width` | Width of CalTag grid (columns) | Required |
| `height` | Height of CalTag grid (rows) | Required |
| `-o, --output` | Output PDF filename | `caltag_pattern.pdf` |
| `-c, --code` | Generate C lookup code files | Disabled |

## Examples

### Generate 95×47 Pattern (4,465 squares)
```bash
./calTagPatternGenerator.sh 95 47 -o large_caltag.pdf -c
```
- **Output**: 96" × 48" PDF
- **Uses**: 4,465 unique patterns
- **Files**: PDF + C lookup tables

### Generate 47×23 Pattern (1,081 squares)
```bash
./calTagPatternGenerator.sh 47 23 -o small_caltag.pdf -c
```
- **Output**: 48" × 24" PDF  
- **Uses**: 1,081 unique patterns
- **Files**: PDF + C lookup tables

### Generate Custom Size
```bash
./calTagPatternGenerator.sh 20 15 -o custom.pdf
```
- **Output**: 21" × 16" PDF
- **Uses**: 300 unique patterns
- **Files**: PDF only

## Pattern Structure

### Main Grid
- **Square Size**: Exactly 1" × 1"
- **Binary Pattern**: 4×4 grid in center 50% of each square
- **Pattern Selection**: Prioritized by balance (8 ones preferred, then 7/9, etc.)
- **Placement**: Randomized locations for selected patterns

### Border Design
- **Border Width**: 0.5" half-squares around perimeter
- **Purpose**: Provides corner visibility for edge square detection
- **Pattern**: Continues checkerboard alternation seamlessly
- **Total Size**: (width + 1)" × (height + 1)"

### Pattern Quality Hierarchy
1. **Distance 0**: 8 ones, 8 zeros *(3,238 patterns)*
2. **Distance 1**: 7 or 9 ones *(5,720 patterns)*
3. **Distance 2**: 6 or 10 ones *(4,032 patterns)*
4. **Distance 3**: 5 or 11 ones *(2,184 patterns)*
5. **Distance 4**: 4 or 12 ones *(928 patterns)*

## Generated Files

### PDF Output
- **Scaling**: 1" = 72 points (exact physical size)
- **Resolution**: 72 DPI for 1:1 printing
- **Colors**: Pure black/white for optimal contrast
- **Format**: Professional print-ready

### C Lookup Tables (with `-c` option)

#### Binary Search Version (`caltag_lookup.c`)
```c
// Optimized for large grids
bool lookupCaltagCode(int code, cv::Point2f* pt);
```
- **Performance**: O(log n) lookup time
- **Memory**: Sorted array of code-coordinate pairs
- **Best for**: Large patterns (>1000 squares)

#### Linear Search Version (`caltag_lookup_linear.c`)
```c
// Compatible with existing code
static const int realBitCodes[height][width] = { ... };
bool lookupCaltagCode(int code, cv::Point2f* pt);
```
- **Performance**: O(n) lookup time
- **Memory**: 2D array matching grid layout
- **Best for**: Smaller patterns, legacy compatibility
- **Coordinates**: Relative to grid center

## Technical Specifications

### Pattern Generation Algorithm
1. **Enumeration**: Generate all 4×4 binary patterns with 4-12 ones
2. **Rotation Filtering**: Remove patterns identical under 90°/180°/270° rotation
3. **Balance Sorting**: Prioritize patterns closest to 8 ones/8 zeros
4. **Randomization**: Shuffle final pattern placement
5. **Grid Assembly**: Place patterns in checkerboard with proper coloring

### Memory Requirements
- **Pattern Generation**: ~64,000 initial patterns
- **Unique Filtering**: ~16,102 final patterns
- **PDF Generation**: Minimal (streaming output)
- **Temporary Storage**: ~500MB during processing

### Performance Characteristics
- **Small Grids** (<1,000 squares): ~30 seconds
- **Medium Grids** (1,000-5,000 squares): ~60-90 seconds  
- **Large Grids** (>5,000 squares): Limited by unique pattern count
- **Bottleneck**: Rotational duplicate removal

## Limitations & Warnings

### Pattern Count Limit
- **Maximum Unique Patterns**: 16,102
- **Above Limit**: Patterns will repeat with warning message
- **Recommendation**: Keep grids under 16,102 squares for uniqueness

### Printer Considerations
- **Resolution**: Ensure printer can handle 1" squares accurately
- **Size Limits**: Verify printer supports output dimensions
- **Color Accuracy**: Use pure black ink for optimal contrast

### Detection Requirements
- **Minimum Resolution**: ~20 pixels per square for reliable detection
- **Lighting**: Even illumination across entire pattern
- **Perspective**: Minimize viewing angle distortion

## Troubleshooting

### Common Issues

**"Not enough unique codes" Error**
- **Cause**: Requested grid exceeds 16,102 squares
- **Solution**: Reduce grid size or accept pattern repetition

**PDF Size Too Large**
- **Cause**: Large grids create big files
- **Solution**: Use vector formats or split into sections

**Detection Problems**
- **Cause**: Poor print quality or lighting
- **Solution**: Verify 1:1 scaling and use high-contrast printing

### Environment Issues

**Python Not Found**
- **Wrapper Scripts**: Handle this automatically
- **Direct Usage**: Install Python 3.6+ and required packages

**Permission Denied**
- **macOS/Linux**: `chmod +x calTagPatternGenerator.sh`
- **Windows**: Run as administrator if needed

## Advanced Usage

### Custom Pattern Selection
Modify the `sort_codes_by_balance()` function to implement custom pattern prioritization schemes.

### Integration with Detection Systems
The generated lookup tables are compatible with OpenCV and most computer vision frameworks:

```cpp
#include "caltag_lookup.c"

cv::Point2f gridPos;
if (lookupCaltagCode(detectedCode, &gridPos)) {
    // gridPos contains relative coordinates from center
    float realX = gridPos.x; // -23.0 to +23.0 for 47×23 grid
    float realY = gridPos.y; // -11.0 to +11.0 for 47×23 grid
}
```

### Batch Processing
Generate multiple patterns with different sizes:

```bash
for size in "20 15" "30 20" "47 23"; do
    ./calTagPatternGenerator.sh $size -o "caltag_${size// x}.pdf"
done
```

## License

This toolkit is provided as-is for research and commercial applications. The generated patterns are unique to each run due to randomization.

## Citation

If you use this toolkit in academic work, please cite:
```
CalTag Pattern Generator
A tool for generating unique checkerboard calibration patterns
https://github.com/your-repo/caltag-generator
```

## Support

For issues, feature requests, or questions:
- Check the troubleshooting section above
- Verify your command line arguments
- Ensure adequate disk space for output files
- Test with smaller grids first

---

*Generated patterns are suitable for camera calibration, 3D reconstruction, robot navigation, and other computer vision applications requiring precise fiducial markers.*