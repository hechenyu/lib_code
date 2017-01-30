#include <iostream>
#include "stl_queue.h"

using namespace stl;

void test_empty()
{
    queue<int> myqueue;
    int sum (0);

    for (int i=1;i<=10;i++) myqueue.push(i);

    while (!myqueue.empty())
    {
        sum += myqueue.front();
        myqueue.pop();
    }

    std::cout << "total: " << sum << '\n';
}

void test_push_pop()
{
    queue<int> myqueue;

    for (int i=0; i<5; ++i) myqueue.push(i);

    std::cout << "Popping out elements...";
    while (!myqueue.empty())
    {
        std::cout << ' ' << myqueue.front();
        myqueue.pop();
    }
    std::cout << '\n';
}

void test_size()
{
    queue<int> myints;
    std::cout << "0. size: " << myints.size() << '\n';

    for (int i=0; i<5; i++) myints.push(i);
    std::cout << "1. size: " << myints.size() << '\n';

    myints.pop();
    std::cout << "2. size: " << myints.size() << '\n';
}

void test_front()
{
  queue<int> myqueue;

  myqueue.push(77);
  myqueue.push(16);

  myqueue.front() -= myqueue.back();    // 77-16=61

  std::cout << "myqueue.front() is now " << myqueue.front() << '\n';
}

void test_back()
{
  queue<int> myqueue;

  myqueue.push(12);
  myqueue.push(75);   // this is now the back

  myqueue.back() -= myqueue.front();

  std::cout << "myqueue.back() is now " << myqueue.back() << '\n';
}

int main()
{
    test_empty();
    test_push_pop();
    test_size();
    test_front();
    test_back();

    return 0;
}
