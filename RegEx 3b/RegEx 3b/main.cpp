#include <iostream>
#include <regex>
#include <string>

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	std::string data = "ksjdhfkjs Беларусь 38923958 площадь 389.381 кв.км";
	std::cout << data << "\n";
	std::regex reg("(\\s+[IN].+\\s+|.+\\s+)?(Беларусь|Венгрия|Польша|Болгария)(\\s+\\d+\\s+|\\s+)(площадь(\\s+\\d+\\s+|\\s+)\\d+(\\.\\d+)? кв\\.км|население\\s+(\\d+|\\d+\\.\\d+))");

	std::smatch m;
	if (std::regex_match(data, m, reg)) {
		if (std::regex_search(m.str(7), std::regex("\\."))) {
			std::cout << "Число населения не должно быть нецелым числом\n\n";
		}
		else {
			std::cout << "Вся строка подходит под шаблон\n\n";
		}
	}
	else {
		std::cout << "Вся строка не подходит под шаблон\n\n";
	}


	if (std::regex_search(data, m, reg)) {
		std::cout << "Подстрока, которая подходит под шаблон:\n";
		std::cout << m.str() << '\n';
	}
	else {
		std::cout << "Не существует подстроки, подходящей под шаблон\n";
	}





	return 0;
}