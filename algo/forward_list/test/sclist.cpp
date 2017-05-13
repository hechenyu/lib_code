#include "sclist.h"
#include <string>
#include <iostream>

template<typename T>
std::ostream& operator<<(std::ostream& s, const sclist<T>& v) {
    s.put('[');
    char comma[3] = {'\0', ' ', '\0'};
    auto print_data = [&](const T &) {
        s << comma << e;
        comma[0] = ',';
    };

    list_for_each(&v, print_data);
    return s << ']';
}

int main()
{
    // c++11 initializer list syntax:
    SCList<std::string> words1;
    list_init(&words1, {"the", "frogurt", "is", "also", "cursed"});
    std::cout << "words1: " << words1 << '\n';

    // words2 == words1
    SCList<std::string> words2;
    list_init(&words2, list_begin(&words1), list_end(&words1));
    std::cout << "words2: " << words2 << '\n';

    // words3 == words1
    SCList<std::string> words3;
    list_init(&word3, &words1);
    std::cout << "words3: " << words3 << '\n';

    // words4 is {"Mo", "Mo", "Mo", "Mo", "Mo"}
    SCList<std::string> words4;
    list_init(&word4, 5, "Mo");
    std::cout << "words4: " << words4 << '\n';

    list_destroy(&words4);
    list_destroy(&words3);
    list_destroy(&words2);
    list_destroy(&words1);
}
