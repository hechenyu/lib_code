#include <iostream>
#include <ostream>

#include "shared_ptr.h"
#include "sputil.h"

using std::cout;

resource *get_resource(int i)
{
    resource *res = new resource(i);
    cout << "created resource with value "
        << *res << '\n';
    return res;
}

void destroy_resource(resource *res)
{
    cout << "destroying resource with value "
        << *res << '\n';
    delete res;
}

int main()
{
    shared_ptr<resource> sp(get_resource(3),
        destroy_resource);

    cout << "In main, resource has value "
        << *sp << '\n';

    return 0;
}

