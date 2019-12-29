/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: me
 * Description: Better SegTree. Range Sum, can be extended to max/min/product/gcd, pay attention 
 * to propagate, f and update functions when extending. Be careful with each initialization aswell.
 */

template<typename T, typename Q>
struct segtree_t {
    int n;
    vector<T> tree;
    vector<Q> lazy, og;
    segtree_t(int N) : n(N), tree(4*N), lazy(4*N) {}
    segtree_t(const vector<Q> &other) :
            n(other.size()), og(other),
            tree(4*n), lazy(4*n) {
        build(1, 0, n-1);
    }
    T f(const T &a, const T &b) { return (a + b); }
    T build(int v, int l, int r) {
        lazy[v] = 0;
        if (l == r) return tree[v] = og[l];
        int m = l + (r - l)/2;
        return tree[v] = f(build(2*v,l, m), build(2*v+1, m+1, r));
    }
    void propagate(int v, int l, int r) {
        if (!lazy[v]) return; 
        int m = l + (r - l)/2;
        tree[2*v] += lazy[v] * (m - l + 1);
        tree[2*v+1] += lazy[v] * (r - (m+1) + 1);
        lazy[2*v] += lazy[v];
        lazy[2*v+1] += lazy[v];
        lazy[v] = 0;
    }
    T query(int a, int b) { return query(a, b, 1, 0, n-1); }
    T query(int a, int b, int v, int l, int r) {
        if (b < l || r < a) return 0;
        if (a <= l && r <= b) return tree[v];
        propagate(v,l, r);
        int m = l + (r - l)/2;
        return f(query(a, b, 2*v,l, m), query(a, b, 2*v+1, m+1, r));
    }
    T update(int a, int b, Q delta) { return update(a, b, delta, 1, 0, n-1); }
    T update(int a, int b, Q delta, int v, int l, int r) {
        if (b < l || r < a) return tree[v];
        if (a <= l && r <= b) {
            tree[v] += delta * (r-l+1);
            lazy[v] += delta;
            return tree[v];
        }
        propagate(v,l, r);
        int m = l + (r - l)/2;
        return tree[v] = f(update(a, b, delta, 2*v, l, m),
            update(a, b, delta, 2*v+1, m+1, r));
    }
};

