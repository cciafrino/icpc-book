/**
 * Author: Chris
 * Description: Sum of all divisors of $n$.
 * Time: O($lg(N)$)
 * Status: stress-tested until $n = 100'000'000$
 */
#include "Sieve.h"
#include "Modpow.h"

template<typename T> T divSum(T n) {
    T sum = 1;
    while (n > 1) {
        int exp = 0;
        T p = lp[n];
        do {
            n /= p;
            ++exp;
        } while(n % p == 0);
        sum *= (Pow(p, exp + 1) - 1)/(p - 1);
    }
    return sum;
}
