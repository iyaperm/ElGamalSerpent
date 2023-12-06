#include "mode_selection.h"

void mode_selection(std::string & user_mode, std::string & str_key, std::string & iv, std::wstring & input_file_path,
	std::wstring & output_file_path, bool& encrypt, QProgressDialog& progress_bar) {

	std::string mode = user_mode;

	std::unique_ptr<EncryptionMode> encryptionMode;

	std::bitset<128> iv_(iv);

	if (mode == "ECB") {
		encryptionMode = std::make_unique<ECB>(str_key);
	}
	else if (mode == "CBC") {
		encryptionMode = std::make_unique<CBC>(str_key, iv_);
	}
	else if (mode == "CFB") {
		encryptionMode = std::make_unique<CFB>(str_key, iv_);
	}
	else if (mode == "CTR") {
		encryptionMode = std::make_unique<CTR>(str_key, iv_);
	}
	else if (mode == "OFB") {
		encryptionMode = std::make_unique<OFB>(str_key, iv_);
	}
	else if (mode == "RandomDelta") {
		encryptionMode = std::make_unique<RandomDelta>(str_key, iv_);
	}

	if (encrypt) {
		encryptionMode->encrypt(input_file_path, output_file_path, progress_bar);
	}
	else {
		encryptionMode->decrypt(input_file_path, output_file_path, progress_bar);
	}
}