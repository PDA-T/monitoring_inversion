cmake_minimum_required(VERSION 3.17)
project(monitoring_inversion)

set(CMAKE_CXX_STANDARD 14)

# Add WIN32 execution level for GUI application
add_executable(monitoring_inversion WIN32 main.cpp)

# Link to user32.lib for Windows API functions
target_link_libraries(monitoring_inversion user32)