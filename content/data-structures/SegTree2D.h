/**
 * Author: Chris
 * Date: 2020
 * License: CC0
 * Source: tfg
 * Description: 2D Segment Tree. 
 * Status: Tested on URI 1511
 */

template<typename T> struct SegTree2D {
    int n, m;
    vector<vector<T>> tree;
    SegTree2D(int n, int m) : n(n), m(m), tree(2*n, vector<int>(2*m)) {}
    T f(int a, int b) { return (a + b); }
    void update(int a, int b, int delta) {
        assert(0 <= a && a < n && 0 <= b && b < m);
        a += n, b += m;
        tree[a][b] = delta;
        for (int i = (b >> 1); i; i >>= 1) 
            tree[a][i] = f(tree[a][i<<1], tree[a][i<<1|1]);
        for (a >>= 1; a; a >>= 1) {
            tree[a][b] = f(tree[a<<1][b], tree[a<<1|1][b]);
            for(int i = (b >> 1); i; i >>= 1) 
                tree[a][i] = f(tree[a][i<<1], tree[a][i<<1|1]);
        }
    }
    vector<int> getCover(int l, int r, int N) {
        l = max(0, l); r = min(N, r);
        vector<int> result;
        for (l += N-1, r += N; l^r^1; l >>= 1, r >>= 1) {
            if(~l & 1) result.push_back(l^1);
            if(r & 1) result.push_back(r^1);
        }
        return result;
    }
    T query(int ya, int yb, int xa, int xb) {
        vector<int> p = getCover(ya, yb, n);
        vector<int> q = getCover(xa, xb, m);
        T ans = T();
        for(int i : p) for(int j : q) ans = f(tree[i][j], ans);
        return ans;
    }
};