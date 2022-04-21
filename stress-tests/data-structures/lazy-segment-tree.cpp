#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
constexpr int inf = INT_MAX;
#include"../../content/data-structures/lazy-segtree.h"

namespace range_add_range_max { 
// query max a[l, r)
// update range a[i] <- v
// update range a[i] <- a[i] + v
template<typename T = int64_t> struct seg_node {
	T val, lz_add, lz_set;
	int sz;
	bool to_set;
	seg_node(T n = -inf) : val(n), lz_add(0), lz_set(0), sz(1), to_set(false) {}
	void push(seg_node& l, seg_node& r) {
		if (to_set) {
			l.assign(lz_set);
			r.assign(lz_set);
			lz_set = 0;
			to_set = false;
		}
		if (lz_add != 0) {
			l.add(lz_add);
			r.add(lz_add);
			lz_add = 0;
		} 
	}
	void merge(const seg_node& l, const seg_node& r) {
		sz = l.sz + r.sz;
		val = max(l.val, r.val);
	}
	void add(T v) {
		val += v;
		lz_add += v;
	}
	void assign(T v) {
		val = v;
		lz_add = 0;
		lz_set = v;
		to_set = true;
	}
	T get_max() const { return val; }
};
}

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
	segtree_range<range_add_range_max::seg_node<int>> seg(v);
	rep(i,0,N) rep(j,0,N) if (i <= j) {
		int ma = -inf;
		rep(k,i,j) ma = max(ma, v[k]);
		assert(ma == seg.query(i,j).get_max());
	}
	rep(it,0,1000000) {
		int i = ra() % (N+1), j = ra() % (N+1);
		if (i > j) swap(i, j);
		int x = (ra() % 10) - 5;

		int r = ra() % 100;
		if (r < 30) {
			::res = seg.query(i, j).get_max();
			int ma = -inf;
			rep(k,i,j) ma = max(ma, v[k]);
			// cout << ma << ' ' << ::res << endl;
			assert(ma == ::res);
		}
		else if (r < 70) {
			seg.update(i, j, &range_add_range_max::seg_node<int>::add, x);
			rep(k,i,j) v[k] += x;
		}
		else {
			seg.update(i, j, &range_add_range_max::seg_node<int>::assign, x);
			rep(k,i,j) v[k] = x;
		}
	}
	cout<<"Tests passed!"<<endl;
}
