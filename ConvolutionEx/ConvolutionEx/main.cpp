#include <iostream>
#include <concepts>
#include <set>

template <typename R, typename ... Ts>
auto IsOneInRange(const R& range, Ts ... ts) {
	return (std::count(std::begin(range), std::end(range), ts) || ...);
}

template <typename R, typename ... Ts>
auto IsAllInRange(const R& range, Ts ... ts) {
	return (std::count(std::begin(range), std::end(range), ts) && ...);
}

template <typename T, typename ... Ts>
auto PushInSet(std::set <T>& s, Ts ... ts) {
	return (s.insert(ts) && ...);
}


int main() {
	std::cout << std::boolalpha;
	std::cout << IsOneInRange("abcdefg", 2, 'y', 'z') << '\n';
	std::cout << IsAllInRange("abcdefg", 'x', 'b', 'c') << '\n';

	std::set <int> s;
	std::cout << PushInSet(s, 3, 389, 323, 578345, 3891237) << '\n';
	for (auto i : s) {
		std::cout << i << ' ';
	}
	std::cout << '\n';




	return 0;
}