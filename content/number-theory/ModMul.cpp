/**
 * Author: Chris
 * Description: Modular multiplication operation
 */

inline lint mul(lint a, lint b, lint m) {
	if (m <= 1000000000) return a * b % m;
	else if (m <= 1000000000000ll) return (((a*(b>>20)%m)<<20)+(a*(b&((1<<20)-1))))%m;
	else {
		lint x = (lint)floor(a*(long double)b/m+0.5);
		lint ret = (a*b - x*m) % m;
		if (ret < 0) ret += m;
		return ret;
	}
}
