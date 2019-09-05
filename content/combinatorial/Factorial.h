/**
 * Author: Chris
 * Description: Precalculate factorials
 */
 
void pre(int lim) {
    fact.resize(lim + 1);
    fact[0] = 1;
    for (int i = 1; i <= lim; ++i)
        fact[i] = (lint)i * fact[i - 1] % mod;
    inv_fact.resize(lim + 1);
    inv_fact[lim] = inv(fact[lim], mod);
    for (int i = lim - 1; i >= 0; --i)
        inv_fact[i] = (lint)(i + 1) * inv_fact[i + 1] % mod;
}

