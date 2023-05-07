project(mapache CXX)

set(BOOST_ROOT "lib/boost_1_68_0")
find_package(Boost 1.68 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/**)

add_executable(mapache 
  src/main.cpp 
  src/utils/config_file_parser.cpp
  src/core/server/server.cpp
)

target_include_directories(mapache PRIVATE ${CMAKE_SOURCE_DIR}/src/**)
target_link_libraries(mapache PRIVATE Boost::boost)
