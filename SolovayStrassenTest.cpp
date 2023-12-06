#include "SolovayStrassenTest.h"
#include "random_number_generator.h"
#include "power.h"
#include "Jacobi.h"

bool SolovayStrassen(cpp_int& n, double& min_p) {
	double k = log2(1 / (1 - min_p));
	for (int i = 0; i < std::ceil(k); i++) {
		mt19937 gen(std::random_device{}());
		cpp_int a = number_generator(n, gen);
		if (gcd(n, a) != 1)
			return false;
		cpp_int exp = (n - 1) / 2;
		if (power(a, exp, n) != (n + Jacobi(a, n)) % n)
			return false;
	}
	return true;
}