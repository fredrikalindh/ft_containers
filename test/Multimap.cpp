#include "../includes/ft.hpp"
#include <map>
#include <iostream>

void test()
{
  ft::multimap<char, int> mymultimap;

  // insert some values:
  mymultimap.insert(ft::pair<char, int>('a', 10));
  mymultimap.insert(ft::pair<char, int>('b', 20));
  mymultimap.insert(ft::pair<char, int>('b', 30));
  mymultimap.insert(ft::pair<char, int>('c', 40));
  mymultimap.insert(ft::pair<char, int>('d', 50));
  mymultimap.insert(ft::pair<char, int>('d', 60));
  mymultimap.insert(ft::pair<char, int>('e', 70));
  mymultimap.insert(ft::pair<char, int>('f', 80));

  ft::multimap<char, int>::iterator it = mymultimap.find('b');

    mymultimap.erase(it); // erasing by iterator (1 element)
    // std::cout << "[[[[[2]]]]]" << std::endl;
         mymultimap.erase('d'); // erasing by key (2 elements)

    it = mymultimap.find('e');

  for (ft::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it){
    // std::cout << "?" << std::endl;
     std::cout << it->first << "=>" << it->second << ", ";
    }
    std::cout << '\n';
  mymultimap.erase(it, mymultimap.end()); // erasing by range

//   int i = 0;
//   int result1[] = {10, 30, 40};
  for (ft::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it){
    // std::cout << "?" << std::endl;
     std::cout << it->first << "=>" << it->second << ", ";
    }
    std::cout << '\n';

    // EXPECT_EQ(it->second, result1[i++]);
}

int main()
{
    test();
    // ft::multimap<char, int> mymap;
    // std::multimap<char, int> stdmap;
    // ft::multimap<char, int>::iterator it;
    // std::multimap<char, int>::iterator stdit;

    // mymap.insert(ft::pair<char, int>('a', 10));
    // stdmap.insert(std::pair<char, int>('a', 10));
    // mymap.insert(ft::pair<char, int>('a', 20));
    // stdmap.insert(std::pair<char, int>('a', 20));
    // mymap.insert(ft::pair<char, int>('a', 30));
    // stdmap.insert(std::pair<char, int>('a', 30));
    // mymap.insert(ft::pair<char, int>('b', 50));
    // stdmap.insert(std::pair<char, int>('b', 50));
    // for (it = mymap.begin(); it != mymap.end(); ++it)
    //     std::cout << it->first << "=>" << it->second << ", ";
    // std::cout << '\n';
    // for (stdit = stdmap.begin(); stdit != stdmap.end(); ++stdit)
    //     std::cout << stdit->first << "=>" << stdit->second << ", ";
    // std::cout << '\n';
    
    // mymap.insert(ft::pair<char, int>('b', 300));
    // stdmap.insert(std::pair<char, int>('b', 300));

    // mymap.insert(mymap.find('b'), ft::pair<char, int>('b', 200));
    // stdmap.insert(stdmap.find('b'), std::pair<char, int>('b', 200));
    // mymap.insert(--mymap.find('b'), ft::pair<char, int>('b', 0));
    // stdmap.insert(--stdmap.find('b'), std::pair<char, int>('b', 0));

    // std::cout << "HEJJJ" << std::endl;
    // std::cout << mymap.find('a')->second << '\n';
    // std::cout << stdmap.find('a')->second << '\n';
    // std::cout << mymap.find('b')->second << '\n';
    // std::cout << stdmap.find('b')->second << '\n';

    //  std::cout << "HEJJJ" << std::endl;
    // //  int i = mymap.size();
    // for (it = mymap.begin(); it != mymap.end(); ++it){
    //     std::cout << it->first << "=>" << it->second << ", ";
    //     // if (!--i) break ;
    // }std::cout << '\n';
    // for (stdit = stdmap.begin(); stdit != stdmap.end(); ++stdit)
    //     std::cout << stdit->first << "=>" << stdit->second << ", ";
    // std::cout << '\n';
    return 0;
}
// void test()
// {
//   ft::multimap<char, int> mymultimap;
//   ft::multimap<char, int>::iterator it;

//   // first insert function version (single parameter):
//   mymultimap.insert(ft::pair<char, int>('a', 100));
//   mymultimap.insert(ft::pair<char, int>('z', 150));
//   it = mymultimap.insert(ft::pair<char, int>('b', 75));

//   // second insert function version (with hint position):
//   mymultimap.insert(it, ft::pair<char, int>('c', 300)); // max efficiency inserting
// //   mymultimap.insert(it, ft::pair<char, int>('z', 400)); // no max efficiency inserting

// //   // third insert function version (range insertion):
// //   ft::multimap<char, int> anothermultimap;
// //   anothermultimap.insert(mymultimap.begin(), mymultimap.find('c'));

// //   int i = 0;
// //   int result1[] = {100, 75, 300, 400, 150};
//   for (ft::multimap<char, int>::iterator it = mymultimap.begin(); it != mymultimap.end(); ++it){
//     std::cout << it->first << "=>" << it->second << ", ";
//     // EXPECT_EQ(it->second, result1[i++]);
// }
// //   i = 0;
// //   int result2[] = {100, 75};
// //   for (ft::multimap<char, int>::iterator it = anothermultimap.begin(); it != anothermultimap.end(); ++it)
// //     EXPECT_EQ(it->second, result2[i++]);
// }

// int main()
// {
//     test();
//     // ft::multimap<char, int> mymap;
//     // std::multimap<char, int> stdmap;
//     // ft::multimap<char, int>::iterator it;
//     // std::multimap<char, int>::iterator stdit;

//     // mymap.insert(ft::pair<char, int>('a', 10));
//     // stdmap.insert(std::pair<char, int>('a', 10));
//     // mymap.insert(ft::pair<char, int>('a', 20));
//     // stdmap.insert(std::pair<char, int>('a', 20));
//     // mymap.insert(ft::pair<char, int>('a', 30));
//     // stdmap.insert(std::pair<char, int>('a', 30));
//     // mymap.insert(ft::pair<char, int>('b', 50));
//     // stdmap.insert(std::pair<char, int>('b', 50));
//     // for (it = mymap.begin(); it != mymap.end(); ++it)
//     //     std::cout << it->first << "=>" << it->second << ", ";
//     // std::cout << '\n';
//     // for (stdit = stdmap.begin(); stdit != stdmap.end(); ++stdit)
//     //     std::cout << stdit->first << "=>" << stdit->second << ", ";
//     // std::cout << '\n';
    
//     // mymap.insert(ft::pair<char, int>('b', 300));
//     // stdmap.insert(std::pair<char, int>('b', 300));

//     // mymap.insert(mymap.find('b'), ft::pair<char, int>('b', 200));
//     // stdmap.insert(stdmap.find('b'), std::pair<char, int>('b', 200));
//     // mymap.insert(--mymap.find('b'), ft::pair<char, int>('b', 0));
//     // stdmap.insert(--stdmap.find('b'), std::pair<char, int>('b', 0));

//     // std::cout << "HEJJJ" << std::endl;
//     // std::cout << mymap.find('a')->second << '\n';
//     // std::cout << stdmap.find('a')->second << '\n';
//     // std::cout << mymap.find('b')->second << '\n';
//     // std::cout << stdmap.find('b')->second << '\n';

//     //  std::cout << "HEJJJ" << std::endl;
//     // //  int i = mymap.size();
//     // for (it = mymap.begin(); it != mymap.end(); ++it){
//     //     std::cout << it->first << "=>" << it->second << ", ";
//     //     // if (!--i) break ;
//     // }std::cout << '\n';
//     // for (stdit = stdmap.begin(); stdit != stdmap.end(); ++stdit)
//     //     std::cout << stdit->first << "=>" << stdit->second << ", ";
//     // std::cout << '\n';
//     return 0;
// }
