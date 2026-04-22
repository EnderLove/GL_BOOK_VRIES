cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find dependencies
find_package(glfw3 REQUIRED)
find_package(Threads REQUIRED)

# 2. CREATE THE TARGET FIRST (The "Bricks")
# This defines that "getStarted" exists
add_executable(test
    src/main.cpp 
    src/shader.cpp
    src/load2DTexture.cpp
    src/gameTextures.cpp
    src/camera.cpp
    src/glad.c
    src/model.cpp
    src/mesh.cpp
    imgui/imgui.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_impl_opengl3_loader.h
)

# 3. NOW apply settings to that target (The "Paint")
target_include_directories(test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)

# DEBUGGING POWER-UPS
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(test PRIVATE -g -O0 -fsanitize=address)
    target_link_libraries(test PRIVATE -fsanitize=address)
endif()

# 4. Link the libraries
target_link_libraries(test
    glfw 
    ${CMAKE_THREAD_LIBS_INIT} 
    ${CMAKE_DL_LIBS} 
    GL
    assimp
)
