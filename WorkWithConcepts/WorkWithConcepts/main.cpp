#include <concepts>
#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
concept RationalNumber = (std::integral<T> || std::floating_point<T>);

template <typename T>
requires RationalNumber<T>
class XX {
public:
	long long sum = 0;

	~XX() {}
	XX() = default;
	XX(T a) {
		sum = a;
	}

	template <typename r1> requires std::integral<r1>
	auto proc(std::vector <r1> a) {
		r1 result = 0;
		for (int i = 0; i < a.size(); i++) {
			result += a[i];
		}
		sum = result;
		return sum;
	}

	template <typename r2> requires std::floating_point<r2>
	auto proc(std::vector <r2> a) {
		r2 result = 0;
		for (int i = 0; i < a.size(); i++) {
			result += a[i];
		}

		sum = result;
		return sum;
	}

};


int main() {
	XX item(10);

	std::vector <int> a({ 1, 2, 3, 4, 5, 6, 7 });
	std::cout << item.proc(a) << '\n';
	std::vector <double> b({ 1.32, 2.589, 3.391, 4.223131, 5.8942 });
	std::cout << item.proc(b) << '\n';



	return 0;
}