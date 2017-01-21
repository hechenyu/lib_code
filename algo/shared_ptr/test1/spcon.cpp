#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    shared_ptr<resource> sp0(new resource(4));

    show("construct from pointer", sp0);
    shared_ptr<resource> sp1(sp0);

    show("construct from shared_ptr object", sp1);
    show("after copying", sp0);

    return 0;
}
