/**
 * Author: Celio Passos
 * Date: 
 * License: 
 * Source: https://github.com/celiopassos/competitive-programming
 * Description: 
 * Status: tested on yosupo
 * Usage:
 * Time: $\mathcal{O}(\min{(N, M)}NM)$
 */
#include"../data-structures/matrix.h"
template<typename T> struct gaussian_elimination {
	int N, M;
	Matrix<T> A, E;
	vector<int> pivot;
	int rank, nullity, sgn;
	gaussian_elimination(const Matrix<T>& A_) : A(A_) {
		N = A.size(), M = A[0].size();
		E = Matrix<T>(N, vector<T>(N));
		for (int i = 0; i < N; ++i) E[i][i] = 1;
		rank = 0, nullity = M, sgn = 0;
		pivot.assign(M, -1);
		for (int col = 0, row = 0; col < M && row < N; ++col) {
			int sel = -1;
			for (int i = row; i < N; ++i) {
				if (A[i][col] != 0) {
					sel = i;
					break;
				}
			}
			if (sel == -1) continue;
			if (sel != row) {
				sgn += 1;
				swap(A[sel], A[row]);
				swap(E[sel], E[row]);
			}
			for (int i = 0; i < N; ++i) {
				if (i == row) continue;
				T c = A[i][col] / A[row][col];
				for (int j = col; j < M; ++j)
					A[i][j] -= c * A[row][j];
				for (int j = 0; j < N; ++j)
					E[i][j] -= c * E[row][j];
			}
			pivot[col] = row++;
			++rank, --nullity;
		}
	}
	pair<bool, vector<T>> solve(vector<T> b, bool reduced = false) const {
		if (reduced == false) b = E * b;
		vector<T> x(M);
		for (int j = 0; j < M; ++j) {
			if (pivot[j] == -1) continue;
			x[j] = b[pivot[j]] / A[pivot[j]][j];
			b[pivot[j]] = 0;
		}
		for (int i = 0; i < N; ++i) 
			if (b[i] != 0) return {false, x};
		return {true, x};
	}
	vector<vector<T>> kernel_basis() const {
		vector<vector<T>> basis;
		vector<T> e(M);
		for (int j = 0; j < M; ++j) {
			if (pivot[j] != -1) continue;
			e[j] = 1;
			auto y = solve(A * e, true).second;
			e[j] = 0, y[j] = -1;
			basis.push_back(y);
		}
		return basis;
	}
	Matrix<T> inverse() const {
		assert(N == M); assert(rank == N);
		Matrix<T> res(N, vector<T>(N));
		vector<T> e(N);
		for (int i = 0; i < N; ++i) {
			e[i] = 1;
			auto x = solve(e).second;
			for (int j = 0; j < N; ++j)
				res[j][i] = x[j];
			e[i] = 0;
		}
		return res;
	}
};

