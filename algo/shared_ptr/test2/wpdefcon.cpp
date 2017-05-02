#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    weak_ptr<int> sp;
    show("default constructor", sp);

    return 0;
}

