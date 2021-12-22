/**
 * Description: Examples of Segment Tree with Lazy update
 */

// query sum a[l, r)
// update range a[i] <- !a[i]
// update range a[i] <- 1
struct seg_node {
	int sz, lz; int64_t sum;
	seg_node() : sz(0), sum(0), lz(-1) {}
	seg_node(int64_t val) : sz(1), sum(val), lz(-1) {}
	void push(const seg_node& l, const seg_node& r) {
		if (lz == 2) {
			l.flip(lz); 
			r.flip(lz);
		} else if (lz != -1) {
			l.assign(lz);
			r.assign(lz);
		}
		lz = -1;
	}
	void merge(const seg_node& l, const seg_node& r) {
		sz = l.sz + r.sz;
		sum = l.sum + r.sum;
	}
	void assign(int val) {
		sum = sz * val;
		lz = val;
	}
	void flip(int val) {
		sum = sz - sum;
		if (lz == -1) lz = 2;
		else if (lz == 0) lz = 1;
		else if (lz == 1) lz = 0;
		else lz = -1;
	}
	int64_t get_sum() const { return sum; }
};

/*
// BE CAREFULL!! The first term will be a0 + d NOT a0
//	Range sum query - { 'n', 0, 0 }
//	Range add arithmetic progression update - { 'a', a0, d } 
//	Range set arithmetic progression update - { 's', a0, d } 
// T query(int v, int l, int r, int a, int b, NZ x) { //(A)
// if (a < l) x.a += (l-a) * x.r, a = l; // (B)
// if (x.type != id_z.type) // (D)
// if (lazy[v].type != id_z.type) // (G)
// tree[vR] = s(lazy[v], tree[vR], r - md, md - l); // (I)
// lazy[vR] = y(lazy[v], lazy[vR], md - l); // (K)
namespace range_sum_range_addAP_range_setAP{
	using T = int64_t;
	struct node{
		char type;
		T a, r;
	};
	const auto F = [](const T& a, const T& b) {
		return a + b;
	};
	const auto US = [](const node& lazy, const T& num, T len, T left = 0) {
		T v = ( (len + left + 1) * (len + left)/2 - (left + 1) * left/2 ) * lazy.r + len * lazy.a;
		if(lazy.type == 'a') v += num;
		return v;
	};
	const auto UY = [](const node& par, const node& ch, T left = 0) {
		T a = par.a + par.r * left;
		T r = par.r;
		if(par.type == 's') return node{ 's', a, r };
		a += ch.a;
		r += ch.r;
		if(ch.type == 'n') return node{ 'a', a, r };
		return node{ ch.type, a, r };
	};
}
*/
