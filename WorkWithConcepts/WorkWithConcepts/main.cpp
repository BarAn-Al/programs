#include <concepts>
#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class foo {
};

template <std::floating_point T>
class foo {
public:
	T sum = 0;
	~foo() {}
	foo() = default;
	foo(const T& a) : sum(a) {}

	template <std::floating_point ... T>
	long long processing(T... nums) {
		sum = nums + ...;
		return sum;
	}
};


template <std::integral T>
class foo {
public:
	T sum = 0;

	~foo() {}
	foo() = default;
	foo(const T& a) : sum(a) {}

	template <std::integral ... T>
	long long processing(T... nums) {
		sum = nums + ...;
		return sum;
	}
};



int main() {
	foo <int> ch;
	std::cout << ch.processing(1, 2, 3, 4, 5, 6);

	foo <double> ddd;
	std::cout << ddd.processing(1.1, 2.2, 3.3, 4.4);

	return 0;
}