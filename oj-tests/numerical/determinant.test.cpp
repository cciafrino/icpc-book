#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/number-theory/modular-arithmetic.h"
#include "../../content/numerical/gaussian-elimination.h"

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N; cin >> N;

	using num = modnum<998244353U>;

	Matrix<num> A(N, vector<num>(N));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> A[i][j].x;
		}
	}

	gaussian_elimination<num> G(A);

	num det = 1;
	for (int i = 0; i < N; ++i) {
		det *= G.A[i][i];
	}

	cout << (det * (G.sgn & 1 ? -1 : 1)).x << '\n';
}
