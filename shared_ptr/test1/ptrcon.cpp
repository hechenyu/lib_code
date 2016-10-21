#include <ostream>

#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    Shared_ptr<resource> sp(new resource(3));
    show("construct from pointer", sp);

    return 0;
}

