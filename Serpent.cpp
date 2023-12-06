#include "Serpent.h"
#include "perm.h"
#include "boxes.h"
#include "iv_gen.h"

Serpent::Serpent(SerpentKeysGenerator serpent_key_gen, int i_num_rounds)
	: SP_Network(serpent_key_gen, i_num_rounds) {}

Serpent::Serpent() {}

std::bitset<128>Serpent::SerpentEncryption(const std::bitset<128>& input_block) {
	std::bitset<128> ip = perm(input_block, IP);
	std::bitset<128> encrypted = encryption(ip);
	std::bitset<128> fp = perm(encrypted, FP);
	return fp;
}

std::bitset<128>Serpent::SerpentDecryption(const std::bitset<128>& input_block) {
	std::bitset<128> ip = perm(input_block, IP);
	std::bitset<128> decrypted = decryption(ip);
	std::bitset<128> fp = perm(decrypted, FP);
	return fp;
}

std::pair<std::string, std::string>Serpent::KeyIvGen() {
	std::string key = key_iv_gen();
	std::string iv = key_iv_gen();
	return std::make_pair(key, iv);
}