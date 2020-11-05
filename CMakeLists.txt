cmake_minimum_required(VERSION 3.8)

set(This CMAKEunitTests)

project(${This} C CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# enable_testing()

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
set(Sources
    # test/DequeTest.cpp
    # test/ListTest.cpp
    # test/MapTest.cpp
    # test/MultimapTest.cpp
    # test/MultisetTest.cpp
    # test/SetTest.cpp
    # test/StackTest.cpp
    # test/VectorTest.cpp
    test/main.cpp
)

set(Headers
    includes/ft.hpp
)


add_executable(${This} ${Sources} ${Headers})
# Link runTests with what we want to test and the GTest and pthread library
target_link_libraries(${This} PUBLIC
	${GTEST_LIBRARIES} 
	pthread
)
# target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
