cmake_minimum_required(VERSION 3.28)

project("helloworld"
    VERSION 0.0.${PROJECT_VERSION_PATCH}
    LANGUAGES CXX)

message("Project version: " ${PROJECT_VERSION})

# ---- Testing ----
include(cmake/testing.cmake)

# ---- Install rules ----
include(cmake/install-rules.cmake)

# ---- Declare sources ----
add_subdirectory(source)

# ---- Packing ----
include(cmake/pack-rules.cmake)