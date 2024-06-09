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
};