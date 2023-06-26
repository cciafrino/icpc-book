/**
 * Author: Chris
 * Date: 2016-08-23
 * License: CC0
 * Source: me
 * Description: 
 */

// Returns one plus the index of the least significant 1-bit of x, or if x is zero, returns zero.
__builtin_ffs(x)

// Returns the number of leading 0-bits in x, starting at the most significant bit position. If x is 0, the result is undefined.
__builtin_clz(x)

// Returns the number of trailing 0-bits in x, starting at the least significant bit position. If x is 0, the result is undefined.
__builtin_ctz(x)

// Returns the number of 1-bits in x.
__builtin_popcount(x)

// For long long versions append ll (e.g. __builtin_popcountll)

// Least significant bit in x.
x & -x

// Iterate on non-empty submasks of a bitmask.
for (int submask = mask; submask > 0; submask = (mask & (submask - 1)))

// Iterate on non-zero bits of a bitset.
for (int j = btset._Find_next(0); j < MAXV; j = btset._Find_next(j))

int __builtin_clz(int x); // number of leading zero
int __builtin_ctz(int x); // number of trailing zero
int __builtin_clzll(lint x); // number of leading zero
int __builtin_ctzll(lint x); // number of trailing zero
int __builtin_popcount(int x); // number of 1-bits in x
int __builtin_popcountll(lint x); // number of 1-bits in x


// compute next perm. i.e. 00111, 01011, 01101, 10011, ...
lint next_perm(lint v) {
	lint t = v | (v-1);
	return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
}


template<typename F>	// All subsets of size k of {0..N-1}
void iterate_k_subset(ll N, ll k, F f){
	ll mask = (1ll << k) - 1;
	while (!(mask & 1ll<<N)) { f(mask);
		ll t = mask | (mask-1);
		mask = (t+1) | (((~t & -~t) - 1) >> (__builtin_ctzll(mask)+1));
	}
}
template<typename F>	// All subsets of set
void iterate_mask_subset(ll set, F f){ ll mask = set;
	do  f(mask), mask = (mask-1) & set;
	while (mask != set);
}
