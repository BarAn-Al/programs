#include <functional>
#include <iostream>
#include <cmath>

template <typename F, typename G1, typename G2, typename G, typename G11>
class FunctionCompose {
    F f;
    G1 g1;
    G2 g2;
    G g;
    G11 g11;
public:
    FunctionCompose(F _f, G1 _g1, G2 _g2, G _g, G11 _g11) : f(_f), g1(_g1), g2(_g2), g(_g), g11(_g11) {}

    template <typename T>
    T operator () (T x, T y) {
        return f(g1(x), g2(y), g(x, y), g11(x));
    }
};

template<typename F, typename G1, typename G2, typename G, typename ... G1n>
auto comp(F func, G1 g1, G2 g2, G g, G1n ... g1n) {
    return [=](auto x, auto y) {
        return func(g1(x), g2(y), g(x, y), g1n(x)...);
    };
}

int main() {

    auto f = [](int a, int b, int c, int d) { return a + b + c + d; };
    auto g1 = [](int x) { return x * x; };
    auto g2 = [](int x) { return x / 2; };
    auto g = [](int x, int y) { return x + x * y; };
    auto g11 = [](int x) { return x - 10; };
    auto g12 = [](int x) { return x + 3; };
    auto g13 = [](int x) { return x - 1; };



    auto h = comp(f, g1, g2, g, g11);

    FunctionCompose<decltype(f), decltype(g1), decltype(g2), decltype(g), decltype(g11)> h1(f, g1, g2, g, g11);


    int x = 1;
    int y = 2;
    //std::cout << g1(x) << ' ' << g2(y) << ' ' << g(x, y) << ' ' << g11(x) << ' ' << '\n';
    std::cout << h(x, y) << '\n';
    std::cout << h1(x, y);


    return 0;
}