#include "ECB.h"
#include "Serpent_read_write_file.h"

ECB::ECB(std::string& key) : EncryptionMode(key) {
	serpent.set_key(key);
}

void ECB::encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {
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

    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (auto& block : blocks) {
        std::bitset<128> encrypt = serpent.encryption(block);
        write_to_file(encrypt, encrypted_file);
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }

    file.close();
    encrypted_file.close();
}

void ECB::decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {

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

    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (int i = 0; i < blocks.size(); ++i) {
        auto& block = blocks[i];
        std::bitset<128> decrypt = serpent.decryption(block);

        if (i == blocks.size() - 1) {
            boost::dynamic_bitset<> last_block = remove_pkcs7_padding(decrypt, 16);
            write_to_file(last_block, decrypted_file);
            break;
        }

        write_to_file(decrypt, decrypted_file);
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }

    file.close();
    decrypted_file.close();
}