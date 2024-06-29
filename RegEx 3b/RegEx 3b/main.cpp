#include <iostream>
#include <regex>

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    std::regex reg("(\\s+[IN].+\\s+|.+\\s+)?(Беларусь|Венгрия|Польша|Болгария)(\\s+\\d+\\s+)(площадь(\\s+|\\s+.+\\s+)(\\d+|\\d+\\.?\\d+) кв.км|население(\\s+ \\d+))");
    std::string data;
    data = "    Iфлыдывотфсдцугфил   Венгрия   89429  площадь          93792.8532 кв.км";
    std::cout << data << "\n\n";

    if (std::regex_match(data, reg)) {
        std::cout << "Строка подходит под шаблон\n\n";
    }
    else {
        std::cout << "Строка не подходит под шаблон\n\n";
    }

    std::smatch m;
    if (std::regex_search(data.cbegin(), data.cend(), m, reg)) {
        std::cout << "Существует подстрока, подходящая под шаблон:\n" << m.str();
    }
    else {
        std::cout << "Не существует подстроки, подходящей под шаблон";
    }

	return 0;
}