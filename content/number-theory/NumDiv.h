/**
 * Author: Chris
 * Description: Count the number of divisors of $n$.
 */
lint NumDiv(lint n){
    lint idx = 0, prime_factors = primes[idx], ans = 1;
    while (prime_factors * prime_factors <= n) {
        lint power = 0;
        while (n % prime_factors == 0) {
            n /= prime_factors;
            power++;
        }
        ans *= (power + 1);
        prime_factors = primes[++idx];
    }
    if (n != 1) ans *= 2;
    return ans;
}
