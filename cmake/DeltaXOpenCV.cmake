# Resolve OpenCV through its CMake package when available. The legacy Windows
# snapshot has no OpenCVConfig.cmake, so it is exposed through an interface
# target as a controlled fallback.
add_library(deltax_opencv INTERFACE)
add_library(DeltaX::OpenCV ALIAS deltax_opencv)

if(WIN32 AND NOT OpenCV_DIR AND
   EXISTS "${PROJECT_SOURCE_DIR}/3rd-party/opencv/build/include/opencv2/core.hpp")
    set(_deltax_default_opencv_root "${PROJECT_SOURCE_DIR}/3rd-party/opencv")
else()
    set(_deltax_default_opencv_root "")
endif()

set(DELTA_X_OPENCV_ROOT "${_deltax_default_opencv_root}" CACHE PATH
    "Legacy OpenCV tree used when OpenCVConfig.cmake is unavailable")
set(DELTA_X_OPENCV_WORLD_VERSION "400" CACHE STRING
    "opencv_world suffix in the legacy Windows tree")

if(DELTA_X_OPENCV_ROOT)
    find_path(DELTA_X_OPENCV_INCLUDE_DIR
        NAMES opencv2/core.hpp
        HINTS "${DELTA_X_OPENCV_ROOT}"
        PATH_SUFFIXES include build/include
        NO_DEFAULT_PATH
    )
    find_library(DELTA_X_OPENCV_RELEASE_LIBRARY
        NAMES "opencv_world${DELTA_X_OPENCV_WORLD_VERSION}"
        HINTS "${DELTA_X_OPENCV_ROOT}"
        PATH_SUFFIXES lib x64/vc17/lib x64/vc16/lib x64/vc15/lib
                      build/x64/vc17/lib build/x64/vc16/lib build/x64/vc15/lib
        NO_DEFAULT_PATH
    )
    find_library(DELTA_X_OPENCV_DEBUG_LIBRARY
        NAMES "opencv_world${DELTA_X_OPENCV_WORLD_VERSION}d"
        HINTS "${DELTA_X_OPENCV_ROOT}"
        PATH_SUFFIXES lib x64/vc17/lib x64/vc16/lib x64/vc15/lib
                      build/x64/vc17/lib build/x64/vc16/lib build/x64/vc15/lib
        NO_DEFAULT_PATH
    )

    if(NOT DELTA_X_OPENCV_INCLUDE_DIR OR NOT DELTA_X_OPENCV_RELEASE_LIBRARY)
        message(FATAL_ERROR
            "DELTA_X_OPENCV_ROOT does not contain the expected headers and "
            "opencv_world${DELTA_X_OPENCV_WORLD_VERSION} library: "
            "${DELTA_X_OPENCV_ROOT}")
    endif()

    target_include_directories(deltax_opencv INTERFACE
        "${DELTA_X_OPENCV_INCLUDE_DIR}"
    )
    if(DELTA_X_OPENCV_DEBUG_LIBRARY)
        target_link_libraries(deltax_opencv INTERFACE
            "$<$<CONFIG:Debug>:${DELTA_X_OPENCV_DEBUG_LIBRARY}>"
            "$<$<NOT:$<CONFIG:Debug>>:${DELTA_X_OPENCV_RELEASE_LIBRARY}>"
        )
    else()
        target_link_libraries(deltax_opencv INTERFACE
            "${DELTA_X_OPENCV_RELEASE_LIBRARY}"
        )
        message(WARNING "OpenCV debug library not found; all configurations use release")
    endif()
    message(STATUS "OpenCV: legacy tree ${DELTA_X_OPENCV_ROOT}")
else()
    find_package(OpenCV REQUIRED)
    if(OpenCV_VERSION VERSION_LESS "4.0")
        message(FATAL_ERROR "Delta X Software requires OpenCV 4.0 or newer")
    endif()
    target_include_directories(deltax_opencv INTERFACE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(deltax_opencv INTERFACE ${OpenCV_LIBS})
    message(STATUS "OpenCV: package ${OpenCV_VERSION}")
endif()
