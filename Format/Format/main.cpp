#include <iostream>
#include <format>

int main() {
    setlocale(LC_ALL, "RUSSIAN");

    double sum{ 100.2567 };
    std::cout << "1)" << std::format("sum = {:.5}", sum) << std::endl;

    return 0;
}