#ifndef ENCRYPTION_MODE_H
#define ENCRYPTION_MODE_H

#include "libraries.h"
#include "Serpent.h"

class EncryptionMode {
protected:
    std::string key_;
    std::bitset<128> iv_;

public:
    EncryptionMode(std::string& key, const std::bitset<128>& iv = std::bitset<128>()) : key_(key), iv_(iv) {}
    virtual void encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) = 0;
    virtual void decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) = 0;
};

#endif // !ENCRYPTION_MODE_H
