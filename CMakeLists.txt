cmake_minimum_required(VERSION 3.20)
project(BDEVPhysicsEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional: Treat warnings as errors
# add_compile_options(-Wall -Wextra -Werror)

# Find SDL2 with pkg-config
find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# Include directories
include_directories(include ${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIBRARY_DIRS})

# Source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Executable
add_executable(physics_engine ${SOURCES})

# Link SDL2
target_link_libraries(physics_engine ${SDL2_LIBRARIES})

