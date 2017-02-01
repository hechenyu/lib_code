#include "max_heap.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    int array_size = 20;
    int *array = new int[array_size];

    for (int i = 1; i <= 10; i++)
        array[i] = i;

    MAXHeap<int> heap;
    heap_build(heap, array, array_size-1, 10);

    cout << "max: " << heap_maximum(heap) << endl;

    cout << "increase 5 to 11" << endl;
    heap_increase_key(heap, 5, 11);

    cout << "max: " << heap_maximum(heap) << endl;

    cout << "array: ";
    for (int i = 1; i <= 10; i++)
        cout << array[i] << " ";
    cout << endl;

    cout << "heap_pop: ";
    while (!heap_is_empty(heap))
        cout << heap_extract_max(heap) << " ";
    cout << endl;

    return 0;
}
