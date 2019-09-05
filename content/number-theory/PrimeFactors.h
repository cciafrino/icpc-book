/**
 * Author: Chris
 * Description: Find all prime factors of $n$.
 */
 
vector<lint> primeFac(lint n){
    vector<int> factors;
    lint idx = 0, prime_factors = primes[idx];
    while (prime_factors * prime_factors <= n){
        while (n % prime_factors == 0) {
            n /= prime_factors;
            factors.push_back(prime_factors);
        }
        prime_factors = primes[++idx];
    }
    if (n != 1) factors.push_back(n);
    return factors;
}
