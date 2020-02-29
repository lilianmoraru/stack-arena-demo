cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(stacked_arena)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/pub>"
        "$<INSTALL_INTERFACE:include>"
)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE ${PROJECT_NAME})
