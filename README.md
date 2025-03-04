# Delta X Software

Delta X Software is a comprehensive control and programming platform for Delta robots.

## Installation Guide

### Prerequisites

- Qt 5.15 with MSVC 2019 (recommended)
- Microsoft Visual Studio 2019 or 2022 Community Edition
- OpenCV 4.0 or higher
- Git
- CMake (3.16 or higher)
- Python (for script execution)

### Hardware Requirements
- Delta robot with compatible controller
- USB webcam or industrial camera (for vision features)
- Conveyor belt system (optional)
- Encoder devices (optional)

### Installation Steps

1. Clone the repository:
```bash
git clone https://github.com/yourusername/Delta-X-Software.git
cd Delta-X-Software
```

2. Open the project in Qt Creator:
   - Launch Qt Creator (with Qt 5.15)
   - Go to File -> Open File or Project
   - Navigate to the cloned repository and select `DeltaRobotSoftware.pro`

3. In Qt Creator:
   - Go to Tools -> Options -> Kits
   - Create a new kit or modify existing one
   - Set the MSVC 2019 compiler as the C++ compiler
   - Select Qt 5.15 as the Qt version
   - Configure the debugger

### Environment Setup

Add these paths to your system's PATH:
- MSVC compiler directory
- Qt 5.15 bin directory
- CMake bin directory
- OpenCV bin directory

### Building the Project

1. Configure build settings in Qt Creator:
   - Select Release or Debug configuration
   - Set build directory

2. Build the project:
   - Click Build -> Build Project or press Ctrl+B

3. Run the application:
   - Click the Run button or press Ctrl+R

### Initial Configuration

1. Configure robot connection:
   - Set COM port in settings
   - Configure speed and acceleration parameters

2. Set up vision system:
   - Select camera ID
   - Configure detection algorithms

3. Connect auxiliary devices:
   - Configure conveyor settings
   - Set up encoder parameters


