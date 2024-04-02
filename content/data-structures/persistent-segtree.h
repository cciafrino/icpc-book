/**
 * Author: Antoni Dlugosz
 * Source:
 * Description: Sparse ($N$ can be up to 1e18) persistent segment tree.
 * Time:
 * Status: Tested on atcoder, dmoj and yosupo library checker.
 */ 
template<typename T> struct seg_tree {
	T idnt = 0; // identity value
	T f(T l, T r) { return l + r; }
	struct node {
		int l = 0, r = 0;
		T x;
		node(T _x) : x(_x) {}
	};
	int N; vector<node> t;
	seg_tree(int _N) : N(_N) { t.push_back(node(idnt)); }
	int cpy(int v) {
		t.push_back(t[v]);
		return int(t.size()) - 1;
	}
	int upd(int v, int p, T x, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		int u = cpy(v);
		if (a == b) {
			t[u].x += x;
			return u;
		}
		int m = (a + b) / 2;
		if (p <= m) t[u].l = upd(t[v].l, p, x, a, m);
		else t[u].r = upd(t[v].r, p, x, m+1, b);
		t[u].x = f(t[t[u].l].x, t[t[u].r].x);
		return u;
	}
	T get(int v, int l, int r, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (!v || l > b || r < a) return idnt;
		if (a >= l && b <= r) return t[v].x;
		int m = (a + b) / 2;
		return f(get(t[v].l, l,r, a, m),get(t[v].r, l, r, m+1, b));
	}
	T get_kth(int l, int r, int k, int a = 0, int b = -1) {
		b = ~b ? b : N - 1;
		if (a == b) return a;
		int cnt = t[t[r].l].x - t[t[l].l].x;
		int m = (a + b) / 2;
		if (k <= cnt) return get_kth(t[l].l, t[r].l, k, a, m);
		return get_kth(t[l].r, t[r].r,  k-cnt, m+1, b);
	}
};