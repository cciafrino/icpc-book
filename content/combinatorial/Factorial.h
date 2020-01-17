/**
 * Author: Chris
 * Description: Precalculate factorials
 */
 
void init(int lim) {
    fact.resize(lim + 1);
    fact[0] = 1;
    for (int i = 1; i <= lim; ++i)
        fact[i] = (lint)i * fact[i-1] % mod;
    ifact.resize(lim + 1);
    ifact[lim] = modinv(fact[lim], mod);
    for (int i = lim-1; i >= 0; --i)
        ifact[i] = (lint)(i+1) * ifact[i+1] % mod;
}

void init(int lim) { // modtemplate!
	fact = {1};
	for(int i = 1; i <= lim; i++) 
		fact.push_back(i * fact[i-1]);
	ifact.resize(fact.size());
	ifact.back() = 1/fact.back();
	for(int i = (int)ifact.size()-1; i > 0; i--) 
		ifact[i-1] = i * ifact[i]; 
}

