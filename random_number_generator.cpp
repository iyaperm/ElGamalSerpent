#include "random_number_generator.h"

cpp_int number_generator(cpp_int& n, mt19937& gen) {
	uniform_int_distribution<cpp_int> dist(2, n - 1);
	cpp_int random_number = dist(gen);
	return random_number;
}