/**
 * Author: Chris
 * Date: 
 * License: CC0
 * Source: Yuhao Du and Chinese Paper.
 * Description: Dirichlet convolution. Change $f$, $gs$ and $fgs$ accordingly. 
 *  This example calculates $\phi(N)$.
 * Status: tested on yosupo
 * Time: $O(N^{\frac{2}{3}})$
 */
template<typename T, typename V> struct dirichlet_convolution {
	V N; // ~ N^{2/3}
	T inv;
	vector<V> fs; // can be any multiplicative function
	vector<T> psum;
	unordered_map<V, T> mapa;
	V f(V x) { return fs[x]; }
	T gs(V x) { return x; }
	T fgs(V x) { return T(x) * (x + 1) / 2; }
	dirichlet_convolution(V _N, const vector<V>& F) : N(_N + 1), fs(F), psum(_N + 1) {
		inv = gs(1);
		for (V a = 0; a + 1 < N; ++a) {
			psum[a + 1] = f(a + 1) + psum[a];
		}
	} 
	T query(V x) {
		if (x < N) return psum[x];
		if (mapa.find(x) != mapa.end()) return mapa[x];
		T ans = fgs(x);
		for (V a = 2, b; a <= x; a = b + 1) {
			b = x / (x / a);
			ans -= (gs(b) - gs(a - 1)) * query(x / a);
		}
		return mapa[x] = (ans / inv);
	}
};
