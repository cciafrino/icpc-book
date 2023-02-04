#include "../utilities/template.h"

#include "../../content/number-theory/discrete-log.h"

int main() {
	const int lim = 100;
	rep(m,1,lim) {
		rep(a,0,lim) {
			vector<ll> ans(m, -1);
			ll b = a % m;
			rep(x,1,max(m,2)) {
				if (ans[b] == -1) ans[b] = x;
				b = b * a % m;
			}
			// special case this because our algorithm considers 0^0 = 1
			ans[1] = 0;
			if (m == 1) ans[0] = 0;
			rep(b,0,m) {
				ll res = modLog(a, b, m);
				if (ans[b] != res) {
					cerr << "FAIL" << endl;
					cerr << "Expected log(" << a << ", " << b << ", " << m << ") = " << ans[b] << ", found " << res << endl;
					return 1;
				}
			}
		}
	}
	cout<<"Tests passed!"<<endl;
}
