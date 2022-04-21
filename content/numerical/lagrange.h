/**
 * Author: Célio Passos
 * Description: Lagrange interpolation over a finite field and some combo stuff 
 * Source: 
 * Time: $O(N)$
 */
#include "../number-theory/modular-arithmetic.h"
#include "../number-theory/preparator.h"
template<typename T> struct Combinatorics {
    vector<T> pref, suff;
    Combinatorics(int N) : pref(N), suff(N) {}
    T interpolate(const vector<T>& y, T x) {
        int n = int(y.size());
        pref[0] = suff[n - 1] = 1;
        for (int i = 0; i + 1 < n; ++i) {
            pref[i + 1] = pref[i] * (x - i);
        }
        for (int i = n - 1; i > 0; --i) {
            suff[i - 1] = suff[i] * (x - i);
        }
        T res = 0;
        for (int i = 0, sgn = (n % 2 ? +1 : -1); i < n; ++i, sgn *= -1) {
            res += y[i] * sgn * pref[i] * suff[i] * invFac[i] * invFac[n - 1 - i];
        }
        return res;
    }
    T C(int n, int k) {
        return k < 0 || n < k ? 0 : fac[n] * invFac[k] * invFac[n - k];
    }
    T S(int n, int k) {
        return k == 0 ? n == 0 : C(n + k - 1, k - 1);
    }
};
