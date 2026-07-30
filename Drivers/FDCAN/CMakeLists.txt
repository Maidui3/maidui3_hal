
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(FDCAN_firm STATIC
    mXCAN_manager.cpp
    mXCAN.cpp
)

target_include_directories(FDCAN_firm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(FDCAN_firm PUBLIC cxx_std_17)

target_link_libraries(FDCAN_firm PRIVATE stm32cubemx)
