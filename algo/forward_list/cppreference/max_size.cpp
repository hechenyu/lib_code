#include <iostream>
#include "forward_list.h"

int main()
{
    forward_list<char> s;
    std::cout << "Maximum size of a 'forward_list' is " << s.max_size() << "\n";
}
