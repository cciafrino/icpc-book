/**
 * Author: BenQ
 * Date: 
 * License: 
 * Source: github.com/bqi343/USACO
 * Description: Fenwick Tree of SegTrees. 1-indexed. x goes from left to right and y top to bottom. 
 * Time: O(\log N)
 * Status:
 */
#include"DynamicSegTree.h" // make point update version
template<typename T> struct FT {
	int n;
    vector<node*> tree;
	FT(int n) : n(n), tree(n) {
        for (int i = 0; i < n; ++i) tree[i] = build(0, n);
	}
	void update(int i, int j, int delta) {
		for (; i < n/2; i += i&-i) upd(tree[i],0, n, j, delta);
	}
	T query(int i, int a, int b) {
		T result = 0; 
		for (; i; i -= i&-i) 
			result = __gcd(result, qry(tree[i], a, b));
		return result;
	}
	T query(int ya, int yb, int xa, int xb) { 
		return query(yb, xa, xb) - query(ya-1, xa, xb);
	}
};