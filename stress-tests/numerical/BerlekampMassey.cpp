#include "../utilities/template.h"

const ll mod = 5;
ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a * a % mod, e >> 1);
	return e & 1 ? x * a % mod : x;
}

#define mod dummy
#define modpow dummy2
#include "../../content/number-theory/mod-pow.h"
#undef mod
#undef modpow

#include "../../content/number-theory/modular-arithmetic.h"
using num = modnum<5>;
#include "../../content/numerical/berlekamp-massey.h"


template<class F>
void gen(vector<num>& v, int at, F f) {
	if (at == sz(v)) f();
	else {
		rep(i,0,mod) {
			v[at] = i;
			gen(v, at+1, f);
		}
	}
}

int main() {
	rep(n,1,5) {
		vector<num> start(n);
		vector<num> coef(n), coef2;
		vector<num> full(2*n);
		gen(start, 0, [&]() {
		gen(coef, 0, [&]() {
			rep(i,0,n) full[i] = start[i];
			rep(i,n,2*n) full[i] = 0;
			rep(i,n,2*n) rep(j,0,n) full[i] += coef[j] * full[i - 1 - j];
			coef2 = BerlekampMassey(full);
// rep(i,0,2*n) cerr << full[i] << ' '; cerr << endl;
// rep(i,0,n) cerr << coef[i] << ' '; cerr << endl;
// rep(i,0,sz(coef2)) cerr << coef2[i] << ' '; cerr << endl;
			if (sz(coef2) == n) assert(coef == coef2);
// rep(i,0,n) cerr << full[i] << ' ';
			rep(i,n,2*n) {
				num x = 0;
				rep(j,0,sz(coef2)) x = (x + coef2[j] * full[i-1 - j]);
				// cerr << x << ' ';
				assert(x == full[i].x);
			}
			// cerr << endl;
// cerr << endl;
		});
		});
	}
	cout<<"Tests passed!"<<endl;
	return 0;
}

// int main() {
// 	vector<ll> v{0, 1, 1, 3, 5, 11};
// 	auto v2 = BerlekampMassey(v);
// 	for(auto &x: v2) cout << x << ' ';
// 	cout << endl;
// 	return 0;
// }
