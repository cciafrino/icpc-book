/**
 * Author: Chris
 * Description: query(a, b) - {{min(v[a..b]), max(v[a..b])}, sum(v[a..b])}
 * update_min(a, b, x) faz com que v[i] <- min(v[i], x) para todo i em [a,b]
 * update_max é análogo a update_min, update_sum soma x em todo mundo do intervalo [a, b]
 * Time: Build - O(n), Query - O(\log(n)), Update - O(\log^2(n))
 */

template<typename T>
struct segtreebeats_t {
	struct node_t {
		int sz;
		T sum, lazy;
		T mx1, mx2, mx;
		T my1, my2, my;
		node_t(T x = 0) {
			sum = mx1 = my1 = x;
			mx2 = INF, my2 = -INF;
			mx = my = sz = 1;
			lazy = 0;
		}
		node(const node_t& left, const node_t& right) {
			sum = left.sum + right.sum;
			sz = left.sz + right.sz;
			lazy = 0;
			if (left.mx1 > right.mx1) {
				mx1 = right.mx1, mx = right.mx;
				mx2 = min(left.mx1, right.mx2);
			} else if (left.mx1 < right.mx1) {
				mx1 = left.mx1, mx = left.mx;
				mx2 = min(right.mx1, left.mx2);
			} else {
				mx1 = left.mx1, mx = left.mx+right.mx;
				mx2 = min(left.mx2, right.mx2);
			}
			if (left.my1 < right.my1) {
				my1 = right.my1, my = right.my;
				my2 = max(left.my1, right.my2);
			} else if (left.my1 > right.my1) {
				my1 = left.my1, my = left.my;
				my2 = max(right.my1, left.my2);
			} else {
				my1 = left.my1, my = left.my+right.my;
				my2 = max(left.my2, right.my2);
			}
		}
		void setmin(T x) {
			if (x >= my1) return;
			sum += (x - my1)*my;
			if (mx1 == my1) mx1 = x;
			if (mx2 == my1) mx2 = x;
			my1 = x;
		}
		void setmax(T x) {	
			if (x <= mx1) return;
			sum += (x - mx1) * mx;
			if (my1 == mx1) my1 = x;
			if (my2 == mx1) my2 = x;
			mx1 = x;
		}
		void setsum(T x) {
			mx1 += x, mx2 += x, my1 += x, my2 += x;
			sum += x * sz;
			lazy += x;
		}
	};
	int n;
	T INF = 0x3f3f3f3f3f3f3f3f;
	vector<T> values;
	vector<node_t> tree;
	segtreebeats_t(vector<T>& other) n(other.size()), values(other), tree(4*n) {}
	node_t build(int v = 1, int lx = 0, int rx = n-1) {
		if (lx == rx) return tree[v] = {values[lx]};
		int mid = (lx + rx)/2;
		return tree[v] = {build(2*v, lx, mid), build(2*v+1, mid+1, rx)};
	}
	void build(int _n, vector<T>& o) {
		n = _n, values(o);
		build();
	}
	void propagate(int v, int lx, int rx) {
		if (lx == rx) return;
		for (int i = 0; i < 2; ++i) {
			if (tree[v].lazy) tree[2*v+i].setsum(tree[v].lazy);
			tree[2*v+i].setmin(tree[v].my1);
			tree[2*v+i].setmax(tree[v].mx1);
		}
		tree[v].lazy = 0;
	}
	pair<pair<T, T>, T> query(int a, int b, int v = 1, int lx = 0, int rx = n-1) {
		if (b < lx || rx < a) return {{INF, -INF}, 0};
		if (a <= lx && rx <= b) return {{tree[v].mx1, tree[v].my1}, tree[v].sum};
		propagate(v, lx, rx);
		int mid = (lx + rx)/2;
		auto L = query(a, b, 2*v, lx, mid), R = query(a, b, 2*v+1, mid+1, rx);
		return {{min(L.first.first, R.first.first), max(L.first.second, R.first.second)}, L.second + R.second};
	}
	node_t update_min(int a, int b, T x, int v = 1, int lx = 0, int rx = n-1) {
		if (b < lx || rx < a || tree[v].my1 <= x) return tree[v];
		if (a <= lx && rx <= b && tree[v].my2 < x) {
			tree[v].setmin(x);
			return tree[v];
		}
		propagate(v, lx, rx);
		int mid = (lx + rx)/2;
		return tree[v] = {update_min(a, b, x, 2*v, lx, mid), update_min(a, b, x, 2*v+1, mid+1, rx)};
	}
	node_t update_max(int a, int b, T x, int v = 1, int lx = 0, int rx = n-1) {
		if (b < lx || rx < a || tree[v].mx1 >= x) return tree[v];
		if (a <= lx && rx <= b && tree[v].mx2 > x) {
			tree[v].setmax(x);
			return tree[v];
		}
		propagate(v, lx, rx);
		int mid = (lx + rx)/2;
		return tree[v] = {update_max(a, b, x, 2*v, lx, mid), update_max(a, b, x, 2*v+1, mid+1, rx)};
	}
	node_t update_sum(int a, int b, T x, int v = 1, int lx = 0, int rx = n-1) {
		if (b < lx || rx < a) return tree[v];
		if (a <= lx && rx <= b) {
			tree[v].setsum(x);
			return tree[v];
		}
		propagate(v, lx, rx);
		int mid = (lx + rx)/2;
		return tree[v] = {update_sum(a, b, x, 2*v, lx, mid), update_sum(a, b, x, 2*v+1, mid+1, rx)};
	}
};