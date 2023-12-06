#ifndef KEYS_H
#define KEYS_H
#include "libraries.h"

using namespace boost::multiprecision;

struct Keys {
	cpp_int prime_number, primitive_root, secret_key, y;
};

#endif