#include <initializer_list>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <concepts>
#include <ranges>

template <typename T>
class check {};

template <std::regular T>
class check <T> {
public:
	check() {
		std::cout << "class is regular";
	}
};

class R {
private:
	int numerator = 0;
	int denominator = 0;

	int gcd(int a, int b) {
		if (a < b) {
			int c = a;
			a = b;
			b = c;
		}

		while (b) {
			a %= b;

			int c = a;
			a = b;
			b = c;
		}

		return a;
	}

	void normalize(int a) {
		int g = gcd(numerator, denominator);
		numerator /= g;
		denominator /= g;

		if (denominator < 0) {
			denominator = -denominator;
			numerator = -numerator;
		}


	}

	R& normalize() {
		R cop(numerator, denominator);
		int g = gcd(cop.numerator, cop.denominator);
		cop.numerator /= g;
		cop.denominator /= g;

		if (cop.denominator < 0) {
			cop.denominator = -cop.denominator;
			cop.numerator = -cop.numerator;
		}

		return cop;
	};

public:
	~R() {}

	R() = default;

	R(const int& a) : numerator(a), denominator(1) {
		normalize(0);
	}

	R operator =(const int& a) {
		numerator = a;
		denominator = 1;

		normalize(0);
		return *this;
	}

	R(const int& num, const int& den) : numerator(num), denominator(den) {
		normalize(0);
	}

	R operator =(const std::initializer_list <int>& list) = delete;

	R(const R& other) : numerator(other.numerator), denominator(other.denominator) {
		normalize(0);
	}

	R& operator =(const R& other) {
		if (*this != other) {
			numerator = other.numerator;
			denominator = other.denominator;

			normalize(0);
		}
		return *this;
	}

	R(R&& other) noexcept : numerator(other.numerator), denominator(other.denominator) {
		normalize(0);
	}

	R& operator =(R&& other) noexcept {
		if (this != &other) {
			numerator = other.numerator;
			denominator = other.denominator;

			normalize(0);
		}
		return *this;
	}


	//==================================================================================



	R operator *(const R& other) {
		return { numerator * other.numerator, denominator * other.denominator };
	}

	R operator *(const int& num) {
		return { numerator * num, denominator };
	}

	R operator /(const R& num) {
		return { numerator * num.denominator, denominator * num.numerator };
	}

	R operator /(const int& num) {
		return { numerator, denominator * num };
	}

	R operator +(const R& other) {
		int nok = other.denominator * denominator / gcd(other.denominator, denominator);
		int n = nok / other.denominator * other.numerator;
		int on = nok / denominator * numerator;

		return { n + on, nok };
	}

	R operator +(const int& num) {
		return { numerator + num * denominator, denominator };
	}

	R operator -() {
		return { 0 - numerator, denominator };
	}

	R operator -(const int& num) {
		return { numerator - num * denominator, denominator };
	}

	R operator -(const R& other) {
		R copy = other;
		return *this + (-copy);
	}


	//================================================================
	R operator +=(const R& other) {
		*this = *this + other;

		normalize(0);
		return *this;
	}

	R operator +=(const int& num) {
		*this = *this + num;

		normalize(0);
		return *this;
	}

	R operator *=(const R& other) {
		*this = *this * other;

		normalize(0);
		return *this;
	}

	R operator *=(const int& num) {
		*this = *this * num;

		normalize(0);
		return *this;
	}

	R operator /=(const R& other) {
		*this = *this / other;

		normalize(0);
		return *this;
	}

	R operator /=(const int& num) {
		*this = *this / num;

		normalize(0);
		return *this;
	}

	R operator -=(const R& other) {
		*this = *this - other;

		normalize(0);
		return *this;
	}

	R operator -=(const int& num) {
		*this = *this - num;

		normalize(0);
		return *this;
	}
	//=====================================================================

	R operator ++() { //prev
		*this = *this + 1;

		normalize(0);
		return *this;
	}

	R operator --() { //prev
		*this = *this - 1;

		normalize(0);
		return *this;
	}

	R operator ++(int a) {// post
		*this = *this + 1;

		normalize(0);
		return *this - 1;
	}

	R operator --(int a) { // post
		*this = *this - 1;

		normalize(0);
		return *this + 1;
	}
	//========================================================

	bool operator ==(const R& other) const {
	}
	
	//==========================================================================

	/*operator double() const {
		double res = double(numerator) / denominator;

		return res;
	}*/

	//==========================================================================

	friend std::ostream& operator <<(std::ostream& os, const R& a) {
		os << '(' << a.numerator << '/' << a.denominator << ')';
		return os;
	}

	friend std::istream& operator >>(std::istream& is, R& a) {
		int n, d;
		is >> n >> d;

		a = (n, d);
		a.normalize(0);
		return is;
	}

	//==========================================================================

	double Value() {
		return double(numerator) / denominator;
	}
};



int main() {
	check <R> bomb;

	const check <R> a;
	if (a == bomb) {

	}

	return 0;
}