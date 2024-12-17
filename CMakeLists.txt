cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(super-mario)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add definition for raygui implementation
add_definitions(-DRAYGUI_IMPLEMENTATION)

# Find raylib
find_package(raylib REQUIRED)
find_package(box2d REQUIRED)
find_package(TMX REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

link_directories(/opt/homebrew/Cellar/box2d/2.4.2/lib)
link_directories(/opt/homebrew/Cellar/tmx/1.10.0/lib)
link_directories(${CMAKE_SOURCE_DIR}/external/tmxlite/tmxlite/build)

# Include directories
include_directories(${raylib_INCLUDE_DIRS})
include_directories(include)
include_directories(src)
include_directories(/opt/homebrew/Cellar/box2d/2.4.2/include)
include_directories(external/raylib-cpp/include)
include_directories(/opt/homebrew/Cellar/tmx/1.10.0/include)
include_directories(external/pocketlzma/src)
include_directories(external/pocketlzma)
include_directories(external/tmxlite/tmxlite/include)
include_directories(external/tmxlite/tmxlite/include/tmxlite)
include_directories(external/ECS)
include_directories(external/raylib-tmx/include)
add_subdirectory(external/raylib-tmx)

# Source files
file(GLOB_RECURSE SOURCES_CPP 
    "src/*.cpp"
    "src/*/*.cpp"
    "src/*/*/*.cpp"
)

file(GLOB_RECURSE SOURCES_H
    "include/*.h"
    "include/*/*.h"
    "include/*/*/*.h"
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES_CPP} ${SOURCES_H})

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    raylib
    raylib-tmx
    box2d
    nlohmann_json::nlohmann_json
    TMX
    ${CMAKE_SOURCE_DIR}/external/tmxlite/tmxlite/build/libtmxlite.dylib
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
if (MSVC)
    file(GLOB_RECURSE DLLS "${raylib_DIR}/../../bin/*.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        ${CMAKE_BINARY_DIR}/assets
    )

endif()