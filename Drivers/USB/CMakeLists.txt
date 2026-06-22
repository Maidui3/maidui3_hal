cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(mUSB_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor
)

set(mUSB_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mUSB.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/mUSB_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor/mUSB_Descriptor.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${mUSB_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${mUSB_Include_Dirs})
