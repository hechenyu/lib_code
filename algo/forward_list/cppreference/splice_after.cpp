#include <iostream>
#include "forward_list.h"
 
int main()
{
    forward_list<int> l1 = {1,2,3,4,5};
    forward_list<int> l2 = {10,11,12};
 
    l2.splice_after(l2.cbegin(), l1, l1.cbegin(), l1.cend());
    // not equivalent to l2.splice_after(l2.cbegin(), l1);
 
    for(int n : l1)
        std::cout << n << ' ';
    std::cout << '\n';
 
    for(int n : l2)
        std::cout << n << ' ';
    std::cout << '\n';
}
