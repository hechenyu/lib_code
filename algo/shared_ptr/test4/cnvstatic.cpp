#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    shared_ptr<resource> sp(new d_res(1));
    shared_ptr<d_res> sp0 = static_pointer_cast<d_res>(sp);
    show("base resource", sp);
    show("derived resource", sp0);

    sp.reset();
    sp0 = static_pointer_cast<d_res>(sp);
    show("null pointer to base resource", sp);
    show("null pointer to derived resource", sp0);

    return 0;
}
