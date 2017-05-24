// reversing forward_list
#include <iostream>
#include "sclist.h"
#include "sclist_iterator.h"
#include "sclist_util.h"

int main ()
{
  SCList<int> mylist;
  list_init(&mylist, {10, 20, 30, 40});

  list_reverse(&mylist);

  std::cout << "mylist contains:";
  std::cout << mylist; 
  std::cout << '\n';

  return 0;
}
