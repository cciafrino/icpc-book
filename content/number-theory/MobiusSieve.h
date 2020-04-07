/**
 * Author: Chris
 * Date: 2016-07-24
 * License: CC0
 * Source: 
 * Description: Pre calculate all mu values.
 * Status: Works
 * Time: $O(N))$
 */
vector<int> mu, lp;
void run_sieve(int n) {
    mu.assign(n+1, -1);
    lp.assign(n+1, 0);
    mu[1] = 1;
    vector<int> prime;
    for (int i = 2; i <= n; ++i) {
        if (lp[i] == 0) {
            lp[i] = i; 
            prime.push_back(i);
        }
        for (int p : prime) {
            if (p > lp[i] || i * p > n) break;
            if (i % p == 0) mu[i*p] = 0;
            lp[i * p] = p;
            mu[i * p] *= mu[i];
        } 
    }
}
