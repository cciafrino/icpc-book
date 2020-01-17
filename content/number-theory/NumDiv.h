/**
 * Author: Chris
 * Description: Count the number of divisors of $n$.
 */
#include "Sieve.h"
int NumDiv(lint n){
    int idx = 0, prime_factors = primes[idx];
    lint ans = 1;
    while (prime_factors * prime_factors <= n) {
        int power = 0;
        while (n % prime_factors == 0) {
            n /= prime_factors;
            ++power;
        }
        ans *= 1ll * (power + 1);
        prime_factors = primes[++idx];
    }
    if (n != 1) ans *= 2;
    return ans;
}
