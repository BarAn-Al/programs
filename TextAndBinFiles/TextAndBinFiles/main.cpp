#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <algorithm>

class film {
public:
	int firmCode = 0;
	char stuffName[31] = "                              ";
	int cost = 0;
	int amount = 0;
	int weight = 0;
	char firmName[11] = "          ";

	film() = default;

	film(const stuff& other) : firmCode(other.firmCode), cost(other.cost), amount(other.amount), weight(other.weight) {
		int i;
		for (i = 0; other.stuffName[i] != '\0'; i++) {
			stuffName[i] = other.stuffName[i];
		}
		stuffName[i] = other.stuffName[i];

		for (i = 0; other.firmName[i] != '\0'; i++) {
			firmName[i] = other.firmName[i];
		}
		firmName[i] = other.firmName[i];
	}

	film operator = (const stuff& other) {
		firmCode = other.firmCode;
		cost = other.cost;
		amount = other.amount;
		weight = other.weight;
		
		int i;
		for (i = 0; other.stuffName[i] != '\0'; i++) {
			stuffName[i] = other.stuffName[i];
		}
		stuffName[i] = other.stuffName[i];

		for (i = 0; other.firmName[i] != '\0'; i++) {
			firmName[i] = other.firmName[i];
		}
		firmName[i] = other.firmName[i];

		return *this;
	}



	bool operator > (stuff const& st) const {
		if (firmCode > st.firmCode) return true;
		else if (firmCode == st.firmCode) {
			if (std::string(stuffName) > std::string(st.stuffName)) return true;
			else if (std::string(stuffName) == std::string(st.stuffName)) {
				if (cost > st.cost) return true;
				else if (cost == st.cost) {
					if (amount > st.amount) return true;
					else if (amount == st.amount) {
						if (weight > st.weight) return true;
						else if (weight == st.weight) {
							if (std::string(firmName) > std::string(st.firmName)) return true;
							else return false;
						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}

	bool operator == (stuff const& st) {
		return firmCode == st.firmCode && std::string(stuffName) == std::string(st.stuffName) && cost == st.cost && amount == st.amount && weight == st.weight && std::string(firmName) == std::string(st.firmName);
	}

	bool operator <= (stuff const& st) {
		return !(*this > st);
	}

	bool operator != (stuff const& st) {
		return !(*this == st);
	}

	bool operator < (stuff const& st) {
		return !(*this > st) && (*this != st);
	}

	bool operator >= (stuff const& st) {
		return (*this > st) || (*this == st);
	}

	friend std::ifstream& operator >> (std::ifstream& file, stuff& st) {
		file.read((char*)&st, sizeof(st));
		
		return file;
	}

	friend std::ofstream& operator << (std::ofstream& file, stuff const& st) {
		file.write((char*)&st.firmCode, sizeof(st));
		return file;
	}

};

template <typename T>
size_t file_Size(T& fin) {
	std::streamoff pos = fin.tellg();  //return current position in file
	fin.seekg(0, std::ios_base::end); //делает текущим конец файла
	long long n2 = fin.tellg();
	fin.seekg(0);
	long long n1 = fin.tellg();

	return n2 - n1;
}

void TXTtoBIN(const std::string& txtFilename, const std::string& binFilename) {
	std::ifstream fin(txtFilename);
	std::ofstream fout(binFilename, std::ios::binary | std::ios::out);

	if (fin.is_open() && fout.is_open()) {
		std::string buffer;
		while (std::getline(fin, buffer)) {
			film a;
			std::istringstream sin(buffer);
			std::vector <std::string> data;
			std::string d;
			while (std::getline(sin, d, '\t')) {
				data.push_back(d);
			}

			if (data.size() == 2) {
				a.firmCode = std::stoi(data[0]);
				for (int i = 0; i < data[1].size(); i++) {
					a.firmName[i] = data[1][i];
				}
				a.firmName[10] = '\0';
			}
			else {
				a.firmCode = std::stoi(data[0]);
				for (int i = 0; i < data[1].size(); i++) {
					a.stuffName[i] = data[1][i];
				}
				a.stuffName[30] = '\0';
				a.cost = std::stoi(data[2]);
				a.amount = std::stoi(data[3]);
				a.weight = std::stoi(data[4]);
			}

			fout << a;
		}
		fin.close();
		fout.close();
	}
	else if (!fin.is_open()) {
		std::cerr << "Error4573: не удалось открыть файл " << txtFilename << '\n';
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл " << binFilename << '\n';
	}

}


void BINtoTXT(const std::string& binFilename, const std::string& txtFilename) {
	std::ifstream fin(binFilename, std::ios::binary | std::ios::in);
	std::ofstream fout(txtFilename);

	if (fin.is_open() && fout.is_open()) {
		size_t n = file_Size(fin) / sizeof(film);
		for (size_t i = 0; i < n; i++) {
			film a;
			fin >> a;
			if (a.firmCode) {
				fout << a.firmCode << '\t';
			}
			if (std::string(a.stuffName) != "                              ") {
				fout << a.stuffName << '\t';
			}
			if (a.cost) {
				fout << a.cost << '\t';
			}
			if (a.amount) {
				fout << a.amount << '\t';
			}
			if (a.weight) {
				fout << a.weight << '\t';
			}
			if (std::string(a.firmName) != "          ") {
				fout << a.firmName << '\t';
			}
			fout << '\n';
		}
		fin.close();
		fout.close();
	}
	else if (!fin.is_open()) {
		std::cerr << "Error4573: не удалось открыть файл " << binFilename << '\n';
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл " << txtFilename << '\n';
	}

}


void CreateNewSortedFile() {
	//Сортировка товаров через оперативную память
	std::fstream fin("stuff.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	size_t stuffSize = file_Size(fin) / sizeof(film);
	film* products = new film[stuffSize];
	if (fin.is_open()) {
		for (size_t i = 0; i < stuffSize; i++) {
			fin.read((char *)&products[i], sizeof(products[0]));
		}
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл stuff.bin" << '\n';
		return;
	}

	for (int i = 0; i < stuffSize; i++) {
		for (int j = i + 1; j < stuffSize; j++) {
			if (products[i] > products[j]) {
				std::swap(products[i], products[j]);
			}
		}
	}

	fin.close();
	fin.open("firm.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);

	size_t firmSize = file_Size(fin) / sizeof(film);
	for (size_t i = 0; i < firmSize; i++) {
		for (size_t j = i + 1; j < firmSize; j++) {
			film s1, s2;
			fin.seekg(i * sizeof(s1));
			fin.read((char*)&s1, sizeof(s1));
			fin.seekg(j * sizeof(s2));
			fin.read((char*)&s2, sizeof(s2));

			if (s1 > s2) {
				fin.seekg(i * sizeof(s1));
				fin.write((char*)&s2, sizeof(s1));

				fin.seekg(j * sizeof(s2));
				fin.write((char*)&s1, sizeof(s1));
			}
		}
	}

	std::ofstream fout("M1.bin");
	size_t i = 0;
	size_t j = 0;
	while (i < firmSize || j < stuffSize) {
		film a;
		fin.seekg(i * sizeof(a));
		fin.read((char*)&a, sizeof(a));

		while ((j == stuffSize && i < firmSize) || (i < firmSize && a.firmCode < products[j].firmCode)) {
			i++;
			fin.seekg(i * sizeof(a));
			fin.read((char*)&a, sizeof(a));
		}

		while ((i == firmSize && j < stuffSize) || (j < stuffSize && products[j].firmCode < a.firmCode)) j++;

		if (a.firmCode == products[j].firmCode) {
			for (int k = 0; k < 11; k++) {
				products[j].firmName[k] = a.firmName[k];
			}
			fout << products[j];

			j++;
		}

	}


	delete[] products;
	fout.close();
	fin.close();
}

void solution() {
	std::fstream m("M1.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	std::vector <film> products(file_Size(m) / sizeof(film));

	for (int i = 0; i < products.size(); i++) {
		m.read((char*)&products[i], sizeof(products[0]));
		int j = 29;
		while (products[i].stuffName[j] == ' ' && j) {
			j--;
		}
		products[i].stuffName[++j] = '\0';

		j = 9;
		while (products[i].firmName[j] == ' ' && j) {
			j--;
		}
		products[i].firmName[++j] = '\0';
	}

	int move = -1;
CONTINUE_PROGRAMM:
	while (move != 0) {
		std::cout << "Выберите действие, указав соответствующую цифру:\n"
			<< "1. Найти самый дорогой товар фирмы.\n"
			<< "2. Найти товар с наибольшей ценой.\n"
			<< "3. Показать все товары фирмы.\n"
			<< "4. Отсортировать товары по убыванию цены.\n"
			<< "5. Поменять местами две (случайные) записи, разность цены у которых не превосходит заданного значения.\n"
			<< "6. Удалить все товары, стоимость которых меньше заданного значения.\n"
			<< "7. Показать ВСЕ товары.\n"
			<< "0. Закрыть программу.\n\n";

			std::cin >> move;
			std::cout << '\n';
			film pr;
			switch (move) {
			case 0:
				goto CLOSE_PROGRAMM;
				break;

			case 1:
				std::cout << "Введите название фирмы (до 10-ти символов): ";
				std::cin >> pr.firmName;
				std::cout << '\n';

				for (int i = 0; i < products.size(); i++) {
					if (std::string(pr.firmName) == std::string(products[i].firmName)) {
						if (pr.cost < products[i].cost) {
							pr = products[i];
						}
					}
				}

				std::cout << "Самый дорогой товар фирмы " << pr.firmName << " - " << pr.stuffName << '\n';
				std::cout << "Его стоимость, количество и вес соответственно:\t" << pr.cost << ",\t" << pr.amount << ",\t" << pr.weight << "\n\n";
				break;

			case 2:
				for (int i = 0; i < products.size(); i++) {
					if (products[i].cost > pr.cost) {
						pr = products[i];
					}
				}
				std::cout << "Самый дорогой товар - " << pr.stuffName << " от фирмы \"" << pr.firmName << "\"\n";
				std::cout << "Его стоимость, количество и вес соответственно:\t" << pr.cost << ",\t" << pr.amount << ",\t" << pr.weight << "\n\n";
				break;

			case 3:
				std::cout << "Введите название фирмы (до 10-ти символов): ";
				std::cin >> pr.firmName;
				std::cout << '\n';

				for (int i = 0; i < products.size(); i++) {
					if (std::string(products[i].firmName) == std::string(pr.firmName)) {
						std::cout << products[i].stuffName << ":\t";
						std::cout << "Стоимость - " << products[i].cost << ",\tколичество - " << products[i].amount << ",\tвес - " << products[i].weight << '\n';

					}
				}
				std::cout << '\n';
				break;

			case 4:
				for (int i = 0; i < products.size(); i++) {
					for (int j = i + 1; j < products.size(); j++) {
						if (products[i] > products[j]) {
							std::swap(products[i], products[j]);
						}
					}
				}
				std::cout << "Товары отсортированы.\n\n";
				break;

			case 5:
				int x;
				std::cout << "Введите значение: ";
				std::cin >> x;
				for (int i = 0; i < products.size(); i++) {
					for (int j = i + 1; j < products.size(); j++) {
						if (std::abs(products[i].cost - products[j].cost) < x) {
							std::swap(products[i], products[j]);
							std::cout << '\n';
							goto CONTINUE_PROGRAMM;
						}
					}
				}
				std::cout << "У любой пары товаров разность стоимостей больше чем значение " << x << "\n\n";
				break;


			case 6:
				std::cout << "Введите значение: ";
				std::cin >> x;
				for (int i = 0; i < products.size(); i++) {
					if (products[i].cost < x) {
						auto it = products.begin();
						std::advance(it, i);
						i--;
						products.erase(it);
					}
				}
				std::cout << "Все товары ниже введённой цены удалены\n\n";
				break;

			case 7:
				for (int i = 0; i < products.size(); i++) {
					std::cout << products[i].stuffName << ":\t";
					std::cout << "Стоимость - " << products[i].cost << ",\tколичество - " << products[i].amount << ",\tвес - " << products[i].weight << ",\tфирма - " << products[i].firmName << '\n';
				}
				std::cout << '\n';
				break;

			}



	}

CLOSE_PROGRAMM:
	m.open("M2.bin", std::ios_base::binary | std::ios_base::in | std::ios_base::out);
	for (int i = 0; i < products.size(); i++) {
		m.write((char*)&products[i], sizeof(products[0]));
	}
	system("cls");
}


int main() {
	setlocale(LC_ALL, "RUSSIAN");
	std::string TXTfirm = "firm.txt";
	std::string TXTstuff = "stuff.txt";
	std::string BINfirm = "firm.bin";
	std::string BINstuff = "stuff.bin";

	TXTtoBIN(TXTfirm, BINfirm);
	TXTtoBIN(TXTstuff, BINstuff);

	CreateNewSortedFile();

	solution();

	return 0;
}