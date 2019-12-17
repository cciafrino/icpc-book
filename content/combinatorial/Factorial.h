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

void init() {
	fact = {1};
	for(int i = 1; i < 1010; i++) 
		fact.push_back(i * fact[i-1]);
	ifact.resize(fact.size());
	ifact.back() = 1/fact.back();
	for(int i = (int)ifact.size()-1; i > 0; i--) 
		ifact[i-1] = i * ifact[i]; 
}

