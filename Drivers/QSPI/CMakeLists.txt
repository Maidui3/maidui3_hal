
cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

add_library(QSPI_firm STATIC
    mQSPI_manager.cpp
    
)

target_include_directories(QSPI_firm PUBLIC
    include/..
)

target_compile_features(QSPI_firm PUBLIC cxx_std_17)

target_link_libraries(QSPI_firm PRIVATE stm32cubemx)
