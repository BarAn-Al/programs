#include <iostream>
#include <regex>
#include <string>

int main() {
	std::string data;
	std::getline(std::cin, data);

	std::string answer;
	std::regex reg("(\".+\")|(\\w+[-']?\\w+)|(\\w+)");


	std::sregex_iterator str(data.begin(), data.end(), reg);
	std::sregex_iterator end;
	for (; str != end; str++) {
		std::string s = str->str();
		s = std::regex_replace(s, std::regex("\\d+"), std::string("$&") + ".0");
		if (s[0] == '\"') {
			s.erase(0, 1);
		}
		if (s[s.size() - 1] == '\"') {
			s.erase(s.size() - 1, 1);
		}

		answer += s + ',';
	}

	answer.erase(answer.size() - 1, 1);
	std::cout << answer << '\n';

	return 0;
}