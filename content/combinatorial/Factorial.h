/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: 
 * Status: 
 * Description: Pre-compute all the factorial numbers until $n$.
 * Usage:
 * Time: 
 */
void init(int n) {
    fact = {1};
    for (int i = 1; i <= n; ++i)
        fact[i] = (ll)i * fact[i-1] % mod;
    ifact.resize(n + 1);
    ifact.back() = modinv(fact.back(), mod);
    for (int i = n; i > 0; --i)
        ifact[i-1] = (ll)i * ifact[i] % mod;
}
