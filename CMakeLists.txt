cmake_minimum_required(VERSION 3.15)

project(MyProject 
        VERSION 1.0.0 
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# 1. Create a library for your core application logic
add_library(imager_core STATIC
    src/BlockDevice.cpp
    src/BlockDeviceManager.cpp
    src/LoopDiskUtils.cpp
)
target_include_directories(imager_core PUBLIC include)

# 2. Keep the main application executable clean
add_executable(imager src/main.cpp)
target_link_libraries(imager PRIVATE imager_core)

# 3. Fetch and configure GoogleTest cleanly
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2  # Safer and faster than pulling the changing 'main' branch
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)
# For Windows MSVC runtime compatibility 
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 4. Configure the test executable
add_executable(imager_tests test/main.cpp)
target_link_libraries(imager_tests PRIVATE 
    imager_core
    gtest_main     # Automatically provides a main() entry point for gtest
)

# 5. Enable automatic test discovery for CTest
include(GoogleTest)
gtest_discover_tests(imager_tests)
