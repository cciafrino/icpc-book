/**
 * Author: Chris
 * Date: 2023
 * License: 
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
 Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description:  For convolution of complex numbers or more than two vectors: FFT, multiply
 pointwise, FFT inverse back.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: stress tested
 * Details: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
 * Useful for convolution:
 * \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
 * Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
 * (in practice $10^{16}$; higher for random inputs). Otherwise, use NTT/FFTMod.
 */
inline int nxt_pow2(int s) { return 1 << (s > 1 ? 32 - __builtin_clz(s-1) : 0); }
template <typename T> struct root_of_unity {};

template <typename dbl> struct cplx {
	dbl x, y; using P = cplx;
	cplx(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) { }
	friend P operator+(P a, P b) { return P(a.x+b.x, a.y+b.y); }
	friend P operator-(P a, P b) { return P(a.x-b.x, a.y-b.y); }
	friend P operator*(P a, P b) { return P(a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x); }
	friend P conj(P a) { return P(a.x, -a.y); }
	friend P inv(P a) { dbl n = (a.x*a.x+a.y*a.y); return P(a.x/n,-a.y/n); }
};
template <typename dbl> struct root_of_unity<cplx<dbl>> {
	static cplx<dbl> f(int k) {
		static const dbl PI = acos(-1); dbl a = 2*PI/k;
		return cplx<dbl>(cos(a),sin(a));
	}
};

//(MOD,3) := (M1:897581057),(M3:985661441),(M5:935329793)
using M0 = modnum<998244353U>;
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
};
template<typename T> struct FFT {
	vector<T> rt; vector<int> rev;
	FFT() : rt(2, T(1)) {}
	void init(int N) {
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
	}
	void fft(vector<T>& xs, bool inverse) const {
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
	}
	vector<T> convolve(vector<T> as, vector<T> bs) {
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
	}
}; FFT<M0> FFT0;

// T = {unsigned, unsigned long long, modnum<M>}
template<class T, unsigned M0, unsigned M1, unsigned M2, unsigned M3, unsigned M4>
T garner(modnum<M0> a0, modnum<M1> a1, modnum<M2> a2, modnum<M3> a3, modnum<M4> a4) {
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	static const modnum<M2> INV_M0M1_M2 = (modnum<M2>(M0) * M1).inv();
	// static const modnum<M3> INV_M0M1M2_M3 = (modnum<M3>(M0) * M1 * M2).inv();
	// static const modnum<M4> INV_M0M1M2M3_M4 = (modnum<M4>(M0) * M1 * M2 * M3).inv();
	const modnum<M1> b1 = INV_M0_M1 * (a1 - a0.x);
	const modnum<M2> b2 = INV_M0M1_M2 * (a2 - (modnum<M2>(b1.x) * M0 + a0.x));
	// const modnum<M3> b3 = INV_M0M1M2_M3 * (a3 - ((modnum<M3>(b2.x) * M1 + b1.x) * M0 + a0.x));
	// const modnum<M4> b4 = INV_M0M1M2M3_M4 * (a4 - (((modnum<M4>(b3.x) * M2 + b2.x) * M1 + b1.x) * M0 + a0.x));
	return (T(b2.x) * M1 + b1.x) * M0 + a0.x;
	// return (((T(b4.x) * M3 + b3.x) * M2 + b2.x) * M1 + b1.x) * M0 + a0.x;
}
// results must be in [-448002610255888384, 448002611254132736]
vector<long long> convolve(const vector<long long>& as, const vector<long long>& bs) {
	static constexpr unsigned M0 = M0::M, M1 = M1::M;
	static const modnum<M1> INV_M0_M1 = modnum<M1>(M0).inv();
	if (as.empty() || bs.empty()) return {};
	const int len_as = int(as.size()), len_bs = int(bs.size());
	vector<modnum<M0>> as0(len_as), bs0(len_bs);
	for (int i = 0; i < len_as; ++i) as0[i] = as[i];
	for (int i = 0; i < len_bs; ++i) bs0[i] = bs[i];
	const vector<modnum<M0>> cs0 = FFT0.convolve(as0, bs0);
	vector<modnum<M1>> as1(len_as), bs1(len_bs);
	for (int i = 0; i < len_as; ++i) as1[i] = as[i];
	for (int i = 0; i < len_bs; ++i) bs1[i] = bs[i];
	const vector<modnum<M1>> cs1 = FFT1.convolve(as1, bs1);
	vector<long long> cs(len_as + len_bs - 1);
	for (int i = 0; i < len_as + len_bs - 1; ++i) {
		const modnum<M1> d1 = INV_M0_M1 * (cs1[i] - cs0[i].x);
		cs[i] = (d1.x > M1 - d1.x)
			? (-1ULL - (static_cast<unsigned long long>(M1 - 1U - d1.x) * M0 + (M0 - 1U - cs0[i].x)))
			: (static_cast<unsigned long long>(d1.x) * M0 + cs0[i].x);
	}
	return cs;
}
