#include "MillerRabinTest.h"
#include "random_number_generator.h"
#include "power.h"

bool MillerRabin(cpp_int& n, double& min_p) {
	double k = (log(1 / (1 - min_p))) / (log(4.0));
	cpp_int s = 0;
	cpp_int d = n - 1;
	while (d % 2 == 0) {
		d /= 2;
		s++;
	}
	for (int i = 0; i < std::ceil(k); i++) {
		mt19937 gen(std::random_device{}());
		cpp_int a = number_generator(n, gen);
		cpp_int x = power(a, d, n);
		cpp_int new_x;
		for (int i = 1; i <= s; i++) {
			new_x = (x * x) % n;
			if ((new_x == 1) and (x != 1) and (x != n - 1))
				return false;
			x = new_x;
		}
		if (x != 1)
			return false;
	}
	return true;
}