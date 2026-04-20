cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(IS25LP064D-JLLE_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(IS25LP064D-JLLE_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/IS25LP064D-JLLE.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${IS25LP064D-JLLE_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${IS25LP064D-JLLE_Include_Dirs})
