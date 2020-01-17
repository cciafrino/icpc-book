/**
 * Author: Chris
 * Description: Find the number o prime factors of $n$.
 */
#include "Sieve.h"
lint nPrimeFac(lint n){
    int idx = 0, prime_factors = primes[idx];
    lint ans = 0;
    while (prime_factors * prime_factors <= n){
        while (n % prime_factors == 0) {
            n /= prime_factors;
            ++ans;
        }
        prime_factors = primes[++idx];
    }
    if (n != 1) ++ans;
    return ans;
}
