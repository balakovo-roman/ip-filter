cmake_minimum_required(VERSION 3.28)

add_subdirectory(ip)
add_subdirectory(version)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ip_lib)

install_binary(${PROJECT_NAME})
