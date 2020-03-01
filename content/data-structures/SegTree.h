/**
 * Author: Lucian Bicsi, Chris
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
    tree_t() {}
    tree_t(int size, T def = LOW) : s(2*size, def), n(size) {}
    tree_t(const vector<T> &other) : n(other.size()), s(2*other.size(), LOW) {
        copy(other.begin(), other.end(), s.begin() + n);
        for (int i = n; i-- > 1; )
            s[i] = f(s[i<<1], s[i<<1|1]);
    }
    void update(int pos, T val) {
        for (s[pos += n] = val; pos > 1; pos /= 2)
            s[pos / 2] = f(s[pos & ~1], s[pos | 1]);
    }
    T query(int l, int r) { // query [b, e)
        T ra = LOW, rb = LOW;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l % 2) ra = f(ra, s[l++]);
            if (r % 2) rb = f(s[--r], rb);
        }
        return f(ra, rb);
    }
};