cmake_minimum_required(VERSION 3.6)
project(OPZ_FROM_JAVA)

set(CMAKE_CXX_STANDARD 14)
include_directories(googletest/googletest/include)
add_executable(OPZ_FROM_JAVA main.cpp opz.h opz.cpp)
add_executable(tests tests.cpp ${SOURCE_FILES})