#include "CFB.h"
#include "Serpent_read_write_file.h"

CFB::CFB(std::string& key, const std::bitset<128>& iv) : EncryptionMode(key, iv) {
    serpent.set_key(key);
}

void CFB::encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {
    std::ifstream file(input_file_path, std::ios::binary);
    std::ofstream encrypted_file(output_file_path, std::ios::binary);

    if (!file)
    {
        throw std::runtime_error("Failed to open file");
    }

    if (!encrypted_file)
    {
        throw std::runtime_error("Failed to open file");
    }

    std::bitset<128> block_xor;
    std::bitset<128> encrypt;
    bool first_block = true;
    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (auto& block : blocks) {
        
        if (first_block) {
            encrypt = serpent.encryption(iv_);
            block_xor = block ^ encrypt;
            write_to_file(block_xor, encrypted_file);
            first_block = false;
        }
        else {
            encrypt = serpent.encryption(block_xor);
            block_xor = block ^ encrypt;
            write_to_file(block_xor, encrypted_file);
        }
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }

    file.close();
    encrypted_file.close();
}

void CFB::decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {

    std::ifstream file(input_file_path, std::ios::binary);
    std::ofstream decrypted_file(output_file_path, std::ios::binary);

    if (!file)
    {
        throw std::runtime_error("Failed to open file");
    }

    if (!decrypted_file)
    {
        throw std::runtime_error("Failed to open file");
    }

    std::bitset<128> block_xor;
    std::bitset<128> decrypt;
    std::bitset<128> previous_block;
    bool first_block = true;
    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (int i = 0; i < blocks.size(); ++i) {
        
        auto& block = blocks[i];
        if (first_block) {
            decrypt = serpent.encryption(iv_);
            block_xor = decrypt ^ block;
            first_block = false;
            previous_block = block;
        }
        else {
            decrypt = serpent.encryption(previous_block);
            block_xor = decrypt ^ block;
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