cmake_minimum_required(VERSION 3.14)
project(mapache CXX)

set(BOOST_ROOT "lib/boost_1_68_0")
find_package(Boost 1.68 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost REQUIRED COMPONENTS)
if(Boost_FOUND)
    include_directories(${BOOST_ROOT})
    message("-- Boost found: ${Boost_VERSION_STRING}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

set(BINARY ${CMAKE_PROJECT_NAME})

set(BINARY_FILES 
    src/main.cpp 
    src/utils/config_file_parser.cpp
    src/core/server/server.cpp
)

set (LIBRARY_FILES
    src/utils/config_file_parser.cpp
    src/core/server/server.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src/**)

add_executable(${BINARY} ${BINARY_FILES})
add_library(${BINARY}_lib STATIC ${LIBRARY_FILES})

target_include_directories(${BINARY} PRIVATE ${CMAKE_SOURCE_DIR}/src/**)
target_link_libraries(${BINARY} PRIVATE Boost::boost)

# Testing

set(TEST_BINARY ${CMAKE_PROJECT_NAME}_tests)
set (TEST_FILES
  tests/health_checkup.cpp
  tests/read_config_test.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ${TEST_BINARY}
    ${TEST_FILES}
)
target_link_libraries(
    ${TEST_BINARY}
    ${BINARY}_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TEST_BINARY})