// forward_list::empty
#include <iostream>
#include "forward_list.h"

int main ()
{
  forward_list<int> first;
  forward_list<int> second = {20, 40, 80};
  std::cout << "first " << (first.empty() ? "is empty" : "is not empty" ) << std::endl;
  std::cout << "second " << (second.empty() ? "is empty" : "is not empty" ) << std::endl;
  return 0;
}
