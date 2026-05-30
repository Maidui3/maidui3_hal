cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(mUSART_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(mUSART_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mUSART.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${mUSART_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${mUSART_Include_Dirs})
