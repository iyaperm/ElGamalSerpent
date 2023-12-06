#ifndef SERPENT_H
#define SERPENT_H

#include "SP_network.h"

class Serpent final : public SP_Network {
public:
	Serpent(SerpentKeysGenerator serpent_key_gen, int i_num_rounds);
	Serpent();
	Serpent(Serpent const&) = delete;
	Serpent& operator=(Serpent const&) = delete;
	Serpent(Serpent&&) = delete;
	Serpent& operator=(Serpent&&) = delete;

	std::bitset<128> SerpentEncryption(const std::bitset<128>& input_block);

	std::bitset<128> SerpentDecryption(const std::bitset<128>& input_block);

	std::pair<std::string, std::string> KeyIvGen();
};

#endif // !SERPENT_H
