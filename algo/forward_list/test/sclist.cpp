#include "sclist.h"
#include "sclist_iterator.h"
#include "sclist_util.h"
#include <string>
#include <iostream>

int main()
{
    // c++11 initializer list syntax:
    SCList<std::string> words1;
    list_init<std::string>(&words1, {"the", "frogurt", "is", "also", "cursed"});
    std::cout << "words1: " << words1 << '\n';

    // words2 == words1
    SCList<std::string> words2;
    list_init(&words2, list_begin(&words1), list_end(&words1));
    std::cout << "words2: " << words2 << '\n';

    // words3 == words1
    SCList<std::string> words3;
    list_init(&words3, list_begin(&words1), list_end(&words1));
    std::cout << "words3: " << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    SCList<std::string> words4;
    list_init<std::string>(&words4, 5, "Mo");
    std::cout << "words4: " << words4 << '\n';

    list_destroy(&words4);
    list_destroy(&words3);
    list_destroy(&words2);
    list_destroy(&words1);
}
