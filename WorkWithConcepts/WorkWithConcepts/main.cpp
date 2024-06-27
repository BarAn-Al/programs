#include <concepts>
#include <cmath>

template <typename T>
class XX {
public:

	template <std::integral r1>
	r1 proc(vector <r1> a) {
		r1 result = 0;
		for (int i = 0; i < a.size(); i++) {
			result += a[i];
		}
		return result;
	}

	template <std::floating_point r2>
	r1 proc(vector <r2> a) {
		r2 result = 0;
		for (int i = 0; i < a.size(); i++) {
			result += a[i];
		}

		return trunc(result);
	}

};