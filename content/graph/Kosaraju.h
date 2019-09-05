/**
 * Author: Chris
 * Description: Find the strongly connected components of a digraph
 * 
 */

struct kosaraju_t {
    int time = 1, n;
    vector<vector<int>> adj, tree;
    vector<bool> vis;
    vector<int> color, s;
    kosaraju_t(int _n) : n(_n), adj(n), tree(n), color(n, -1), vis(n, false) {}
    void dfs(int u) {
        vis[u] = true;
        for (int v : adj[u]) if (!vis[v]) dfs(v);
        s.emplace_back(u);
    }
    int e;
    void dfs2(int u, int delta) {
        color[u] = delta;
        for (int v : tree[u])
            if (color[v] == -1) dfs2(v, delta);
    }
    void solve() {
        for (int i = 0; i < n; ++i)
            if (!vis[i]) dfs(i);
        e = 0;
        reverse(s.begin(), s.end());
        for (int i : s) {
            if (color[i] == -1) {
                ++e;
                dfs2(i,i);
            }
        }
    }
};
