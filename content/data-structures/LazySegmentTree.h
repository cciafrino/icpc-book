/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: me
 * Description: Segment tree with ability to add or set values of large intervals, and compute sum of intervals.
 * Can be changed to other things.
 */
 
template<typename T>
struct segtree_t {
    int n;
    vector<T> tree, lazy;
    segtree_t(int _n) : n(_n), tree(4*n, 0), lazy(4*n, 0) { build(1, 0, n-1); }
    T f(const T a, const T b) { return a + b; } //any commutative
    void build(int v, int lx, int rx) {
        if (lx == rx) return;
        else {
            int m = lx + (rx - lx)/2;
            build(2*v, lx, m);
            build(2*v+1, m+1, rx);
            tree[v] = f(tree[2*v], tree[2*v+1]);
        }
    }
    void push(int v, int lx, int rx) {
        tree[v] += lazy[v] * (rx - lx + 1); // Change if needed
        if (lx != rx) {
            lazy[2*v] += lazy[v];
            lazy[2*v+1] += lazy[v];
        }
        lazy[v] = 0;
    }
    void update(int a, int b, T delta) { update(1,0,n-1,a,b,delta); }
    void update(int v, int lx, int rx, int a, int b, T delta) {
        push(v, lx, rx);
        if (b < lx || rx < a) return;
        if (a <= lx && rx <= b) {
            lazy[v] = delta;
            push(v, lx, rx);
        }
        else {
            int m = lx + (rx - lx)/2;
            update(2*v, lx, m, a, b, delta);
            update(2*v+1, m+1, rx, a, b, delta);
            tree[v] = f(tree[2*v], tree[2*v+1]);
        }
    }
    T query(int a, int b) { return query(1, 0, n-1, a, b); }
    T query(int v, int lx, int rx, int a, int b) {
        push(v, lx, rx);
        if (a <= lx && rx <= b) return tree[v];
        if (b < lx || rx < a) return 0;
        int m = lx + (rx - lx)/2;
        return f(query(2*v, lx, m, a, b), query(2*v+1, m+1, rx, a, b));
    } 
};

