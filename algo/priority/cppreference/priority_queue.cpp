#include <queue>
#include <vector>
#include <iostream>
#include <functional>
 
int main()
{
    std::priority_queue<int> c1;
    c1.push(5);
    std::cout << c1.size() << '\n';
 
    std::priority_queue<int> c2(c1);
    std::cout << c2.size() << '\n';
 
    std::vector<int> vec={3, 1, 4, 1, 5};
    std::priority_queue<int> c3(std::less<int>(), vec);
    std::cout << c3.size() << '\n';
}
