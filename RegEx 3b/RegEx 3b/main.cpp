#include <iostream>
#include <regex>
#include <string>

int main() {
	setlocale(LC_ALL, "RUSSIAN");
	std::string data = "ksjdhfkjs �������� 38923958 ������� 389.381 ��.��";
	std::cout << data << "\n";
	std::regex reg("(\\s+[IN].+\\s+|.+\\s+)?(��������|�������|������|��������)(\\s+\\d+\\s+|\\s+)(�������(\\s+\\d+\\s+|\\s+)\\d+(\\.\\d+)? ��\\.��|���������\\s+(\\d+|\\d+\\.\\d+))");

	std::smatch m;
	if (std::regex_match(data, m, reg)) {
		if (std::regex_search(m.str(7), std::regex("\\."))) {
			std::cout << "����� ��������� �� ������ ���� ������� ������\n\n";
		}
		else {
			std::cout << "��� ������ �������� ��� ������\n\n";
		}
	}
	else {
		std::cout << "��� ������ �� �������� ��� ������\n\n";
	}


	if (std::regex_search(data, m, reg)) {
		std::cout << "���������, ������� �������� ��� ������:\n";
		std::cout << m.str() << '\n';
	}
	else {
		std::cout << "�� ���������� ���������, ���������� ��� ������\n";
	}





	return 0;
}