// forward_list::begin example
#include <iostream>
#include "sclist.h"
#include "sclist_iterator.h"
#include "sclist_util.h"

int main ()
{
  SCList<int> mylist;
  list_init(&mylist, { 34, 77, 16, 2 });

  std::cout << "mylist contains:";
  for ( auto it = list_begin(&mylist); it != list_end(&mylist); ++it )
    std::cout << ' ' << *it;

  std::cout << '\n';

  list_destroy(&mylist);
  return 0;
}
