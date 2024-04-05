#include "../utilities/template.h"

void FST(vector<int> &a, bool inv) {
	for (int n = a.size(), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) for(int j = i; j < i+step; ++j) {
			int &u = a[j], &v = a[j + step]; tie(u, v) =
				// inv ? pii(v - u, u) : pii(v, u + v); // AND
				// inv ? pii(v, u - v) : pii(u + v, u); // OR
				pii(u + v, u - v);                   // XOR
		}
	}
	if (inv) for(auto &x : a) x /= a.size(); // XOR only
}
vector<int> conv(vector<int> a, vector<int> b) {
	FST(a, 0); FST(b, 0);
	for(int i = 0; i < a.size(); ++i) a[i] *= b[i];
	FST(a, 1); return a;
}

int main() {
	rep(k,0,10) {
		vi a(1 << k), b = a, c = a, target = a;
		for(auto &x: a) x = rand() % 6 - 2;
		for(auto &x: b) x = rand() % 6 - 2;
		rep(i,0,1 << k) rep(j,0,1 << k) target[i ^ j] += a[i] * b[j];
		// rep(i,0,1 << k) cout << a[i] << ' '; cout << endl;
		// rep(i,0,1 << k) cout << b[i] << ' '; cout << endl;
		FST(a, false);
		FST(b, false);
		rep(i,0,1 << k) c[i] = a[i] * b[i];
		FST(c, true);
		// rep(i,0,1 << k) cout << c[i] << ' '; cout << endl;
		// rep(i,0,1 << k) cout << target[i] << ' '; cout << endl;
		assert(c == target);
	}
	cout<<"Tests passed!"<<endl;
}
