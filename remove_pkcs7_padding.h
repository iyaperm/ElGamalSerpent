#ifndef REMOVE_PKCS7_PADDING_H
#define REMOVE_PKCS7_PADDING_H

#include "libraries.h"

boost::dynamic_bitset<> remove_pkcs7_padding(std::bitset<128>& input, size_t block_size);

#endif // !REMOVE_PKCS7_PADDING_H
