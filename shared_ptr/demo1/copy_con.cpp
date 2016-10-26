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

void print_details(const shared_ptr<int> &sp)
{
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
}

int main()
{
    cout << "sizeof int: " << sizeof (int) << '\n';
    cout << "sizeof sp_counted_impl_p<int>: " << sizeof (sp_counted_impl_p<int>) << '\n';

    cout << "shared_ptr<int> sp0(new int(3));" << '\n';
    shared_ptr<int> sp0(new int(3));

    cout << "-----------------------------\n";
    cout << "sp0:\n";
    print_details(sp0);
    cout << "-----------------------------\n\n";

    cout << "shared_ptr<int> sp1(sp0);" << '\n';
    shared_ptr<int> sp1(sp0);

    cout << "-----------------------------\n";
    cout << "sp0:\n";
    print_details(sp0);
    cout << "-----------------------------\n\n";

    cout << "-----------------------------\n";
    cout << "sp1:\n";
    print_details(sp1);
    cout << "-----------------------------\n\n";

    cout << "sp0.reset();" << '\n';
    sp0.reset();

    cout << "-----------------------------\n";
    cout << "sp0:\n";
    print_details(sp0);
    cout << "-----------------------------\n\n";

    cout << "-----------------------------\n";
    cout << "sp1:\n";
    print_details(sp1);
    cout << "-----------------------------\n\n";

    cout << "sp1.reset();" << '\n';
    sp1.reset();

    cout << "-----------------------------\n";
    cout << "sp0:\n";
    print_details(sp0);
    cout << "-----------------------------\n\n";

    cout << "-----------------------------\n";
    cout << "sp1:\n";
    print_details(sp1);
    cout << "-----------------------------\n\n";

    return 0;
}

