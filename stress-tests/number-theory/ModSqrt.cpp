#include "../utilities/template.h"

ll modpow(ll a, ll e, ll mod) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1, mod);
	return e & 1 ? x * a % mod : x;
}

unsigned xrand() {
	static unsigned x = 314159265, y = 358979323, z = 846264338, w = 327950288;
	unsigned t = x ^ x << 11; x = y; y = z; z = w; return w = w ^ w >> 19 ^ t ^ t >> 8;
}


#include "../../content/number-theory/mod-sqrt.h"

int main() {
	rep(p,2,10000) {
		rep(i,2,p) if (p % i == 0) goto next;
		rep(a,0,p) {
			if (p != 2 && modpow(a, (p-1)/2, p) == p-1) continue;
			auto v = mod_sqrt(a, p);
			auto x = v.front();
			assert(0 <= x && x < p);
			assert(x * x % p == a);
		}
next:;
	}
	cout<<"Tests passed!"<<endl;
}
