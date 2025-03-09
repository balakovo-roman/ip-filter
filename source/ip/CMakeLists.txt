cmake_minimum_required(VERSION 3.28)

set(IP_LIB ip)

add_library(${IP_LIB} STATIC
    filter.cpp
    ipv4.cpp
    utils.cpp
)

set(TEST_SOURCES
    filter_test.cpp
    ipv4_test.cpp
    utils_test.cpp
)

make_main_test(ip "${TEST_SOURCES}" "${IP_LIB}")