#define PROBLEM "https://judge.yosupo.jp/problem/product_of_polynomial_sequence"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/number-theory/modular-arithmetic.h"

using num = modnum<998244353U>;

inline int nxt_pow2(int s) { return 1 << (s > 1 ? 32 - __builtin_clz(s-1) : 0); }
template <typename T> struct root_of_unity {};
//(MOD,3) := (M1:897581057),(M3:985661441),(M5:935329793)
using M0 = modnum<998244353U>;///start-hash
constexpr unsigned primitive_root(unsigned M) {
	if (M == 880803841U) return 26U; // (M2)
	else if (M == 943718401U) return 7U; // (M4)
	else if (M == 918552577U) return 5U; // (M6)
	else return 3U;
}
template<unsigned MOD> struct root_of_unity<modnum<MOD>> {
	static constexpr modnum<MOD> g0 = primitive_root(MOD);
	static modnum<MOD> f(int K) {
		assert((MOD-1)%K == 0); return g0.pow((MOD-1)/K);
	}
};///end-hash
template<typename T> struct FFT {
	vector<T> rt; vector<int> rev;
	FFT() : rt(2, T(1)) {}
	void init(int N) {///start-hash
		N = nxt_pow2(N);
		if (N > int(rt.size())) {
			rev.resize(N); rt.reserve(N);
			for (int a = 0; a < N; ++a)
				rev[a] = (rev[a/2] | ((a&1)*N)) >> 1;
			for (int k = int(rt.size()); k < N; k *= 2) {
				rt.resize(2*k);
				T z = root_of_unity<T>::f(2*k);
				for (int a = k/2; a < k; ++a)
					rt[2*a] = rt[a], rt[2*a+1] = rt[a] * z;
			}
		}
	}///end-hash
	void fft(vector<T>& xs, bool inverse) const {///start-hash
		int N = int(xs.size());
		int s = __builtin_ctz(int(rev.size())/N);
		if (inverse) reverse(xs.begin() + 1, xs.end());
		for (int a = 0; a < N; ++a) {
			if (a < (rev[a] >> s)) swap(xs[a], xs[rev[a] >> s]);
		}
		for (int k = 1; k < N; k *= 2) {
			for (int a = 0; a < N; a += 2*k) {
				int u = a, v = u + k;
				for (int b = 0; b < k; ++b, ++u, ++v) {
					T z = rt[b + k] * xs[v];
					xs[v] = xs[u] - z, xs[u] = xs[u] + z;
				}
			}
		}
		if (inverse)
			for (int a = 0; a < N; ++a) xs[a] = xs[a] * inv(T(N));
	}///end-hash
	vector<T> convolve(vector<T> as, vector<T> bs) {///start-hash
		int N = int(as.size()), M = int(bs.size());
		int K = N + M - 1, S = nxt_pow2(K); init(S);
		if (min(N, M) <= 64) {
			vector<T> res(K);
			for (int u = 0; u < N; ++u) for (int v = 0; v < M; ++v)
				res[u + v] = res[u + v] + as[u] * bs[v];
			return res;
		} else {
			as.resize(S), bs.resize(S);
			fft(as, false); fft(bs, false);
			for (int i = 0; i < S; ++i) as[i] = as[i] * bs[i];
			fft(as, true); as.resize(K); return as;
		}
	}///end-hash
}; FFT<num> fft;

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;

	if (N == 0) {
		cout << 1 << '\n';
		exit(0);
	}
	vector<vector<num>> poly(N);
	
	for (int i = 0; i < N; ++i) {
		int d; cin >> d;
		poly[i].resize(d+1);
		for (int j = 0; j <= d; ++j) {
			cin >> poly[i][j].x;
		}
	}


	for (int i = N-1; i > 0; --i) {
		int j = i - (i&-i);
		poly[j] = fft.convolve(poly[j], poly[i]);
	}

	for (auto v : poly[0]) {
		cout << v.x << ' ';
	}
	cout << '\n';
}
