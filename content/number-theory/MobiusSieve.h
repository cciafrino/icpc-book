/**
 * Author: Chris
 * Date: 2016-07-24
 * License: CC0
 * Source: 
 * Description: Pre calculate all mobius values.
 * Status: Works
 * Time: $O(sqrt(n))$
 */

vector<int> mobius, lp;
void run_sieve(int n) {
    mobius.assign(n, -1);
    lp.assign(n, 0);
    mobius[1] = 1;
    vector<int> prime;
    for (int i = 2; i <= n; ++i) {
        if (!lp[i]) {
            lp[i] = i; 
            prime.push_back(i);
        }
        for (int p : prime) {
            if (p > lp[i] || p*i > n) break;
            if (i % p == 0) mobius[i*p] = 0;
            lp[p*i] = p;
            mobius[p*i] *= mobius[i];
        } 
    }
}
