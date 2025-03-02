include(CTest)

message(STATUS "Build testing: " ${BUILD_TESTING})

if(NOT BUILD_TESTING)
    return()
endif()

set(FETCHCONTENT_QUIET OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(googletest)

function(make_main_test testname sources libraries)
    set(TEST_NAME "test_${testname}")

    add_executable(${TEST_NAME} ${sources})

    target_link_libraries(${TEST_NAME}
        PRIVATE
        ${libraries}
        gmock
        gtest
        gtest_main)

    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endfunction()