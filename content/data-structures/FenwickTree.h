/**
 * Author: ?
 * Date: 
 * License: 
 * Source: BenQ + https://codeforces.com/blog/entry/64914
 * Description: $N$-D Fenwick Tree that supports range sum query with point update.
 * Usage: FT<int, 10, 10> tree; -> 2D BIT
 * Time: Both operations are $O((\log N)^D)$.
 */

template <class T, int ...Ns> struct FT {
	T val = 0;
	void update(T v) { val += v; }
	T query() { return val; }
};
template <class T, int N, int... Ns> struct FT<T, N, Ns...> {
	FT<T,Ns...> tree[N+1];
	template<typename... Args> void update(int pos, Args... args) {
		for (; pos <= N; pos += (pos&-pos)) tree[pos].update(args...);
	}
	template<typename... Args> T sum(int r, Args... args) {
		T res = 0; for (; r; r -= (r&-r)) 
			res += tree[r].query(args...); 
		return res;
	}
	template<typename... Args> T query(int l, int r, Args... 
		args) { return sum(r,args...)-sum(l-1,args...); }
}; 
