/**
 * Author: Lucian Bicsi, Chris, Daniel Rutschmann
 * Date: 
 * License: 
 * Source:
 * Description: Fast Kuhn! Simple maximum cardinality bipartite matching algorithm. 
 * Better than hopcroftKarp in practice(Crazy heuristic huh). 
 * Worst case is $O(VE)$ on an hairy tree. Shuffling the
 * edges and vertices ordering should break some worst-case inputs.
 * Time: $\Omega(VE)$ 
 * Usage: 
 * Status: stress-tested
 */
struct Matching {
    int N, M, T;
    vector<vector<int>> edges;
    vector<int> match, seen;
    Matching(int a, int b) : N(a), M(a + b), edges(M), 
            match(M, -1), seen(M, -1), T(0) {}
    void addEdge(int a, int b) {
        assert(0 <= a && a < N && b + N < M && N <= b + N);
        edges[a].push_back(b + N);
    }
    void shuffle_edges() { // useful to break some hairy tests
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < int(edges.size()); ++i)
            shuffle(edges[i].begin(), edges[i].end(), rng);
    } 
    bool dfs(int v) {
        if (seen[v] == T) return false;
        seen[v] = T;
        for (int u : edges[v]) 
            if (match[u] == -1) {
                match[u] = v, match[v] = u;
                return true;
            }
        for (int u : edges[v]) 
            if (dfs(match[u])) {
                match[u] = v, match[v] = u;
                return true;
            }
        return false;
    }
    int solve() {
        int res = 0;
        while (true) {
            int cur = 0; ++T;
            for (int i = 0; i < N; ++i) 
                if (match[i] == -1) cur += dfs(i);
            if (cur == 0) break;
            else res += cur;
        }
        return res;
    }
};
