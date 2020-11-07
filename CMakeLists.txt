cmake_minimum_required(VERSION 3.8)

set(This myTester)

project(${This} C CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(includes)
 
set(CLANG_WARNINGS
    -Wall 
    -Werror 
    -Wextra 
    # -Wpedantic
    # -Wshadow
    # -Wnon-virtual-dtor
    # -Wold-style-cast
    # -Wcast-align
    # -Wunused
    # -Wconversion
    # -Wsign-conversion
    # -Wnull-dereference
    # -Wdouble-promotion
)
# -std=c++0x 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_compile_options(${CLANG_WARNINGS})
# add_subdirectory()

# target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

add_compile_options(-w)

set(Sources test/main.cpp)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
	${GTEST_LIBRARIES}
	pthread
)

