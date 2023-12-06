#include "CBC.h"
#include "Serpent_read_write_file.h"
#include "remove_pkcs7_padding.h"

CBC::CBC(std::string& key, const std::bitset<128>& iv) : EncryptionMode(key, iv) {
	serpent.set_key(key);
}

void CBC::encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {
    std::ifstream file(input_file_path, std::ios::binary);
    std::ofstream encrypted_file(output_file_path, std::ios::binary);

    if (!file)
    {
        throw std::runtime_error("Failed to open file!");
    }

    if (!encrypted_file)
    {
        throw std::runtime_error("Failed to open file!");
    }

    std::bitset<128> block_xor;
    std::bitset<128> encrypt;
    bool first_block = true;
    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (auto& block : blocks) {
        
        if (first_block) {
            block_xor = block ^ iv_;
            encrypt = serpent.encryption(block_xor);
            write_to_file(encrypt, encrypted_file);
            first_block = false;
        }
        else {
            block_xor = block ^ encrypt;
            encrypt = serpent.encryption(block_xor);
            write_to_file(encrypt, encrypted_file);
        }
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }

    file.close();
    encrypted_file.close();
}

void CBC::decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {

    std::ifstream file(input_file_path, std::ios::binary);
    std::ofstream decrypted_file(output_file_path, std::ios::binary);

    if (!file)
    {
        throw std::runtime_error("Failed to open file!");
    }

    if (!decrypted_file)
    {
        throw std::runtime_error("Failed to open file!");
    }

    std::bitset<128> block_xor;
    std::bitset<128> decrypt;
    std::bitset<128> previous_block;
    bool first_block = true;
    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (size_t i = 0; i < blocks.size(); ++i) {
        auto& block = blocks[i];
        if (first_block) {
            previous_block = block;
            decrypt = serpent.decryption(block);
            block_xor = decrypt ^ iv_;
            first_block = false;
        }

        else {
            decrypt = serpent.decryption(block);
            block_xor = decrypt ^ previous_block;
            
            previous_block = block;
        }

        if (i == blocks.size() - 1) {
            boost::dynamic_bitset<> last_block = remove_pkcs7_padding(block_xor, 16);
            write_to_file(last_block, decrypted_file);
            break;
        }

        write_to_file(block_xor, decrypted_file);
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }
    file.close();
    decrypted_file.close();
}