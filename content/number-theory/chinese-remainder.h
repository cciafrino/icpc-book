/**
 * Author: Chris
 * Description: Chinese Remainder Theorem.
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv b \pmod n$.
 * If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x < \text{lcm}(m, n)$.
 * Assumes $mn < 2^{62}$.
 * Status: tested on kattis
 * Time: $O(n\log(LCM(m)))$
 */
#include "extended-euclid.h"
template<typename T>
pair<T, T> crt(const vector<T>& a, const vector<T>& m) {
    int N = int(a.size());
    T r = 0, md = 1, x, y;
    for (int i = 0; i < N; ++i) {
        T g = egcd(md, m[i], x = 0, y = 0);
        T im = x;
        if ((a[i] - r) % g) return {0, -1};
        T tmp = (a[i] - r) / g * im % (m[i] / g);
        r += md * tmp;
        md *= m[i] / g;
    }
    return {(r % md + md) % md, md};
}
