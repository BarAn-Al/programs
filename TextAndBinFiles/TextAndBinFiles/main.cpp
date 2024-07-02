#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

class stuff {
public:
	int firmCode;
	char stuffName[30];
	int cost;
	int amount;
	int weight;

	bool operator <= (stuff const& st) const {
		if (firmCode <= st.firmCode) return true;
		else return false;

		if (stuffName <= st.stuffName) return true;
		else return false;

		if (cost <= st.cost) return true;
		else return false;

		if (amount <= st.amount) return true;
		else return false;

		if (weight <= st.weight) return true;
		else return false;
	}

	bool operator > (stuff const& st) {
		return !(*this <= st);
	}

	bool operator == (stuff const& st) {
		return firmCode == st.firmCode && stuffName == st.stuffName && cost == st.cost && amount == st.amount && weight == st.weight;
	}

	bool operator != (stuff const& st) {
		return !(*this == st);
	}

	bool operator < (stuff const& st) {
		return (*this <= st) && (*this != st);
	}

	bool operator >= (stuff const& st) {
		return (*this > st) || (*this == st);
	}

	friend std::ifstream& operator >> (std::ifstream& file, stuff& st) {
		file.read((char*)&st, sizeof(st));
		return file;
	}

	friend std::ofstream& operator << (std::ofstream& file, stuff const& st) {
		file.write((char*)&st, sizeof(st));
		return file;
	}

};

struct stuffTXT {
	stuffTXT(stuff& aRec) : st(aRec) { }
	stuff& st;
	friend std::istream& operator >> (std::istream& file, stuffTXT& aRec) {
		std::string s;
		if (getline(file, s)) {

			std::istringstream ss(s);
			std::string sf;
			std::getline(ss, sf, '\t');
			aRec.st.firmCode = stoi(sf);
			ss.getline(aRec.st.stuffName, 30, '\t');
			std::getline(ss, sf, '\t');
			aRec.st.cost = stoi(sf);
			std::getline(ss, sf, '\t');
			aRec.st.amount = stoi(sf);
			getline(ss, sf, '\t');
			aRec.st.weight = stoi(sf);
		}
		return file;
	}

	friend std::ostream& operator << (std::ostream& file, stuffTXT const& rec) {
		file << rec.st.firmCode << '\t' << rec.st.stuffName << '\t' << rec.st.cost << '\t' << rec.st.amount << '\t' << rec.st.weight;
		return file;
	}
};

class firm {
	int firmCode;
	char firmName[10];

	bool operator <= (firm const& st) const {
		if (firmCode <= st.firmCode) return true;
		else return false;

		if (firmName <= st.firmName) return true;
		else return false;
	}

	bool operator > (firm const& st) {
		return !(*this <= st);
	}

	bool operator == (firm const& st) {
		return firmCode == st.firmCode && firmName == st.firmName;
	}

	bool operator != (firm const& st) {
		return !(*this == st);
	}

	bool operator < (firm const& st) {
		return (*this <= st) && (*this != st);
	}

	bool operator >= (firm const& st) {
		return (*this > st) || (*this == st);
	}

	friend std::ifstream& operator >> (std::ifstream& file, firm& st) {
		file.read((char*)&st, sizeof(st));
		return file;
	}

	friend std::ofstream& operator << (std::ofstream& file, firm const& st) {
		file.write((char*)&st, sizeof(st));
		return file;
	}
};

struct firmTXT {
	firmTXT(firm& aRec) : f(aRec) { }
	firm& f;
	friend std::istream& operator >> (std::istream& file, firmTXT& aRec) {
		std::string s;
		if (getline(file, s)) {

			std::istringstream ss(s);
			std::string sf;
			std::getline(ss, sf, '\t');
			aRec.f.firmCode = stoi(sf);
			ss.getline(aRec.f.firmName, 30, '\t');
			std::getline(ss, sf, '\t');
		}
		return file;
	}

	friend std::ostream& operator << (std::ostream& file, stuffTXT const& rec) {
		file << rec.st.firmCode << '\t' << rec.st.stuffName << '\t' << rec.st.cost << '\t' << rec.st.amount << '\t' << rec.st.weight;
		return file;
	}
};

void CCtoStuff(const char* c, stuff& st) {
	int i = 0;
	st.firmCode = 0;
	while (c[i] != '\t') {
		st.firmCode = st.firmCode * 10 + (c[i] - '0');
		i++;
	}
	i++;
	
	int j = i;
	while (c[i] != '\t') {
		st.stuffName[i - j] = c[i];
		i++;
	}
	i++;

	st.cost = 0;
	while (c[i] != '\t') {
		st.cost = st.cost * 10 + (c[i] - '0');
		i++;
	}
	i++;

	st.amount = 0;
	while (c[i] != '\t') {
		st.amount = st.amount * 10 + (c[i] - '0');
		i++;
	}
	i++;

	st.weight = 0;
	while (c[i] != '\0') {
		st.weight = st.weight * 10 + (c[i] - '0');
		i++;
	}
}

void CCtoFirm(const char* c, firm& f) {
	int i = 0;
	while (c[i] != '\t') {
		f.firmCode = f.firmCode * 10 + (c[i] - '0');
		i++;
	}
	i++;

	int j = i;
	while (c[i] != '\0') {
		f.firmName[i - j] = c[i];
		i++;
	}
}

void TXTtoBIN(const std::string& txtFilename, const std::string& binFilename) {
	std::string buffer;
	std::ifstream fin(txtFilename);
	std::ofstream fout(binFilename, std::ios::binary | std::ios::out);
	if (fin.is_open() && fout.is_open()) {
		while (std::getline(fin, buffer)) {
			size_t size = buffer.size();
			fout.write((char*)&size, sizeof(size));
			fout.write(buffer.c_str(), size);
		}
	}
	else if (!fin.is_open()) {
		std::cerr << "Error4573: не удалось открыть файл " << txtFilename << '\n';
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл " << binFilename << '\n';
	}

	fin.close();
	fout.close();
}


void BINtoTXT(const std::string& binFilename, const std::string& txtFilename) {
	std::ifstream fin(binFilename, std::ios::binary | std::ios::in);
	std::ofstream fout(txtFilename);
	if (fin.is_open() && fout.is_open()) {
		size_t size;
		// читаем длину очередной строки:
		while (fin.read((char*)&size, sizeof(size))) {
			// читаем саму строку:
			char* buffer = new char[size + 1];
			fin.read(buffer, size);
			buffer[size] = '\0';
			
			fout.write(buffer, size);
			fout << '\n';

			delete[] buffer;
		}
	}
	else if (!fin.is_open()) {
		std::cerr << "Error4573: не удалось открыть файл " << binFilename << '\n';
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл " << txtFilename << '\n';
	}

	fin.close();
	fout.close();
}


void solution() {
	//Сортировка товаров через оперативную память
	std::ifstream fin("stuff.bin", std::ios::binary | std::ios::in);
	long long size = fin.tellg() / (sizeof(size_t) + sizeof(stuff));
	stuff* products = new stuff[size];
	if (fin.is_open()) {
		size_t fsize;
		int cnt = 0;
		while (fin.read((char*)&fsize, sizeof(fsize))) {
			char* buffer = new char[fsize + 1];
			fin.read(buffer, fsize);
			buffer[fsize] = '\0';

			CCtoStuff(buffer, products[cnt]);

			cnt++;
		}
	}
	else {
		std::cerr << "Error4573: не удалось открыть файл stuff.bin" << '\n';
		return;
	}

	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (products[i].firmCode > products[j].firmCode) {
				std::swap(products[i], products[j]);
			}
		}
	}

	fin.close();
	fin.open("firm.bin");
}



int main() {
	setlocale(LC_ALL, "RUSSIAN");
	TXTtoBIN("firm.txt", "firm.bin");
	TXTtoBIN("stuff.txt", "stuff.bin");
	
	solution();



	return 0;
}