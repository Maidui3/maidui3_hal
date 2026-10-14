
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(USB_HID_firm STATIC
    src/mUSB_HID.cpp
)

target_include_directories(USB_HID_firm PUBLIC
    include
)

target_compile_features(USB_HID_firm PUBLIC cxx_std_17)

target_link_libraries(USB_HID_firm PRIVATE stm32cubemx)
target_link_libraries(USB_HID_firm PUBLIC USB_firm)