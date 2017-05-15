// forward_list::sort
#include <iostream>
#include "forward_list.h"
#include <functional>

int main ()
{
  forward_list<int> mylist = {22, 13, 5, 40, 90, 62, 31};

  mylist.sort();

  std::cout << "default sort (operator<):";
  for (int& x: mylist) std::cout << ' ' << x;
  std::cout << '\n';

  mylist.sort(std::greater<int>());

  std::cout << "sort with std::greater():";
  for (int& x: mylist) std::cout << ' ' << x;
  std::cout << '\n';

  return 0;
}
