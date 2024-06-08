#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include<bits/stdc++.h>
using namespace std;

#include "../../content/graph/tarjan.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

	vector<vector<int>> adj(N);
	
	for (int i = 0; i < M; ++i) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
	}
	
	scc_t S(adj);

	vector<vector<int>> ccs; ccs.reserve(N);
	S.solve([&](const auto& v) {
		ccs.push_back(v);
	});
	
	cout << S.scc_num << '\n';
	reverse(ccs.begin(), ccs.end());
	for (int i = 0; i < int(ccs.size()); ++i) {
		cout << int(ccs[i].size());
		for (int v : ccs[i]) cout << ' ' << v;
		cout << '\n';
	}
}
