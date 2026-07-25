
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(PID_app STATIC
    Proportional-Integral-Derivative.cpp
    
)

target_include_directories(PID_app PUBLIC
    include/..
)

target_compile_features(PID_app PUBLIC cxx_std_17)

target_link_libraries(PID_app PRIVATE stm32cubemx)
