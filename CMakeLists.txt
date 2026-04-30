cmake_minimum_required(VERSION 4.2)
project(gasm)

set(CMAKE_CXX_STANDARD 26)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(gasm main.cpp ${SRC_FILES})

# --- ARM64 FIX ---
if (MSVC AND CMAKE_VS_PLATFORM_NAME STREQUAL "ARM64")
    target_link_libraries(gasm PRIVATE
            windowsapp
            runtimeobject
    )
endif()
