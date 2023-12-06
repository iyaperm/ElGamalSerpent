#include "convert.h"

std::bitset<128> convert(const boost::dynamic_bitset<>& dynamicBitset) {
    std::bitset<128> bitset;
    for (int i = 0; i < dynamicBitset.size(); ++i) {
        bitset[i] = dynamicBitset[i];
    }
    return bitset;
}