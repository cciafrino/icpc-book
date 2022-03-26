/**
 * Author: Chris
 * Source: Zhou + some blog on cf
 * Description: Persistent implementation of a segment tree. This one compute the kth smallest element in a subarray $[a, b]$. 
 * Time: 
 */
struct segtree_t {
    struct snapshot {
	int cnt, linkl, linkr;
	snapshot() : cnt(0), linkl(0), linkr(0) {}
	snapshot(int _cnt, int l, int r) : cnt(_cnt), linkl(l), linkr(r) {}
    };
    int id;
    vector<snapshot> tree;
    segtree_t() {}
    segtree_t(int n) : id(1), tree(20*n) {}
    int update(int v, int l, int r, int x) {
	if (x < l || x > r) return v;
	if (l == r) {
	    tree[id] = snapshot(1, 0, 0);
	    return id++;
	}
	int m = (l + r) >> 1;
	int lx = update(tree[v].linkl, l, m, x);
	int rx = update(tree[v].linkr, m+1, r, x);
	tree[id] = snapshot(tree[lx].cnt + tree[rx].cnt, lx, rx);
	return id++;
    }
    int query(int a, int b, int l, int r, int k) {
	if (l == r) return l;
	int m = (l + r) >> 1;
	int cnt = tree[tree[b].linkl].cnt - tree[tree[a].linkl].cnt;
	if (k <= cnt)
	    return query(tree[a].linkl, tree[b].linkl, l, m, k);
	return query(tree[a].linkr, tree[b].linkr, m+1, r, k-cnt);
    }
};
