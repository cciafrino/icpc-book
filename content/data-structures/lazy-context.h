/**
 * Author: Chris
 * Description: Examples of Segment Tree with Lazy update
 */
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
	void assign(int val) { // range a[i] <- val
		sum = sz * val;
		lz = val;
	}
	void flip(int val) {  // range a[i] <- !a[i]
		sum = sz - sum;
		if (lz == -1) lz = 2;
		else if (lz == 0) lz = 1;
		else if (lz == 1) lz = 0;
		else lz = -1;
	}
	int64_t get_sum() const { return sum; } // sum a[l, r)
};

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
	void add(T v) {  // update range a[i] <- a[i] + v
		val += v * sz;
		lz_add += v;
	}
	void assign(T v) {   // update range a[i] <- v
		val = v * sz;
		lz_add = 0;
		lz_set = v;
		to_set = true;
	}
	T get_sum() const { return val; } // sum a[l, r)
};

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
