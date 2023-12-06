#ifndef RANDOM_DELTA_H
#define RANDOM_DELTA_H

#include "encryption_mode.h"

class RandomDelta :public EncryptionMode {
public:
	RandomDelta(std::string& key, const std::bitset<128>& iv);

	void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void increment_counter_randomly(std::bitset<128>& counter, std::bitset<64>& delta);
};

#endif // !RANDOM_DELTA_H
