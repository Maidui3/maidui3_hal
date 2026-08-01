
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(USB_firm STATIC
    mUSB.cpp
    mUSB_stack.cpp
    Descriptor/mUSB_Descriptor.cpp
    
)

target_include_directories(USB_firm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Descriptor
)

target_compile_features(USB_firm PUBLIC cxx_std_17)

target_link_libraries(USB_firm PRIVATE stm32cubemx)
 