// forward_list::remove_if
#include <iostream>
#include "sclist.h"
#include "sclist_util.h"

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
class is_odd_class
{
public:
  bool operator() (const int& value) {return (value%2)==1; }
} is_odd_object;

int main ()
{
  SCList<int> mylist;
  list_init(&mylist, {7, 80, 7, 15, 85, 52, 6});

  list_remove_if (&mylist, single_digit);      // 80 15 85 52

  list_remove_if (&mylist, is_odd_object);     // 80 52

  std::cout << "mylist contains:";
  std::cout << mylist;
  std::cout << '\n';

  return 0;
}
