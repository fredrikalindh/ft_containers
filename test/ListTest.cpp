// #include "../includes/ft.hpp"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
#include <string>
#include <cctype>

TEST(ListTest, Constructor)
{
  // constructors used in the same order as described above:
  LIBRARY::list<int> first;                               // empty list of ints
  LIBRARY::list<int> second(4, 100);                      // four ints with value 100
  LIBRARY::list<int> third(second.begin(), second.end()); // iterating through second
  LIBRARY::list<int> fourth(third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16, 2, 77, 29, 22};
  LIBRARY::list<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  EXPECT_EQ(first.size(), 0);
  EXPECT_EQ(second.size(), 4);
  EXPECT_EQ(third.size(), 4);
  EXPECT_EQ(fourth.size(), 4);
  EXPECT_EQ(fifth.size(), 5);
  for (LIBRARY::list<int>::iterator it = second.begin(); it != second.end(); ++it)
    EXPECT_EQ(*it, 100);
  int i = 0;
  for (LIBRARY::list<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    EXPECT_EQ(*it, myints[i++]);
}

TEST(ListTest, AssignmentOp)
{
  LIBRARY::list<int> first(3);  // list of 3 zero-initialized ints
  LIBRARY::list<int> second(5); // list of 5 zero-initialized ints

  second = first;
  first = LIBRARY::list<int>();

  EXPECT_EQ(first.size(), 0);
  EXPECT_EQ(second.size(), 3);
}

TEST(ListTest, Begin)
{
  int myints[] = {75, 23, 65, 42, 13};
  LIBRARY::list<int> mylist(myints, myints + 5);
  std::list<int> stdlist(myints, myints + 5);

  LIBRARY::list<int>::iterator it = mylist.begin();
  std::list<int>::iterator stdit = stdlist.begin();

  while (it != mylist.end())
  {
    EXPECT_EQ(*it, *stdit);
    stdit++;
    it++;
  }
}

TEST(ListTest, ReverseBegin)
{
  LIBRARY::list<int> mylist;
  for (int i = 1; i <= 5; ++i)
    mylist.push_back(i);

  int i = 5;
  for (LIBRARY::list<int>::reverse_iterator rit = mylist.rbegin(); rit != mylist.rend(); ++rit)
    EXPECT_EQ(*rit, i--);
}

TEST(ListTest, Empty)
{
  LIBRARY::list<int> mylist;
  int sum(0);

  for (int i = 1; i <= 10; ++i)
    mylist.push_back(i);

  while (!mylist.empty())
  {
    sum += mylist.front();
    mylist.pop_front();
  }
  EXPECT_EQ(sum, 55);
}

TEST(ListTest, Size)
{
  LIBRARY::list<int> myints;
  EXPECT_EQ(myints.size(), 0);

  for (int i = 0; i < 10; i++)
    myints.push_back(i);
  EXPECT_EQ(myints.size(), 10);

  myints.insert(myints.begin(), 10, 100);
  EXPECT_EQ(myints.size(), 20);

  myints.pop_back();
  EXPECT_EQ(myints.size(), 19);
}

TEST(ListTest, MaxSize)
{
  LIBRARY::list<int> mylist;
  std::list<int> stdlist;
  EXPECT_EQ(mylist.max_size(), stdlist.max_size());
}

TEST(ListTest, Front)
{
  LIBRARY::list<int> mylist;

  mylist.push_back(77);
  mylist.push_back(22);

  // now front equals 77, and back 22
  EXPECT_EQ(mylist.front(), 77);
  mylist.front() -= mylist.back();
  EXPECT_EQ(mylist.front(), 55);
}

TEST(ListTest, Back)
{
  LIBRARY::list<int> mylist;

  mylist.push_back(10);

  while (mylist.back() != 0)
  {
    mylist.push_back(mylist.back() - 1);
  }
  int i = 10;
  for (LIBRARY::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, i--);
}

TEST(ListTest, Assign)
{
  LIBRARY::list<int> first;
  LIBRARY::list<int> second;

  first.assign(7, 100); // 7 ints with value 100
  EXPECT_EQ(first.size(), 7);
  second.assign(first.begin(), first.end()); // a copy of first

  int myints[] = {1776, 7, 4};
  first.assign(myints, myints + 3); // assigning from array
  EXPECT_EQ(second.size(), 7);
  EXPECT_EQ(first.size(), 3);
}

TEST(ListTest, PushFront)
{
  LIBRARY::list<int> mylist(2, 100); // two ints with a value of 100

  for (int i = 0; i < 1300; ++i)
    mylist.push_front(i);

  EXPECT_EQ(mylist.size(), 1302);
}

TEST(ListTest, PopFront)
{
  LIBRARY::list<int> mylist;
  mylist.push_back(100);
  mylist.push_back(200);
  mylist.push_back(300);

  while (!mylist.empty())
  {
    mylist.pop_front();
  }
  EXPECT_EQ(mylist.size(), 0);
}

TEST(ListTest, PushBack)
{
  LIBRARY::list<int> mylist;
  for (int i = 0; i < 1300; ++i)
    mylist.push_back(i);

  EXPECT_EQ(mylist.size(), 1300);
}

TEST(ListTest, PopBack)
{
  LIBRARY::list<int> mylist;
  int sum(0);
  mylist.push_back(100);
  mylist.push_back(200);
  mylist.push_back(300);

  while (!mylist.empty())
  {
    sum += mylist.back();
    mylist.pop_back();
  }
  EXPECT_EQ(sum, 600);
}

TEST(ListTest, Insert)
{
  LIBRARY::list<int> mylist;
  LIBRARY::list<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 5; ++i)
    mylist.push_back(i); // 1 2 3 4 5

  it = mylist.begin();
  ++it; // it points now to number 2           ^

  mylist.insert(it, 10); // 1 10 2 3 4 5

  // "it" still points to number 2                      ^
  mylist.insert(it, 2, 20); // 1 10 20 20 2 3 4 5

  --it; // it points now to the second 20            ^

  std::vector<int> myvector(2, 30);
  mylist.insert(it, myvector.begin(), myvector.end());
  // 1 10 20 30 30 20 2 3 4 5
  //               ^
  int result[] = {1, 10, 20, 30, 30, 20, 2, 3, 4, 5};
  int i = 0;
  for (it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}

TEST(ListTest, Erase)
{
  LIBRARY::list<int> mylist;
  LIBRARY::list<int>::iterator it1, it2;

  // set some values:
  for (int i = 1; i < 10; ++i)
    mylist.push_back(i * 10);

  // 10 20 30 40 50 60 70 80 90
  it1 = it2 = mylist.begin(); // ^^
  LIBRARY::advance(it2, 6);   // ^                 ^
  ++it1;                      //    ^              ^

  it1 = mylist.erase(it1); // 10 30 40 50 60 70 80 90
                           //    ^           ^

  it2 = mylist.erase(it2); // 10 30 40 50 60 80 90
                           //    ^           ^

  ++it1; //       ^        ^
  --it2; //       ^     ^

  mylist.erase(it1, it2); // 10 30 60 80 90
                          //        ^

  int result[] = {10, 30, 60, 80, 90};
  int i = 0;
  for (LIBRARY::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}

TEST(ListTest, Swap)
{
  LIBRARY::list<int> foo(3, 100); // three ints with a value of 100
  LIBRARY::list<int> bar(5, 200); // five ints with a value of 200

  EXPECT_EQ(foo.size(), 3);
  EXPECT_EQ(bar.size(), 5);
  foo.swap(bar);
  EXPECT_EQ(foo.size(), 5);
  EXPECT_EQ(bar.size(), 3);
}

TEST(ListTest, Resize)
{
  LIBRARY::list<int> mylist;

  // set some initial content:
  for (int i = 1; i < 10; ++i)
    mylist.push_back(i);

  mylist.resize(5);
  mylist.resize(8, 100);
  mylist.resize(12);

  int myints[] = {1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0};
  int i = 0;
  for (LIBRARY::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, myints[i++]);
}

TEST(ListTest, Clear)
{
  LIBRARY::list<int> mylist;
  LIBRARY::list<int>::iterator it;

  mylist.push_back(100);
  mylist.push_back(200);
  mylist.push_back(300);

  mylist.clear();
  EXPECT_EQ(mylist.size(), 0);
  mylist.push_back(1101);
  mylist.push_back(2202);
  EXPECT_EQ(mylist.size(), 2);
}

TEST(ListTest, Splice)
{
  LIBRARY::list<int> mylist1, mylist2;
  LIBRARY::list<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 4; ++i)
    mylist1.push_back(i); // mylist1: 1 2 3 4

  for (int i = 1; i <= 3; ++i)
    mylist2.push_back(i * 10); // mylist2: 10 20 30

  it = mylist1.begin();
  ++it; // points to 2

  mylist1.splice(it, mylist2); // mylist1: 1 10 20 30 2 3 4
                               // mylist2 (empty)
                               // "it" still points to 2 (the 5th element)
  int myints1[] = {1, 10, 20, 30, 2, 3, 4};
  int i = 0;
  for (LIBRARY::list<int>::iterator it = mylist1.begin(); it != mylist1.end(); ++it)
    EXPECT_EQ(*it, myints1[i++]);
  mylist2.splice(mylist2.begin(), mylist1, it);
  // mylist1: 1 10 20 30 3 4
  // mylist2: 2
  // "it" is now invalid.
  EXPECT_EQ(mylist2.front(), 2);
  it = mylist1.begin();
  LIBRARY::advance(it, 3); // "it" points now to 30

  mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end());
  // mylist1: 30 3 4 1 10 20
  int myints2[] = {30, 3, 4, 1, 10, 20};
  i = 0;
  for (LIBRARY::list<int>::iterator it = mylist1.begin(); it != mylist1.end(); ++it)
    EXPECT_EQ(*it, myints2[i++]);
}

TEST(ListTest, Remove)
{
  int myints[] = {17, 89, 7, 14};
  LIBRARY::list<int> mylist(myints, myints + 4);

  mylist.remove(89);
  int myints2[] = {17, 7, 14};
  int i = 0;
  for (LIBRARY::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, myints2[i++]);
}

// a predicate implemented as a function:
bool single_digit(const int &value) { return (value < 10); }

// a predicate implemented as a class:
struct is_odd
{
  bool operator()(const int &value) { return (value % 2) == 1; }
};

TEST(ListTest, RemoveIf)
{
  int myints[] = {15, 36, 7, 17, 20, 39, 4, 1};
  LIBRARY::list<int> mylist(myints, myints + 8); // 15 36 7 17 20 39 4 1

  mylist.remove_if(single_digit); // 15 36 17 20 39
  int myints2[] = {15, 36, 17, 20, 39};
  int i = 0;
  for (LIBRARY::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, myints2[i++]);
  mylist.remove_if(is_odd()); // 36 20
  int myints3[] = {36, 20};
  i = 0;
  for (LIBRARY::list<int>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, myints3[i++]);
}

// a binary predicate implemented as a function:
bool same_integral_part(double first, double second)
{
  return (int(first) == int(second));
}

// a binary predicate implemented as a class:
struct is_near
{
  bool operator()(double first, double second)
  {
    return (fabs(first - second) < 5.0);
  }
};

TEST(ListTest, Unique)
{
  double mydoubles[] = {12.15, 2.72, 73.0, 12.77, 3.14,
                        12.77, 73.35, 72.25, 15.3, 72.25};
  LIBRARY::list<double> mylist(mydoubles, mydoubles + 10);

  mylist.sort(); //  2.72,  3.14, 12.15, 12.77, 12.77,
                 // 15.3,  72.25, 72.25, 73.0,  73.35

  double mysorted[] = {2.72, 3.14, 12.15, 12.77, 12.77,
                       15.3, 72.25, 72.25, 73.0, 73.35};
  int i = 0;
  for (LIBRARY::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, mysorted[i++]);

  mylist.unique(); //  2.72,  3.14, 12.15, 12.77
                   // 15.3,  72.25, 73.0,  73.35

  double myunique[] = {2.72, 3.14, 12.15, 12.77,
                       15.3, 72.25, 73.0, 73.35};
  i = 0;
  for (LIBRARY::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, myunique[i++]);

  mylist.unique(same_integral_part); //  2.72,  3.14, 12.15
                                     // 15.3,  72.25, 73.0

  double myunique2[] = {2.72, 3.14, 12.15,
                        15.3, 72.25, 73.0};
  i = 0;
  for (LIBRARY::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, myunique2[i++]);

  mylist.unique(is_near()); //  2.72, 12.15, 72.25

  double final[] = {2.72, 12.15, 72.25};
  i = 0;
  for (LIBRARY::list<double>::iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, final[i++]);
}

// compare only integral part:
bool mycomparison(double first, double second)
{
  return (int(first) < int(second));
}

TEST(ListTest, Merge)
{
  LIBRARY::list<double> first, second;

  first.push_back(3.1);
  first.push_back(2.2);
  first.push_back(2.9);

  second.push_back(3.7);
  second.push_back(7.1);
  second.push_back(1.4);

  first.sort();
  second.sort();

  first.merge(second);
  double test1[] = {1.4, 2.2, 2.9, 3.1, 3.7, 7.1};
  int i = 0;
  for (LIBRARY::list<double>::iterator it = first.begin(); it != first.end(); ++it)
    EXPECT_EQ(*it, test1[i++]);

  // (second is now empty)
  EXPECT_EQ(second.size(), 0);
  second.push_back(2.1);

  first.merge(second, mycomparison);
  double final[] = {1.4, 2.2, 2.9, 2.1, 3.1, 3.7, 7.1};
  i = 0;
  for (LIBRARY::list<double>::iterator it = first.begin(); it != first.end(); ++it)
    EXPECT_EQ(*it, final[i++]);
}
// comparison, not case sensitive.
bool compare_nocase(const std::string &first, const std::string &second)
{
  unsigned int i = 0;
  while ((i < first.length()) && (i < second.length()))
  {
    if (tolower(first[i]) < tolower(second[i]))
      return true;
    else if (tolower(first[i]) > tolower(second[i]))
      return false;
    ++i;
  }
  return (first.length() < second.length());
}

TEST(ListTest, Sort)
{
  LIBRARY::list<std::string> mylist;
  std::list<std::string> stdlist;
  mylist.push_back("one");
  mylist.push_back("two");
  mylist.push_back("Three");
  stdlist.push_back("one");
  stdlist.push_back("two");
  stdlist.push_back("Three");

  mylist.sort();
  stdlist.sort();
  EXPECT_EQ(mylist.front(), stdlist.front());

  mylist.sort(compare_nocase);
  stdlist.sort(compare_nocase);
  EXPECT_EQ(mylist.front(), stdlist.front());
}

TEST(ListTest, Reverse)
{
  LIBRARY::list<int> mylist;

  for (int i = 1; i < 10; ++i)
    mylist.push_back(i);

  mylist.reverse();

  int i = 9;
  for (LIBRARY::list<int>::const_iterator it = mylist.begin(); it != mylist.end(); ++it)
    EXPECT_EQ(*it, i--);
}

TEST(ListTest, RelationalOp)
{
  LIBRARY::list<int> foo(3, 100); // three ints with a value of 100
  LIBRARY::list<int> bar(2, 200); // two ints with a value of 200

  EXPECT_FALSE(foo == bar);
  EXPECT_TRUE(foo != bar);
  EXPECT_FALSE(foo > bar);
  EXPECT_TRUE(foo < bar);
  EXPECT_FALSE(foo >= bar);
  EXPECT_TRUE(foo <= bar);
}
