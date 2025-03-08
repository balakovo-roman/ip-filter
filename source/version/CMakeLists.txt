cmake_minimum_required(VERSION 3.28)

set(VERSION_LIB version)

add_library(${VERSION_LIB} STATIC version.cpp)
configure_file(config.hpp.in config.hpp)
target_include_directories(${VERSION_LIB} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

make_main_test(version version_test.cpp ${VERSION_LIB})