/**
 * Author: Chris
 * Date: 
 * License: CC0 
 * Source: 
 * Description: Segment Tree with Lazy update (half-open interval). 
 * Status: 
 * Time: $O(\lg(N)*Q)$
 */
template<class T> struct segtree_range {
	int N;
	vector<T> ts;
	segtree_range() {}
	explicit segtree_range(int N_) : N(1 << __lg(2*N_-1)) {
		ts.resize(2*N); build();
	}
	template<class Q> explicit segtree_range(const vector<Q>& A){
		const int N_ = int(A.size());
		N = (1 << __lg(2*N_-1));
		ts.resize(2*N);
		for (int i = 0; i < N_; ++i) at(i) = T(A[i]);
		build();
	}
	T& at(int a) { return ts[a + N]; }
	void build() { for (int a = N; --a; ) merge(a); }
	inline void push(int a) { ts[a].push(ts[2*a], ts[2*a+1]); }
	inline void merge(int a) { ts[a].merge(ts[2*a], ts[2*a+1]); }
	template<class Op, class E, class F, class... Args>
	auto query(int v, int l, int r, int a, int b, Op op, E e, F f, Args&&... args) {
		if (l >= b || r <= a) return e();
		if (l >= a && r <= b) {
			return (ts[v].*f)(args...);
		}
		int m = (l + r)/2;
		push(v);
		return op(query(2*v, l, m, a, b, op, args...), query(2*v+1, m, r, a, b, op, args...));
	}
	template<class Op, class E, class F, class... Args>
	auto query(int a, int b, Op op, E e, F f, Args&&... args) {
		return query(1, 0, N, a, b, op, e, f, args...);
	}
	T query(int v, int l, int r, int a, int b) {
		if (l >= b || r <= a) return T();
		if (l >= a && r <= b) return ts[v];
		int m = (l + r)/2;
		push(v); T t;
		t.merge(query(2*v, l, m, a, b), query(2*v+1, m, r, a, b));
		return t;
	}
	T query(int a, int b) { return query(1, 0, N, a, b); }
	template<class F, class... Args> void update(int v, int l, int r, int a, int b, F f, Args&&... args) {
		if (l >= b || r <= a) return;
		if (l >= a && r <= b && (ts[v].*f)(args...)) return;
		int m = (l + r)/2;
		push(v);
		update(2*v, l, m, a, b, f, args...);
		update(2*v+1, m, r, a, b, f, args...);
		merge(v);
	}
	template<class F, class... Args>
	void update(int a, int b, F f, Args&&... args) {
		update(1, 0, N, a, b, f, args...);
	}
	template<class F, class... Args> int find_first(int v, int l, int r, int a, int b, F f, Args&&... args) {
		if (l >= b || r <= a || !(ts[v].*f)(args...)) return -1;
		if (l + 1 == r) return l;
		int m = (l + r)/2;
		push(v);
		int cur = find_first(2*v, l, m, a, b, f, args...);
		if (cur == -1) cur = find_first(2*v+1, m, r, a, b, f, args...);
		return cur;
	}
	template<class F, class... Args> 
	int find_first(int a, int b, F f, Args&&... args) {
		return find_first(1, 0, N, a, b, f, args...);
	}
};
