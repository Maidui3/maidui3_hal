
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(USART_firm STATIC
    mUSART.cpp
    
)

target_include_directories(USART_firm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_features(USART_firm PUBLIC cxx_std_17)

target_link_libraries(USART_firm PRIVATE stm32cubemx)
