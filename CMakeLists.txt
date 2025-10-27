cmake_minimum_required(VERSION 3.15)
project(Clicker C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_path(RL_INCLUDE_DIR NAMES raylib.h PATHS /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})
# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find raylib
find_package(raylib 5.0 QUIET)

if (NOT raylib_FOUND)
    # If raylib is not found, fetch it from GitHub
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0
    )
    FetchContent_MakeAvailable(raylib)
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/includes)

# Add executable
add_executable(${PROJECT_NAME} 
    src/main.c
)

# Link raylib
target_link_libraries(${PROJECT_NAME} raylib)

# macOS specific settings
if(APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit" "-framework Cocoa" "-framework OpenGL" "-framework ApplicationServices")
endif()


# Copy assets to build directory if you have any
# file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
