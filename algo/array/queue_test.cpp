#include "queue.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Queue<string> queue;
    queue_init(queue, new string[argc], argc);

    // push back
    for (int i = 1; i < argc; i++) {
        queue_put(queue, string(argv[i]));
        cout << argv[i] << " ";
    }
    cout << endl;

    // pop front
    while (!queue_is_empty(queue)) {
        cout << queue_head(queue) << " ";
        queue_get(queue);
    }
    cout << endl;

    return 0;
}

