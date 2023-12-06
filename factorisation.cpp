#include "factorisation.h"
#include "pollard.h"

void factorisation(std::vector<cpp_int>& factors, cpp_int n) {
    if (n == 1) {
        return;
    }
    cpp_int factor = pollard(n);
    if (factor == n) {
        factors.push_back(n);
    }
    else {
        factorisation(factors, factor);
        factorisation(factors, n / factor);
    }
}
