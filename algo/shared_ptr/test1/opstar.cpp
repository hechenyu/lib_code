#include <iostream>

#include "shared_ptr.h"

using std::cout;

int main()
{
	int *ip = new int(3);
	cout << (void *) ip << '\n';
	shared_ptr<int> sp(ip);
	cout << *sp << '\n';
	cout << (void *)&*sp << '\n';
	return 0;
}
