#ifndef ECB_H
#define ECB_H

#include "encryption_mode.h"

class ECB :public EncryptionMode {
public:
	ECB(std::string& key);

	void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;
};

#endif // !ECB_H
