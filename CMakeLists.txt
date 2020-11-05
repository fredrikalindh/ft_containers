cmake_minimum_required(VERSION 3.8)

set(This myTester)

project(${This} C CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(includes)

add_compile_options(-w)

set(Sources test/UnitTest.cpp)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
	${GTEST_LIBRARIES}
	pthread
)

