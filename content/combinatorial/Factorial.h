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
    fact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i)
        fact[i] = (lint)i * fact[i-1] % mod;
    ifact.resize(n + 1);
    ifact[n] = modinv(fact[n], mod);
    for (int i = n-1; i >= 0; --i)
        ifact[i] = (lint)(i+1) * ifact[i+1] % mod;
}

