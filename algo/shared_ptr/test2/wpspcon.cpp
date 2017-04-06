#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    shared_ptr<resource> sp(new resource(4));

    show("shared_ptr", sp);
    weak_ptr<resource> wp(sp);
    show("weak_ptr", wp);

    return 0;
}
