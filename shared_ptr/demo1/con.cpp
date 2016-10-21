#include <iostream>
#include "shared_ptr.h"

using std::cout;

void print_details(const shared_ptr<int> &sp)
{
    cout << "use_count: " << sp.use_count() << '\n'
        << "get: " << sp.get() << '\n';
    if (sp) {
        cout << "resource value: " << *sp << '\n';
    } else {
        cout << "no resource\n";
    }
    if (get_deleter<void>(sp)) {
        cout << "deleter at: " << get_deleter<void>(sp) << '\n';
    } else {
        cout << "no deleter, use default delete\n";
    }
}

struct deleter
{
    void operator ()(int *p)
    {
        cout << "destroying int at "
            << (void *) p << '\n';
        delete p;
    }
};

int main()
{
    shared_ptr<int> sp0;
    shared_ptr<int> sp1(new int(3));
    shared_ptr<int> sp2(nullptr);
    shared_ptr<int> sp3(new int(3), deleter());

    cout << "-----------------------------\n";
    cout << "sp0:\n";
    print_details(sp0);
    cout << "-----------------------------\n\n";

    cout << "-----------------------------\n";
    cout << "sp1:\n";
    print_details(sp1);
    cout << "-----------------------------\n\n";

    cout << "-----------------------------\n";
    cout << "sp2:\n";
    print_details(sp2);
    cout << "-----------------------------\n\n";

    cout << "-----------------------------\n";
    cout << "sp3:\n";
    print_details(sp3);
    cout << "-----------------------------\n\n";

    return 0;
}
