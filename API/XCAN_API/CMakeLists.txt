cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

set(XCAN_API_Include_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/4ch_MD_v1
    ${CMAKE_CURRENT_SOURCE_DIR}/USB_MainBoard_v1
)

set(XCAN_API_App_Dirs
    ${CMAKE_CURRENT_SOURCE_DIR}/4ch_MD_v1/4ch_MD_v1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/USB_MainBoard_v1/USB_MainBoard_v1.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${XCAN_API_App_Dirs})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${XCAN_API_Include_Dirs})
