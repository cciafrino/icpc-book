/**
 * Author: Chris
 * Description: Lagrange interpolation over a finite field and some combo stuff 
 * Source: Célio Passos
 * Time: $O(N)$
 */
#include "../number-theory/modular-arithmetic.h"
#include "../number-theory/preparator.h"
template<typename T> struct interpolator_t {
	vector<T> pref, suff;
	interpolator_t(int N): pref(N), suff(N) {}
	T interpolate(const vector<T>& y, T x) {
		int N = int(y.size()); T res = 0;
		pref[0] = suff[N - 1] = 1;
		for (int i = 0; i+1 < N; ++i) pref[i+1] = pref[i] * (x-i);
		for (int i = N-1; i > 0; --i) suff[i-1] = suff[i] * (x-i);
		for (int i = 0, sgn = (N & 1 ? +1 : -1); i < N; ++i, sgn *= -1) {
			res += y[i] * sgn * pref[i] * suff[i] * invFac[i] * invFac[N-1-i];
		}
		return res;
	}
};
