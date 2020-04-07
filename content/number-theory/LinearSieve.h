/**
 * Author: Tourist
 * Source: https://codeforces.com/blog/entry/54090
 * Description: Prime sieve for generating all primes up to a certain limit.  
 * Status: Tested
 * Time: $O(n)$
 */
vector<int> primes, least = {0, 1};
int precalculated = 1;
void LinearSieve(int n) {
    n = max(n, 1);
    least.assign(n + 1, 0);
    primes.clear();
    for (int i = 2; i <= n; i++) {
        if (least[i] == 0) {
            least[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (p > least[i] || i * p > n) break;
            least[i * p] = p;
        }
    }
    precalculated = n;
}
