#ifndef CBC_H
#define CBC_H

#include "encryption_mode.h"

class CBC :public EncryptionMode {
public:
	CBC(std::string& key, const std::bitset<128>& iv);

	void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;
};

#endif // !CBC_H
