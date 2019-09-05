/**
 * Author: BenQ
 * Description: Full Iterative Segment Tree
 */

template <typename T>
struct segtree_t {
    T id = 0; 
    int n; vector<T> tree;
    segtree_t(int _n) : n(_n), tree(4*n, 0) { 
        for (int i = 1; i <= n; ++i) 
	    	tree[i] = f(tree[2*i], tree[2*i+1]);
    }
    T f(const T &a, const T &b) { return a+b; }
    T query(int lx, int rx) {
		T x = id, y = id; rx++;
		for (lx += n, rx += n; lx < rx; lx /= 2, rx /= 2) {
	    	    if (lx % 2) x = f(x, tree[lx++]);
		        if (rx % 2) y = f(tree[--rx], y);
		}
		return f(x, y);
    }
    void update(int v, T delta) {
        tree[v += n] = delta;
		for (v /= 2; v; v /= 2) 
		    tree[v] = f(tree[2*v], tree[2*v+1]);
    }
    T find_first(int v, int lx, int rx) { // fist [l,r] <= v
        int l = -1;
        int r = -1;
        for (int a = lx + n, b = rx + n; a < b ; a /= 2, b /= 2) {
            if (a&1) {
                if (tree[a] <= v) 
                    if (l == -1) l = a;
                a += 1;
            }
            if (b&1) {
                b--;
                if (tree[b] <= v) r = b;
            }
        }
        int cur;
        if (l != -1) cur = l;
        else if (r != -1) cur = r;
        else return -1;
        assert(tree[cur] <= v);
        while(cur < n) {
            if (tree[2*cur] <= v) cur = 2*cur;
            else if (tree[2*cur+1] <= v) cur = 2*cur+1;
            else assert(false);
        }
        return cur - n;
    }
};
