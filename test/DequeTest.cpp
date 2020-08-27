TEST(DequeTest, Constructors)
{
  // constructors used in the same order as described above:
  LIBRARY::deque<int> first;                               // empty deque of ints
  LIBRARY::deque<int> second(4, 100);                      // four ints with value 100
  LIBRARY::deque<int> third(second.begin(), second.end()); // iterating through second
  LIBRARY::deque<int> fourth(4000, 1);                      // a copy of third
   LIBRARY::deque<int> sixth(fourth); 
  // the iterator constructor can be used to copy arrays:
  int myints[] = {16, 2, 77, 29, 20};
  LIBRARY::deque<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

  EXPECT_EQ(first.size(), 0);
  EXPECT_EQ(second.size(), 4);
  EXPECT_EQ(third.size(), 4);
  EXPECT_EQ(fourth.size(), 4000);
  EXPECT_EQ(fifth.size(), 5);
  EXPECT_EQ(sixth.size(), 4000);

  for (LIBRARY::deque<int>::iterator it = second.begin(); it != second.end(); ++it)
    EXPECT_EQ(*it, 100);
  for (int i = 0; i < fifth.size(); ++i)
    EXPECT_EQ(myints[i], fifth[i]);
  
}

TEST(DequeTest, Assignment)
{
  LIBRARY::deque<int> first(3);  // deque with 3 zero-initialized ints
  LIBRARY::deque<int> second(5); // deque with 5 zero-initialized ints

  second = first;
  first = LIBRARY::deque<int>();

  EXPECT_EQ(first.size(), 0);
  EXPECT_EQ(second.size(), 3);
}

TEST(DequeTest, Begin)
{
  LIBRARY::deque<int> mydeque(100);
  std::deque<int> stddeque(100);

  for (int i = 1; i <= 5; i++)
  {
    mydeque.push_back(i);
    stddeque.push_back(i);
  }
  LIBRARY::deque<int>::iterator it = mydeque.begin();
  std::deque<int>::iterator stdit = stddeque.begin();

  while (it != mydeque.end())
  {
    EXPECT_EQ(*it, *stdit);
    stdit++;
    it++;
  }
}

TEST(DequeTest, RBegin)
{

  LIBRARY::deque<int> mydeque(5); // 5 default-constructed ints
  std::deque<int> stddeque(5);
  LIBRARY::deque<int>::reverse_iterator rit = mydeque.rbegin();
  std::deque<int>::reverse_iterator stdrit = stddeque.rbegin();

  int i = 0;
  for (rit = mydeque.rbegin(); rit != mydeque.rend(); ++rit)
  {
    *stdrit++ = ++i;
    *rit = i;
  }

  std::deque<int>::iterator stdit = stddeque.begin();
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    EXPECT_EQ(*it, *stdit++);
}

TEST(DequeTest, Empty)
{
  LIBRARY::deque<int> mydeque;
  int sum(0);

  for (int i = 1; i <= 10; i++)
    mydeque.push_back(i);

  while (!mydeque.empty())
  {
    sum += mydeque.front();
    mydeque.pop_front();
  }
  EXPECT_EQ(sum, 55);
}

TEST(DequeTest, Size)
{
  LIBRARY::deque<int> myints;
  EXPECT_EQ(myints.size(), 0);
  for (int i = 0; i < 5; i++)
    myints.push_back(i);
  EXPECT_EQ(myints.size(), 5);
  myints.insert(myints.begin(), 5, 100);
  EXPECT_EQ(myints.size(), 10);
  myints.pop_back();
  EXPECT_EQ(myints.size(), 9);
}

TEST(DequeTest, MaxSize)
{
  LIBRARY::deque<int> mydeque;
  std::deque<int> stddeque;
  EXPECT_EQ(mydeque.max_size(), stddeque.max_size());
  LIBRARY::deque<double> mydeque2;
  std::deque<double> stddeque2;
  EXPECT_EQ(mydeque2.max_size(), stddeque2.max_size());
}

TEST(DequeTest, Resize)
{
  LIBRARY::deque<int> mydeque;

  // set some initial content:
  for (int i = 1; i < 10; ++i)
    mydeque.push_back(i);

  mydeque.resize(5);
  mydeque.resize(8, 100);
  mydeque.resize(1300);
  mydeque.resize(12);

  int myints[] = {1, 2, 3, 4, 5, 100, 100, 100, 0, 0, 0, 0};
  int i = 0;
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    EXPECT_EQ(*it, myints[i++]);
}

TEST(DequeTest, Bracket)
{
  LIBRARY::deque<int> mydeque(10); // 10 zero-initialized elements
  LIBRARY::deque<int> mydeque2(1300, 100); // 10 zero-initialized elements
  LIBRARY::deque<int>::size_type sz = mydeque.size();

  // assign some values:
  for (unsigned i = 0; i < sz; i++)
    mydeque[i] = i;

  // reverse order of elements using operator[]:
  for (unsigned i = 0; i < sz / 2; i++)
  {
    int temp;
    temp = mydeque[sz - 1 - i];
    mydeque[sz - 1 - i] = mydeque[i];
    mydeque[i] = temp;
  }

  // print content:
  int j = 9;
  for (unsigned i = 0; i < sz; i++)
    EXPECT_EQ(mydeque[i], j--);
  EXPECT_EQ(mydeque2[1260], 100);
}

TEST(DequeTest, At)
{
  LIBRARY::deque<unsigned> mydeque(10); // 10 zero-initialized unsigneds

  // assign some values:
  for (unsigned i = 0; i < mydeque.size(); i++)
    mydeque.at(i) = i;

  for (unsigned i = 0; i < mydeque.size(); i++)
    EXPECT_EQ(mydeque.at(i), i);
  EXPECT_ANY_THROW(mydeque.at(20));
  EXPECT_ANY_THROW(mydeque.at(-1));
}

TEST(DequeTest, Front)
{
  LIBRARY::deque<int> mydeque;

  mydeque.push_front(77);
  EXPECT_EQ(mydeque.front(), 77);
  mydeque.push_back(20);
  mydeque.front() -= mydeque.back();
  EXPECT_EQ(mydeque.front(), 57);
}

TEST(DequeTest, Back)
{
  LIBRARY::deque<int> mydeque;

  mydeque.push_back(10);

  while (mydeque.back() != 0)
    mydeque.push_back(mydeque.back() - 1);
  int i = 10;
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    EXPECT_EQ(*it, i--);
}

TEST(DequeTest, Assign)
{
  LIBRARY::deque<int> first;
  LIBRARY::deque<int> second;
  LIBRARY::deque<int> third;

  first.assign(7, 100); // 7 ints with a value of 100

  LIBRARY::deque<int>::iterator it = first.begin() + 1;

  second.assign(it, first.end() - 1); // the 5 central values of first

  int myints[] = {1776, 7, 4};
  third.assign(myints, myints + 3); // assigning from array.
  EXPECT_EQ(first.size(), 7);
  EXPECT_EQ(second.size(), 5);
  EXPECT_EQ(third.size(), 3);
}

TEST(DequeTest, PushBack)
{
  LIBRARY::deque<int> mydeque;
  LIBRARY::deque<int> mydeque2(1023);

  for (int i = 0; i < 1300; ++i)
    mydeque.push_back(i);
  mydeque2.push_back(20);
  mydeque2.push_back(30);
  EXPECT_EQ(mydeque.size(), 1300);
  EXPECT_EQ(mydeque2.size(), 1025);
  EXPECT_EQ(mydeque2.back(), 30);
}

TEST(DequeTest, PushFront)
{
  LIBRARY::deque<int> mydeque;
  LIBRARY::deque<int> mydeque2(1023);

  for (int i = 0; i < 1300; ++i)
    mydeque.push_front(i);
    mydeque2.push_front(20);
  mydeque2.push_front(30);
  EXPECT_EQ(mydeque.size(), 1300);
    EXPECT_EQ(mydeque2.size(), 1025);
  EXPECT_EQ(mydeque2.front(), 30);
}

TEST(DequeTest, PopBack)
{
  LIBRARY::deque<int> mydeque(1023, 0);
  int sum(0);
  mydeque.push_back(10);
  mydeque.push_back(20);
  mydeque.push_back(30);

  for (int i = 0; i < 10; i++){
      sum += mydeque.back();
      mydeque.pop_back();
  }
  EXPECT_EQ(mydeque.size(), 1016);
  while (!mydeque.empty())
  {
    sum += mydeque.back();
    mydeque.pop_back();
  }
  EXPECT_EQ(sum, 60);
}
TEST(DequeTest, PopFront)
{
  LIBRARY::deque<int> mydeque(1023);

  mydeque.push_back(100);
  mydeque.push_back(200);
  mydeque.push_back(300);

  while (!mydeque.empty())
  {
    mydeque.pop_front();
  }
  EXPECT_EQ(mydeque.size(), 0);
}

TEST(DequeTest, Insert)
{

  LIBRARY::deque<int> mydeque;

  // set some initial values:
  for (int i = 1; i < 6; i++)
    mydeque.push_back(i); // 1 2 3 4 5

  LIBRARY::deque<int>::iterator it;
  it = mydeque.begin();
  ++it;

  it = mydeque.insert(it, 10); // 1 10 2 3 4 5
  // "it" now points to the newly inserted 10

  mydeque.insert(it, 2, 20); // 1 20 20 10 2 3 4 5
  // "it" no longer valid!

  it = mydeque.begin() + 2;

  std::vector<int> myvector(2, 30);
  mydeque.insert(it, myvector.begin(), myvector.end());
  // 1 20 30 30 20 10 2 3 4 5

  int result[] = {1, 20, 30, 30, 20, 10, 2, 3, 4, 5};
  int i = 0;
  for (it = mydeque.begin(); it != mydeque.end(); ++it)
    EXPECT_EQ(*it, result[i++]);

  it = mydeque.begin() + 5;
  // mydeque.insert(it, 1030, 100);
  // EXPECT_EQ(mydeque.size(), 1040);
  // EXPECT_EQ(mydeque.front(), 1);
  // EXPECT_EQ(mydeque.back(), 5);
  // EXPECT_EQ(*(mydeque.begin() + 6), 100);
}

TEST(DequeTest, Erase)
{
  LIBRARY::deque<int> mydeque;

  // set some values (from 1 to 10)
  for (int i = 1; i <= 10; i++)
    mydeque.push_back(i);

  // erase the 6th element
  mydeque.erase(mydeque.begin() + 5);

  // erase the first 3 elements:
  mydeque.erase(mydeque.begin(), mydeque.begin() + 3);

  int result[] = {4, 5, 7, 8, 9, 10};
  int i = 0;
  for (LIBRARY::deque<int>::iterator it = mydeque.begin(); it != mydeque.end(); ++it)
    EXPECT_EQ(*it, result[i++]);
}

TEST(DequeTest, Swap)
{

  LIBRARY::deque<int> foo(3, 100); // three ints with a value of 100
  LIBRARY::deque<int> bar(5, 200); // five ints with a value of 200

  EXPECT_EQ(foo.size(), 3);
  EXPECT_EQ(bar.size(), 5);
  foo.swap(bar);
  EXPECT_EQ(foo.size(), 5);
  EXPECT_EQ(bar.size(), 3);
}

TEST(DequeTest, Clear)
{
  LIBRARY::deque<int> mydeque;
  mydeque.push_back(100);
  mydeque.push_back(200);
  mydeque.push_back(300);
  mydeque.clear();
  EXPECT_EQ(mydeque.size(), 0);
  mydeque.push_back(1101);
  mydeque.push_back(2202);
  EXPECT_EQ(mydeque.size(), 2);
}

TEST(DequeTest, RelOps)
{

  LIBRARY::deque<int> foo(3, 100); // three ints with a value of 100
  LIBRARY::deque<int> bar(2, 200); // two ints with a value of 200

  EXPECT_FALSE(foo == bar);
  EXPECT_TRUE(foo != bar);
  EXPECT_FALSE(foo > bar);
  EXPECT_TRUE(foo < bar);
  EXPECT_FALSE(foo >= bar);
  EXPECT_TRUE(foo <= bar);
}
