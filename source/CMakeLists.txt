cmake_minimum_required(VERSION 3.28)

set(VERSION_LIB version)

add_library(${VERSION_LIB} STATIC version/version.cpp)
configure_file(version/config.h.in config.h)
target_include_directories(${VERSION_LIB} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

make_main_test(version version/version_test.cpp ${VERSION_LIB})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${VERSION_LIB})

install_binary(${PROJECT_NAME})
