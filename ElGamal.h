#ifndef ELGAMAL_H
#define ELGAMAL_H
#include "libraries.h"
#include "ElGamalKeyGenerator.h"

using namespace boost::multiprecision;

class ElGamal final {
private:
	ElGamalKeyGenerator key_gen;
	Keys _keys;

public:
	ElGamal(TestType test);
	ElGamal();
	ElGamal(ElGamal const&) = delete;
	ElGamal& operator=(ElGamal const&) = delete;
	ElGamal(ElGamal&&) = delete;
	ElGamal& operator=(ElGamal&&) = delete;

	std::pair<cpp_int, cpp_int> Encrypt(cpp_int& message, cpp_int& prime_number, cpp_int& root, cpp_int& y);

	cpp_int Decrypt(std::pair<cpp_int, cpp_int>& message, cpp_int& prime_number, cpp_int& secret_key);

	void encrypt_file(const std::wstring& input_filename, const std::wstring& output_filename, cpp_int& prime_number,
		cpp_int& root, cpp_int& y, QProgressDialog& progress);

	void decrypt_file(const std::wstring& input_filename, const std::wstring& output_filename, cpp_int& prime_number,
		cpp_int& secret_key, QProgressDialog& progress);

	Keys GetKey() const {
		return _keys;
	}
};

#endif // !ELGAMAL_H

