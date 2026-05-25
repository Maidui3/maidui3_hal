cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(PID_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(PID_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/Proportional-Integral-Derivative.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${PID_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PID_Include_Dirs})
