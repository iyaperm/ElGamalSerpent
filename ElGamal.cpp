#include "ElGamal.h"
#include "random_number_generator.h"
#include "power.h"
#include "extended_euclidean.h"

ElGamal::ElGamal(TestType test) :  key_gen(test) {
	_keys = key_gen.GenerateKeys();
}

ElGamal::ElGamal() {}

std::pair<cpp_int, cpp_int> ElGamal::Encrypt(cpp_int& message, cpp_int& prime_number, cpp_int& root, cpp_int& y) {
	mt19937 gen(std::random_device{}());
	cpp_int k = number_generator(prime_number, gen);
	cpp_int u = power(root, k, prime_number);
	cpp_int v = (message * power(y, k, prime_number)) % prime_number;
	return std::make_pair(u, v);
}

cpp_int ElGamal::Decrypt(std::pair<cpp_int, cpp_int>& message, cpp_int& prime_number, cpp_int& secret_key) {
	cpp_int tmp = power(message.first, secret_key, prime_number);
	std::pair<cpp_int, cpp_int> xy = extended_euclidean(tmp, prime_number);
	return (message.second * xy.first) % prime_number;
}

void ElGamal::encrypt_file(const std::wstring& input_filename, const std::wstring& output_filename, cpp_int& prime_number,
    cpp_int& root, cpp_int& y, QProgressDialog& progress_bar) {
    std::ifstream input_file(input_filename, std::ios::binary);
    std::ofstream output_file(output_filename, std::ios::binary);

    if (!input_file.is_open() || !output_file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    unsigned char c;
    int progress = 0;
    while (input_file.read(reinterpret_cast<char*>(&c), sizeof(c))) {
        cpp_int data = c;
        std::pair<cpp_int, cpp_int> encrypted_data = this->Encrypt(data, prime_number, root, y);
        std::string str1 = encrypted_data.first.str();
        std::string str2 = encrypted_data.second.str();
        output_file << str1 << "\n";
        output_file << str2 << "\n";
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }
}

void ElGamal::decrypt_file(const std::wstring& input_filename, const std::wstring& output_filename, cpp_int& prime_number,
    cpp_int& secret_key, QProgressDialog& progress_bar) {
    std::ifstream input_file(input_filename, std::ios::binary);
    std::ofstream output_file(output_filename, std::ios::binary);

    if (!input_file.is_open() || !output_file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл");
    }

    std::string str;
    int progress = 0;
    while (std::getline(input_file, str)) {
        cpp_int num1(str);
        if (std::getline(input_file, str)) {
            cpp_int num2(str);
            std::pair<cpp_int, cpp_int> encrypted_data = std::make_pair(num1, num2);
            cpp_int decrypted_data = this->Decrypt(encrypted_data, prime_number, secret_key);
            unsigned char c = static_cast<unsigned char>(decrypted_data);
            output_file.write(reinterpret_cast<const char*>(&c), sizeof(c));
        }
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }
}