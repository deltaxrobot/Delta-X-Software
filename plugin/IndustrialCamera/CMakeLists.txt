set(DELTA_X_PYLON_ROOT "" CACHE PATH
    "Basler pylon Development directory (contains include/ and lib/x64/)")
set(DELTA_X_MVS_ROOT "" CACHE PATH
    "Hikrobot MVS Development directory (contains Includes/ and Libraries/win64/)")

if(DELTA_X_ALLOW_LEGACY_VENDOR_SDKS)
    if(NOT DELTA_X_PYLON_ROOT)
        set(DELTA_X_PYLON_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/pylon")
    endif()
    if(NOT DELTA_X_MVS_ROOT)
        set(DELTA_X_MVS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/3rd-party/mvs")
    endif()
    message(WARNING
        "Building against quarantined legacy camera SDK files. "
        "Do not redistribute them in public artifacts.")
endif()

if(NOT DELTA_X_PYLON_ROOT OR NOT DELTA_X_MVS_ROOT)
    message(FATAL_ERROR
        "Industrial camera plugin requires -DDELTA_X_PYLON_ROOT=<pylon Development> "
        "and -DDELTA_X_MVS_ROOT=<MVS Development>. For local migration testing "
        "only, use -DDELTA_X_ALLOW_LEGACY_VENDOR_SDKS=ON.")
endif()

find_path(DELTA_X_PYLON_INCLUDE_DIR
    NAMES pylon/PylonIncludes.h
    HINTS "${DELTA_X_PYLON_ROOT}"
    PATH_SUFFIXES include
    NO_DEFAULT_PATH
    REQUIRED
)
find_path(DELTA_X_MVS_INCLUDE_DIR
    NAMES MvCameraControl.h
    HINTS "${DELTA_X_MVS_ROOT}"
    PATH_SUFFIXES Includes include
    NO_DEFAULT_PATH
    REQUIRED
)
find_library(DELTA_X_MVS_LIBRARY
    NAMES MvCameraControl
    HINTS "${DELTA_X_MVS_ROOT}"
    PATH_SUFFIXES Libraries/win64 lib/x64 lib
    NO_DEFAULT_PATH
    REQUIRED
)

set(_deltax_pylon_library_hints
    "${DELTA_X_PYLON_ROOT}/lib/x64"
    "${DELTA_X_PYLON_ROOT}/lib64"
    "${DELTA_X_PYLON_ROOT}/lib"
)
foreach(_library IN ITEMS
        PylonBase_v9
        PylonUtility_v9
        PylonGUI_v9
        GCBase_MD_VC141_v3_1_Basler_pylon
        GenApi_MD_VC141_v3_1_Basler_pylon)
    string(TOUPPER "${_library}" _variable_name)
    find_library(DELTA_X_${_variable_name}_LIBRARY
        NAMES "${_library}"
        HINTS ${_deltax_pylon_library_hints}
        NO_DEFAULT_PATH
        REQUIRED
    )
    list(APPEND DELTA_X_PYLON_LIBRARIES "${DELTA_X_${_variable_name}_LIBRARY}")
endforeach()

set(_deltax_plugin_sources
    CameraReader.cpp
    IndustrialCameraPlugin.cpp
    form.cpp
    xcam.cpp
    xcambasler.cpp
    xcamhik.cpp
    xcammanager.cpp
    CameraReader.h
    ImageUnity.h
    IndustrialCameraPlugin.h
    form.h
    xcam.h
    xcambasler.h
    xcamhik.h
    xcammanager.h
    form.ui
    IndustrialCameraPlugin.json
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPlugin.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPluginV2.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPanelProvider.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXCommandProvider.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPluginMetadata.h"
)

add_library(IndustrialCameraPlugin MODULE ${_deltax_plugin_sources})

target_compile_definitions(IndustrialCameraPlugin PRIVATE
    QT_DISABLE_DEPRECATED_BEFORE=0x060000
)
target_include_directories(IndustrialCameraPlugin PRIVATE
    "${PROJECT_SOURCE_DIR}/sdk"
    "${DELTA_X_PYLON_INCLUDE_DIR}"
    "${DELTA_X_MVS_INCLUDE_DIR}"
)
target_link_libraries(IndustrialCameraPlugin PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    DeltaX::OpenCV
    "${DELTA_X_MVS_LIBRARY}"
    ${DELTA_X_PYLON_LIBRARIES}
)

if(MSVC)
    target_compile_options(IndustrialCameraPlugin PRIVATE
        /Zc:__cplusplus
        /permissive-
        /bigobj
        /FS
        /wd4828
    )
    target_link_options(IndustrialCameraPlugin PRIVATE
        /DELAYLOAD:MvCameraControl.dll
        /DELAYLOAD:GCBase_MD_VC141_v3_1_Basler_pylon.dll
        /DELAYLOAD:PylonUtility_v9.dll
        /DELAYLOAD:PylonBase_v9.dll
    )
    target_link_libraries(IndustrialCameraPlugin PRIVATE delayimp)
endif()

set_target_properties(IndustrialCameraPlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin"
)

install(TARGETS IndustrialCameraPlugin
    LIBRARY DESTINATION plugin
    RUNTIME DESTINATION plugin
)
