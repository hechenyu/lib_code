#include "forward_list.h"
#include <iterator>
#include <iostream>
int main()
{
    forward_list<int> l = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
 
    //    l.erase( l.begin() ); // ERROR: No function erase
 
    l.erase_after( l.before_begin() ); // Removes first element
 
    for( auto n : l ) std::cout << n << " ";
    std::cout << '\n';
 
    auto fi= std::next( l.begin() );
    auto la= std::next( fi, 3 );
 
    l.erase_after( fi, la );
 
    for( auto n : l ) std::cout << n << " ";
    std::cout << '\n';
}
