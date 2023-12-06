#include "Serpent_read_write_file.h"
#include "convert.h"

SerpentKeysGenerator key_g;
int rounds = 32;
Serpent serpent(key_g, rounds);

boost::dynamic_bitset<> read_file(std::ifstream& file) {
    file.seekg(0, std::ios::end);
    const size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<char> buffer(fileSize);
    file.read(buffer.data(), fileSize);

    boost::dynamic_bitset<> input_data;
    for (const char c : buffer)
    {
        for (int i = 7; i >= 0; --i)
        {
            input_data.push_back((c >> i) & 1);
        }
    }

    return input_data;
}

std::vector<std::bitset<128>> block_processing(const boost::dynamic_bitset<>& input_data) {
    size_t padding_block_size = 16;
    std::vector<std::bitset<128>> blocks;

    for (size_t i = 0; i < input_data.size(); i += 128)
    {
        size_t block_size = std::min<size_t>(128, input_data.size() - i);
        boost::dynamic_bitset<> current_block(block_size);

        for (size_t j = 0; j < block_size; ++j)
        {
            current_block[j] = input_data[i + j];
        }

        std::bitset<128> current_block_128 = convert(current_block);

        if (block_size < 128)
        {
            current_block_128 = pkcs7_padding(current_block, padding_block_size);
        }

        blocks.push_back(current_block_128);
    }

    return blocks;
}

void write_to_file(const std::bitset<128>& bitset, std::ofstream& file) {
    for (int i = 0; i < bitset.size(); i += CHAR_BIT) {
        char byte = 0;
        for (int j = 0; j < CHAR_BIT; ++j) {
            byte |= (bitset[i + (CHAR_BIT - 1 - j)] << j);
        }
        file.write(&byte, sizeof(byte));
    }
}

void write_to_file(const boost::dynamic_bitset<>& bitset, std::ofstream& file) {
    for (int i = 0; i < bitset.size(); i += CHAR_BIT) {
        char byte = 0;
        for (int j = 0; j < CHAR_BIT; ++j) {
            byte |= (bitset[i + (CHAR_BIT - 1 - j)] << j);
        }
        file.write(&byte, sizeof(byte));
    }
}