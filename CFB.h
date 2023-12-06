#ifndef CFB_H
#define CFB_H

#include "encryption_mode.h"

class CFB :public EncryptionMode {
public:
	CFB(std::string& key, const std::bitset<128>& iv);

	void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;
};

#endif // !CFB_H
