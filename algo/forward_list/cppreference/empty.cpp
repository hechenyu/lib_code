#include "forward_list.h"
#include <iostream>

int main()
{
    forward_list<int> numbers;
    std::cout << "Initially, numbers.empty(): " << numbers.empty() << '\n';

    numbers.push_front(42);
    numbers.push_front(13317);
    std::cout << "After adding elements, numbers.empty(): " << numbers.empty() << '\n';
}
