#include "Jacobi.h"

int Jacobi(cpp_int a, cpp_int n) {
	int j = 1;
	while (a != 0) {
		while (a % 2 == 0) {
			a /= 2;
			if (n % 8 == 3 || n % 8 == 5) {
				j = -j;
			}
		}
		cpp_int temp = a;
		a = n;
		n = temp;
		if (a % 4 == n % 4 && n % 4 == 3) {
			j = -j;
		}
		a %= n;
	}
	if (n == 1) {
		return j;
	}
	else {
		return 0;
	}
}