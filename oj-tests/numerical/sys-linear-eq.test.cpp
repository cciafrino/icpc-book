#define PROBLEM "https://judge.yosupo.jp/problem/system_of_linear_equations"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/number-theory/modular-arithmetic.h"
#include "../../content/numerical/gaussian-elimination.h"

int main() {
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

	using num = modnum<998244353U>;

	Matrix<num> A(N, vector<num>(M));

	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			cin >> A[i][j].x;
		}
	}

	vector<num> b(N); for (auto& v : b) cin >> v.x;

	gaussian_elimination<num> ge(A);

	auto sol = ge.solve(b);

	if (sol.first) {
		cout << ge.nullity << '\n';

		for (int i = 0; i < M; ++i) cout << sol.second[i].x << ' ';
		cout << '\n';

		auto basis = ge.kernel_basis();
		for (int i = 0; i < ge.nullity; ++i) {
			for (int j = 0; j < M; ++j) {
				cout << basis[i][j].x << ' ';
			}
			cout << '\n';
		}
	} else cout << "-1\n";
}
