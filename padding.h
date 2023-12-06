#ifndef PADDING_H
#define PADDING_H

#include "libraries.h"

std::bitset<128> pkcs7_padding(const boost::dynamic_bitset<>& input, size_t block_size);

#endif // !PADDING_H