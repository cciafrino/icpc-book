/**
 * Author: Chris
 * Description: Computes monomials and sum of powers product certain 
 * polynomials. Check "General purpose numbers" section for more info.
 * (Monomials) $\displaystyle pw(x) = x^d$ for a fixed $d$.
 * $\displaystyle \sum_{x=0}^{\infty} r^x f(x)$. (degree of $f \leq d$).
 * $\displaystyle \sum_{x=0}^{N-1} r^x f(x)$. (degree of $f \leq d$).
 * Source: library-checker
 */
#include "../number-theory/modular-arithmetic.h"
#include "/lagrange.h"
vector<num> get_monomials(int N, long long d) {
	vector<int> pfac(N);
	for (int i = 2; i < N; ++i) pfac[i] = i;
	for (int p = 2; p < N; ++p) if (pfac[p] == p) {
		for(int m = 2*p; m < N; m += p) if(pfac[m] > p) pfac[m] = p;
	}
	vector<num> pw(N);
	for (int i = 0; i < N; ++i) {
		if (i <= 1 || pfac[i] == i) pw[i] = num(i).pow(d);
		else pw[i] = (pw[pfac[i]] * pw[i / pfac[i]]);
	}
	return pw;
}
num sum_of_power_limit(num r, int d, const vector<num>& fs) {
	interpolator_t<num> M(d + 2); num s = 1; auto gs = fs;
	for (int x = 0; x <= d; ++x, s *= r) gs[x] *= s;
	num ans = 0, cur_sum = 0; s = 1;
	for (int x = 0; x <= d; ++x, s *= -r) {
		cur_sum += choose(d+1, x) * s; ans += cur_sum * gs[d-x];
	} ans *= (1 - r).pow(-(d + 1));
	return ans;
}
num sum_of_power(num r, int d, vector<num>& fs, ll N) {
	if (r == 0) return (0 < N) ? fs[0] : 0;
	interpolator_t<num> M(d + 2);
	vector<num> gs(d + 2); gs[0] = 0; num s = 1;
	for (int x = 0; x <= d; ++x, s *= r)
		gs[x + 1] = gs[x] + s * fs[x];
	if (r == 1) return M.interpolate(gs, N);
	const num c = sum_of_power_limit(r, d, fs);
	const num r_inv = r.inv(); num w = 1;
	for (int x = 0; x <= d + 1; ++x, w *= r_inv)
		gs[x] = w * (gs[x] - c);
	return c + r.pow(N) * M.interpolate(gs, N);
}
