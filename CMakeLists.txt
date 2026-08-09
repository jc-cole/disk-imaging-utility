cmake_minimum_required(VERSION 3.15)

# Set the project name, version, and language
project(MyProject 
        VERSION 1.0.0 
        LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# default to including debug symbols
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Add executables or libraries
add_executable(imager
    src/main.cpp
    src/BlockDevice.cpp
    src/BlockDeviceManager.cpp
)

# Include directories (where header files are located)
target_include_directories(imager PUBLIC include)