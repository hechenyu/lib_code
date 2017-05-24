// forward_list::sort
#include <iostream>
#include "sclist.h"
#include "sclist_util.h"
#include <functional>

int main ()
{
  SCList<int> mylist;
  list_init(&mylist, {22, 13, 5, 40, 90, 62, 31});

  list_selection(&mylist);

  std::cout << "default sort (operator<):";
  std::cout << mylist;
  std::cout << '\n';

  list_selection(&mylist, std::greater<int>());

  std::cout << "sort with std::greater():";
  std::cout << mylist;
  std::cout << '\n';

  return 0;
}
