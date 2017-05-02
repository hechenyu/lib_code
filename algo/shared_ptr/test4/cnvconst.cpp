#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    shared_ptr<const resource> sp(new resource(1));
    show("shared_ptr to const object", sp);
    shared_ptr<resource> sp0 =
        const_pointer_cast<resource>(sp);
    show("shared_ptr to non-const object", sp0);

    return 0;
}

