cmake_minimum_required(VERSION 3.16)
project(gasm)

set(CMAKE_CXX_STANDARD 26)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(gasm main.cpp ${SRC_FILES} "src/codegen.h" "src/codegen.cpp")

# --- ARM64 FIX ---
if (MSVC AND CMAKE_VS_PLATFORM_NAME STREQUAL "ARM64")
    target_link_libraries(gasm PRIVATE
            windowsapp
            runtimeobject
    )
endif()
