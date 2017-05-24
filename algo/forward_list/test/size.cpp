#include "sclist.h"
#include "sclist_util.h"
#include <iostream>
 
int main()
{ 
  SCList<int> nums;
  list_init(&nums, {1, 3, 5, 7});

  std::cout << "nums contains " << list_size(&nums) << " elements.\n";

  list_destroy(&nums);
  return 0;
}
