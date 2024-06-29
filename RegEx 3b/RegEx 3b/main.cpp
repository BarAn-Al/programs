#include <iostream>
#include <regex>

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    std::regex reg("(\\s+[IN].+\\s+|.+\\s+)?(��������|�������|������|��������)(\\s+\\d+\\s+)(�������(\\s+|\\s+.+\\s+)(\\d+|\\d+\\.?\\d+) ��.��|���������(\\s+ \\d+))");
    std::string data;
    data = "    I�����������������   �������   89429  �������          93792.8532 ��.��";
    std::cout << data << "\n\n";

    if (std::regex_match(data, reg)) {
        std::cout << "������ �������� ��� ������\n\n";
    }
    else {
        std::cout << "������ �� �������� ��� ������\n\n";
    }

    std::smatch m;
    if (std::regex_search(data.cbegin(), data.cend(), m, reg)) {
        std::cout << "���������� ���������, ���������� ��� ������:\n" << m.str();
    }
    else {
        std::cout << "�� ���������� ���������, ���������� ��� ������";
    }

	return 0;
}