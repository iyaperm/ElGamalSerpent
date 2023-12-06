#include "primitive_root.h"
#include "factorisation.h"
#include "random_number_generator.h"
#include "power.h"

cpp_int find_primitive_root(cpp_int& n) {
    std::vector<cpp_int> factors;
    cpp_int phi = n - 1;
    factorisation(factors, phi);
    while (true) {
        mt19937 gen(std::random_device{}());
        cpp_int a = number_generator(n, gen);
        bool flag = true;
        for (auto& factor : factors)
        {
            if (power(a, (n - 1) / factor, n) == 1)
            {
                flag = false;
                break;
            }
        }
        if (flag)
            return a;
    }
    return -1;
}
