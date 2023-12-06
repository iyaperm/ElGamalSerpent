#include "gcd.h"

cpp_int GCD(cpp_int a, cpp_int b) {
    if (b == 0)
        return a;
    else
        return GCD(b, a % b);
}