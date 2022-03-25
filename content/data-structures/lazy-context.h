/**
 * Author: Chris
 * Description: Examples of Segment Tree with Lazy update
 */

namespace range_flip_range_sum { //4a7f6d
// query sum a[l, r)
// update range a[i] <- !a[i]
// update range a[i] <- 1
struct seg_node {
	int sz, lz; int64_t sum;
	seg_node() : sz(1), sum(0), lz(-1) {}
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
}

namespace range_add_range_sum { // d9640e
// query sum a[l, r)
// update range a[i] <- v
// update range a[i] <- a[i] + v
template<typename T = int64_t> struct seg_node {
	T val, lz_add, lz_set;
	int sz;
	bool to_set;
	seg_node(T n = 0) : val(n), lz_add(0), lz_set(0), sz(1), to_set(0) {}
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
		val = l.val + r.val;
	}
	void add(T v) {
		val += v * sz;
		lz_add += v;
	}
	void assign(T v) {
		val = v * sz;
		lz_add = 0;
		lz_set = v;
		to_set = true;
	}
	T get_sum() const { return val; }
};
}

namespace range_add_linear_range_sum { // a922ef
// update range a[i] <- a[i] + b * (i - s) + c
// assuming b and c are non zero, be careful
// get sum a[l, r)
template<typename T = int64_t> struct seg_node {
	T sum, lzB, lzC;
	int sz, idx;
	seg_node(int id = 0, T v = 0, int s = 0, T b = 0, T c = 0) : 
		sum(v), lzB(b), lzC(c - s * b), idx(id), sz(1) {}
	void push(seg_node& l, seg_node& r) {
		l.add(lzB, lzC);
		r.add(lzB, lzC);
		lzB = lzC = 0;
	}
	void merge(const seg_node& l, const seg_node& r) {
		idx = min(l.idx, r.idx);
		sz = l.sz + r.sz;
		sum = l.sum + r.sum;
	}  
	T sum_idx(T n) const { return n * (n + 1) / 2; }
	void add(T b, T c) {
		sum += b * (sum_idx(idx + sz) - sum_idx(idx)) + sz * c;
		lzB += b;
		lzC += c;
	}
	T get_sum() const { return sum; }
};
}

namespace range_affine_range_sum { // 61a09f
// update range a[i] <- b * a[i] + c
// get sum a[l, r)
struct seg_node {
	int sz; i64 sum, lzB, lzC;
	seg_node() : sz(1), sum(0), lzB(1), lzC(0) {}
	seg_node(i64 v) : sz(1), sum(v), lzB(1), lzC(0) {}
	void push(seg_node& l, seg_node& r) {
		l.add(lzB, lzC);
		r.add(lzB, lzC);
		lzB = 1, lzC = 0;
	}
	void merge(const seg_node& l, const seg_node& r) {
		sz = l.sz + r.sz;
		sum = l.sum + r.sum;
	}
	void add(i64 b, i64 c) {
		sum = (b * sum + c * sz);
		lzB = (lzB * b);
		lzC = (lzC * b + c);
	}
	i64 get_sum() const { return sum; }
};
}

namespace range_chmin_chmax_point_query { // 8bab55
// update range a[i] <- min(a[i], b);
// update range a[i] <- max(a[i], b);
// get val a[i]
struct seg_node {
	int mn, mx;
	int lz0, lz1;
	seg_node() : mn(INT_MAX), mx(INT_MIN), lz0(INT_MAX), lz1(INT_MIN) {}
	void push(seg_node& l, seg_node& r) {
		l.minimize(lz0);
		l.maximize(lz1);
		r.minimize(lz0);
		r.maximize(lz1);
		lz0 = INT_MAX;
		lz1 = INT_MIN;
	}
	void merge(const seg_node& l, const seg_node& r) {
		mn = min(l.mn, r.mn);
		mx = max(l.mx, r.mx);
	}
	void minimize(int val) {
		mn = lz0 = min(lz0, val);
		mx = lz1 = min(lz0, lz1);
	}
	void maximize(int val) {
		mx = lz1 = max(lz1, val);
		mn = lz0 = max(lz0, lz1);
	}
	pair<int, int> get() const { return {mx, mn}; }
};
}

auto get_sum = [&](segtree_range<seg_node>& st, int a, int b) {
	return st.query(a, b, [&](auto l, auto r) -> i64 { return l + r; },
		[&]() -> i64 { return 0; }, &seg_node::get_sum);
};
