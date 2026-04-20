cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(mQSPI_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(mQSPI_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/mQSPI_manager.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${mQSPI_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${mQSPI_Include_Dirs})
