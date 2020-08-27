#include "gtest/gtest.h"

#ifndef LIBRARY
#define LIBRARY std
#endif

#include <ft.hpp>
#include "VectorTest.cpp"
#include "ListTest.cpp"
#include "StackTest.cpp"
#include "QueueTest.cpp"
#include "MapTest.cpp"
#include "SetTest.cpp"

#ifdef BONUS
#include "DequeTest.cpp"
#include "MultisetTest.cpp"
#include "MultimapTest.cpp"
#endif

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
