cmake_minimum_required(VERSION 3.10)

project(DragDropSDL2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the directories where CMake can find the SDL2 headers and libraries
set(SDL2_PATH "${CMAKE_SOURCE_DIR}/lib/SDL2")
set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
set(SDL2_LIBRARY_DIR "${SDL2_PATH}/lib/x64") # Assuming you're targeting 64-bit

# Add the SDL2 directories to the project
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIBRARY_DIR})

add_definitions(-DSDL_MAIN_HANDLED)

# Add the source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(DragDrop WIN32 ${SOURCES})

# Link the SDL2 libraries
target_link_libraries(DragDrop SDL2.lib SDL2main.lib)

