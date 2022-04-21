/**
 * Author: Chris
 * Description: Computes monomials and sum of powers product certain 
 * polynomials. Check "General purpose numbers" section for more info.
 *
 * (Monomials) $\displaystyle pw(x) = x^d$ for a fixed $d$.
 *
 * (Sum of power limit) $\displaystyle \sum_{x=0}^{\infty} r^x f(x)$. (degree of $f \leq d$).
 *
 * (Sum of powers til n) $\displaystyle \sum_{x=0}^{N} r^x f(x)$. (degree of $f \leq d$).
 * Source: library-checker
 */
#include "../number-theory/modular-arithmetic.h"
#include "/lagrange.h"

vector<num> get_monomials(int N, long long d) {
    vector<int> pfac(N);
    for (int i = 2; i < N; ++i) pfac[i] = i;
    for (int p = 2; p < N; ++p) if (pfac[p] == p) {
        for (int m = 2*p; m < N; m += p) if (pfac[m] > p) pfac[m] = p;
    }
    vector<num> pw(N);
    for (int i = 0; i < N; ++i) {
        if (i <= 1 || pfac[i] == i) pw[i] = num(i).pow(d);
        else pw[i] = (pw[pfac[i]] * pw[i / pfac[i]]);
    }
    return pw;
}

num sum_of_power_limit(num r, int d, const vector<num>& fs) {
    Combinatorics<num> M(d + 2);
    vector<num> qs(d + 1); qs[0] = 1;
    for (int x = 1; x <= d; ++x) qs[x] = qs[x - 1] * r;
    num ans = 0, cur_sum = 0;
    for (int x = 0; x <= d; ++x) {
        cur_sum += qs[x] * fs[x];
        ans += cur_sum * invFac[d - x] * invFac[x + 1] * (((d - x) & 1) ? -1 : +1) * qs[d - x];
    }
    // ans is equivalent to invFac(d + 1) * dp(d+1), where
    // for all x in [0, d], dp(x + 1) := E(d, d-x) + dp(x) * r, dp(0) = 0.
    // with E being the eulerian number. Works in O(d^2).
    ans *= (1 - r).pow(-(d + 1)) * fac[d + 1];
    return ans;
}

num sum_of_power(num r, int d, const vector<num>& fs, long long N) {
    if (r == 0) return (0 < N) ? fs[0] : 0;
    Combinatorics<num> M(d + 10);
    vector<num> gs(d + 2); gs[0] = 0;
    num rr = 1;
    for (int x = 0; x <= d; ++x) {
        gs[x + 1] = gs[x] + rr * fs[x];
        rr *= r;
    }
    if (r == 1) return M.interpolate(gs, N);
    const num c = sum_of_power_limit(r, d, fs);
    const num r_inv = r.inv();
    num rr_inv = 1;
    for (int x = 0; x <= d + 1; ++x) {
        gs[x] = rr_inv * (gs[x] - c);
        rr_inv *= r_inv;
    }
    return c + r.pow(N) * M.interpolate(gs, N);
}
