#include <map>
#include <iostream>
#include "../ft.hpp"

#ifndef LIBRARY
# define LIBRARY ft
#endif

bool fncomp (char lhs, char rhs) {return lhs<rhs;}

struct classcomp {
  bool operator() (const char& lhs, const char& rhs) const
  {return lhs<rhs;}
};


int main ()
{
  LIBRARY::map<int,int> first;


  first[3]=70;
  // std::cout << "root = " << first.root_->pair_.first << '\n';

  first[1]=20;
  first[2]=120;
  first[3]=120;
  first[4]=120;
  first[5]=120;
  first[6]=100;
  first[7]=100;
  first[8]=160;
  first[9]=160;
  // std::cout << "root = " << first.root_->pair_.first << '\n';

  first[10]=10;
  first[11]=30;
  first[12]=50;
  first[2]=50;
  first[4]=50;
  first[21]=30;
  first[32]=50;
  first[44]=50;
  first[41]=50;
  // first.printTree();
  // first[1]=20;
  // first[5]=120;
  // first[5]=120;
  //
  // first[7]=100;
  // first[6]=100;
  // first[8]=160;
  // first[9]=160;
  // std::cout << "root = " << first.root_->pair_.first << '\n';
  //
  // first[10]=10;
  // first[11]=30;
  // first[12]=50;
  // first[2]=50;
  // // first[4]=50;
  // // first[21]=30;
  // // first[32]=50;
  // // first[44]=50;
  // // first[41]=50;
  // first.printTree();


  // std::cout << "root = " << first.root_->pair_.first << '\n';
  std::cout << "size = " << first.size()<< '\n';

	first.erase(2);
	std::cout << "size = " << first.size()<< '\n';

  std::cout << "first:" << '\n';
   for (LIBRARY::map<int,int>::iterator it = first.begin(); it != first.end(); it++)
		std::cout << "[" <<  it->first << "][" << it->second << "] - ";
		// std::cout << "[" <<  it->first << "][" << it->second << "][" <<  it.base()->isRed_ << "] - ";
		std::cout << '\n';
		std::cout << "\n/* ----------------------------- */" << '\n';


	// LIBRARY::map<int,int>::iterator it = first.begin();
    // std::cout << it->first << '\n';
	// it++;
    // std::cout << it->first << '\n';
	// it++;
    // std::cout << it->first << '\n';
	// it++;
    // std::cout << it->first << '\n';
	// it++;
	// if (it.base())
    // 	std::cout << "last ? " <<  it->first << '\n';




	// first.printTree();
 // Node *tmp = first.begin().base()
 // first.checkColor(first.begin().base());
 // first.checkColor(first.uppest().base());
 //
 //  LIBRARY::map<char,int> second (first.begin(),first.end());
 //  std::cout << "\nsecond:" << '\n';
 //  for (LIBRARY::map<char,int>::iterator it = second.begin(); it != second.end(); it++)
	//    std::cout << it->first << ' ' << it->second << " | ";
 // //
 //  LIBRARY::map<char,int> third (second);
 //  std::cout << "\nthird:" << '\n';
 //  for (LIBRARY::map<char,int>::iterator it = third.begin(); it != third.end(); it++)
	//   std::cout << it->first << ' ' << it->second << " | ";
 //
 //  LIBRARY::map<char,int,classcomp> fourth;                 // class as Compare
 //
 //  bool(*fn_pt)(char,char) = fncomp;
 //  LIBRARY::map<char,int,bool(*)(char,char)> fifth (fn_pt); // function pointer as Compare
 //  std::cout << "\nSize of first: " << first.size() << '\n';
 //  std::cout << "Size of second: " << second.size() << '\n';
 //  std::cout << "Size of third: " << third.size() << '\n';
 //  std::cout << "Size of fourth: " << fourth.size() << '\n';
 // first.clear();
 // second.clear();
 //
 // first['x']=8;
 // first['y']=16;
 // first['z']=32;
 // //
 // second=first;                // second now contains 3 ints
	// std::cout << "\n----------------------------------------------------" << '\n';
 // for (LIBRARY::map<char,int>::iterator it = first.begin(); it != first.end(); it++)
	//  std::cout << it->first << ' ' << it->second << '\n';
 // first=LIBRARY::map<char,int>();  // and first is now empty
 //
 // std::cout << "Size of first: " << first.size() << '\n';
 // std::cout << "Size of second: " << second.size() << '\n';
 return 0;
}
