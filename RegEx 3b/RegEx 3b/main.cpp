#include <iostream>
#include <regex>

int main() {
    std::regex reg("(ab)+");
    std::string s;
    std::cin >> s;

    std::string copy = s;
    std::sregex_iterator end;
    std::sregex_iterator pos(s.begin(), s.end(), reg);
    for (; pos != end; ) {
        std::cout << pos->str() << '\n';
        copy = std::string(pos->str()) + std::string(pos->suffix());
        copy[0] = ' ';
        pos = std::sregex_iterator(copy.begin(), copy.end(), reg);
    }



	return 0;
}