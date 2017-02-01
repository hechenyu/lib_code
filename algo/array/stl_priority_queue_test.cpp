#include <iostream>
#include <string>
#include <stdlib.h>
#include "stl_priority_queue.h"

using namespace stl;

void test_empty()
{
    priority_queue<int> mypq;
    int sum (0);

    for (int i=1;i<=10;i++) mypq.push(i);

    while (!mypq.empty())
    {
        sum += mypq.top();
        mypq.pop();
    }

    std::cout << "total: " << sum << '\n';
}

void test_push_pop()
{
    priority_queue<int> mypq;

    mypq.push(30);
    mypq.push(100);
    mypq.push(25);
    mypq.push(40);

    std::cout << "Popping out elements...";
    while (!mypq.empty())
    {
        std::cout << ' ' << mypq.top();
        mypq.pop();
    }
    std::cout << '\n';
}

void test_size()
{
    priority_queue<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';
}

void test_top()
{
    priority_queue<int> mypq;

    mypq.push(10);
    mypq.push(20);
    mypq.push(15);

    std::cout << "mypq.top() is now " << mypq.top() << '\n';
}

void test_main(int argc, char *argv[])
{
    priority_queue<int> mypq;

    // push front
    for (int i = 1; i < argc; i++) {
        mypq.push(atoi(argv[i]));
        std::cout << atoi(argv[i]) << " ";
    }
    std::cout << std::endl;

    // pop front
    while (!mypq.empty()) {
        std::cout << mypq.top() << " ";
        mypq.pop();
    }
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    test_empty();
    test_push_pop();
    test_size();
    test_top();
    test_main(argc, argv);

    return 0;
}
