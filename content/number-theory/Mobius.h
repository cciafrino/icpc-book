/**
 * Author: Chris
 * Date: 2016-07-24
 * License: CC0
 * Source: 
 * Description: Return 0 if divisible by any perfect square, 1 if has an even quantity of prime numbers and -1 if has an odd quantity of primes.
 * Status: Works
 * Time: $O(sqrt(n))$
 */

template<typename T>
T mobius(T n) {
    T p = 0, aux = n;
    for (int i = 2; i*i <= n; ++i)
        if (n % i == 0) {
            n /= i;
            p += 1;
            if (n % i == 0) return 0;
        }
    return (p&1 ? 1 : -1);
}
