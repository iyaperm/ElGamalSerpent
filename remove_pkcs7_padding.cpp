#include "remove_pkcs7_padding.h"

boost::dynamic_bitset<> remove_pkcs7_padding(std::bitset<128>& input, size_t block_size) {
    boost::dynamic_bitset<> output(input.to_string());

    int padding_size = 0;
    std::bitset<8> bits;
    for (int i = 0; i < 8; ++i) {
        bits[i] = output[output.size() - 1 - i];
    }
    
    padding_size = bits.to_ulong();
    if (padding_size > block_size) {
        return output;
    }

    output.resize(output.size() - padding_size * 8);

    return output;
}
