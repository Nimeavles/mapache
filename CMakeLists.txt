cmake_minimum_required(VERSION 3.14)
project(mapache CXX)

set(BOOST_ROOT "lib/boost_1_68_0")
find_package(Boost 1.68 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/**)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(mapache 
  src/main.cpp 
  src/utils/config_file_parser.cpp
  src/core/server/server.cpp
)

target_include_directories(mapache PRIVATE ${CMAKE_SOURCE_DIR}/src/**)
target_link_libraries(mapache PRIVATE Boost::boost)

enable_testing()

add_executable(
  health_test
  tests/health_checkup.cpp
)
target_link_libraries(
  health_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(health_test)