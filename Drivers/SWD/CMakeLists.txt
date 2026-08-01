
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(SWD_USB_Protocol STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/SWD_USB_Protocol.cpp
)

target_include_directories(SWD_USB_Protocol PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(SWD_USB_Protocol PUBLIC cxx_std_17)

target_link_libraries(SWD_USB_Protocol PRIVATE stm32cubemx)
