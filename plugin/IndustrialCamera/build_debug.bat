@echo off
REM ===================================================================
REM Build Debug DLL for IndustrialCamera Plugin
REM ===================================================================

echo.
echo ===================================================================
echo Building IndustrialCamera Plugin (Debug Mode)
echo ===================================================================
echo.

REM Check if Qt is installed
where qmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Qt is not installed or not in PATH
    echo.
    echo Please install Qt and add qmake to your system PATH, or run this script from Qt Command Prompt
    echo.
    echo Qt Download: https://www.qt.io/download-qt-installer
    echo.
    pause
    exit /b 1
)

REM Display Qt version
echo Detecting Qt version...
qmake -version
echo.

REM Clean previous build
echo Cleaning previous build...
if exist Makefile (
    if exist debug\*.* (
        rmdir /s /q debug
    )
    if exist release\*.* (
        rmdir /s /q release  
    )
    del /q Makefile.Debug Makefile.Release Makefile 2>nul
)
echo.

REM Generate Makefiles
echo Generating Makefiles...
qmake IndustrialCamera.pro -spec win32-msvc CONFIG+=debug CONFIG+=qml_debug
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Failed to generate Makefiles
    pause
    exit /b 1
)
echo.

REM Build debug version
echo Building debug version...
nmake debug
if %ERRORLEVEL% NEQ 0 (
    echo.
    echo ERROR: Build failed. Trying alternative build method...
    echo.
    
    REM Try mingw32-make if nmake fails
    where mingw32-make >nul 2>&1
    if %ERRORLEVEL% EQU 0 (
        echo Using mingw32-make...
        qmake IndustrialCamera.pro -spec win32-g++ CONFIG+=debug CONFIG+=qml_debug
        mingw32-make debug
        if %ERRORLEVEL% NEQ 0 (
            echo ERROR: Build failed with both nmake and mingw32-make
            pause
            exit /b 1
        )
    ) else (
        echo ERROR: No suitable build tool found (nmake or mingw32-make)
        echo.
        echo Please ensure you have:
        echo 1. Visual Studio Build Tools (for nmake)
        echo 2. OR MinGW (for mingw32-make)
        echo.
        pause
        exit /b 1
    )
)
echo.

REM Check if DLL was created
if exist "debug\IndustrialCameraPlugind.dll" (
    echo ===================================================================
    echo SUCCESS: Plugin built successfully!
    echo ===================================================================
    echo.
    echo Debug DLL location: debug\IndustrialCameraPlugind.dll
    echo Plugin destination: ..\..\plugin\
    echo.
    
    REM Copy to plugin directory
    if not exist "..\..\plugin" mkdir "..\..\plugin"
    copy "debug\IndustrialCameraPlugind.dll" "..\..\plugin\" >nul
    
    echo DLL copied to plugin directory successfully!
    echo.
    echo Plugin is ready for integration with Delta X Software
    echo.
    
) else if exist "debug\IndustrialCameraPlugin.dll" (
    echo ===================================================================
    echo SUCCESS: Plugin built successfully! 
    echo ===================================================================
    echo.
    echo Debug DLL location: debug\IndustrialCameraPlugin.dll
    echo Plugin destination: ..\..\plugin\
    echo.
    
    REM Copy to plugin directory
    if not exist "..\..\plugin" mkdir "..\..\plugin"
    copy "debug\IndustrialCameraPlugin.dll" "..\..\plugin\" >nul
    
    echo DLL copied to plugin directory successfully!
    echo.
    echo Plugin is ready for integration with Delta X Software
    echo.
    
) else (
    echo ERROR: Build completed but DLL not found
    echo Expected locations:
    echo   - debug\IndustrialCameraPlugind.dll
    echo   - debug\IndustrialCameraPlugin.dll
    echo.
    echo Please check build output for errors.
)

pause