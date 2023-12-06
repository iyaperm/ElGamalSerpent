#ifndef CTR_H
#define CTR_H

#include "encryption_mode.h"

class CTR :public EncryptionMode {
public:
	CTR(std::string& key, const std::bitset<128>& iv);

	void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void increment_counter(std::bitset<128>& counter);
};

#endif // !CTR_H
