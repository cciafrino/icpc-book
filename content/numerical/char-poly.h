/**
 * Author: Chris
 * Date: 2020
 * Source: Yui
 * Description: Calculates the characteristic polynomial of a matrix. 
 * $\sum_{k=0}^n p(k) (-1)^{n-k}$
 * Time: $O(N^3)$ and div-free is $O(N^4)$
 * Status: stress-tested
 */
// det(x I + a)
template<class T> vector<T> char_poly(const vector<vector<T>>& a) {
	const int N = int(a.size()); auto b = a;
	for (int j = 0; j < N - 2; ++j) {
		for (int i = j + 1; i < N; ++i) {
			if (b[i][j]) {
				swap(b[j + 1], b[i]);
				for (int k = 0; k < N; ++k) swap(b[k][j + 1], b[k][i]);
				break;
			}
		}
		if (b[j + 1][j]) {
			const T r = 1 / b[j + 1][j];
			for (int i = j + 2; i < N; ++i) {
				const T s = r * b[i][j];
				for (int q = j; q < N; ++q) b[i][q] -= s * b[j + 1][q];
				for (int p = 0; p < N; ++p) b[p][j + 1] += s * b[p][i];
			}
		}
	}
	// fss[i] := det(x I_i + b[0..i][0..i])
	vector<vector<T>> fss(N + 1);
	fss[0] = {1};
	for (int i = 0; i < N; ++i) {
		fss[i + 1].assign(i + 2, 0);
		for (int k = 0; k <= i; ++k) fss[i + 1][k + 1] = fss[i][k];
		for (int k = 0; k <= i; ++k) fss[i + 1][k] += b[i][i] * fss[i][k];
		T q = 1;
		for (int j = i - 1; j >= 0; --j) {
			q *= -b[j + 1][j];
			const T s = q * b[j][i];
			for (int k = 0; k <= j; ++k) fss[i + 1][k] += s * fss[j][k];
		}
	}
	return fss[N];
}
// det(x I + a), division free
template<class T> vector<T> char_poly_div_free(const vector<vector<T>>& a) {
	const int N = int(a.size());
	vector<T> ps(N + 1, 0);
	ps[N] = 1;
	for (int h = N - 1; h >= 0; --h) {
		vector<vector<T>> sub(N, vector<T>(h + 1, 0));
		for (int i = N; i >= 1; --i) 
			sub[i - 1][h] += ps[i];
		for (int i = N - 1; i >= 1; --i) for (int u = 0; u <= h; ++u) {
			for (int v = 0; v < h; ++v) 
				sub[i - 1][v] -= sub[i][u] * a[u][v];
		}
		for (int i = N - 1; i >= 1; --i) for (int u = 0; u <= h; ++u) {
			ps[i] += sub[i][u] * a[u][h];
		}
	}
	return ps;
}
