#ifndef S_BOXES_H
#define S_BOXES_H

#include "libraries.h"

std::bitset<4> s_boxes(const std::bitset<4>& input_bits, const int(&s_box)[8][16], const int& num_of_round);

#endif // !S_BOXES_H
