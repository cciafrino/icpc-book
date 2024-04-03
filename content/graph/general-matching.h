/**
 * Author: Yui Hosaka
 * Description: Maximum Matching for general graphs 
 * (undirected and non bipartite) using Edmond's Blossom Algorithm.
 * Time: $O(EV^2)$ 
 * Status: tested on yosupo
 */
struct blossom_t { ///start-hash
	int N, M; vector<vector<int>> adj;
	vector<int> match, ts, ps; vector<array<int, 2>> fs;
	blossom_t(auto& G) : N(int(G.size())), M(0), adj(G), match(N,-1), ts(N,-1), ps(N,-1), fs(N,{-1,-1}) {}
	int root(int a) {
		return (ts[a] != M || !~ps[a]) ? a : (ps[a] = root(ps[a]));
	} ///end-hash
	void rematch(int a, int b) { ///start-hash
		const int w = match[a]; match[a] = b; auto [x, y] = fs[a];
		if (~w && match[w] == a) {
			if (~y) rematch(x, y), rematch(y, x);
			else match[w] = x, rematch(x, w);
		}
	} ///end-hash
	bool augment(int src) { ///start-hash
		vector<int> bfs = {src}; bfs.reserve(N);
		ts[src] = M; ps[src] = -1; fs[src] = {-1,-1};
		for (int z = 0; z < int(bfs.size()); ++z) {
			int cur = bfs[z];
			for (int nxt : adj[cur]) if (nxt != src) {
				if (match[nxt] == -1) {
					match[nxt] = cur; rematch(cur, nxt); return true;
				}
				if (ts[nxt] == M) {
					int a = root(cur), b = root(nxt), m = src;
					if (a == b) continue;
					while (a != src || b != src) {
						if (b != src) swap(a, b);
						if (fs[a][0]==cur&&fs[a][1]==nxt) { m = a; break; }
						fs[a] = {cur, nxt}; a = root(fs[match[a]][0]);
					}
					for (const int r : {root(cur), root(nxt)})
						for (int v = r; v != m; v = root(fs[match[v]][0]))
							ts[v] = M, ps[v] = m, bfs.push_back(v);
				} else if (ts[match[nxt]] != M) {
					fs[nxt] = {-1, -1}; ts[match[nxt]] = M;
					ps[match[nxt]] = nxt; fs[match[nxt]] = {cur, -1};
					bfs.push_back(match[nxt]);
				}
			}
		} return false;
	} ///end-hash
	int run() {
		for(int v = 0; v < N; ++v) if(!~match[v]) M += augment(v);
		return M;
	}
};
