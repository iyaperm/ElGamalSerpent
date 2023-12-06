#include "SerpentKeysGenerator.h"
#include "s_boxes.h"
#include "boxes.h"

std::array<std::bitset<128>, 33>SerpentKeysGenerator::GenerateKeys(std::string& input_key) {
	int size = input_key.size();
	if (size != 256) {
		input_key += "1";
	}
	std::reverse(input_key.begin(), input_key.end());
	std::bitset<256> key(input_key);

	std::array<std::bitset<32>, 8> keys;

	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 32; ++j) {
			keys[i][j] = key[i * 32 + j];
		}
	}

	std::bitset<32> frac = 0x9e3779b9;
	std::string frac_str = frac.to_string();
	std::reverse(frac_str.begin(), frac_str.end());
	std::bitset<32> frac_of_golden_ratio(frac_str);

	std::array<std::bitset<32>, 132> words;
	std::array<std::bitset<32>, 140> tmp_arr;

	for (int i = 0; i < 8; ++i) {
		tmp_arr[i] = keys[i];
	}

	for (int i = 8; i < 140; ++i) {
		std::bitset<32> i_bitset(i);
		std::bitset<32> after_xor = tmp_arr[i - 8] ^ tmp_arr[i - 5] ^ tmp_arr[i - 3] ^ tmp_arr[i - 1] ^ frac_of_golden_ratio ^ i_bitset;
		tmp_arr[i] = (after_xor >> 11) | (after_xor << 21);
		words[i - 8] = tmp_arr[i];
	}

	std::array<std::bitset<32>, 132> k;

	for (int i = 0; i < 129; i += 4) {
		for (int j = 0; j < 32; ++j) {
			std::bitset<4> input;
			for (int z = 0; z < 4; ++z) {
				input[z] = words[i + z][j];
			}
			int num_of_box = 3;
			std::bitset<4> output = s_boxes(input, SBoxes, num_of_box);
			num_of_box--;
			if (num_of_box < 0) {
				num_of_box = 7;
			}
			for (int t = 0; t < 4; ++t) {
				k[i + t][j] = output[t];
			}
		}
	}

	std::array<std::bitset<128>, 33> round_keys;

	for (int i = 0; i < 33; ++i) {
		for (int j = 0; j < 4; ++j) {
			for (int t = 0; t < 32; ++t) {
				round_keys[i][j * 32 + t] = k[i * 4 + j][t];
			}
		}
	}

	return round_keys;
}