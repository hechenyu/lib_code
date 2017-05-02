#include <iostream>
#include "shared_ptr.h"

#include "sputil.h"

using std::cout;

int main()
{
    weak_ptr<resource> empty_wp;
    show("empty weak_ptr", empty_wp);

    try 
    {
        shared_ptr<resource> sp0(empty_wp);
    }
    catch (const bad_weak_ptr &)
    {
        cout << "caught bad_weak_ptr object\n";
    }

    shared_ptr<resource> sp((resource *) 0);
    weak_ptr<resource> wp1(sp);
    shared_ptr<resource> sp1(wp1);
    show("weak_ptr holding null pointer", wp1);
    show("copy of weak_ptr holding null pointer", sp1);

    sp.reset(new resource);
    weak_ptr<resource> wp2(sp);
    shared_ptr<resource> sp2(wp2);
    show("weak_ptr holding pointer to resource", wp2);
    show("shared_ptr holding pointer to resource", sp2);

    show("weak_ptr holding null pointer", wp1);
    show("copy of weak_ptr holding null pointer", sp1);

    shared_ptr<resource> sp3(new resource);
    weak_ptr<resource> wp3(sp3);
    sp3.reset();
    try
    {
        shared_ptr<resource> sp4(wp3);
    }
    catch (const bad_weak_ptr &)
    {
        cout << "caught bad_weak_ptr object\n";
    }

    return 0;
}
