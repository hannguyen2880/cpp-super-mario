include(FetchContent)

# ECS
set(ECS_LOCAL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/ECS")
if(EXISTS ${ECS_LOCAL_PATH})
    add_library(ECS INTERFACE)
    target_include_directories(ECS INTERFACE ${ECS_LOCAL_PATH})
else()
    FetchContent_Declare(ECS
        GIT_REPOSITORY https://github.com/redxdev/ECS.git
        HEADER_ONLY ON
    )
    FetchContent_MakeAvailable(ECS)
    add_library(ECS INTERFACE)
    target_include_directories(ECS INTERFACE ${ecs_SOURCE_DIR})
endif()

# single header
# If cloning from the repository fails, use a local path
set(POCKETLZMA_LOCAL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/pocketlzma")
if(EXISTS ${POCKETLZMA_LOCAL_PATH})
    add_library(pocketlzma INTERFACE)
    target_include_directories(pocketlzma INTERFACE ${POCKETLZMA_LOCAL_PATH})
else()
    FetchContent_Declare(pocketlzma
        GIT_REPOSITORY https://github.com/SSBMTonberry/pocketlzma.git
        GIT_TAG v1.0.0
        HEADER_ONLY ON
    )
    FetchContent_MakeAvailable(pocketlzma)
    add_library(pocketlzma INTERFACE)
    target_include_directories(pocketlzma INTERFACE ${pocketlzma_SOURCE_DIR})
endif()

# raylib-cpp
set(RAYLIB_CPP_LOCAL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/raylib-cpp")
if(EXISTS ${RAYLIB_CPP_LOCAL_PATH})
    add_library(raylib_cpp INTERFACE)
    target_include_directories(raylib_cpp INTERFACE ${RAYLIB_CPP_LOCAL_PATH})
else()
    FetchContent_Declare(raylib-cpp
        GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
        GIT_TAG v5.5.0
        HEADER_ONLY ON
    )
    FetchContent_MakeAvailable(raylib-cpp)
    add_library(raylib_cpp INTERFACE)
    target_include_directories(raylib_cpp INTERFACE ${raylib_cpp_SOURCE_DIR})
endif()

# raylib-tmx
set(RAYLIB_TMX_LOCAL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/raylib-tmx")
if(EXISTS ${RAYLIB_TMX_LOCAL_PATH})
    add_library(raylib_tmx INTERFACE)
    target_include_directories(raylib_tmx INTERFACE ${RAYLIB_TMX_LOCAL_PATH})
else()
    FetchContent_Declare(raylib-tmx
        GIT_REPOSITORY https://github.com/RobLoach/raylib-tmx.git
        HEADER_ONLY ON
    )
    FetchContent_MakeAvailable(raylib-tmx)
    add_library(raylib_tmx INTERFACE)
    target_include_directories(raylib_tmx INTERFACE ${raylib_tmx_SOURCE_DIR})
endif()

# tmxlite and add the path to FindTMXLITE.cmake to CMAKE_MODULE_PATH
set(TMXLITE_LOCAL_PATH "${CMAKE_CURRENT_LIST_DIR}/lib/tmxlite")
if(EXISTS ${TMXLITE_LOCAL_PATH})
    set(TMXLITE_MODULE_PATH ${TMXLITE_LOCAL_PATH}/cmake/modules)
else()
    FetchContent_Declare(tmxlite
        GIT_REPOSITORY https://github.com/fallahn/tmxlite.git
    )
    FetchContent_MakeAvailable(tmxlite)
    set(TMXLITE_MODULE_PATH ${tmxlite_SOURCE_DIR}/cmake/modules)
endif()
