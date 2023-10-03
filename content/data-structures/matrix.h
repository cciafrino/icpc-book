/**
 * Author: Chris
 * Date: 2020
 * License: 
 * Source: Yosupo
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int> A(N, vector<int>(N));
 * Status: tested extensively
 */
template <typename T> struct Matrix : vector<vector<T>> {
	using vector<vector<T>>::vector;
	using vector<vector<T>>::size;
	int h() const { return int(size()); }
	int w() const { return int((*this)[0].size()); }
	Matrix operator*(const Matrix& r) const {
		assert(w() == r.h()); Matrix res(h(), vector<T>(r.w()));
		for(int i = 0; i < h(); ++i) for(int j = 0; j < r.w(); ++j)
			for (int k = 0; k < w(); ++k)
				res[i][j] += (*this)[i][k] * r[k][j];
		return res;
	}
	friend vector<T> operator*(const Matrix<T>& A, const vector<T>& b) {
		int N = int(A.size()), M = int(A[0].size());
		vector<T> y(N);
		for (int i = 0; i < N; ++i) 
			for (int j = 0; j < M; ++j) y[i] += A[i][j] * b[j];
		return y;
	}
	Matrix& operator*=(const Matrix& r){return *this= *this * r;}
	Matrix pow(int n) const {
		assert(h() == w()); assert(n >= 0);
		Matrix x = *this, r(h(), vector<T>(w()));
		for (int i = 0; i < h(); ++i) r[i][i] = T(1);
		while (n) { if (n & 1) r *= x; x *= x; n >>= 1; }
		return r;
	}
};

