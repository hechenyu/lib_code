// forward_list::unique
#include <iostream>
#include <cmath>
#include "sclist.h"
#include "sclist_util.h"

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
class is_near_class
{
public:
  bool operator() (double first, double second)
  { return (fabs(first-second)<5.0); }
} is_near_object;

int main ()
{

  SCList<double> mylist;
  list_init(&mylist, { 15.2, 73.0, 3.14, 15.85, 69.5,
                                       73.0, 3.99, 15.2, 69.2,  18.5 });

  list_sort(&mylist);                        //   3.14,  3.99, 15.2, 15.2, 15.85
                                             //  18.5,  69.2,  69.5, 73.0, 73.0

  list_unique(&mylist);                      //   3.14,  3.99, 15.2, 15.85
                                             //  18.5,  69.2,  69.5, 73.0

  list_unique(&mylist, same_integral_part);  //  3.14, 15.2, 18.5,  69.2, 73.0

  list_unique(&mylist, is_near_object);      //  3.14, 15.2, 69.2

  std::cout << "mylist contains:";
  std::cout << mylist;
  std::cout << '\n';

  return 0;
}
