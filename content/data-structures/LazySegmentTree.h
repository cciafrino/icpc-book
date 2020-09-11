/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: me
 * Description: Segment Tree with Lazy update. Can be extended to max/min/product/gcd, pay attention 
 * to propagate, f and update functions when extending. Be careful with each initialization aswell.
 * Status: Tested on USACO 2015 December Contest (Platinum) P3 - Counting Haybales.
 * Time: $O(\lg(N)*Q)$
 */
template<typename T, typename Q> struct segtree_t {
    int N;
    vector<T> tree;
    vector<Q> lazy;
    segtree_t(int _N) : N(_N), tree(4*N), lazy(4*N) {}
    segtree_t(const vector<Q>& o): N(int(o.size())), tree(4*N),
    lazy(4*N){ for (int a = 0; a < N; ++a) tree[a + N] = o[a];}
    T f(const T &a, const T &b) { return (a + b); }
    void propagate(int v, int l, int r) {
        if (!lazy[v]) return; 
        tree[v] += T(r - l + 1) * lazy[v];
        if (l != r) for (int a = 0; a < 2; ++a) lazy[2*v+a] += lazy[v];
        lazy[v] = 0;
    }
    T query(int a, int b) { return query(a, b, 1, 0, N-1); }
    T query(int a, int b, int v, int l, int r) {
        propagate(v, l, r);
        if (b < l || r < a) return 0;
        if (a <= l && r <= b) return tree[v];
        int m = l + (r - l)/2;
        return f(query(a, b, 2*v, l, m), query(a, b, 2*v+1, m+1, r));
    }
    void update(int a, int b, Q delta) { return update(a, b, delta, 1, 0, N-1); }
    void update(int a, int b, Q delta, int v, int l, int r) {
        propagate(v, l, r);
        if (b < l || r < a) return;
        if (a <= l && r <= b) {
            lazy[v] = delta; propagate(v, l, r);
            return;
        }
        int m = l + (r - l)/2;
        update(a, b, delta, 2*v, l, m), update(a, b, delta, 2*v+1, m+1, r);
        tree[v] = f(tree[2*v], tree[2*v + 1]);
    }
};
