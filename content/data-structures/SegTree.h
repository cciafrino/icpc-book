/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed sum-tree. Bounds are inclusive to the left and exclusive to the right. Can be changed by modifying T, LOW and f.
 * Time: O(\log N)
 * Status: fuzz-tested
 */
template<typename T>
struct tree_t {
    static const T LOW = 0;
    T f(T a, T b) { return (a + b); } // (any associative fn)
    vector<T> s; int n;
    tree_t(int n = 0, T def = 0) : s(2*n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos > 1; pos /= 2)
            s[pos / 2] = f(s[pos & ~1], s[pos | 1]);
    }
    T query(int b, int e) { // query [b, e)
        T ra = LOW, rb = LOW;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};
