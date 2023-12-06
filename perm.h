#ifndef PERM_H
#define PERM_H

#include "libraries.h"

std::bitset<128> perm(const std::bitset<128>& input_block, const int(&perm)[128]);

#endif