cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(mSPI_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(mSPI_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mSPI.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${mSPI_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${mSPI_Include_Dirs})
