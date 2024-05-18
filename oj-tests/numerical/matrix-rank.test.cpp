#define PROBLEM "https://judge.yosupo.jp/problem/matrix_rank"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;

#include "../../content/number-theory/modular-arithmetic.h"
#include "../../content/numerical/gaussian-elimination.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

	using num = modnum<998244353U>;

	if (!N || !M) {
		cout << 0 << '\n';
		exit(0);
	}

    Matrix<num> A(N, vector<num>(M));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            cin >> A[i][j].x;
        }
    }

    gaussian_elimination<num> ge(A);
    
	cout << ge.rank << '\n';
}
