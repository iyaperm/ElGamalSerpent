#include "iv_gen.h"

std::string key_iv_gen() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;

    std::bitset<128> iv;

    for (int i = 0; i < 2; ++i) {
        uint64_t random_value = dis(gen);
        for (int j = 0; j < 64; ++j) {
            iv[i * 64 + j] = (random_value >> j) & 1;
        }
    }

    return iv.to_string();
}
