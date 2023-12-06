#ifndef ELGAMAL_KEY_GENERATOR_H
#define ELGAMAL_KEY_GENERATOR_H
#include "TestType.h"
#include "Keys.h"

class ElGamalKeyGenerator final {
private:
	TestType _test;
	int _bit_length;
	cpp_int GenerateRandomNumber(int bit_length);
	cpp_int GetPrimeNumber();

public:
	ElGamalKeyGenerator(TestType test);
	ElGamalKeyGenerator();
	ElGamalKeyGenerator(ElGamalKeyGenerator const&) = delete;
	ElGamalKeyGenerator& operator=(ElGamalKeyGenerator const&) = delete;
	ElGamalKeyGenerator(ElGamalKeyGenerator&&) = delete;
	ElGamalKeyGenerator& operator=(ElGamalKeyGenerator&&) = delete;

	Keys GenerateKeys();
};

#endif // !ELGAMAL_KEY_GENERATOR_H