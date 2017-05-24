// forward_list::before_begin
#include <iostream>
#include "sclist.h"
#include "sclist_iterator.h"
#include "sclist_util.h"

int main ()
{
  SCList<int> mylist;
  list_init(&mylist, {20, 30, 40, 50});

  list_insert_next(list_dummy_head(&mylist), new SCList_node<int>(11));

  std::cout << "mylist contains:";
  std::cout << mylist;
  std::cout << '\n';

  list_destroy(&mylist);
  return 0;
}
