#include <iomanip>
#include <iostream>
#include "shared_ptr.h"
#include "sputil.h"

using std::cout;
using std::boolalpha;

int main()
{
    cout << boolalpha;
    shared_ptr<resource> sp(new resource);
    weak_ptr<resource> wp(sp);
    cout << "points to resource: " << wp.expired() << '\n';
    sp.reset();
    cout << "expired: " << wp.expired() << '\n';

    return 0;
}
