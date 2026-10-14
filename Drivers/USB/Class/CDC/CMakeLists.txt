
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(USB_CDC_firm STATIC
    src/mUSB_CDC.cpp
)

target_include_directories(USB_CDC_firm PUBLIC
    include
)

target_compile_features(USB_CDC_firm PUBLIC cxx_std_17)

target_link_libraries(USB_CDC_firm PRIVATE stm32cubemx)
target_link_libraries(USB_CDC_firm PRIVATE USB_firm)