#include "s_boxes.h"
#include "boxes.h"

std::bitset<4> s_boxes(const std::bitset<4>& input_bits, const int(&sbox)[8][16], const int& num_of_round) {
	std::bitset<4> output_bits;
	std::string tmp = input_bits.to_string();
	std::reverse(tmp.begin(), tmp.end());
	std::bitset<4> reverse_input_bits(tmp);
	int input_to_sbox = reverse_input_bits.to_ulong();
	std::bitset<4> output = sbox[num_of_round][input_to_sbox];
	std::string output_str = output.to_string();
	std::reverse(output_str.begin(), output_str.end());
	std::bitset<4> output_from_sbox(output_str);
	return output_from_sbox;
}