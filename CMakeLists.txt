cmake_minimum_required(VERSION 3.10)
project(OpenGL_Experiment_Template)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 OpenGL
find_package(OpenGL REQUIRED)

# GLAD 库设置
set(GLAD_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/glad/include)
set(GLAD_SOURCE ${CMAKE_SOURCE_DIR}/glad/src/glad.c)

# GLFW 库设置
set(GLFW_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/vcpkg/glfw/include)
if(NOT EXISTS ${GLFW_INCLUDE_DIR}/GLFW/glfw3.h)
    message(FATAL_ERROR "GLFW header file not found at ${GLFW_INCLUDE_DIR}/GLFW/glfw3.h")
endif()
set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/vcpkg/glfw/build/src/libglfw3.a)
if(NOT EXISTS ${GLFW_LIBRARY})
    message(FATAL_ERROR "GLFW library file not found at ${GLFW_LIBRARY}")
endif()

# 包含头文件目录
include_directories(
    .
    ${GLAD_INCLUDE_DIR}
    ${GLFW_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/glm
    ${CMAKE_SOURCE_DIR}/glm/glm
    ${OPENGL_INCLUDE_DIR}
)

# 源文件
set(SOURCE_FILES
    main.cpp
    Shader.cpp
    ${GLAD_SOURCE}
)

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# 链接库
target_link_libraries(${PROJECT_NAME}
    ${GLFW_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${CMAKE_DL_LIBS}
    ws2_32
    winmm
    gdi32
)
