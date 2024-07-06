#include <iostream>
#include <string>
#include <regex>

int main() {
    std::string line = "Suzie Smith-Hopper test--hyphens: lkncsk'aceukl.";
    std::regex reg("(\".+\")|\\w+([-\']\\w+)?");
    std::string answer;

    std::smatch m;
    std::string copy = line;
    for (; std::regex_search(copy, m, reg); copy = m.suffix()) {
        answer += m.str() + ',';
    }

    answer.erase(answer.size() - 1, 1);
    std::cout << answer;

    return 0;
}
