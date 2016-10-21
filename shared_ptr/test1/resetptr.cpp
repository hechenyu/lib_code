#include "shared_ptr.h"
#include "sputil.h"

using std::cout;

class FreeResource {
public:
	void operator ()(resource *res)
	{
		cout << "delete resource: ";
		if (res != NULL)
			cout << *res;
		cout << "\n";
		delete res;
	}
};

int main()
{
    Shared_ptr<resource> sp0;
    show("empty object before reset", sp0);

    sp0.reset(new resource(1), FreeResource());
    show("empty object after reset", sp0);

    sp0.reset(new resource(2), FreeResource());
    show("non-empty object after reset", sp0);

    return 0;
}
