cmake_minimum_required(VERSION 3.28)

set(IP_LIB ip)

add_library(${IP_LIB} STATIC ipv4.cpp)

make_main_test(ip ipv4_test.cpp ${IP_LIB})