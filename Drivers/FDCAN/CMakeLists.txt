cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(mXCAN_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(mXCAN_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mXCAN_manager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mXCAN.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${mXCAN_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${mXCAN_Include_Dirs})
