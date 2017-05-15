#include "forward_list.h"
#include <iostream>

int main()
{
    forward_list<char> characters;

    characters.assign(5, 'a');

    for (char c : characters) {
        std::cout << c << '\n';
    }

    return 0;
}
