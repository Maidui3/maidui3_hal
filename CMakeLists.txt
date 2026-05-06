cmake_minimum_required(VERSION 3.22)

enable_language(C CXX ASM)

#add_subdirectory(Drivers/FDCAN)
add_subdirectory(Drivers/QSPI)
add_subdirectory(Drivers/USB)

add_subdirectory(Middleware/FLASH/IS25LP064D-JLLE)

#add_subdirectory(API/XCAN_API)
