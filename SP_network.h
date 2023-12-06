#ifndef SP_NETWORK_H
#define SP_NETWORK_H

#include "libraries.h"
#include "SerpentKeysGenerator.h"

class SP_Network {
private:
	SerpentKeysGenerator keys_gen;
	int num_rounds;
	std::array<std::bitset<128>, 33> round_keys;

public:
	SP_Network(SerpentKeysGenerator serpent_key_gen, int i_num_rounds);
	SP_Network();
	SP_Network(SP_Network const&) = delete;
	SP_Network& operator=(SP_Network const&) = delete;
	SP_Network(SP_Network&&) = delete;
	SP_Network& operator=(SP_Network&&) = delete;

	std::bitset<128> encryption(const std::bitset<128>& input_block);

	std::bitset<128> decryption(const std::bitset<128>& input_block);

	void set_key(std::string& input_key);
};

#endif // !FEISTEL_NETWORK_H
