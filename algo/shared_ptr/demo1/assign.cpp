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
        << "get: " << sp.get() << '\n'
        << "unique: " << std::boolalpha << sp.unique() << '\n'
        << "operator bool: " << static_cast<bool>(sp) << '\n';
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

    cout << "shared_ptr<int> sp0(new int(3));" << '\n';
    shared_ptr<int> sp0(new int(3));

    cout << "shared_ptr<int> sp1(new int(3));" << '\n';
    shared_ptr<int> sp1(new int(4));

    print_details(sp0, "sp0");
    print_details(sp1, "sp1");

    cout << "sp0 = sp1;" << '\n';
    sp0 = sp1;

    print_details(sp0, "sp0");
    print_details(sp1, "sp1");

    return 0;
}

