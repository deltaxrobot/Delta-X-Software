cmake_minimum_required(VERSION 3.21)

file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" DELTA_X_VERSION
     LIMIT_COUNT 1)
string(STRIP "${DELTA_X_VERSION}" DELTA_X_VERSION)
if(NOT DELTA_X_VERSION MATCHES "^[0-9]+\\.[0-9]+\\.[0-9]+$")
    message(FATAL_ERROR "VERSION.txt must contain one semantic version (x.y.z)")
endif()

project(DeltaXSoftware VERSION "${DELTA_X_VERSION}" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui")

find_package(Qt6 6.2 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    SerialPort
    Network
    PrintSupport
    Multimedia
    Svg
    SvgWidgets
    Concurrent
)

include(cmake/DeltaXOpenCV.cmake)

file(GLOB DELTA_X_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/device/*.cpp"
)
file(GLOB DELTA_X_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/device/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/sdk/*.h"
)
file(GLOB DELTA_X_FORMS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui"
)

qt_add_executable(DeltaRobotSoftware
    WIN32
    MACOSX_BUNDLE
    MANUAL_FINALIZATION
    ${DELTA_X_SOURCES}
    ${DELTA_X_HEADERS}
    ${DELTA_X_FORMS}
    resource.qrc
)

target_include_directories(DeltaRobotSoftware PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/device"
    "${CMAKE_CURRENT_SOURCE_DIR}/sdk"
)

target_compile_definitions(DeltaRobotSoftware PRIVATE
    DELTA_X_VERSION_STRING="${PROJECT_VERSION}"
)

target_link_libraries(DeltaRobotSoftware PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::SerialPort
    Qt6::Network
    Qt6::PrintSupport
    Qt6::Multimedia
    Qt6::Svg
    Qt6::SvgWidgets
    Qt6::Concurrent
    DeltaX::OpenCV
)

if(MSVC)
    target_compile_options(DeltaRobotSoftware PRIVATE
        /Zc:__cplusplus
        /permissive-
        /bigobj
        /FS
        $<$<CONFIG:Debug>:/Z7>
    )
endif()

set_target_properties(DeltaRobotSoftware PROPERTIES
    MACOSX_BUNDLE_BUNDLE_NAME "Delta X Software"
    MACOSX_BUNDLE_GUI_IDENTIFIER "deltaxrobotics.DeltaRobotSoftware"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/Info.plist"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    MACOSX_BUNDLE_BUNDLE_VERSION "${PROJECT_VERSION}"
)

include(GNUInstallDirs)
install(TARGETS DeltaRobotSoftware
    BUNDLE DESTINATION .
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
install(FILES version.json DESTINATION "${CMAKE_INSTALL_DATADIR}/DeltaXSoftware")
install(FILES
    README.md
    LICENSE
    NOTICE
    THIRD_PARTY_NOTICES.md
    licenses/OpenCV-notice.md
    licenses/Qt-runtime-notice.md
    DESTINATION "${CMAKE_INSTALL_DATADIR}/DeltaXSoftware"
)
install(DIRECTORY docs/
    DESTINATION "${CMAKE_INSTALL_DATADIR}/DeltaXSoftware/docs"
    FILES_MATCHING
    PATTERN "*.md"
    PATTERN "*.png"
    PATTERN "*.docx"
)
install(DIRECTORY script-example/multi-robot-sorting/
    DESTINATION "${CMAKE_INSTALL_DATADIR}/DeltaXSoftware/examples/multi-robot-sorting"
)

# OpenCV's official Windows package exposes imported libraries but its runtime
# DLL is not copied by windeployqt. CPack artifacts need it next to the app.
# The separately audited public packager still performs its own pinned-runtime
# verification and does not depend on this contributor-package rule.
if(WIN32 AND OpenCV_LIB_PATH)
    file(GLOB DELTA_X_OPENCV_RUNTIME_DLLS CONFIGURE_DEPENDS
        "${OpenCV_LIB_PATH}/../bin/opencv_world*.dll"
    )
    list(FILTER DELTA_X_OPENCV_RUNTIME_DLLS EXCLUDE REGEX "d\\.dll$")
    if(DELTA_X_OPENCV_RUNTIME_DLLS)
        install(FILES ${DELTA_X_OPENCV_RUNTIME_DLLS}
            DESTINATION "${CMAKE_INSTALL_BINDIR}")
    else()
        message(WARNING
            "OpenCV runtime DLL was not found next to ${OpenCV_LIB_PATH}; "
            "the contributor package may require OpenCV on PATH")
    endif()
endif()

option(DELTA_X_BUILD_INDUSTRIAL_CAMERA_PLUGIN
    "Build the optional Basler/Hikrobot industrial camera plugin" OFF)
option(DELTA_X_ALLOW_LEGACY_VENDOR_SDKS
    "Allow camera plugin builds against quarantined vendored SDK snapshots" OFF)
option(DELTA_X_BUILD_REFERENCE_PLUGIN
    "Build the API v3 reference inspection plugin" OFF)
option(DELTA_X_BUILD_BLOCK_PROGRAMMING_PLUGIN
    "Build the native block programming plugin" ON)

if(DELTA_X_BUILD_BLOCK_PROGRAMMING_PLUGIN)
    add_subdirectory(plugin/BlockProgramming)
endif()

if(DELTA_X_BUILD_REFERENCE_PLUGIN)
    add_subdirectory(sdk/examples/inspection-plugin)
endif()

if(DELTA_X_BUILD_INDUSTRIAL_CAMERA_PLUGIN)
    if(NOT WIN32)
        message(FATAL_ERROR
            "The industrial camera plugin currently supports Windows SDKs only")
    endif()
    add_subdirectory(plugin/IndustrialCamera)
endif()

qt_finalize_executable(DeltaRobotSoftware)

# Copy Qt plugins and runtime dependencies into install/package trees when the
# selected shared Qt build supports the deployment API. Distribution-provided
# Qt 6.2 Linux kits remain valid and produce a system-dependent TGZ.
if(COMMAND qt_generate_deploy_app_script)
    qt_generate_deploy_app_script(
        TARGET DeltaRobotSoftware
        OUTPUT_SCRIPT DELTA_X_QT_DEPLOY_SCRIPT
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT "${DELTA_X_QT_DEPLOY_SCRIPT}")
endif()

set(CPACK_PACKAGE_NAME "DeltaXSoftware")
set(CPACK_PACKAGE_VENDOR "Delta X Robotics")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
    "Control and programming platform for Delta robots")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_FILE_NAME
    "DeltaXSoftware-${PROJECT_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_VERBATIM_VARIABLES YES)
if(WIN32)
    set(CPACK_GENERATOR "ZIP")
elseif(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_VOLUME_NAME "Delta X Software ${PROJECT_VERSION}")
else()
    set(CPACK_GENERATOR "TGZ")
endif()
include(CPack)
