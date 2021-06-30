#include "List.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {
  List<int> list;
  list.insertBack(1);
  list.insertBack(2);
  list.insertBack(3);
  list.insertBack(4);
  list.insertBack(5);
  list.insertBack(6);
  list.insertBack(7);
  list.insertBack(8);
  list.insertBack(9);
  list.insertBack(10);
  list.insertBack(11);
  list.insertBack(12);

  std::stringstream s1, s2;
  List<int> slist = list;
  list.reverseNth(4);


  /**
  for (List<int>::ListIterator i = slist.begin(); i != slist.end(); ++i) {
    std::cout << *i;
  }
  */

  list.print(s1);
  slist.print(s2);
  std::cout << s1.str();
  std::cout << s2.str();
  return 0;
}
