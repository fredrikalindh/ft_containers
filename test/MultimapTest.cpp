#include <map>
#include <iostream>

TEST(MultimapTest, Constructors)
{
  LIBRARY::multimap<char, int> first;

  first.insert(LIBRARY::pair<char, int>('a', 10));
  first.insert(LIBRARY::pair<char, int>('b', 15));
  first.insert(LIBRARY::pair<char, int>('b', 35));
  first.insert(LIBRARY::pair<char, int>('b', 20));
  first.insert(LIBRARY::pair<char, int>('c', 25));

  int i = 0;
  int result[] = {10, 15, 35, 20, 25, 10, 15, 35, 20, 25};
  for (LIBRARY::multimap<char, int>::iterator it = first.begin(); it != first.end(); ++it){
    EXPECT_EQ(it->second, result[i++]); 
  }

  LIBRARY::multimap<char, int> second(first.begin(), first.end());
  for (LIBRARY::multimap<char, int>::iterator it = first.begin(); it != first.end(); ++it)
    EXPECT_EQ(it->second, result[i++]);

  LIBRARY::multimap<char, int> third(second);

  LIBRARY::multimap<char, int, classcomp> fourth; // class as Compare

  bool (*fn_pt)(char, char) = fncomp;
  LIBRARY::multimap<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as comp

  EXPECT_EQ(first.size(), 5);
  EXPECT_EQ(second.size(), 5);
  EXPECT_EQ(third.size(), 5);
  EXPECT_EQ(fourth.size(), 0);
  EXPECT_EQ(fifth.size(), 0);
}

TEST(MultimapTest, Assignment)
{
  LIBRARY::multimap<char, int> foo, bar;

  foo.insert(LIBRARY::make_pair('x', 32));
  foo.insert(LIBRARY::make_pair('y', 64));
  foo.insert(LIBRARY::make_pair('y', 96));
  foo.insert(LIBRARY::make_pair('z', 128));

  bar = foo;   // bar now contains 4 ints
  foo.clear(); // and first is now empty

  EXPECT_EQ(foo.size(), 0);
  EXPECT_EQ(bar.size(), 4);
}

TEST(MultimapTest, Begin)
{
  LIBRARY::multimap<char, int> mymultimap;

  mymultimap.insert(LIBRARY::pair<char, int>('a', 10));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 20));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 150));

  int i = 0;
  int result[] = {10, 20, 150};
  for (LIBRARY::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result[i++]);
}

TEST(MultimapTest, RBegin)
{
  LIBRARY::multimap<char, int> mymultimap;

  mymultimap.insert(LIBRARY::make_pair('x', 10));
  mymultimap.insert(LIBRARY::make_pair('y', 20));
  mymultimap.insert(LIBRARY::make_pair('y', 150));
  mymultimap.insert(LIBRARY::make_pair('z', 9));

  int i = 0;
  int result[] = {9, 150, 20, 10};
  for (LIBRARY::multimap<char, int>::reverse_iterator it = mymultimap.rbegin(); it != mymultimap.rend(); ++it)
    EXPECT_EQ(it->second, result[i++]);
}

TEST(MultimapTest, Empty)
{
  LIBRARY::multimap<char, int> mymultimap;

  mymultimap.insert(LIBRARY::pair<char, int>('b', 101));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 202));
  mymultimap.insert(LIBRARY::pair<char, int>('q', 505));
  mymultimap.insert(LIBRARY::pair<char, int>('q', 405));

  while (!mymultimap.empty())
  {
    mymultimap.erase(mymultimap.begin());
  }
  EXPECT_EQ(mymultimap.size(), 0);
}
TEST(MultimapTest, Size)
{
  LIBRARY::multimap<char, int> mymultimap;

  mymultimap.insert(LIBRARY::make_pair('x', 100));
  mymultimap.insert(LIBRARY::make_pair('y', 200));
  mymultimap.insert(LIBRARY::make_pair('y', 350));
  mymultimap.insert(LIBRARY::make_pair('z', 500));

  EXPECT_EQ(mymultimap.size(), 4);
}

TEST(MultimapTest, MaxSize)
{
  LIBRARY::multimap<int, int> mymap;
  std::multimap<int, int> stdmap;
  EXPECT_EQ(mymap.max_size(), stdmap.max_size()) << "int, int";
  LIBRARY::multimap<double, double> mymap2;
  std::multimap<double, double> stdmap2;
  EXPECT_EQ(mymap2.max_size(), stdmap2.max_size()) << "double, double";
  LIBRARY::multimap<char, int> mymap3;
  std::multimap<char, int> stdmap3;
  EXPECT_EQ(mymap3.max_size(), stdmap3.max_size()) << "char, int";
}

TEST(MultimapTest, Insert)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it;

  // first insert function version (single parameter):
  mymultimap.insert(LIBRARY::pair<char, int>('a', 100));
  mymultimap.insert(LIBRARY::pair<char, int>('z', 150));
  it = mymultimap.insert(LIBRARY::pair<char, int>('b', 75));

  // second insert function version (with hint position):
  mymultimap.insert(it, LIBRARY::pair<char, int>('c', 300)); // max efficiency inserting
  mymultimap.insert(it, LIBRARY::pair<char, int>('z', 400)); // no max efficiency inserting

  // third insert function version (range insertion):
  LIBRARY::multimap<char, int> anothermultimap;
  anothermultimap.insert(mymultimap.begin(), mymultimap.find('c'));

  int i = 0;
  int result1[] = {100, 75, 300, 400, 150};
  for (LIBRARY::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it){
    EXPECT_EQ(it->second, result1[i++]);
}
  i = 0;
  int result2[] = {100, 75};
  for (LIBRARY::multimap<char, int>::iterator it = anothermultimap.begin(); it != anothermultimap.end(); ++it)
    EXPECT_EQ(it->second, result2[i++]);
}

TEST(MultimapTest, EraseAtPosition)
{
  LIBRARY::multimap<char, int> mymultimap;
   LIBRARY::multimap<char, int>::iterator it;

  // insert some values:
  mymultimap.insert(LIBRARY::pair<char, int>('a', 10));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 20));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 30));
  mymultimap.insert(LIBRARY::pair<char, int>('c', 40));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 50));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 60));
  mymultimap.insert(LIBRARY::pair<char, int>('e', 70));
  mymultimap.insert(LIBRARY::pair<char, int>('f', 80));

  it = mymultimap.find('b');
  mymultimap.erase(it); // erasing by iterator (1 element)
  int i = 0;
  int result1[] = {10, 30, 40, 50, 60, 70, 80};
  ASSERT_EQ(mymultimap.size(), 7);
  EXPECT_EQ(mymultimap.count('b'), 1);
  EXPECT_EQ(mymultimap.count('d'), 2);
  for (LIBRARY::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result1[i++]);

  mymultimap.erase(mymultimap.begin()); // erasing by key (2 elements)
  i = 0;
  int result2[] = {30, 40, 50, 60, 70, 80};
  ASSERT_EQ(mymultimap.size(), 6);
  for (LIBRARY::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result2[i++]);

  it = mymultimap.find('f');
  mymultimap.erase(it); // erasing by range
  i = 0;
  int result3[] = {30, 40, 50, 60, 70};
  ASSERT_EQ(mymultimap.size(), 5);
  for (LIBRARY::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result3[i++]);

}

TEST(MultimapTest, EraseByKey)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it;

  // insert some values:
  mymultimap.insert(LIBRARY::pair<char, int>('a', 10));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 20));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 30));
  mymultimap.insert(LIBRARY::pair<char, int>('c', 40));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 50));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 60));
  mymultimap.insert(LIBRARY::pair<char, int>('e', 70));
  mymultimap.insert(LIBRARY::pair<char, int>('f', 80));

  mymultimap.erase('d'); // erasing by key (2 elements)
  EXPECT_EQ(mymultimap.count('d'), 0);
  int i = 0;
  int result1[] = {10, 20, 30, 40, 70, 80};
  ASSERT_EQ(mymultimap.size(), 6);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result1[i++]);

  mymultimap.erase('a');
  EXPECT_EQ(mymultimap.count('a'), 0);
  i = 0;
  int result2[] = {20, 30, 40, 70, 80};
  ASSERT_EQ(mymultimap.size(), 5);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result2[i++]);

  mymultimap.erase('b');
  EXPECT_EQ(mymultimap.count('b'), 0);
  i = 0;
  int result3[] = {40, 70, 80};
  ASSERT_EQ(mymultimap.size(), 3);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result3[i++]);

  mymultimap.erase('f');
  EXPECT_EQ(mymultimap.count('f'), 0);
  i = 0;
  int result4[] = {40, 70};
  ASSERT_EQ(mymultimap.size(), 2);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result4[i++]);
  
  mymultimap.erase('c');
  mymultimap.erase('e');
    ASSERT_TRUE(mymultimap.empty());
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result4[i++]);
}

TEST(MultimapTest, EraseRange)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it;

  // insert some values:
  mymultimap.insert(LIBRARY::pair<char, int>('a', 10));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 20));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 30));
  mymultimap.insert(LIBRARY::pair<char, int>('c', 40));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 50));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 60));
  mymultimap.insert(LIBRARY::pair<char, int>('e', 70));
  mymultimap.insert(LIBRARY::pair<char, int>('f', 80));

  it = mymultimap.find('e');
  mymultimap.erase(it, mymultimap.end()); // erasing by range
  int i = 0;
  int result1[] = {10, 20, 30, 40, 50, 60};
  ASSERT_EQ(mymultimap.size(), 6);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result1[i++]);

  it = mymultimap.find('d');
  mymultimap.erase(mymultimap.begin(), it); // erasing by range
  i = 0;
  int result2[] = {50, 60};
  ASSERT_EQ(mymultimap.size(), 2);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result2[i++]);
  
  mymultimap.erase(mymultimap.begin(), mymultimap.end()); // erasing by range
  ASSERT_TRUE(mymultimap.empty());
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result1[i++]);
}

TEST(MultimapTest, EraseRange2)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it;
  LIBRARY::multimap<char, int>::iterator it2;

  // insert some values:
  mymultimap.insert(LIBRARY::pair<char, int>('a', 10));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 20));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 30));
  mymultimap.insert(LIBRARY::pair<char, int>('c', 40));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 50));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 60));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 70));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 80));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 90));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 100));

  it = mymultimap.find('c');
  it2 = mymultimap.end();
  advance(it2, -4);

  mymultimap.erase(it, it2); // erasing by range
  int i = 0;
  int result2[] = {10, 20, 30, 70, 80, 90, 100};
  ASSERT_EQ(mymultimap.size(), 7);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result2[i++]);
}

TEST(MultimapTest, EraseRange3)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it;
  LIBRARY::multimap<char, int>::iterator it2;

  // insert some values:
  mymultimap.insert(LIBRARY::pair<char, int>('a', 10));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 20));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 30));
  mymultimap.insert(LIBRARY::pair<char, int>('c', 40));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 50));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 60));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 70));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 80));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 90));
  mymultimap.insert(LIBRARY::pair<char, int>('d', 100));

  it = mymultimap.find('c');
  it2 = mymultimap.end();
  advance(it2, -5);

  mymultimap.erase(it, it2); // erasing by range
  int i = 0;
  int result2[] = {10, 20, 30, 60, 70, 80, 90, 100};
  ASSERT_EQ(mymultimap.size(), 8);
  for (it = mymultimap.begin(); it != mymultimap.end(); ++it)
    EXPECT_EQ(it->second, result2[i++]);
}

TEST(MultimapTest, Swap)
{
  LIBRARY::multimap<char, int> foo, bar;

  foo.insert(LIBRARY::make_pair('x', 100));
  foo.insert(LIBRARY::make_pair('y', 200));

  bar.insert(LIBRARY::make_pair('a', 11));
  bar.insert(LIBRARY::make_pair('b', 22));
  bar.insert(LIBRARY::make_pair('a', 55));

  EXPECT_EQ(foo.size(), 2);
  EXPECT_EQ(bar.size(), 3);
  foo.swap(bar);
  EXPECT_EQ(bar.size(), 2);
  EXPECT_EQ(foo.size(), 3);

  swap(bar, foo);
  EXPECT_EQ(foo.size(), 2);
  EXPECT_EQ(bar.size(), 3);
}

TEST(MultimapTest, Clear)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it;

  mymultimap.insert(LIBRARY::pair<char, int>('b', 80));
  mymultimap.insert(LIBRARY::pair<char, int>('b', 120));
  mymultimap.insert(LIBRARY::pair<char, int>('q', 360));
  EXPECT_EQ(mymultimap.size(), 3);
  mymultimap.clear();
  EXPECT_EQ(mymultimap.size(), 0);
  mymultimap.insert(LIBRARY::pair<char, int>('a', 11));
  mymultimap.insert(LIBRARY::pair<char, int>('x', 22));
  EXPECT_EQ(mymultimap.size(), 2);
}

TEST(MultimapTest, KeyComp)
{
  LIBRARY::multimap<char, int> mymultimap;

  LIBRARY::multimap<char, int>::key_compare mycomp = mymultimap.key_comp();

  mymultimap.insert(LIBRARY::make_pair('a', 100));
  mymultimap.insert(LIBRARY::make_pair('b', 200));
  mymultimap.insert(LIBRARY::make_pair('b', 211));
  mymultimap.insert(LIBRARY::make_pair('c', 300));

  char highest = mymultimap.rbegin()->first; // key value of last element

  LIBRARY::multimap<char, int>::iterator it = mymultimap.begin();
  while (mycomp((*it++).first, highest))
    ;
  EXPECT_EQ(it, mymultimap.end());
}

TEST(MultimapTest, ValComp)
{
  LIBRARY::multimap<char, int> mymultimap;

  mymultimap.insert(LIBRARY::make_pair('x', 101));
  mymultimap.insert(LIBRARY::make_pair('y', 202));
  mymultimap.insert(LIBRARY::make_pair('y', 252));
  mymultimap.insert(LIBRARY::make_pair('z', 303));

  LIBRARY::pair<char, int> highest = *mymultimap.rbegin(); // last element

  LIBRARY::multimap<char, int>::iterator it = mymultimap.begin();
  while (mymultimap.value_comp()(*it++, highest))
    ;
  EXPECT_EQ(it, mymultimap.end());
}

TEST(MultimapTest, Find)
{
  LIBRARY::multimap<char, int> mymm;

  mymm.insert(LIBRARY::make_pair('x', 10));
  mymm.insert(LIBRARY::make_pair('y', 20));
  mymm.insert(LIBRARY::make_pair('z', 30));
  mymm.insert(LIBRARY::make_pair('z', 40));

  LIBRARY::multimap<char, int>::iterator it = mymm.find('x');
  mymm.erase(it);
  mymm.erase(mymm.find('z'));
  EXPECT_EQ(mymm.size(), 2);
  EXPECT_EQ(mymm.find('y')->second, 20);
  EXPECT_EQ(mymm.find('z')->second, 40);
}

TEST(MultimapTest, Count)
{
  LIBRARY::multimap<char, int> mymm;

  mymm.insert(LIBRARY::make_pair('x', 50));
  mymm.insert(LIBRARY::make_pair('y', 100));
  mymm.insert(LIBRARY::make_pair('y', 150));
  mymm.insert(LIBRARY::make_pair('y', 200));
  mymm.insert(LIBRARY::make_pair('z', 250));
  mymm.insert(LIBRARY::make_pair('z', 300));

  EXPECT_EQ(mymm.count('x'), 1);
  EXPECT_EQ(mymm.count('y'), 3);
  EXPECT_EQ(mymm.count('z'), 2);
  EXPECT_EQ(mymm.count('o'), 0);
}

TEST(MultimapTest, Bound)
{
  LIBRARY::multimap<char, int> mymultimap;
  LIBRARY::multimap<char, int>::iterator it, itlow, itup;

  mymultimap.insert(LIBRARY::make_pair('a', 10));
  mymultimap.insert(LIBRARY::make_pair('b', 121));
  mymultimap.insert(LIBRARY::make_pair('c', 1001));
  mymultimap.insert(LIBRARY::make_pair('c', 2002));
  mymultimap.insert(LIBRARY::make_pair('d', 11011));
  mymultimap.insert(LIBRARY::make_pair('e', 44));

  itlow = mymultimap.lower_bound('b'); // itlow points to b
  itup = mymultimap.upper_bound('d');  // itup points to e (not d)

  EXPECT_EQ(distance(itlow, itup), 4);
  int i = 0;
  int result1[] = {121, 1001, 2002, 11011};
  for (it = itlow; it != itup; ++it)
    EXPECT_EQ(it->second, result1[i++]);
}

TEST(MultimapTest, EqualRange)
{
  LIBRARY::multimap<char, int> mymm;

  mymm.insert(LIBRARY::pair<char, int>('a', 10));
  mymm.insert(LIBRARY::pair<char, int>('b', 20));
  mymm.insert(LIBRARY::pair<char, int>('b', 30));
  mymm.insert(LIBRARY::pair<char, int>('b', 40));
  mymm.insert(LIBRARY::pair<char, int>('c', 50));
  mymm.insert(LIBRARY::pair<char, int>('c', 60));
  mymm.insert(LIBRARY::pair<char, int>('d', 60));

  LIBRARY::pair<LIBRARY::multimap<char, int>::iterator, LIBRARY::multimap<char, int>::iterator> ret;
  ret = mymm.equal_range('b');
  EXPECT_EQ(distance(ret.first, ret.second), 3);
  ret = mymm.equal_range('c');
  mymm.erase(ret.first, ret.second);
  EXPECT_FALSE(mymm.count('c'));
}

TEST(MultimapTest, RelOps)
{
  LIBRARY::multimap<char, int> foo, bar;

  foo.insert(LIBRARY::make_pair('b', 100));
  foo.insert(LIBRARY::make_pair('z', 900));
  bar.insert(LIBRARY::make_pair('b', 100));
  bar.insert(LIBRARY::make_pair('b', 350));

  EXPECT_FALSE(foo == bar);
  EXPECT_TRUE(foo != bar);
  EXPECT_FALSE(foo < bar);
  EXPECT_TRUE(foo > bar);
  EXPECT_FALSE(foo <= bar);
  EXPECT_TRUE(foo >= bar);
}
