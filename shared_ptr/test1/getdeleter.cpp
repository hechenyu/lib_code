#include <iostream>

#include "shared_ptr.h"

using std::cout;

struct del
{
    void operator ()(void *ptr)
    {
        delete ptr;
    }
};

int main()
{
    Shared_ptr<int> sp0(new int);
    Shared_ptr<int> sp1(new int, del());
    cout << get_deleter<del>(sp0) << '\n';
    cout << get_deleter<del>(sp1) << '\n';

    return 0;
}

