#include <iostream>

#ifndef NDEBUG
#define private public
#endif

#include "shared_ptr.h"

using std::cout;

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
    if (get_deleter<void>(sp)) {
        cout << "get_deleter: " << get_deleter<void>(sp) << '\n';
    } else {
        cout << "no deleter, use default delete\n";
    }
    cout << "-----------------------------\n\n";
}

struct deleter
{
    void operator ()(int *p)
    {
        cout << "destroying int at "
            << p << '\n';
        delete p;
    }
};

int main()
{
    shared_ptr<int> sp0;
    shared_ptr<int> sp1(new int(3));
    shared_ptr<int> sp2(nullptr);
    shared_ptr<int> sp3(new int(3), deleter());

    print_details(sp0, "sp0");
    print_details(sp1, "sp1");
    print_details(sp2, "sp2");
    print_details(sp3, "sp3");

    return 0;
}
