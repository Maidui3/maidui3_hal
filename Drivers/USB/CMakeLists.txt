
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(USB_firm STATIC
    src/mUSB_stack.cpp
    src/mUSB_Request.cpp
    Descriptor/src/mUSB_GetDescriptor.cpp
)

target_include_directories(USB_firm PUBLIC
    include
    Descriptor/include
)

if(mUSB_BUILD_CDC)
    add_subdirectory(Class/CDC)
    target_link_libraries(USB_firm PUBLIC USB_CDC_firm)
endif()

if(mUSB_BUILD_HID)
    add_subdirectory(Class/HID)
    target_link_libraries(USB_firm PUBLIC USB_HID_firm)
endif()

target_compile_features(USB_firm PUBLIC cxx_std_17)

target_link_libraries(USB_firm PUBLIC stm32cubemx)
 