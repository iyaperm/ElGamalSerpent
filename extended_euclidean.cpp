#include "extended_euclidean.h"

std::pair<cpp_int, cpp_int> extended_euclidean(const cpp_int& a_input, const cpp_int& b_input) {
	cpp_int a = a_input, b = b_input;
	cpp_int x = 0, y = 1, last_x = 1, last_y = 0, temp;
	while (b != 0) {
		cpp_int q = a / b;
		cpp_int r = a % b;

		a = b;
		b = r;

		temp = x;
		x = last_x - q * x;
		last_x = temp;

		temp = y;
		y = last_y - q * y;
		last_y = temp;
	}

	if (last_x < 0) {
		last_x += b_input;
	}

	if (last_y < 0) {
		last_y += a_input;
	}

	return { last_x, last_y };
}

