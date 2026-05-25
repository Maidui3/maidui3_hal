cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(FF_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(FF_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/Feed-forward.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${FF_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${FF_Include_Dirs})
