#include <ostream>

#include "shared_ptr.h"
#include "sputil.h"

int main()
{
    shared_ptr<resource> sp((resource *) 0);
    show("construct from null pointer", sp);

    return 0;
}
