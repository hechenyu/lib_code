#include <iostream>

#include "shared_ptr.h"

using std::cout;

struct S {
	int member;
};

int main()
{
	S *s = new S;
	s->member = 4;
	Shared_ptr<S> sp(s);
	cout << sp->member << '\n';
	return 0;
}
