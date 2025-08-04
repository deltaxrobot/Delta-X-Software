# IndustrialCamera Plugin - Build Instructions

## 🚀 Quick Build

### Option 1: Automated Build (Recommended)
```batch
# Run the automated build script
build_debug.bat
```

### Option 2: Manual Build
```batch
# 1. Generate Makefiles
qmake IndustrialCamera.pro -spec win32-msvc CONFIG+=debug CONFIG+=qml_debug

# 2. Build debug version
nmake debug

# 3. Copy DLL to plugin directory
copy debug\IndustrialCameraPlugind.dll ..\..\plugin\
```

## 📋 Prerequisites

### Required Software:
1. **Qt Framework** (5.12+ or 6.x)
   - Download: https://www.qt.io/download-qt-installer
   - Ensure `qmake` is in system PATH

2. **Build Tools** (One of the following):
   - **Visual Studio Build Tools** (for nmake)
   - **MinGW** (for mingw32-make)

3. **Dependencies** (Already included in 3rd-party folder):
   - OpenCV 4.0+
   - Basler Pylon SDK
   - HIKVision MVS SDK

## 🛠️ Environment Setup

### Qt Setup:
```batch
# Add Qt bin directory to PATH
set PATH=C:\Qt\5.15.2\msvc2019_64\bin;%PATH%

# Or use Qt Command Prompt
# Start Menu → Qt → Qt 5.15.2 (MSVC 2019 64-bit)
```

### Visual Studio Setup:
```batch
# Use Developer Command Prompt for VS
# Start Menu → Visual Studio → Developer Command Prompt
```

## 📁 Output Files

### Debug Build:
- **DLL**: `debug/IndustrialCameraPlugind.dll`
- **Destination**: `../../plugin/IndustrialCameraPlugind.dll`

### Expected Plugin Structure:
```
Delta-X-Software/
├── plugin/
│   └── IndustrialCameraPlugind.dll  ← Plugin DLL
└── plugin/IndustrialCamera/
    ├── debug/
    │   ├── IndustrialCameraPlugind.dll
    │   └── ... (other build artifacts)
    └── ... (source files)
```

## 🔧 Troubleshooting

### Common Issues:

#### ❌ "qmake is not recognized"
**Solution:**
- Install Qt or add Qt bin directory to PATH
- Use Qt Command Prompt instead of regular cmd

#### ❌ "nmake is not recognized"  
**Solution:**
- Install Visual Studio Build Tools
- Use Developer Command Prompt for VS
- Alternative: Try `mingw32-make` if MinGW is installed

#### ❌ "Cannot open include file"
**Solution:**
- Verify 3rd-party dependencies are present:
  - `3rd-party/opencv/build/include/`
  - `3rd-party/pylon/include/`
  - `3rd-party/mvs/Includes/`

#### ❌ "Cannot open input file '*.lib'"
**Solution:**
- Verify library files exist:
  - `3rd-party/opencv/build/x64/vc15/lib/opencv_world400d.lib`
  - `3rd-party/pylon/lib/x64/`
  - `3rd-party/mvs/Libraries/win64/MvCameraControl.lib`

## 🏗️ Build Configurations

### Debug Configuration:
- **Target**: `IndustrialCameraPlugind.dll`
- **OpenCV**: `opencv_world400d.lib` (debug version)
- **Symbols**: Included for debugging
- **Optimization**: Disabled

### Release Configuration:
```batch
# Generate release Makefiles
qmake IndustrialCamera.pro -spec win32-msvc CONFIG+=release

# Build release version  
nmake release
```

## 🧪 Integration Testing

### Plugin Loading Test:
1. Copy `IndustrialCameraPlugind.dll` to `Delta-X-Software/plugin/`
2. Launch Delta X Software
3. Check console for plugin loading messages
4. Verify plugin tab appears in UI

### Camera Connection Test:
1. Open IndustrialCamera plugin tab
2. Click "Refresh" to scan cameras
3. Select camera from dropdown
4. Click "Connect" 
5. Test image capture functionality

## 📝 Code Changes Made

### Fixed Issues:
- ✅ **Memory leak** in `GetUI()` method
- ✅ **Thread safety** in `CameraReader::ShotImage()`
- ✅ **Null pointer checks** in settings methods
- ✅ **Duplicate includes** removed
- ✅ **Project configuration** paths corrected
- ✅ **Error handling** added for Pylon initialization

### Code Quality Improvements:
- ✅ **Safe pointer operations**
- ✅ **Exception handling** for OpenCV operations
- ✅ **Input validation** for image dimensions
- ✅ **Proper resource cleanup**
- ✅ **Conditional library linking** (debug/release)

## 📞 Support

If you encounter build issues:
1. Check Prerequisites section
2. Review Troubleshooting guide
3. Verify all dependencies are present
4. Ensure correct Qt and build tools versions

## 🎯 Next Steps

After successful build:
1. Copy DLL to main application plugin directory
2. Test plugin loading in Delta X Software
3. Configure camera settings
4. Test image capture functionality
5. Integrate with main application workflow