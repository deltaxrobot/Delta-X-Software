import sys
import subprocess

# Function to install missing packages
def install_missing_packages(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

# Check and install necessary packages
try:
    from PyQt5.QtWidgets import QApplication, QFileDialog
except ImportError:
    install_missing_packages("PyQt5")
    from PyQt5.QtWidgets import QApplication, QFileDialog

try:
    import svgpathtools
except ImportError:
    install_missing_packages("svgpathtools")
    import svgpathtools

try:
    import matplotlib.pyplot as plt
except ImportError:
    install_missing_packages("matplotlib")
    import matplotlib.pyplot as plt

import numpy as np


def load_svg_file():
    app = QApplication(sys.argv)
    options = QFileDialog.Options()
    file_path, _ = QFileDialog.getOpenFileName(None, "Open SVG File", "", "SVG Files (*.svg)", options=options)
    return file_path


def parse_svg(svg_file):
    paths, _ = svgpathtools.svg2paths(svg_file)
    return paths


def plot_svg(paths):
    fig, ax = plt.subplots()
    ax.set_aspect('equal')

    for path in paths:
        for segment in path:
            x, y = [], []
            points = segment.point(np.linspace(0, 1, 100))
            x = [p.real for p in points]
            y = [p.imag for p in points]
            ax.plot(x, y, color='blue')

    ax.set_title('SVG Paths')
    plt.gca().invert_yaxis()
    plt.show()


def svg_to_gcode(paths):
    gcode = []
    for path in paths:
        first_segment = True
        for segment in path:
            start = segment.start
            end = segment.end
            if first_segment:
                gcode.append(f"G00 X{start.real:.3f} Y{start.imag:.3f} Z5.000")  # Move to start and lift Z axis
                gcode.append(f"G01 Z0.000")  # Lower Z axis to start drawing
                first_segment = False
            gcode.append(f"G01 X{end.real:.3f} Y{end.imag:.3f}")  # Draw to end
        gcode.append(f"G00 Z5.000")  # Lift Z axis after finishing path
    return gcode


def plot_gcode(gcode):
    fig, ax = plt.subplots()
    ax.set_aspect('equal')
    current_x, current_y = 0, 0

    for line in gcode:
        parts = line.split()
        if parts[0] == 'G00':
            if 'X' in parts[1] and 'Y' in parts[2]:
                x = float(parts[1][1:])
                y = float(parts[2][1:])
                ax.plot([current_x, x], [current_y, y], color='green', linestyle='dashed')  # Move without drawing
                current_x, current_y = x, y
        elif parts[0] == 'G01':
            if 'X' in parts[1] and 'Y' in parts[2]:
                x = float(parts[1][1:])
                y = float(parts[2][1:])
                ax.plot([current_x, x], [current_y, y], color='red')  # Draw
                current_x, current_y = x, y

    ax.set_title('G-code Paths')
    plt.gca().invert_yaxis()
    plt.show()


def main():
    svg_file = load_svg_file()
    if not svg_file:
        print("No file selected!")
        return

    # Parse and plot SVG file
    paths = parse_svg(svg_file)
    plot_svg(paths)

    # Convert SVG to G-code and plot G-code
    gcode = svg_to_gcode(paths)
    plot_gcode(gcode)


if __name__ == "__main__":
    main()
