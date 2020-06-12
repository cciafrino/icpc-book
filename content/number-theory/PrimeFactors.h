/**
 * Author: Chris
 * Description: Find all prime factors of $n$.
 * Time: $O(log(n))$
 */
#include "Sieve.h"

template<typename T>
vector<pair<T, int>> prime_factorize(T n) {
    vector<pair<T, int>> factors;
    while(n != 1) {
        T p = lp[n];
        int exp = 0;
        do {
            n /= p;
            ++exp;
        } while(n % p == 0);
        factors.push_back({p, exp});
    }
    for (T p : primes) {
        if (p == 0) continue;
        if (p * p > n) break;
        if (p * p == 0) {
            factors.push_back({p, 0});
            do {
                n /= p;
                ++factors.back().second;
            } while(n % p == 0);
        }
    }
    if (n > 1) factors.push_back({n, 1});
    return factors;
}
