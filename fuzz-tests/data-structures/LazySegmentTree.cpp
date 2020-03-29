#include "../utilities/template.h"

struct node {
	node *l, *r;
	int minv, sumv, lazy;
	int lx, rx;
};

void push(node *v) { 
	if(v != nullptr && v->lazy) { 
		v->minv += v->lazy;
		v->sumv += v->lazy * (v->rx - v->lx + 1);
		if(v->l) v->l->lazy += v->lazy;
		if(v->r) v->r->lazy += v->lazy;
		v->lazy = 0;
	}
}

void update(node *v, int lx, int rx, ll delta) {
	push(v);
	if(rx < v->lx || v->rx < lx) return;
	if(lx <= v->lx && v->rx <= rx) {
		v->lazy += delta; 
		push(v);
		return;
	}
	update(v->l, lx, rx, delta);
	update(v->r, lx, rx, delta);	
	push(v->l);
	v->minv = max(v->l->minv, v->r->minv);
	v->sumv = v->l->sumv + v->r->sumv;	
}

// without propagation, way faster in practice
void upd(node *v, int lx, int rx, int delta) {
	if(rx < v->lx || v->rx < lx) return;
	if(v->lx == v->rx) {
		v->lazy += delta; 
		v->minv += delta;
		v->sumv += delta;
		return;
	}
	upd(v->l, lx, rx, delta);
	upd(v->r, lx, rx, delta);	
	v->minv = max(v->l->minv, v->r->minv) + v->lazy;
	v->sumv = v->l->sumv + v->r->sumv + v->lazy * (v->rx - v->lx + 1);		
}
void setv(node *v, int lx, int rx, int delta) {
	if(rx < v->lx || v->rx < lx) return;
	if(v->lx == v->rx) {
		v->lazy = delta; 
		v->minv = delta;
		v->sumv += delta;
		return;
	}
	setv(v->l, lx, rx, delta);
	setv(v->r, lx, rx, delta);	
	v->minv = max(v->l->minv, v->r->minv) + v->lazy;
	v->sumv = v->l->sumv + v->r->sumv + v->lazy * (v->rx - v->lx + 1);		
}

int mquery(node *v, int lx, int rx) {
	push(v);
	if(rx < v->lx || v->rx < lx) return -1e9;
	if(lx <= v->lx && v->rx <= rx) return v->minv;
	return max(mquery(v->l, lx, rx), mquery(v->r, lx, rx));
}

node *build(int lx, int rx, vector<int>& ar) {
	node *v = new node();
	v->lx = lx; v->rx = rx;
	if(lx == rx) {
		v->lazy = 0;
		v->l = v->r = nullptr;
		v->minv = v->sumv = ar[lx];
	}
	else {
		v->l = build(lx, (lx + rx)/2, ar);
		v->r = build((lx + rx)/2 + 1, rx, ar);
		v->minv = max(v->l->minv, v->r->minv);
		v->sumv = v->l->sumv + v->r->sumv;
		v->lazy = 0;
	}
	return v;
}

template<typename T, typename Q>
struct segtree_t {
    int n;
    vector<T> tree;
    vector<Q> lazy, og;
    segtree_t(int N) : n(N), tree(4*N), lazy(4*N) {}
    segtree_t(const vector<Q> &other) : n(other.size()), og(other), 
    tree(4*n), lazy(4*n) { build(1, 0, n-1); }
    T f(const T &a, const T &b) { return max(a, b); }
    T build(int v, int l, int r) {
        lazy[v] = 0;
        if (l == r) return tree[v] = og[l];
        int m = l + (r - l)/2;
        return tree[v] = f(build(v<<1, l, m), build(v<<1|1, m+1, r));
    }
    void propagate(int v, int l, int r) {
        if (!lazy[v]) return; 
        int m = l + (r - l)/2;
        // tree[v<<1] += lazy[v] * (m - l + 1);
        // tree[v<<1|1] += lazy[v] * (r - (m + 1) + 1);
        tree[v<<1] += lazy[v];
        tree[v<<1|1] += lazy[v];
        for (int i = 0; i < 2; ++i) lazy[v<<1|i] += lazy[v];
        lazy[v] = 0;
    }
    T query(int a, int b) { return query(a, b, 1, 0, n-1); }
    T query(int a, int b, int v, int l, int r) {
        if (b < l || r < a) return -1e9;
        if (a <= l && r <= b) return tree[v];
        propagate(v,l, r);
        int m = l + (r - l)/2;
        return f(query(a, b, v<<1,l, m), query(a, b, v<<1|1, m+1, r));
    }
    T update(int a, int b, Q delta) { return update(a, b, delta, 1, 0, n-1); }
    T update(int a, int b, Q delta, int v, int l, int r) {
        if (b < l || r < a) return tree[v];
        if (a <= l && r <= b) {
            tree[v] += delta;
            lazy[v] += delta;
            return tree[v];
        }
        propagate(v,l, r);
        int m = l + (r - l)/2;
        return tree[v] = f(update(a, b, delta, v<<1, l, m),
            update(a, b, delta, v<<1|1, m+1, r));
    }
};

const int inf = 1e9;
struct Node {
	Node *l = 0, *r = 0;
	int lo, hi, mset = inf, madd = 0, val = -inf;
	Node(int lo,int hi):lo(lo),hi(hi){} // Large interval of -inf
	Node(vi& v, int lo, int hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			int mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid); r = new Node(v, mid, hi);
			val = max(l->val, r->val);
		}
		else val = v[lo];
	}
	int query(int L, int R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) mset = val = x, madd = 0;
		else {
			push(), l->set(L, R, x), r->set(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void add(int L, int R, int x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		}
		else {
			push(), l->add(L, R, x), r->add(L, R, x);
			val = max(l->val, r->val);
		}
	}
	void push() {
		if (!l) {
			int mid = lo + (hi - lo)/2;
			l = new Node(lo, mid); r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}
};

static unsigned R;
int ra() {
	R *= 791231;
	R += 1231;
	return (int)(R >> 1);
}

volatile int res;
int main() {

	int N = 10;
	vi v(N);
	iota(all(v), 0);
	random_shuffle(all(v), [](int x) { return ra() % x; });
	
	// auto start_kactl = chrono::high_resolution_clock::now();
	// Node* tr = new Node(v,0,N);
	auto start_dyn = chrono::high_resolution_clock::now();
	node* tree2 = build(0, N, v);
	// auto start_seg = chrono::high_resolution_clock::now();
	// segtree_t<int,int> tree(v);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		// assert(ma == tr->query(i,j));
		assert(ma == mquery(tree2, i, j-1));
		// assert(ma == tree.query(i, j-1));
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			// ::res = tr->query(i, j);
			::res = mquery(tree2, i, j-1);
			// ::res = tree.query(i,j-1);
			int ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			assert(ma == ::res);
		}
		else if (r < 70) {
			tr->add(i, j, x);
			// upd(tree2, i, j-1, x);
			update(tree2, i, j-1,x);
			// tree.update(i, j-1, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			// tr->set(i, j, x);
			// setv(tree2, i, j-1, x);
			// setx(tree2, i, j-1)
			// rep(k,i,j) v[k] = x;
		}
	}
	auto end_kactl = chrono::high_resolution_clock::now();
	double time_kactl = chrono::duration_cast<chrono::nanoseconds>(end_kactl - start_kactl).count(); 
	cout<<"Tests passed! " << time_kactl * 1e-9 <<endl;

	// auto end_dyn = chrono::high_resolution_clock::now();
	// double time_dyn = chrono::duration_cast<chrono::nanoseconds>(end_dyn - start_dyn).count(); 
	// cout<<"Tests passed! " << time_dyn * 1e-9 <<endl;

	// auto end_seg = chrono::high_resolution_clock::now();
	// double time_seg = chrono::duration_cast<chrono::nanoseconds>(end_seg - start_seg).count(); 
	// cout<<"Tests passed! " << time_seg * 1e-9 <<endl;
}

// Seg = 0.182484
// Dyn 标记永久化 = 0.142638
// Dyn Lazy Prop = 0.160497
// Kactl = 0.143635