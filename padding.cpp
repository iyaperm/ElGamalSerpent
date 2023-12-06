#include "padding.h"
#include "convert.h"
#include <iostream>

std::bitset<128> pkcs7_padding(const boost::dynamic_bitset<>& input, size_t block_size) {
    size_t input_size = input.size() / 8;
    size_t padding_size = block_size - (input_size % block_size);
    boost::dynamic_bitset<> output = input;
    std::bitset<8> padding_bits(padding_size);
    for (int i = 0; i < padding_size; ++i) {
        for (int j = 7; j >= 0; --j) {
            output.push_back(padding_bits[j]);
        }
    }
    return convert(output);
}