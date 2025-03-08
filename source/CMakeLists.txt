cmake_minimum_required(VERSION 3.28)

add_subdirectory(ip)
add_subdirectory(version)

add_executable(${PROJECT_NAME} main.cpp)

install_binary(${PROJECT_NAME})
