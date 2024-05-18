#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"
#include<bits/stdc++.h>
using namespace std;

#include "../../content/graph/general-matching.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;
	vector<vector<int>> adj(N);
	for (int i = 0; i < M; ++i) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	blossom_t B(adj);
	cout << B.run() << '\n';
	for (int i = 0; i < N; ++i) {
		if (i >= B.match[i]) continue;
		cout << i << ' ' << B.match[i] << '\n';
	}
}
