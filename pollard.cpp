#include "pollard.h"
#include "gcd.h"

cpp_int pollard(cpp_int n) {
	if (n % 2 == 0) {
		return 2;
	}
	cpp_int x = 2, y = 2, d = 1;
	auto f = [&](cpp_int x) { return (x * x + 1) % n; };
	while (d == 1) {
		x = f(x);
		y = f(f(y));
		d = GCD(abs(x - y), n);
	}
	return d;
}