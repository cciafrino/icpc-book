/*
 * Author: Chris
 * Source: usaco.guide
 *
 */
template<typename T> struct ST {
	int H, N; 
	T unit = 0;
	vector<T> data;
	vector<vector<T>> table;
	static constexpr int S = 31;
	ST(vector<T>& A) : H(S - __builtin_clz(int(A.size()) - 1) + 1), 
			N(1 << H), data(A), table(N, vector<T>(H)) {
			data.resize(1 << H); rec(H-1, 0, 1 << H);
	}
	T op(const T a, const T b) const { return a + b; }
	void rec(int nh, int a, int b) {
		if (nh < 0) return;
		int md = (a + b) / 2;
		T d = unit;
		for (int i = md - 1; i >= a; --i) {
			d = op(data[i], d);
			table[i][nh] = d;
		}
		d = unit;
		for (int i = md; i < b; ++i) {
			d = op(d, data[i]);
			table[i][nh] = d;
		}
		rec(nh - 1, a, md); rec(nh - 1, md, b);
	}
	T query(int a, int b) const {
		if (a == b) return data[a];
		int t = S - __builtin_clz(b ^ a);
		return op(table[a][t], table[b][t]);
	}
};
