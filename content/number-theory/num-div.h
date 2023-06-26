/**
 * Author: Chris
 * Description: Count the number of divisors of $n$. Requires having run Sieve up to at least sqrt(n).
 * Time: $O(log(N))$
 */
#include "sieve.h"
template<typename T> T numDiv(T n) {
	T how_many = 1, prime_factors = 0;
	while(n != 1) {
		T p = lp[n];
		int exp = 0;
		do {
			n /= p;
			++exp;
			++prime_factors; //count prime factors!
		} while(n % p == 0);
		how_many *= 1ll * (exp + 1);
	}
	if (n != 1) ++prime_factors;
	return how_many;
}
