cmake_minimum_required(VERSION 3.16)
project(mario_maker)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# Setting Raylib

# Set this to the minimal version you want to support
find_package(raylib 3.5.0 QUIET) # Let CMake search for a raylib-config.cmake
find_package(TMXLITE REQUIRED)

SET(TMXLITE_INCLUDE_DIR "/usr/local/include/tmxlite")
SET(TMXLITE_LIBRARIES "/usr/local/lib/libtmxlite.so")

# You could change the QUIET above to REQUIRED and remove this if() clause
# This part downloads raylib and builds it if it's not installed on your system
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples

        # build raylib
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()

endif()

file(GLOB src
        "src/*.cpp"
        "src/systems/*.cpp"
        "src/renderers/*.cpp"
        "src/*/*.cpp"
        "src/*/*/*.cpp")
add_executable(mario_maker ${src})

include_directories(
        include
        ${TMXLITE_INCLUDE_DIR})

include_directories(src)
include_directories(src/systems)
include_directories(src/renderers/*.h)
include_directories(src/components/*.h)
include_directories(src/screens)
include_directories(src/audio)
include_directories(src/events)
include_directories(src/game)
include_directories(src/game/State)
include_directories(src/map)
include_directories(src/ui)


target_link_libraries(mario_maker raylib ${TMXLITE_LIBRARIES})
