cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compilation flags
set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# Set project name
project(SnakeGame)

# Set the module path for additional CMake modules if needed
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Find SDL2
find_package(SDL2 REQUIRED)

# Include directories for SDL2 and source files
include_directories(${SDL2_INCLUDE_DIRS} src)

# Create the executable
add_executable(SnakeGame 
    src/main.cpp 
    src/game.cpp 
    src/controller.cpp 
    src/renderer.cpp 
    src/snake.cpp 
    src/food.cpp
)

# Strip whitespace from the SDL2_LIBRARIES variable
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)

# Link SDL2 libraries to the executable
target_link_libraries(SnakeGame PRIVATE ${SDL2_LIBRARIES})

# Find and link pthread for threading support
find_package(Threads REQUIRED)  # Find Threads package
target_link_libraries(SnakeGame PRIVATE ${CMAKE_THREAD_LIBS_INIT})  # Link pthread
