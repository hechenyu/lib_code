// forward_list::swap
#include <iostream>
#include "sclist.h"
#include "sclist_util.h"

int main ()
{
  SCList<int> first;
  SCList<int> second;
  list_init(&first, {10, 20, 30});
  list_init(&second, {100, 200});

  list_swap(&first, &second);

  std::cout << "first contains:";
  std::cout << first;
  std::cout << std::endl;

  std::cout << "second contains:";
  std::cout << second;
  std::cout << std::endl;

  return 0;
}
