/**
 * Author: Chris
 * Description: Lagrange interpolation over a finite field and some combo stuff 
 * Source: Célio Passos
 * Time: $O(N)$
 */
#include "../number-theory/modular-arithmetic.h"
#include "../number-theory/preparator.h"
template<typename T> struct interpolator_t {
	vector<T> S;
	interpolator_t(int N): S(N) {}
	T interpolate(const vector<T>& y, T x) { ///start-hash
		int N = int(y.size()); int sgn = (N & 1 ? 1 : -1);
		T res = 0, P = 1; S[N - 1] = 1;
		for (int i = N-1; i > 0; --i) S[i-1] = S[i] * (x-i);
		for (int i = 0; i < N; ++i, sgn *= -1, P *= (x - i + 1)) {
			res += y[i] * sgn * P * S[i] * ifact[i] * ifact[N-1-i];
		}
		return res;
	} ///end-hash
};
