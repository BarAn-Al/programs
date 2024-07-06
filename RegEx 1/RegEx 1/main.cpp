#include <regex>
#include <string>
#include <iostream>

int main() {
    std::regex reg("a\\D+?a");
    std::string s;
    std::cin >> s;

    std::sregex_iterator end;
    std::sregex_iterator pos(s.begin(), s.end(), reg);
    for (; pos != end; pos++) {
        std::cout << pos->str() << '\n';
    }

}