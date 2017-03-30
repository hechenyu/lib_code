#include <stdio.h>
#include <iostream>
#include <stdexcept>

#ifndef NDEBUG
#define private public
#endif

#include "shared_ptr.h"

using std::cout;

void *operator new(size_t sz)
{
    void *res = malloc(sz);
    if (res == 0) {
        printf("no memory");
        throw std::bad_alloc();
    }
    printf("\n*** new %d bytes at %p ***\n", (int) sz, res);
    return res;
}

void operator delete(void *ptr)
{
    printf("\n*** delete at %p ***\n", ptr);
    free(ptr);
}

void print_details(const shared_ptr<int> &sp, const std::string &name)
{
    cout << "-----------------------------\n";
    cout << name << '\n';
#ifndef NDEBUG
    cout << "pi_: " << sp.pi_ << '\n';
#endif
    cout << "use_count: " << sp.use_count() << '\n'
        << "get: " << sp.get() << '\n';
    if (sp) {
        cout << "resource value: " << *sp << '\n';
    } else {
        cout << "no resource\n";
    }
    cout << "-----------------------------\n\n";
}

int main()
{
    cout << "sizeof int: " << sizeof (int) << '\n';
#ifndef NDEBUG
    cout << "sizeof long: " << sizeof (long) << '\n';
    cout << "sizeof atomic<long>: " << sizeof (std::atomic<long>) << '\n';
    cout << "sizeof sp_counted_base: " << sizeof (sp_counted_base) << '\n';
    cout << "sizeof sp_counted_impl_p<int>: " << sizeof (sp_counted_impl_p<int>) << '\n';
#endif

    int *p = new int(3);
    shared_ptr<int> sp0(p);
    shared_ptr<int> sp1(p);
    print_details(sp0, "sp0");
    print_details(sp1, "sp1");

    sp0.reset();
    sp1.reset();

    return 0;
}
