#include <iostream>
#include <cmath>
#include <functional>

template <typename T>
using UnarFuncType = std::function <T(T)>;

template <typename T>
using BinFuncType = std::function <T(T, T)>;

template <typename T>
using ComposeType = std::function <BinFuncType <T>(BinFuncType <T>, BinFuncType <T>, UnarFuncType <T>, UnarFuncType <T>)>;


int main() {
	ComposeType <int> comp = [](BinFuncType <int> f, BinFuncType <int> g, UnarFuncType <int> g1, UnarFuncType <int> g2)->BinFuncType <int> { 
		return std::bind(f, std::bind(g, std::bind(g1, std::placeholders::_1), std::bind(g2, std::placeholders::_2)), std::bind(g2, std::placeholders::_1));
	};

	BinFuncType <int> f = [](int x, int y) { return x + y; };
	BinFuncType <int> g = [](int x, int y) { return x * y; };
	UnarFuncType <int> g1 = [](int x) { return x + 1; };
	UnarFuncType <int> g2 = [](int x) { return x - 2; };

	BinFuncType <int> h = comp(f, g, g1, g2);
	std::cout << h(2, 1);

	return 0;
}