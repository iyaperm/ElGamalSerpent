#include "power.h"

cpp_int power(const cpp_int& base, const cpp_int& exp, const cpp_int& mod) {
	cpp_int result = 1;
	cpp_int temp_exp = exp;
	cpp_int temp_base = base;
	while (temp_exp > 0) {
		cpp_int last_bit = (temp_exp & 1);
		if (last_bit)
			result = (result * temp_base) % mod;
		temp_base = (temp_base * temp_base) % mod;
		temp_exp = temp_exp >> 1;
	}
	return result;
}
