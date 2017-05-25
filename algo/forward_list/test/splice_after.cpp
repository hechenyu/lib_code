// forward_list::splice_after
#include <iostream>
#include "sclist.h"
#include "sclist_util.h"

int main ()
{
  SCList<int> first;
  SCList<int> second;
  list_init(&first, { 1, 2, 3 });
  list_init(&second, { 10, 20, 30 });

  auto it = list_head(&first);  // points to the 1

  list_transfer_next ( list_dummy_head(&first), &second );
                          // first: 10 20 30 1 2 3
                          // second: (empty)
                          // "it" still points to the 1 (now first's 4th element)

  list_transfer_next ( list_dummy_head(&second), list_head(&first), it);
                          // first: 10 1 2 3
                          // second: 20 30

  list_transfer_next ( list_dummy_head(&first), list_head(&second) );
                          // first: 30 10 1 2 3
                          // second: 20
                          // * notice that what is moved is AFTER the iterator

  std::cout << "first contains:";
  std::cout << first;
  std::cout << std::endl;

  std::cout << "second contains:";
  std::cout << second;
  std::cout << std::endl;

  return 0;
}
