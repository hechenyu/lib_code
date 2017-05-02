#include <stdlib.h>
#include <iostream>
#include <new>

#include "shared_ptr.h"
#include "sputil.h"

using std::bad_alloc;
using std::cout;

static bool no_memory = false;

void *operator new(size_t sz)
{
    void *res;
    bool no_mem = no_memory;
    no_memory = false;
    if (no_mem || (res = malloc(sz)) == 0)
        throw bad_alloc();

    return res;
}

void operator delete(void *ptr)
{
    free(ptr);
}

int main()
{
    try
    {
        cout << "construct with no memory:\n";
        instrumented *ip = new instrumented;
        no_memory = true;
        shared_ptr<instrumented> sp0(ip);
    }
    catch(...)
    {
        cout << " caught the exception\n";
    }

    try
    {
        cout << "reset with no memory:\n";
        shared_ptr<instrumented> sp1;
        instrumented *ip = new instrumented;
        no_memory = true;
        sp1.reset(ip);
    }
    catch(...)
    {
        cout << " caught the exception\n";
    }

    return 0;
}

