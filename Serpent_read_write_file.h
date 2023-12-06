#ifndef SERPENT_READ_WRITE_FILE_H
#define SERPENT_READ_WRITE_FILE_H

#include "libraries.h"
#include "Serpent.h"
#include "padding.h"
#include "remove_pkcs7_padding.h"

extern SerpentKeysGenerator key_g;
extern int rounds;
extern Serpent serpent;

std::vector<std::bitset<128>> block_processing(const boost::dynamic_bitset<>& input_data);

boost::dynamic_bitset<> read_file(std::ifstream& file);

void write_to_file(const std::bitset<128>& bitset, std::ofstream& file);

void write_to_file(const boost::dynamic_bitset<>& bitset, std::ofstream& file);

#endif // !SERPENT_READ_WRITE_FILE_H
