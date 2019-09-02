cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(stacked_arena)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:"${CMAKE_CURRENT_SOURCE_DIR}/pub">
        $<INSTALL_INTERFACE:include>
)
