#ifndef SERPENT_KEYS_GENERATOR_H
#define SERPENT_KEYS_GENERATOR_H

#include "libraries.h"

class SerpentKeysGenerator final {
public:
	std::array<std::bitset<128>, 33> GenerateKeys(std::string& input_key);
};

#endif // !SERPENT_KEYS_GENERATOR_H
