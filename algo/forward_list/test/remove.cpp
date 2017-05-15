// remove from forward_list
#include <iostream>
#include "sclist.h"
#include "sclist_util.h"

int main ()
{
  SCList<int> mylist;
  list_init(&mylist, {10, 20, 30, 40, 30, 20, 10});

  list_remove(&mylist, 20);

  std::cout << "mylist contains:";
  std::cout << mylist;
  std::cout << '\n';

  return 0;
}
