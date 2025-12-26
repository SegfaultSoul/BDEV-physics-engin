cmake_minimum_required(VERSION 3.20)
project(BDEVPhysicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- SDL2 -------------------------------------------------

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

# ---- Sources ---------------------------------------------

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

add_executable(physics_engine ${SOURCES})

# ---- Includes (THIS IS THE IMPORTANT PART) ----------------

target_include_directories(physics_engine
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${SDL2_INCLUDE_DIRS}
)

# ---- Compile flags ----------------------------------------

target_compile_options(physics_engine
    PRIVATE
        ${SDL2_CFLAGS_OTHER}
)

# ---- Link -------------------------------------------------

target_link_libraries(physics_engine
    PRIVATE
        ${SDL2_LIBRARIES}
)
