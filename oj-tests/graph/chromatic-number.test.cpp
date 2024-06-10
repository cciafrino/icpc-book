#define PROBLEM "https://judge.yosupo.jp/problem/chromatic_number"
#include<bits/stdc++.h>
using namespace std;

#include "../../content/graph/chromatic-number.h"

int main() {
	using namespace std;
	cin.tie(nullptr)->sync_with_stdio(false);
	int N, M; cin >> N >> M;

    vector<vector<int>> adj(N, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        int a, b; cin >> a >> b;
        adj[a][b] = adj[b][a] = 1;
    }

    cout << min_colors(N, adj) << '\n';
}
