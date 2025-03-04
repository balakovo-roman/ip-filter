option(ENABLE_COVERAGE "Enable generating coverage report: " OFF)

if(NOT ENABLE_COVERAGE)
    return()
endif()

set(COVERAGE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/coverage-report" CACHE PATH "Path for the generated coverage report")

add_custom_target(coverage
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${COVERAGE_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${COVERAGE_OUTPUT_DIRECTORY}
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND gcovr -r ${CMAKE_SOURCE_DIR} --filter ${CMAKE_SOURCE_DIR}/source/ --exclude .*main.cpp --exclude .*_test.cpp --html --html-details -o ${COVERAGE_OUTPUT_DIRECTORY}/coverage.html
    COMMAND echo "Coverage report generated successfully!"
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    COMMENT "Generating coverage report"
    VERBATIM
)
