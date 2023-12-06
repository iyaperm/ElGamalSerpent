#include "SP_network.h"
#include "boxes.h"
#include "s_boxes.h"

SP_Network::SP_Network(SerpentKeysGenerator serpent_key_gen, int i_num_rounds) {
	keys_gen = serpent_key_gen;
	num_rounds = i_num_rounds;
}

SP_Network::SP_Network() {}

void SP_Network::set_key(std::string& input_key) {
	round_keys = keys_gen.GenerateKeys(input_key);
}

std::bitset<128>SP_Network::encryption(const std::bitset<128>& input_block) {
	std::bitset<128> block = input_block;
	for (int i = 0; i < 32; ++i) {
		std::bitset<128> block_after_xor = block ^ round_keys[i];
		std::array<std::bitset<32>, 4> words;
		for (int k = 0; k < 4; ++k) {
			for (int j = 0; j < 32; ++j) {
				words[k][j] = block_after_xor[k * 32 + j];
			}
		}
		std::array<std::bitset<32>, 4> x;
		for (int q = 0; q < 32; ++q) {
			std::bitset<4> input;
			for (int z = 0; z < 4; ++z) {
				input[z] = words[z][q];
			}
			std::bitset<4> output = s_boxes(input, SBoxes, q % 8);
			for (int d = 0; d < 4; ++d) {
				x[d][q] = output[d];
			}
		}
		x[0] = (x[0] >> 13) | (x[0] << 19);
		x[2] = (x[2] >> 3) | (x[2] << 29);
		x[1] = x[1] ^ x[0] ^ x[2];
		x[3] = x[3] ^ x[2] ^ (x[0] >> 3);
		x[1] = (x[1] >> 1) | (x[1] << 31);
		x[3] = (x[3] >> 7) | (x[3] << 25);
		x[0] = x[0] ^ x[1] ^ x[3];
		x[2] = x[2] ^ x[3] ^ (x[1] >> 7);
		x[0] = (x[0] >> 5) | (x[0] << 27);
		x[2] = (x[2] >> 22) | (x[2] << 10);
		for (int r = 0; r < 4; ++r) {
			for (int p = 0; p < 32; ++p) {
				block[r * 32 + p] = x[r][p];
			}
		}
	}
	std::bitset<128> final_block = block ^ round_keys[32];
	return final_block;
}

std::bitset<128>SP_Network::decryption(const std::bitset<128>& input_block) {
	std::bitset<128> block = input_block ^ round_keys[32];
	for (int i = 31; i >= 0; --i) {
		std::array<std::bitset<32>, 4> x;
		for (int r = 0; r < 4; ++r) {
			for (int p = 0; p < 32; ++p) {
				x[r][p] = block[r * 32 + p];
			}
		}
		x[2] = (x[2] << 22) | (x[2] >> 10);
		x[0] = (x[0] << 5) | (x[0] >> 27);
		x[2] = x[2] ^ x[3] ^ (x[1] >> 7);
		x[0] = x[0] ^ x[1] ^ x[3];
		x[3] = (x[3] << 7) | (x[3] >> 25);
		x[1] = (x[1] << 1) | (x[1] >> 31);
		x[3] = x[3] ^ x[2] ^ (x[0] >> 3);
		x[1] = x[1] ^ x[0] ^ x[2];
		x[2] = (x[2] << 3) | (x[2] >> 29);
		x[0] = (x[0] << 13) | (x[0] >> 19);
		std::bitset<128> xblock;
		for (int q = 0; q < 32; ++q) {
			std::bitset<4> input;
			for (int d = 0; d < 4; ++d) {
				input[d] = x[d][q];
			}
			std::bitset<4> output = s_boxes(input, InvSBoxes, q % 8);
			for (int z = 0; z < 4; ++z) {
				xblock[z * 32 + q] = output[z];
			}
		}
		block = xblock ^ round_keys[i];
	}
	return block;
}