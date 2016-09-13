#include <iostream>

#include "shared_ptr.h"
#include "sputil.h"

typedef Shared_ptr<resource> sps;

static void asgn0()
{
    sps sp0(new resource(1));
    show("construct sp0", sp0);

    sps sp1(new resource(2));
    show("construct sp1", sp1);

    sp1 = sp0;

    show("assign, sp0", sp0);
    show("assign, sp1", sp1);
}

int main()
{
    asgn0();

    return 0;
}
