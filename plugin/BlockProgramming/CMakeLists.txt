set(_deltax_block_programming_sources
    BlockProgram.cpp
    BlockProgram.h
    BlockCanvas.cpp
    BlockCanvas.h
    BlockProgrammingPanel.cpp
    BlockProgrammingPanel.h
    BlockProgrammingPlugin.cpp
    BlockProgrammingPlugin.h
    BlockProgrammingPlugin.json
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXCommandProvider.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXHostContext.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPanelProvider.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPermissions.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPluginMetadata.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPluginV2.h"
    "${PROJECT_SOURCE_DIR}/sdk/DeltaXPluginV3.h"
)

add_library(BlockProgrammingPlugin MODULE ${_deltax_block_programming_sources})
target_include_directories(BlockProgrammingPlugin PRIVATE
    "${PROJECT_SOURCE_DIR}/sdk"
)
target_link_libraries(BlockProgrammingPlugin PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

if(MSVC)
    target_compile_options(BlockProgrammingPlugin PRIVATE
        /Zc:__cplusplus
        /permissive-
        /FS
    )
endif()

set_target_properties(BlockProgrammingPlugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugin"
)

if(APPLE)
    set(_deltax_block_programming_install_destination
        "DeltaRobotSoftware.app/Contents/PlugIns/deltax")
else()
    set(_deltax_block_programming_install_destination
        "${CMAKE_INSTALL_BINDIR}/plugin")
endif()

install(TARGETS BlockProgrammingPlugin
    LIBRARY DESTINATION "${_deltax_block_programming_install_destination}"
    RUNTIME DESTINATION "${_deltax_block_programming_install_destination}"
)
