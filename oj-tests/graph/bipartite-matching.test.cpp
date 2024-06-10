#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include<bits/stdc++.h>
using namespace std;

#include "../../content/graph/bipartite-matching.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	int L, R, M; cin >> L >> R >> M;
	bm_t B(L, R);
	for (int i = 0; i < M; ++i) {
		int a, b; cin >> a >> b;
		B.add_edge(a, b);
	}
	
	mt19937 rng(48);
	for (auto& g : B.adj) {
		shuffle(g.begin(), g.end(), rng);
	}

	cout << B.solve() << '\n';
	for (int i = 0; i < L; ++i) {
		if (B.match[i] == -1) continue;
		cout << i << ' ' << B.match[i] - L << '\n';
	}
}
