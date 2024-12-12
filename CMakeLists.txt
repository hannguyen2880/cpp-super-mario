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
find_package(nlohmann_json 3.11.2 REQUIRED)
find_package(glfw3 3.4 REQUIRED)

link_directories(/opt/homebrew/Cellar/box2d/2.4.2/lib)
# Include directories
include_directories(${raylib_INCLUDE_DIRS})
include_directories(include)
include_directories(/opt/homebrew/Cellar/box2d/2.4.2/include)
include_directories(external/raylib-cpp/include)
include_directories(external/tileson/include)
include_directories(external/pocketlzma/src)
include_directories(external/pocketlzma)

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
    box2d
    nlohmann_json::nlohmann_json
    glfw
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