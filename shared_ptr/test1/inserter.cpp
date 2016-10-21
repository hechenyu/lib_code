#include <iostream>

#include "shared_ptr.h"

using std::cout;

int main()
{
    Shared_ptr<int> sp(new int);
    cout << "   get: " << sp.get() << '\n';
    cout << "object: " << sp << '\n';

    return 0;
}
