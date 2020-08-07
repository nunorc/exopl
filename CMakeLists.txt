# only for cmake --version >= 3.5.1
cmake_minimum_required(VERSION 3.0.1)

# project name
project(exopl)

set(EXEC exopl)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SOURCES src/*.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
pkg_check_modules(LIBCURL libcurl)

link_libraries(${JSONCPP_LIBRARIES})
include_directories("${JSONCPP_INCLUDE_DIRS}")

link_libraries(${LIBCURL_LIBRARIES})
#include_directories("${LIBCURL_INCLUDE_DIRS}")

add_executable(${EXEC} ${SOURCES})
target_link_libraries(${EXEC} ${JSONCPP_LDFLAGS})
target_link_libraries(${EXEC} ${LIBCURL_LDFLAGS})

