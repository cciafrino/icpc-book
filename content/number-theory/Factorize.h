/**
 * Author: Chris
 * Description: Get all factors of $n$.
 * Time: $O(sqrt(N)/log(N))$
 */
vector<pair<int, int>> factorize(int value) {
    vector<pair<int, int>> result;
    for (int p = 2; p*p <= value; ++p)
        if (value % p == 0) {
            int exp = 0;
            while (value % p == 0) {
                value /= p;
                ++exp;
            }
            result.emplace_back(p, exp);
        }
    if (value != 1) {
        result.emplace_back(value, 1);
        value = 1;
    }
    return result;
}
vector<pair<int64_t, int>> prime_factorize(int64_t n) {
    int64_t sieve_max = int64_t(smallest_factor.size()) - 1;
    assert(1 <= n && n <= sieve_max * sieve_max);
    vector<pair<int64_t, int>> result;
    if (n <= sieve_max) {
        while (n != 1) {
            int64_t p = smallest_factor[n];
            int exponent = 0;
            do {
                n /= p;
                exponent++;
            } while (n % p == 0);
            result.emplace_back(p, exponent);
        }
        return result;
    }
    for (int64_t p : primes) {
        if (p * p > n) break;
        if (n % p == 0) {
            result.emplace_back(p, 0);
            do {
                n /= p;
                result.back().second++;
            } while (n % p == 0);
        }
    }
    if (n > 1) result.emplace_back(n, 1);
    return result;
}
