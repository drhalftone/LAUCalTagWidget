#!/usr/bin/env python3
"""
Generate CalTag checkerboard patterns with unique 4x4 binary codes.
Creates PDF output with 1"x1" squares.
"""

import argparse
import itertools
import numpy as np
from reportlab.pdfgen import canvas
from reportlab.lib.pagesizes import letter
from reportlab.lib.units import inch
import sys
import random

def generate_patterns_with_n_white(n):
    """Generate all 4x4 binary patterns with exactly n white squares (1s)."""
    patterns = []
    for positions in itertools.combinations(range(16), n):
        pattern = [0] * 16
        for pos in positions:
            pattern[pos] = 1
        patterns.append(pattern)
    return patterns

def rotate_pattern(pattern):
    """Rotate a 16-bit pattern 90 degrees clockwise."""
    # Reshape to 4x4, rotate, flatten
    grid = np.array(pattern).reshape(4, 4)
    rotated = np.rot90(grid, -1)  # -1 for clockwise
    return rotated.flatten().tolist()

def get_all_rotations(pattern):
    """Get all 4 rotations of a pattern."""
    rotations = [pattern]
    current = pattern
    for _ in range(3):
        current = rotate_pattern(current)
        rotations.append(current)
    return rotations

def remove_rotational_duplicates(patterns):
    """Remove patterns that are rotational duplicates of others."""
    print("Removing rotational duplicates...")
    
    unique_patterns = []
    seen = set()
    
    for i, pattern in enumerate(patterns):
        if i % 1000 == 0:
            print(f"Processed {i}/{len(patterns)} patterns")
            
        pattern_tuple = tuple(pattern)
        if pattern_tuple in seen:
            continue
            
        # Add all rotations to seen set
        rotations = get_all_rotations(pattern)
        for rot in rotations:
            seen.add(tuple(rot))
            
        unique_patterns.append(pattern)
    
    return unique_patterns

def sort_codes_by_balance(codes):
    """Sort codes by preference for balanced patterns (equal 1s and 0s)."""
    print("Sorting codes by balance...")
    
    # Calculate balance for each pattern
    balance_data = []
    for code in codes:
        ones_count = sum(code)
        distance_from_ideal = abs(ones_count - 8)  # 8 is ideal for 16-bit pattern
        balance_data.append((distance_from_ideal, ones_count, code))
    
    # Sort by distance from ideal, then by ones count
    balance_data.sort(key=lambda x: (x[0], x[1]))
    
    sorted_codes = [item[2] for item in balance_data]
    
    # Print summary
    print("Sorting summary:")
    for dist in range(5):
        count = sum(1 for item in balance_data if item[0] == dist)
        if count > 0:
            ones_vals = sorted(set(item[1] for item in balance_data if item[0] == dist))
            print(f"  Distance {dist} from ideal (8 ones): {count} patterns with {ones_vals} ones")
    
    return sorted_codes

def generate_unique_codes():
    """Generate all unique 4x4 binary patterns with 4-12 white squares."""
    print("Generating CalTag codes...")
    
    all_patterns = []
    for num_white in range(4, 13):  # 4 to 12 inclusive
        print(f"Processing patterns with {num_white} white squares...")
        patterns = generate_patterns_with_n_white(num_white)
        all_patterns.extend(patterns)
    
    print(f"Total patterns generated: {len(all_patterns)}")
    
    # Remove rotational duplicates
    unique_codes = remove_rotational_duplicates(all_patterns)
    print(f"Unique rotationally distinct patterns: {len(unique_codes)}")
    
    # Sort by balance
    sorted_codes = sort_codes_by_balance(unique_codes)
    
    return sorted_codes

def draw_binary_pattern(c, x, y, square_size, code, is_white_base):
    """Draw 4x4 binary pattern in the center 50% of the square."""
    # Calculate binary pattern area (center 50%)
    margin = square_size * 0.25
    binary_size = square_size * 0.5
    binary_x = x + margin
    binary_y = y + margin
    cell_size = binary_size / 4
    
    # Reshape 16-bit code to 4x4 pattern
    pattern = np.array(code).reshape(4, 4)
    
    # Draw each cell of the 4x4 pattern
    for i in range(4):
        for j in range(4):
            cell_x = binary_x + j * cell_size
            cell_y = binary_y + (3 - i) * cell_size  # Flip Y
            
            # Determine cell color based on base square and binary value
            if is_white_base:
                # White base square: 1 = black, 0 = white
                fill_color = 0 if pattern[i, j] == 1 else 1  # 0=black, 1=white
            else:
                # Black base square: 1 = white, 0 = black
                fill_color = 1 if pattern[i, j] == 1 else 0
            
            c.setFillGray(fill_color)
            c.rect(cell_x, cell_y, cell_size, cell_size, fill=1, stroke=0)

def generate_caltag_pdf(width, height, filename="caltag_pattern.pdf"):
    """Generate CalTag checkerboard pattern as PDF."""
    
    total_squares = width * height
    max_unique = 16102
    
    # Warning for exceeding unique patterns
    if total_squares > max_unique:
        print(f"WARNING: Grid has {total_squares} squares but only {max_unique} unique patterns available.")
        print(f"Some patterns will be repeated.")
    
    # Generate unique codes
    unique_codes = generate_unique_codes()
    
    # Prepare codes (repeat if necessary)
    if total_squares <= len(unique_codes):
        codes_to_use = unique_codes[:total_squares]
    else:
        # Repeat the pattern if we need more codes
        codes_to_use = []
        for i in range(total_squares):
            codes_to_use.append(unique_codes[i % len(unique_codes)])
    
    # Randomize the order of codes while keeping the sorted preference
    print("Randomizing code locations...")
    random.shuffle(codes_to_use)
    
    # Calculate page size (add 0.5" border on each side for half squares)
    page_width = (width + 1) * inch
    page_height = (height + 1) * inch
    
    print(f"Generating {width}x{height} CalTag pattern...")
    print(f"PDF size: {page_width/inch:.1f}\" x {page_height/inch:.1f}\"")
    
    # Create canvas
    c = canvas.Canvas(filename, pagesize=(page_width, page_height))
    
    # Draw main checkerboard pattern
    code_idx = 0
    for row in range(height):
        for col in range(width):
            # Calculate position (0.5" offset for border)
            x = (col + 0.5) * inch
            y = (height - row - 0.5) * inch  # Fixed: subtract 0.5 instead of add
            
            # Determine base checkerboard color (alternating)
            is_white_square = (row + col) % 2 == 0
            
            # Draw base square
            c.setStrokeGray(0)  # Black border
            c.setLineWidth(1)
            
            if is_white_square:
                c.setFillGray(1)  # White
            else:
                c.setFillGray(0)  # Black
            
            c.rect(x, y, inch, inch, fill=1, stroke=1)
            
            # Draw 4x4 binary pattern in center
            draw_binary_pattern(c, x, y, inch, codes_to_use[code_idx], is_white_square)
            
            code_idx += 1
        
        if (row + 1) % 10 == 0:
            print(f"Completed row {row + 1}/{height}")
    
    # Draw border half-squares (0.5" visible)
    half_inch = 0.5 * inch
    
    # Top border (half squares) - row index -1
    for col in range(width):
        x = (col + 0.5) * inch
        y_top = (height + 0.5) * inch
        # Color continues the checkerboard pattern: virtual row -1, column col
        is_white_top = ((-1) + col) % 2 == 0
        c.setFillGray(1 if is_white_top else 0)
        c.rect(x, y_top, inch, half_inch, fill=1, stroke=1)
    
    # Bottom border (half squares) - row index height
    for col in range(width):
        x = (col + 0.5) * inch
        y_bottom = 0
        # Color continues the checkerboard pattern: virtual row height, column col
        is_white_bottom = (height + col) % 2 == 0
        c.setFillGray(1 if is_white_bottom else 0)
        c.rect(x, y_bottom, inch, half_inch, fill=1, stroke=1)
    
    # Left border (half squares) - column index -1
    for row in range(height):
        y = (height - row - 0.5) * inch
        x_left = 0
        # Color continues the checkerboard pattern: row row, virtual column -1
        is_white_left = (row + (-1)) % 2 == 0
        c.setFillGray(1 if is_white_left else 0)
        c.rect(x_left, y, half_inch, inch, fill=1, stroke=1)
    
    # Right border (half squares) - column index width
    for row in range(height):
        y = (height - row - 0.5) * inch
        x_right = (width + 0.5) * inch
        # Color continues the checkerboard pattern: row row, virtual column width
        is_white_right = (row + width) % 2 == 0
        c.setFillGray(1 if is_white_right else 0)
        c.rect(x_right, y, half_inch, inch, fill=1, stroke=1)
    
    # Corner quarter squares (0.5" x 0.5")
    # Top-left corner: virtual row -1, virtual column -1
    is_white_tl = ((-1) + (-1)) % 2 == 0
    c.setFillGray(1 if is_white_tl else 0)
    c.rect(0, (height + 0.5) * inch, half_inch, half_inch, fill=1, stroke=1)
    
    # Top-right corner: virtual row -1, virtual column width
    is_white_tr = ((-1) + width) % 2 == 0
    c.setFillGray(1 if is_white_tr else 0)
    c.rect((width + 0.5) * inch, (height + 0.5) * inch, half_inch, half_inch, fill=1, stroke=1)
    
    # Bottom-left corner: virtual row height, virtual column -1
    is_white_bl = (height + (-1)) % 2 == 0
    c.setFillGray(1 if is_white_bl else 0)
    c.rect(0, 0, half_inch, half_inch, fill=1, stroke=1)
    
    # Bottom-right corner: virtual row height, virtual column width
    is_white_br = (height + width) % 2 == 0
    c.setFillGray(1 if is_white_br else 0)
    c.rect((width + 0.5) * inch, 0, half_inch, half_inch, fill=1, stroke=1)
    
    # Save PDF
    c.save()
    print(f"CalTag pattern saved to {filename}")
    print(f"Pattern uses {len(codes_to_use)} codes ({len(set(map(tuple, codes_to_use)))} unique)")
    
    return codes_to_use

def pattern_to_int(pattern):
    """Convert 16-bit binary pattern to integer."""
    result = 0
    for i, bit in enumerate(pattern):
        if bit:
            result |= (1 << (15 - i))  # MSB first
    return result

def generate_lookup_code(width, height, codes_to_use, output_file="caltag_lookup.c"):
    """Generate C code lookup table for pattern detection."""
    
    print(f"Generating lookup table C code...")
    
    # Convert patterns to integers and create lookup mapping
    code_to_position = {}
    code_idx = 0
    
    for row in range(height):
        for col in range(width):
            pattern = codes_to_use[code_idx]
            code_int = pattern_to_int(pattern)
            
            # Store position relative to center (like original code)
            center_col = (width - 1) / 2
            center_row = (height - 1) / 2
            rel_col = col - center_col
            rel_row = row - center_row
            
            code_to_position[code_int] = (rel_col, rel_row)
            code_idx += 1
    
    # Sort codes for organized output
    sorted_codes = sorted(code_to_position.keys())
    
    # Generate C code
    with open(output_file, 'w') as f:
        f.write("// CalTag lookup table - auto-generated\n")
        f.write(f"// Grid size: {width}x{height}\n")
        f.write(f"// Total codes: {len(sorted_codes)}\n\n")
        
        # Write lookup table
        f.write(f"static const struct {{\n")
        f.write(f"    int code;\n")
        f.write(f"    float x, y;\n")
        f.write(f"}} caltagCodes[{len(sorted_codes)}] = {{\n")
        
        for i, code in enumerate(sorted_codes):
            x, y = code_to_position[code]
            f.write(f"    {{{code:5d}, {x:6.1f}f, {y:6.1f}f}}")
            if i < len(sorted_codes) - 1:
                f.write(",")
            f.write(f"  // Pattern {i+1}\n")
        
        f.write("};\n\n")
        
        # Write lookup function
        f.write("bool lookupCaltagCode(int code, cv::Point2f* pt) {\n")
        f.write("    // Binary search through sorted codes\n")
        f.write("    int left = 0;\n")
        f.write(f"    int right = {len(sorted_codes) - 1};\n")
        f.write("    \n")
        f.write("    while (left <= right) {\n")
        f.write("        int mid = (left + right) / 2;\n")
        f.write("        if (caltagCodes[mid].code == code) {\n")
        f.write("            *pt = cv::Point2f(caltagCodes[mid].x, caltagCodes[mid].y);\n")
        f.write("            return true;\n")
        f.write("        } else if (caltagCodes[mid].code < code) {\n")
        f.write("            left = mid + 1;\n")
        f.write("        } else {\n")
        f.write("            right = mid - 1;\n")
        f.write("        }\n")
        f.write("    }\n")
        f.write("    return false;\n")
        f.write("}\n")
    
    print(f"Lookup table saved to {output_file}")
    print(f"Contains {len(sorted_codes)} unique codes")
    
    # Also generate a simple linear search version like the original
    linear_file = output_file.replace('.c', '_linear.c')
    with open(linear_file, 'w') as f:
        f.write("// CalTag lookup table - linear search version\n")
        f.write(f"// Grid size: {width}x{height}\n\n")
        
        # Group codes by rows for compact representation
        codes_by_row = []
        code_idx = 0
        for row in range(height):
            row_codes = []
            for col in range(width):
                pattern = codes_to_use[code_idx]
                code_int = pattern_to_int(pattern)
                row_codes.append(code_int)
                code_idx += 1
            codes_by_row.append(row_codes)
        
        f.write(f"static const int realBitCodes[{height}][{width}] = {{\n")
        for row in range(height):
            f.write("    {")
            for col in range(width):
                f.write(f"{codes_by_row[row][col]:5d}")
                if col < width - 1:
                    f.write(", ")
            f.write("}")
            if row < height - 1:
                f.write(",")
            f.write(f"  // Row {row}\n")
        f.write("};\n\n")
        
        f.write("bool lookupCaltagCode(int code, cv::Point2f* pt) {\n")
        f.write(f"    for (int i = 0; i < {height}; i++) {{\n")
        f.write(f"        for (int j = {width-1}; j >= 0; j--) {{\n")
        f.write("            if (code == realBitCodes[i][j]) {\n")
        f.write(f"                *pt = cv::Point2f((float)(j - {(width-1)//2}), (float)(i - {(height-1)//2}));\n")
        f.write("                return true;\n")
        f.write("            }\n")
        f.write("        }\n")
        f.write("    }\n")
        f.write("    return false;\n")
        f.write("}\n")
    
    print(f"Linear lookup version saved to {linear_file}")

def main():
    parser = argparse.ArgumentParser(description="Generate CalTag checkerboard patterns")
    parser.add_argument("width", type=int, help="Width of CalTag grid (number of squares)")
    parser.add_argument("height", type=int, help="Height of CalTag grid (number of squares)")
    parser.add_argument("-o", "--output", default="caltag_pattern.pdf", 
                        help="Output PDF filename (default: caltag_pattern.pdf)")
    parser.add_argument("-c", "--code", action="store_true",
                        help="Generate C lookup code files")
    
    args = parser.parse_args()
    
    if args.width <= 0 or args.height <= 0:
        print("Error: Width and height must be positive integers")
        sys.exit(1)
    
    codes_used = generate_caltag_pdf(args.width, args.height, args.output)
    
    if args.code:
        generate_lookup_code(args.width, args.height, codes_used)

if __name__ == "__main__":
    main()