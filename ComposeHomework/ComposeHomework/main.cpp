#include <functional>
#include <iostream>
#include <cmath>

template<typename F, typename G1, typename G2, typename G, typename ... G1n>
auto comp(F func, G1 g1, G2 g2, G g, G1n ... g1n) {
    return [=](auto x, auto y) {
        return func(g1(x), g2(y), g(x, y), g1n(x)...);
    };
}

int main() {

    auto f = [](int a, int b, int c, int d, int e, int g) { return a + b + c + d + e + g; };
    auto g1 = [](int x) { return x * x; };
    auto g2 = [](int x) { return x / 2; };
    auto g = [](int x, int y) { return x + x * y; };
    auto g11 = [](int x) { return x - 10; };
    auto g12 = [](int x) { return x + 3; };
    auto g13 = [](int x) { return x - 1; };



    auto h = comp(f, g1, g2, g, g11, g12, g13);

    int x = 1;
    std::cout << g1(x) << ' ' << g2(x) << ' ' << g(x, x) << ' ' << g11(x) << ' ' << g12(x) << ' ' << g13(x);
    std::cout << h(x, x);


    return 0;
}