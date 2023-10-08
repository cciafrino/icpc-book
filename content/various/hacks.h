/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: 
 */
// Iterate on non-empty submasks of a bitmask.
for (int s = m; s > 0; s = (m & (s - 1))) 
// Iterate on non-zero bits of a bitset B.
for (int j = B._Find_next(0); j < MAXV; j = B._Find_next(j))
ll next_perm(ll v) { // compute next perm i.e.
	ll t = v | (v-1);  // 00111,01011,01101,10011 ...
	return (t + 1) | (((~t & -~t) - 1)>>(__builtin_ctz(v) + 1));
}
template<typename F>	// All subsets of size k of {0..N-1}
void iterate_k_subset(ll N, ll k, F f){
	ll mask = (1ll << k) - 1;
	while (!(mask & 1ll<<N)) { f(mask);
		ll t = mask | (mask-1);
		mask = (t+1)|(((~t & -~t)-1)>>(__builtin_ctzll(mask)+1));
	}
}
template<typename F> // All subsets of set
void iterate_mask_subset(ll set, F f){ ll mask = set;
	do  f(mask), mask = (mask-1) & set;
	while (mask != set);
}
