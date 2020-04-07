/**
 * Author: Chris
 * Description: Divide and Conquer on Trees.
 * 
 */
struct centroid_t {
    vector<bool> seen;
    vector<int> sz, level, par_tree, closest;
    vector<vector<int>> edges, dist, parent;
    centroid_t(vector<vector<int>> &e, int n) : edges(e), seen(n), 
        sz(n), level(n), par_tree(n), closest(n, INT_MAX/2), 
        dist(n, vector<int>(20)), parent(n, vector<int>(20)) { 
            build(0, -1); }
    void dfs(int v, int p, int parc, int lvl) {
        sz[v] = 1;
        parent[v][lvl] = parc;
        dist[v][lvl] = 1 + dist[p][lvl];
        for (int u : edges[v]) {
            if (u == p || seen[u]) continue;
            dfs(u, v, parc, lvl);
            sz[v] += sz[u];
        }
    }
    int get_centroid(int v, int p, int tsz) {
        for (int u : edges[v]) 
            if (!seen[u] && u != p && sz[u] > tsz/2)
                return get_centroid(u, v, tsz);
        return v;
    }
    void build(int v, int p, int lvl = 0) {
        dfs(v, -1, p, lvl);
        int x = get_centroid(v, v, sz[v]);
        seen[x] = 1;
        par_tree[x] = p;
        level[x] = 1 + lvl;
        for (int u : edges[x]) 
            if (!seen[u]) build(u, x, 1 + lvl);
    }
};
