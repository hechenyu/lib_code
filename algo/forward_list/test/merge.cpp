// forward_list::merge
#include <iostream>
#include "sclist.h"
#include "sclist_util.h"
#include <functional>

int main ()
{
  SCList<double> first;
  SCList<double> second;
  SCList<double> third;
  list_init(&first, {4.2, 2.9, 3.1});
  list_init(&second, {1.4, 7.7, 3.1});
  list_init(&third, {6.2, 3.7, 7.1});

  list_sort(&first);
  list_sort(&second);
  list_merge(&first, &second);

  std::cout << "first contains:";
  std::cout << first;
  std::cout << std::endl;

  list_sort(&first, std::greater<double>());
  list_sort(&third, std::greater<double>());
  list_merge(&first, &third, std::greater<double>());

  std::cout << "first contains:";
  std::cout << first;
  std::cout << std::endl;

  list_destroy(&third);
  list_destroy(&second);
  list_destroy(&first);

  return 0;
}
