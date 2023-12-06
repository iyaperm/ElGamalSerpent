#include "perm.h"

std::bitset<128> perm(const std::bitset<128>& input_block, const int(&perm)[128]) {
	std::bitset<128> block_after_perm;
	for (int i = 0; i < 128; ++i) {
		block_after_perm[i] = input_block[perm[i]];
	}
	return block_after_perm;
}