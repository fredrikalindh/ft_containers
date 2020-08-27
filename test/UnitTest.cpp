#include "gtest/gtest.h"

#include <deque>
#include <vector>
#include <iostream>
#include <list>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
#include <stack>
#include <queue>
#include <set>

// #ifndef LIBRARY
// #define LIBRARY ft
// #endif

bool fncomp(char lhs, char rhs) { return lhs < rhs; }
bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp
{
  bool operator()(const char &lhs, const char &rhs) const
  {
    return lhs < rhs;
  }
};

#include <ft.hpp>

#ifdef BASIC
#include "VectorTest.cpp"
#include "ListTest.cpp"
#include "StackTest.cpp"
#include "QueueTest.cpp"
#include "MapTest.cpp"
#include "SetTest.cpp"
#endif

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
