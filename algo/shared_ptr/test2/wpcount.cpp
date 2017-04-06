#include "shared_ptr.h"
#include <iostream>

using std::cout;

typedef shared_ptr<int> spi;
typedef weak_ptr<int> wpi;

int main()
{
    wpi wp0;
    cout << "empty object: " << wp0.use_count() << '\n';

    spi sp1((int *) 0);
    wpi wp1(sp1);
    cout << "null pointer: " << wp1.use_count() << '\n';

    spi sp2(new int);
    wpi wp2(sp2);

    cout << "one object: " << wp2.use_count() << '\n';
    {
        spi sp3(sp2);
        cout << "two objects: " << wp2.use_count() << '\n';
    }
    cout << "one object: " << wp2.use_count() << '\n';
    sp2.reset();
    cout << "expired: " << wp2.use_count() << '\n';

    return 0;
}
