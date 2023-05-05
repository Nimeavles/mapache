project(mapache CXX)

set(BOOST_ROOT "lib/boost_1_62_0")
find_package(Boost 1.62 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(mapache 
  src/core/main.cpp 
  src/utils/config_file_parser.cpp
)

target_include_directories(mapache PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(mapache PRIVATE Boost::boost)
