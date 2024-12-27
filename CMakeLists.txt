cmake_minimum_required(VERSION 3.31.2)

set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include dependencies and compiler options
include(${CMAKE_SOURCE_DIR}/dependencies.cmake)
# include(${CMAKE_SOURCE_DIR}/compiler_options.cmake)

# Define variables for common directories
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

# Set the CMake module path to include custom modules and tmxlite's FindTMXLITE.cmake
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${TMXLITE_MODULE_PATH})

project(super-mario LANGUAGES CXX)

# Find packages
set(REQUIRED_PACKAGES
    box2d
    nlohmann_json
    opengl
    raylib
    tinyfiledialogs
    tmx
)

foreach(PKG ${REQUIRED_PACKAGES})
    find_package(${PKG} CONFIG REQUIRED)
endforeach()

# Find additional packages that do not have CONFIG files or are header-only
find_package(TMXLITE REQUIRED)
find_path(RAYGUI_INCLUDE_DIRS "raygui.h")

# Setting OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Setting Raylib
find_package(raylib 3.5.0 QUIET) # Let CMake search for a raylib-config.cmake
if (NOT raylib_FOUND)
    # Build raylib from source
    message(STATUS "raylib not found, fetching from source...")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Setting TMXLITE
find_package(TMXLITE REQUIRED)
if (NOT TMXLITE_FOUND)
    message(FATAL_ERROR "tmxlite not found! Ensure it's installed and properly set.")
endif()

# Collect source files
file(GLOB_RECURSE SOURCES_CPP "${PROJECT_SOURCE_DIR}/*.cpp")

# Create the executable with source files
add_executable(${PROJECT_NAME} ${SOURCES_CPP})

# Use target_include_directories for the executable
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${RAYGUI_INCLUDE_DIRS}
)

# Define preprocessor macros
target_compile_definitions(${PROJECT_NAME} PRIVATE
    POCKETLZMA_LZMA_C_DEFINE
    RAYGUI_IMPLEMENTATION
    RAYLIB_TMX_IMPLEMENTATION
)

# Link libraries to the executable
target_link_libraries(${PROJECT_NAME} PRIVATE
    box2d::box2d
    ECS
    nlohmann_json::nlohmann_json
    OpenGL::GL
    pocketlzma
    raylib::raylib
    raylib_cpp
    raylib_tmx
    tinyfiledialogs::tinyfiledialogs
    tmx::tmx
    TMXLITE
)

# Ensure C++17 features are available
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Post-build commands for copying DLLs and assets
if(MSVC)
    file(GLOB DLLS "${CMAKE_PREFIX_PATH}/../bin/*.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLLS}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_BINARY_DIR}/assets
)

# Organize source files into subdirectories and create corresponding CMake targets
add_subdirectory(src)
