#ifndef OFB_H
#define OFB_H

#include "encryption_mode.h"

class OFB :public EncryptionMode {
public:
	OFB(std::string& key, const std::bitset<128>& iv);

	void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;

	void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) override;
};

#endif // !OFB_H
