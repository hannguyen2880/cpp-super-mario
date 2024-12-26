# cmake_minimum_required(VERSION 3.16)
# project(mario_maker)

# set(CMAKE_CXX_STANDARD 14)

# SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# # Setting OpenGL
# find_package(OpenGL REQUIRED)
# if (OPENGL_FOUND)
#     include_directories(${OPENGL_INCLUDE_DIR})
# else()
#     message(FATAL_ERROR "OpenGL not found!")
# endif()

# # Setting Raylib
# find_package(raylib 3.5.0 QUIET) # Let CMake search for a raylib-config.cmake

# if (NOT raylib_FOUND) # If Raylib is not found, fetch and build it
#     include(FetchContent)

#     FetchContent_Declare(
#             raylib
#             URL https://github.com/raysan5/raylib/archive/master.tar.gz
#     )

#     FetchContent_GetProperties(raylib)
#     if (NOT raylib_POPULATED) # If not already downloaded, populate
#         set(FETCHCONTENT_QUIET NO)
#         FetchContent_Populate(raylib)

#         set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disable building Raylib examples
#         add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
#     endif()
# endif()

# # Setting TMXLITE
# find_package(TMXLITE REQUIRED)
# if (NOT TMXLITE_FOUND)
#     message(FATAL_ERROR "tmxlite not found! Ensure it's installed and properly set.")
# endif()

# # Add source files
# file(GLOB src
#         "src/*.cpp"
#         "src/systems/*.cpp"
#         "src/renderers/*.cpp")

# add_executable(mario_maker ${src})

# # Include directories for tmxlite and project-specific headers
# include_directories(
#         include
#         include/systems
#         include/renderers
#         /home/thinh/Source/Mario/mario-maker/include/tmxlite
#         ${OPENGL_INCLUDE_DIR}
# )

# # Link libraries
# target_link_libraries(mario_maker raylib ${OPENGL_gl_LIBRARY} /usr/local/lib/libtmxlite.so)

cmake_minimum_required(VERSION 3.16)
project(mario_maker)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

# Setting OpenGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
else()
    message(FATAL_ERROR "OpenGL not found!")
endif()

# Setting Raylib
find_package(raylib 3.5.0 QUIET) # Let CMake search for a raylib-config.cmake

if (NOT raylib_FOUND) # If Raylib is not found, fetch and build it
    include(FetchContent)

    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # If not already downloaded, populate
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)

        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Disable building Raylib examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Setting TMXLITE
find_package(TMXLITE REQUIRED)
if (NOT TMXLITE_FOUND)
    message(FATAL_ERROR "tmxlite not found! Ensure it's installed and properly set.")
endif()

# Add source files
file(GLOB src
        "src/*.cpp"
        "src/systems/*.cpp"
        "src/renderers/*.cpp"
        "src/*/*.cpp"
        "src/*/*/*.cpp"
        )

add_executable(mario_maker ${src})

# Include directories for tmxlite and project-specific headers
include_directories(
        include
        include/systems
        include/renderers
        include/tmxlite
        ${OPENGL_INCLUDE_DIR}
        
)
include_directories(src)
include_directories(src/systems/*)

# Link libraries
target_link_libraries(mario_maker raylib ${OPENGL_gl_LIBRARY} /usr/local/lib/libtmxlite.so)
