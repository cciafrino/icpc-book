/**
 * Author: Lukas Polacek
 * Date: 2009-10-30
 * License: CC0
 * Source: folklore/TopCoder
 * Description: Computes partial sums a[0] + a[1] + ... + a[pos - 1], and updates single elements a[i],
 * taking the difference between the old and new value.
 * Time: Both operations are $O(\log N)$.
 * Status: Stress-tested
 */
template<typename T> struct FT { // 8b7639
	vector<T> s;
	FT(int n) : s(n) {}
	FT(const vector<T>& A) : s(A) {
		const int N = int(s.size());
		for (int a = 0; a < N; ++a) {
			if ((a | (a + 1)) < N) s[a | (a + 1)] += s[a];
		}
	}
	void update(int pos, T dif) { // a[pos] += dif
		for (; pos < (int)s.size(); pos |= pos + 1) s[pos] += dif;
	}
	T query(int pos) { // sum of values in [0, pos)
		T res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(T sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= (int)s.size() && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};
