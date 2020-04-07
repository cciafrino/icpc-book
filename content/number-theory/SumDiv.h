/**
 * Author: Chris
 * Description: Sum of all divisors of $n$.
 */
#include "Sieve.h"
#include "Modpow.h"
lint sumDiv(int n){
    int idx = 0, prime_factors = primes[idx];
    lint ans = 1;
    while (prime_factors * prime_factors <= n){
        int power = 0;
        while (n % prime_factors == 0) {
            n /= prime_factors;
            power++;
        }
        ans *= (Pow(prime_factors, power+1)-1)/(prime_factors-1);
        prime_factors = primes[++idx];
    }
    if (n != 1) ans *= (n*n - 1)/(n-1);
    return ans;
}
