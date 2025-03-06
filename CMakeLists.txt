cmake_minimum_required(VERSION 3.28)

if(DEFINED ENV{PROJECT_VERSION_PATCH})
    set(PROJECT_VERSION_PATCH $ENV{PROJECT_VERSION_PATCH})
else()
    set(PROJECT_VERSION_PATCH 1)
endif()

project("helloworld"
    VERSION 0.0.${PROJECT_VERSION_PATCH}
    LANGUAGES CXX)

# ---- Testing ----
include(cmake/testing.cmake)

# ---- Coverage ----
include(cmake/coverage.cmake)

# ---- Install rules ----
include(cmake/install-rules.cmake)

# ---- Declare sources ----
add_subdirectory(source)

# ---- Packing ----
include(cmake/pack-rules.cmake)