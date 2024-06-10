#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include<bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
#include "../../content/graph/heavylight.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, Q; cin >> N >> Q;

	vector<vector<int>> adj(N);
	for (int i = 1; i < N; ++i) {
		int a; cin >> a;
		adj[a].push_back(i);
		adj[i].push_back(a);
	}

	hld_t<false> hld(adj);

	while (Q--) {
		int a, b; cin >> a >> b;
		cout << hld.lca(a, b) << '\n';
	}
}
