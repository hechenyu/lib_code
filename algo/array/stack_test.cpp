#include "stack.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    Stack<string> stack;
    stack_init(stack, new string[argc], argc);

    // push front
    for (int i = 1; i < argc; i++) {
        stack_push(stack, string(argv[i]));
        cout << argv[i] << " ";
    }
    cout << endl;

    // pop front
    while (!stack_is_empty(stack)) {
        cout << stack_peek(stack) << " ";
        stack_pop(stack);
    }
    cout << endl;

    return 0;
}
