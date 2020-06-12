/**
 * Author: Chris
 * Description: Sum of all divisors of $n$.
 * Time: O($lg(N)$)
 * Status: stress-tested until $n = 100'000'000$
 */
#include "Sieve.h"
#include "Modpow.h"

lint divsum(int n) {
    lint sum = 1;
    int p, f;
    while (n > 1) {
        for (p = lp[n], f = 0; (n > 1) && (p == lp[n]); n /= p) f++;
        sum *= (Pow(p, f + 1) - 1)/(p - 1);
    }
}
