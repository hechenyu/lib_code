#include <iostream>

#include "shared_ptr.h"

using std::cout;

typedef Shared_ptr<int> spi;

int main()
{
	spi sp0;
	cout << "empty object: " << sp0.use_count() << '\n';
	spi sp1((int *) 0);
	cout << "null pointer: " << sp1.use_count() << '\n';
	spi sp2(new int);
	cout << "one object: " << sp2.use_count() << '\n';
	{
		spi sp3(sp2);
		cout << "two object: " << sp2.use_count() << '\n';
	}
	cout << "one object: " << sp2.use_count() << '\n';
	return 0;
}
