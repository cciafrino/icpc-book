/**
 * Author: Chris
 * Description: Divide and Conquer on Trees.
 * 
 */

struct centroid_t {
    vector<bool> mark;
    vector<int> subtree, level, par_tree, closest;
    vector<vector<int>> edges, dist, parent;
    centroid_t(vector<vector<int>> &e, int n) : mark(n, 0), subtree(n), level(n), par_tree(n), closest(n, INT_MAX/2), dist(n, vector<int>(20)), parent(n, vector<int>(20)) { edges = e; build(0, -1); update(0); }
    void dfs(int v, int par, int parc, int lvl) {
        subtree[v] = 1;
        parent[v][lvl] = parc;
        dist[v][lvl] = 1 + dist[par][lvl];
        for (int u : edges[v]) {
            if (u == par) continue;
            if (!mark[u]) {
                dfs(u, v, parc, lvl);
                subtree[v] += subtree[u];
            }
        }
    }
    int get_centroid(int v, int par, int sz) {
        for (int u : edges[v]) 
            if (!mark[u] && u != par && subtree[u] > sz/2)
                return get_centroid(u, v, sz);
        return v;
    }
    void build(int v, int p, int lvl = 0) {
        dfs(v, v, p, lvl);
        int x = get_centroid(v, v, subtree[v]);
        mark[x] = 1;
        par_tree[x] = p;
        level[x] = 1 + lvl;
        for (int u : edges[x]) 
            if (!mark[u]) build(u, x, 1 + lvl);
    }
};
