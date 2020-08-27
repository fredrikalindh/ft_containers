#include <set>
#include <iostream>

// bool fncomp(int lhs, int rhs) { return lhs < rhs; }

// struct classcomp
// {
//   bool operator()(const int &lhs, const int &rhs) const
//   {
//     return lhs < rhs;
//   }
// };

TEST(Multiset, Constructors)
{
  LIBRARY::multiset<int> first; // empty set of ints

  int myints[] = {10, 20, 30, 40, 50};
  LIBRARY::multiset<int> second(myints, myints + 5); // range

  LIBRARY::multiset<int> third(second); // a copy of second

  LIBRARY::multiset<int> fourth(second.begin(), second.end()); // iterator ctor.

  LIBRARY::multiset<int, classcomp> fifth; // class as Compare

  bool (*fn_pt)(int, int) = fncomp;
  LIBRARY::multiset<int, bool (*)(int, int)> sixth(fn_pt); // function pointer as Compare

  EXPECT_EQ(first.size(), 0);
  EXPECT_EQ(second.size(), 5);
  EXPECT_EQ(third.size(), 5);
  EXPECT_EQ(fourth.size(), 5);
}

TEST(Multiset, Assignment)
{
  int myints[] = {12, 82, 37, 64, 15};
  LIBRARY::multiset<int> first(myints, myints + 5); // set with 5 ints
  LIBRARY::multiset<int> second;                    // empty set

  second = first;                   // now second contains the 5 ints
  first = LIBRARY::multiset<int>(); // and first is empty
  EXPECT_EQ(first.size(), 0);
  EXPECT_EQ(second.size(), 5);
}

TEST(Multiset, Begin)
{
  int myints[] = {75, 23, 65, 42, 13};
  LIBRARY::multiset<int> myset(myints, myints + 5);

  int i = 0;
  int result[] = {13, 23, 42, 65, 75};
  ASSERT_EQ(myset.size(), 5);
  for (LIBRARY::multiset<int>::iterator it = myset.begin(); it != myset.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}

TEST(Multiset, RBegin)
{
  int myints[] = {21, 64, 17, 78, 49};
  LIBRARY::multiset<int> myset(myints, myints + 5);

  LIBRARY::multiset<int>::reverse_iterator it;
  int i = 0;
  int result[] = {78, 64, 49, 21, 17};
  ASSERT_EQ(myset.size(), 5);
  for (it = myset.rbegin(); it != myset.rend(); ++it)
    EXPECT_EQ(*it, result[i++]);
}

TEST(Multiset, Empty)
{
  LIBRARY::multiset<int> myset;

  myset.insert(20);
  myset.insert(30);
  myset.insert(10);

  int i = 10;
  while (!myset.empty())
  {
    EXPECT_EQ(*myset.begin(), i);
    i += 10;
    myset.erase(myset.begin());
  }
  EXPECT_TRUE(myset.empty());
}
TEST(Multiset, Size)
{
  LIBRARY::multiset<int> myints;
  EXPECT_EQ(myints.size(), 0);
  for (int i = 0; i < 10; ++i)
    myints.insert(i);
  EXPECT_EQ(myints.size(), 10);
  myints.insert(10);
  EXPECT_EQ(myints.size(), 11);
  myints.erase(5);
  EXPECT_EQ(myints.size(), 10);
}

TEST(Multiset, MaxSize)
{
  LIBRARY::multiset<int> myset;
  std::multiset<int> stdset;
  EXPECT_EQ(myset.max_size(), stdset.max_size());
  LIBRARY::multiset<double> myset2;
  std::multiset<double> stdset2;
  EXPECT_EQ(myset2.max_size(), stdset2.max_size());
  LIBRARY::multiset<char> myset3;
  std::multiset<char> stdset3;
  EXPECT_EQ(myset3.max_size(), stdset3.max_size());
}

TEST(Multiset, Insert)
{
  LIBRARY::multiset<int> myset;
  LIBRARY::multiset<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 5; ++i)
    myset.insert(i * 10); // set: 10 20 30 40 50

  myset.insert(20); // no new element inserted

  it = myset.begin(); // "it" now points to element 20

  advance(it, 4);
  myset.insert(it, 25); // max efficiency inserting
  myset.insert(it, 24); // max efficiency inserting
  myset.insert(it, 26); // no max efficiency inserting

  int myints[] = {5, 10, 15}; // 10 already in set, not inserted
  myset.insert(myints, myints + 3);

  int i = 0;
  int result[] = {5, 10, 10, 15, 20, 20, 24, 25, 26, 30, 40, 50};
  ASSERT_EQ(myset.size(), 12);
  for (LIBRARY::multiset<int>::iterator it = myset.begin(); it != myset.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}
TEST(Multiset, Erase)
{
  LIBRARY::multiset<int> myset;
  LIBRARY::multiset<int>::iterator it;

  // insert some values:
  for (int i = 1; i < 10; i++)
    myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90

  it = myset.begin();
  ++it; // "it" points now to 20

  myset.erase(it);

  myset.erase(40);

  it = myset.find(60);
  myset.erase(it, myset.end());
  int i = 0;
  int result[] = {10, 30, 50};
  ASSERT_EQ(myset.size(), 3);
  for (LIBRARY::multiset<int>::iterator it = myset.begin(); it != myset.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}
TEST(Multiset, Swap)
{
  int myints[] = {12, 75, 10, 10, 32, 20, 25};
  LIBRARY::multiset<int> first(myints, myints + 3);      // 10,12,75
  LIBRARY::multiset<int> second(myints + 3, myints + 7); // 10, 20,25,32
  LIBRARY::multiset<int>::iterator it;

  first.swap(second);

  int i = 0;
  int result1[] = {10, 20, 25, 32};
  ASSERT_EQ(first.size(), 4);
  for (it = first.begin(); it != first.end(); ++it)
    EXPECT_EQ(*it, result1[i++]);

  i = 0;
  int result2[] = {10, 12, 75};
  ASSERT_EQ(second.size(), 3);
  for (it = second.begin(); it != second.end(); ++it)
    EXPECT_EQ(*it, result2[i++]);
}

TEST(Multiset, Clear)
{
  LIBRARY::multiset<int> myset;

  myset.insert(100);
  myset.insert(200);
  myset.insert(300);

  ASSERT_EQ(myset.size(), 3);
  myset.clear();
  ASSERT_EQ(myset.size(), 0);
  myset.insert(1101);
  myset.insert(2202);
  ASSERT_EQ(myset.size(), 2);
}

TEST(Multiset, KeyComp)
{
  LIBRARY::multiset<int> myset;
  int highest;

  LIBRARY::multiset<int>::key_compare mycomp = myset.key_comp();

  for (int i = 0; i <= 5; i++)
    myset.insert(i);

  highest = *myset.rbegin();
  LIBRARY::multiset<int>::iterator it = myset.begin();
  while (mycomp(*(it++), highest))
    ;
  EXPECT_EQ(it, myset.end());
}

TEST(Multiset, ValComp)
{
  LIBRARY::multiset<int> myset;

  LIBRARY::multiset<int>::value_compare mycomp = myset.value_comp();

  for (int i = 0; i <= 5; i++)
    myset.insert(i);

  int highest = *myset.rbegin();
  LIBRARY::multiset<int>::iterator it = myset.begin();
  while (mycomp(*(it++), highest))
    ;
  EXPECT_EQ(it, myset.end());
}
TEST(Multiset, Find)
{
  LIBRARY::multiset<int> myset;
  LIBRARY::multiset<int>::iterator it;

  // set some initial values:
  for (int i = 1; i <= 5; i++)
    myset.insert(i * 10); // set: 10 20 30 40 50

  myset.insert(20);
  it = myset.find(20);
  myset.erase(it);
  myset.erase(myset.find(40));

  int i = 0;
  int result[] = {10, 20, 30, 50};
  ASSERT_EQ(myset.size(), 4);
  for (LIBRARY::multiset<int>::iterator it = myset.begin(); it != myset.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}
TEST(Multiset, Count)
{
  LIBRARY::multiset<int> myset;

  // set some initial values:
  for (int i = 1; i < 5; ++i)
    myset.insert(i * 3); // set: 3 6 9 12
  myset.insert(9);
  EXPECT_TRUE(myset.count(3));
  EXPECT_FALSE(myset.count(4));
  EXPECT_EQ(myset.count(9), 2);
  EXPECT_TRUE(myset.count(12));
}

TEST(Multiset, Bound)
{
  LIBRARY::multiset<int> mymultiset;
  LIBRARY::multiset<int>::iterator itlow, itup;

  for (int i = 1; i < 8; i++)
    mymultiset.insert(i * 10); // 10 20 30 40 50 60 70

  itlow = mymultiset.lower_bound(30); //       ^
  itup = mymultiset.upper_bound(40);  //             ^

  mymultiset.erase(itlow, itup); // 10 20 50 60 70
  int i = 0;
  int result[] = {10, 20, 50, 60, 70};
  ASSERT_EQ(mymultiset.size(), 5);
  for (LIBRARY::multiset<int>::iterator it = mymultiset.begin(); it != mymultiset.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}

TEST(Multiset, EqualRange)
{
  int myints[] = {77, 30, 16, 2, 30, 30};
  LIBRARY::multiset<int> mymultiset(myints, myints + 6); // 2 16 30 30 30 77

  LIBRARY::pair<LIBRARY::multiset<int>::iterator, LIBRARY::multiset<int>::iterator> ret = mymultiset.equal_range(30); //      ^        ^

  for (LIBRARY::multiset<int>::iterator it = ret.first; it != ret.second; ++it)
    EXPECT_EQ(*it, 30);
  mymultiset.erase(ret.first, ret.second);
  EXPECT_EQ(mymultiset.size(), 3);
}

TEST(Multiset, RelOps)
{
  int myints[] = {10, 2, 2, 7, 3, 20, 6, 15};
  LIBRARY::multiset<int> foo(myints, myints + 5);
  LIBRARY::multiset<int> bar(myints + 4, myints + 8);

  // for (LIBRARY::multiset<int>::iterator it = foo.begin(); it != foo.end(); ++it)
  //   std::cout << *it << ", ";
  // std::cout << std::endl;
  // for (LIBRARY::multiset<int>::iterator it = bar.begin(); it != bar.end(); ++it)
  //   std::cout << *it << ", ";

  EXPECT_FALSE(foo == bar);
  EXPECT_TRUE(foo != bar);
  EXPECT_FALSE(foo > bar);
  EXPECT_TRUE(foo < bar);
  EXPECT_FALSE(foo >= bar);
  EXPECT_TRUE(foo <= bar);
}
