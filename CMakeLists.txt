cmake_minimum_required(VERSION 3.24)
project(MAGISTERI)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_COMPILER "C:/MinGW/x86_64-8.1.0-release-win32-seh-rt_v6-rev0/bin/gcc.exe") # Set the path to your g++ executable
set(CMAKE_C_COMPILER "C:/MinGW/x86_64-8.1.0-release-win32-seh-rt_v6-rev0/bin/g++.exe")    # Set the path to your gcc executable


add_executable(MAGISTERI main.c)
# Set optimization flags
target_compile_options(MAGISTERI PRIVATE -O3)

