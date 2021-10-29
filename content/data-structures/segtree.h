/**
 * Author: Chris Ciafrino
 * Date: 2021
 * License: CC0
 * Source: KACTL and Yui Hosaka
 * Description: Zero-indexed seg-tree. Bounds are inclusive to the left and exclusive to the right. 
 * Time: O(\log N)
 * Status: stress-tested
 */
template<class T, class F> struct segtree_t {
	const F f;
	const T id_t;
	vector<T> s; int n;
	segtree_t(int _n, const F _f, const T& _id) : f(_f), id_t(_id) {
		for (n = 1; n < _n; n *= 2) {}
		s.assign(2 * n, id_t);
	}
	T& at(int a) { return s[a + n]; }
	void build() {
		for (int a = n; --a;) s[a] = f(s[2 * a], s[2 * a + 1]);
	}
	void set(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	void add_left(int a, T val) {
		set(a, f(val, s[a + n]));
	}
	void add_right(int a, T val) {
		set(a, f(s[a + n], val));
	}
	T query(int b, int e) { // query [b, e)
		T ra = id_t, rb = id_t;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
	// min b s.t. pred(prod of [a, b)) (or n + 1 if no such b)
	//   0 <= a <= n
	//   assume pred(prod of [a, b)) is non-decreasing in b
	template<class P> int bsearch_r(int a, P pred) const {
		if (pred(id_t)) return a;
		if (a == n) return n + 1;
		T prod = id_t;
		for (a += n; ; a /= 2) {
			if (a & 1) {
				if (pred(f(prod, s[a]))) {
					while (a < n) {
						a *= 2;
						if (!pred(f(prod, s[a]))) {
							prod = f(prod, s[a++]);
						}
					}
					return (a - n + 1);
				}
				prod = f(prod, s[a++]);
				if (!(a & (a - 1))) return n + 1;
			}
		}
	}
	// max a s.t. pred(prod of [a, b)) (or -1 if no such a)
	//   0 <= b <= n
	//   assume pred(prod of [a, b)) is non-increasing in a
	template<class P> int bsearch_l(int b, P pred) const {
		if (pred(id_t)) return b;
		if (b == 0) return -1;
		T prod = id_t;
		for (b += n; ; b /= 2) {
			if ((b & 1) || b == 2) {
				if (pred(f(prod, s[b - 1]))) {
					while (b <= n) {
						b *= 2;
						if (!pred(f(prod, s[b - 1]))) {
							prod = f(prod, s[--b]);
						}
					}
					return (b - n - 1);
				}
				prod = f(prod, s[--b]);
				if (!(b & (b - 1))) return -1;
			}
		}
	}
};
