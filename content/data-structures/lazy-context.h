/**
 * Author: Chris
 * Description: Examples of Segment Tree with Lazy update
 */
template<typename T = int64_t> struct seg_node {///start-hash
	T val, lz_add, lz_set;
	int sz; bool to_set;
	seg_node(T n = 0) : val(n), lz_add(0), lz_set(0), sz(1), to_set(0) {}
	void push(seg_node& l, seg_node& r) {
		if (to_set) {
			l.assign(lz_set), r.assign(lz_set);
			lz_set = 0; to_set = false;
		}
		if (lz_add != 0) {
			l.add(lz_add), r.add(lz_add), lz_add = 0;
		}
	}
	void merge(const seg_node& l, const seg_node& r) {
		sz = l.sz + r.sz; val = l.val + r.val;
	}
	bool add(T v) {  // update range a[i] <- a[i] + v
		val += v * sz; lz_add += v; return true;
	}
	bool assign(T v) {   // update range a[i] <- v
		val = v * sz; lz_add = 0;
		lz_set = v; to_set = true; return true;
	}
	T get_sum() const { return val; } // sum a[l, r)
};///end-hash
// update range a[i] <- a[i] + b * (i - s) + c
// assuming b and c are non zero, be careful
// get sum a[l, r)
template<typename T = int64_t> struct seg_node {///start-hash
	T sum, lzB, lzC;
	int sz, idx;
	seg_node(int id = 0, T v = 0, int s = 0, T b = 0, T c = 0) : 
		sum(v), lzB(b), lzC(c - s * b), idx(id), sz(1) {}
	void push(seg_node& l, seg_node& r) {
		l.add(lzB, lzC), r.add(lzB, lzC);
		lzB = lzC = 0;
	}
	void merge(const seg_node& l, const seg_node& r) {
		idx = min(l.idx, r.idx), sz = l.sz + r.sz;
		sum = l.sum + r.sum;
	}
	T sum_idx(T n) const { return n * (n + 1) / 2; }
	bool add(T b, T c) {
		sum += b * (sum_idx(idx + sz) - sum_idx(idx)) + sz * c;
		lzB += b, lzC += c; return true;
	}
	T get_sum() const { return sum; }
};///end-hash
// update range a[i] <- b * a[i] + c
// get sum a[l, r)
struct seg_node {///start-hash
	int sz; i64 sum, lzB, lzC;
	seg_node() : sz(1), sum(0), lzB(1), lzC(0) {}
	seg_node(i64 v) : sz(1), sum(v), lzB(1), lzC(0) {}
	void push(seg_node& l, seg_node& r) {
		l.add(lzB, lzC), r.add(lzB, lzC);
		lzB = 1, lzC = 0;
	}
	void merge(const seg_node& l, const seg_node& r) {
		sz = l.sz + r.sz, sum = l.sum + r.sum;
	}
	bool add(i64 b, i64 c) {
		sum = (b * sum + c * sz), lzB = (lzB * b);
		lzC = (lzC * b + c); return true;
	}
	i64 get_sum() const { return sum; }
};///end-hash
// update range a[i] <- min(a[i], b);
// update range a[i] <- max(a[i], b);
// get val a[i]
struct seg_node {///start-hash
	int mn, mx;
	int lz0, lz1;
	seg_node() : mn(INT_MAX), mx(INT_MIN), lz0(INT_MAX), lz1(INT_MIN) {}
	void push(seg_node& l, seg_node& r) {
		l.minimize(lz0), l.maximize(lz1);
		r.minimize(lz0), r.maximize(lz1);
		lz0 = INT_MAX, lz1 = INT_MIN;
	}
	void merge(const seg_node& l, const seg_node& r) {
		mn = min(l.mn, r.mn), mx = max(l.mx, r.mx);
	}
	bool minimize(int val) {
		mn = lz0 = min(lz0, val);
		mx = lz1 = min(lz0, lz1); return true;
	}
	bool maximize(int val) {
		mx = lz1 = max(lz1, val);
		mn = lz0 = max(lz0, lz1); return true;
	}
	pair<int, int> get() const { return {mx, mn}; }
};///end-hash

template<typename T> struct lazy_t {///start-hash
	T a, b, c;
	lazy_t() : a(0), b(-INF), c(+INF) {}
	lazy_t(T a, T b, T c) : a(a), b(b), c(c) {}
	void add(T val) {
		a += val, b += val, c += val;
	}
	void upd_min(T val) {
		if (b > val) b = val;
		if (c > val) c = val;
	}
	void upd_max(T val) {
		if (b < val) b = val;
		if (c < val) c = val;
	}
};///end-hash
template<typename T = int64_t> struct seg_node {///start-hash
	T mi, mi2, ma, ma2, sum;
	T cnt_mi, cnt_ma, sz;
	lazy_t<T> lz;
	seg_node() : mi(INF), mi2(INF), ma(-INF), ma2(-INF), sum(0), cnt_mi(0), cnt_ma(0), sz(0), lz() {}
	seg_node(T n) : mi(n), mi2(INF), ma(n), ma2(-INF), sum(n), cnt_mi(1), cnt_ma(1), sz(1), lz() {}
	void push(seg_node& l, seg_node& r) {
		if (!l.can_apply(lz) || !r.can_apply(lz)) return;
		lz = lazy_t<T>();
	}
	bool can_apply(const lazy_t<T>& f) {
		if (!add(f.a) || !upd_max(f.b) || !upd_min(f.c)) return false;
		return true;
	} ///end-hash
	void merge(const seg_node& l, const seg_node& r) {///start-hash
		mi = min(l.mi, r.mi);
		mi2 = min((l.mi == mi) ? l.mi2 : l.mi, (r.mi == mi) ? r.mi2 : r.mi);
		cnt_mi = ((l.mi == mi) ? l.cnt_mi : 0) + ((r.mi == mi) ? r.cnt_mi : 0);
		ma = max(l.ma, r.ma);
		ma2 = max((l.ma == ma) ? l.ma2 : l.ma, (r.ma == ma) ? r.ma2 : r.ma);
		cnt_ma = ((l.ma == ma) ? l.cnt_ma : 0) + ((r.ma == ma) ? r.cnt_ma : 0);
		sum = l.sum + r.sum;
		sz = l.sz + r.sz;
	}///end-hash
	bool add(T v) { // a_i = a_i + v ///start-hash
		if (v) {
			mi += v;
			if (mi2 < INF) mi2 += v;
			ma += v;
			if (ma2 > -INF) ma2 += v;
			sum += sz * v;
			lz.add(v);
		}
		return true;
	}///end-hash
	bool upd_max(T v) { // a_i = max(a_i, v) ///start-hash   
		if (v > -INF) {
			if (v >= mi2) return false;
			else if (v > mi) {
				if (ma == mi) ma = v;
				if (ma2 == mi) ma2 = v;
				sum += cnt_mi * (v - mi);
				mi = v;
				lz.upd_max(v);
			}
		}
		return true;
	}///end-hash
	bool upd_min(T v) { // a_i = min(a_i, v) ///start-hash
		if (v < INF) {
			if (v <= ma2) return false;
			else if (v < ma) {
				if (ma == mi) mi = v;
				if (mi2 == ma) mi2 = v;
				sum -= cnt_ma * (ma - v);
				ma = v;
				lz.upd_min(v);
			}
		}
		return true;
	} ///end-hash
	T get_sum() const { return sum; } // sum a[l, r)
};
