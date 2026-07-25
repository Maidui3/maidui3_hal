
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(FF_app STATIC
    Feed-forward.cpp
    
)

target_include_directories(Mlink_soft PUBLIC
    include/..
)

target_compile_features(FF_app PUBLIC cxx_std_17)

target_link_libraries(FF_app PRIVATE stm32cubemx)
