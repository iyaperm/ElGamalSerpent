#include "CTR.h"
#include "Serpent_read_write_file.h" 

CTR::CTR(std::string& key, const std::bitset<128>& iv) : EncryptionMode(key, iv) {
    serpent.set_key(key);
}

void CTR::encrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {

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
    std::bitset<128> counter = iv_;
    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (auto& block : blocks) {
        
        encrypt = serpent.encryption(counter);
        block_xor = block ^ encrypt;
        write_to_file(block_xor, encrypted_file);
        increment_counter(counter);
        progress_bar.setValue(++progress);
        QCoreApplication::processEvents();
    }

    file.close();
    encrypted_file.close();
}

void CTR::decrypt(const std::wstring& input_file_path, const std::wstring& output_file_path, QProgressDialog& progress_bar) {

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
    std::bitset<128> counter = iv_;
    boost::dynamic_bitset<> file_bits = read_file(file);
    std::vector<std::bitset<128>> blocks = block_processing(file_bits);
    int progress = 0;
    for (int i = 0; i < blocks.size(); ++i) {
        
        auto& block = blocks[i];
        decrypt = serpent.encryption(counter);
        block_xor = block ^ decrypt;
        increment_counter(counter);

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

void CTR::increment_counter(std::bitset<128>& counter) {
    for (int i = counter.size() - 1; i >= 0; --i) {
        if (!counter[i]) {
            counter[i] = 1;
            break;
        }
        else {
            counter[i] = 0;
        }
    }
}