/**
 * Author: Chris
 * Description: Sum of all divisors of $n$.
 */
#include "Sieve.h"
lint sum(int n){
    int idx = 0, prime_factors = primes[idx];
    lint ans = 1;
    while (prime_factors * prime_factors <= n){
        int power = 0;
        while (n % prime_factors == 0) {
            n /= prime_factors;
            power++;
        }
        ans *= ((lint)pow((double)prime_factors, power+1.0)-1)/(prime_factors-1);
        prime_factors = primes[++idx];
    }
    if (n != 1) ans *= ((lint)pow((double)n, 2.0)-1)/(n-1);
    return ans;
}
