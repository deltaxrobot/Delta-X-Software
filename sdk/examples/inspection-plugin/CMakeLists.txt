cmake_minimum_required(VERSION 3.21)
project(DeltaXInspectionPlugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_plugin(DeltaXInspectionPlugin
    CLASS_NAME InspectionPlugin
    InspectionPlugin.cpp
    InspectionPlugin.h
    InspectionPlugin.json
)
target_include_directories(DeltaXInspectionPlugin PRIVATE "${CMAKE_CURRENT_LIST_DIR}/../..")
target_link_libraries(DeltaXInspectionPlugin PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
install(TARGETS DeltaXInspectionPlugin
    RUNTIME DESTINATION plugin
    LIBRARY DESTINATION plugin
)
