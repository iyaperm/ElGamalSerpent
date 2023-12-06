#include "ElGamalKeyGenerator.h"
#include "FermatTest.h"
#include "MillerRabinTest.h"
#include "SolovayStrassenTest.h"
#include "primitive_root.h"
#include "power.h"
#include "random_number_generator.h"

ElGamalKeyGenerator::ElGamalKeyGenerator(TestType test) {
	_test = test;
}

ElGamalKeyGenerator::ElGamalKeyGenerator() {}

cpp_int ElGamalKeyGenerator::GenerateRandomNumber(int bit_length) {
	std::random_device rd;
	mt19937 gen(rd());
	cpp_int max_number = (cpp_int(1) << bit_length) - 1;
	cpp_int min_number = (cpp_int(1) << (bit_length - 1));
	uniform_int_distribution<cpp_int> dist(min_number, max_number);
	cpp_int random_number = dist(gen);
	return random_number;
}

cpp_int ElGamalKeyGenerator::GetPrimeNumber() {
	cpp_int prime_number;
	bool is_prime = false;
	double min_p = 0.99998;
	int bit_length = 64;

	while (!is_prime) {
		prime_number = GenerateRandomNumber(bit_length);

		if (_test == TestType::Fermat) {
			is_prime = FermatTest(prime_number, min_p);
		}
		else if (_test == TestType::MillerRabin) {
			is_prime = MillerRabin(prime_number, min_p);
		}
		else if (_test == TestType::SolovayStrassen) {
			is_prime = SolovayStrassen(prime_number, min_p);
		}
	}
	return prime_number;
}

Keys ElGamalKeyGenerator::GenerateKeys() {
	Keys keys;
	cpp_int p, g, x, y;

	p = GetPrimeNumber();
	g = find_primitive_root(p);
	x = GenerateRandomNumber(60);
	y = power(g, x, p);
	

	keys.prime_number = p;
	keys.primitive_root = g;
	keys.secret_key = x;
	keys.y = y;

	return keys;
}