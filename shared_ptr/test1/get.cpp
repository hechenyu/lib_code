#include <iostream>

#include "shared_ptr.h"

using std::cout;

int main()
{
	int *ip = new int(3);
	cout << (void *) ip << '\n';
	Shared_ptr<int> sp(ip);
	cout << (void *) sp.get() << '\n';
	Shared_ptr<int> sq;
	cout << (void *) sq.get() << '\n';

	return 0;
}
