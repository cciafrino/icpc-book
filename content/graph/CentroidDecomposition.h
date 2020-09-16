/**
 * Author: Chris
 * Description: Divide and Conquer on Trees.
 * 
 */

struct centroid_t {
    int n;
    vector<vector<int>> edges; 
    vector<vector<int>> dist; // dist to all ancestors
    vector<bool> blocked; // processed centroid
    vector<int> sz, depth, parent; // centroid parent
    centroid_t(int _n) : n(_n), edges(n), blocked(n), sz(n), depth(n),
        parent(n), dist(32 - __builtin_clz(n), vector<int>(n)) {}
    void addEdge(int a, int b) {
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    void dfs_sz(int v, int p) { 
        sz[v] = 1;
        for (int u : edges[v]) {
            if (u == p || blocked[u]) continue;
            dfs_sz(u, v);
            sz[v] += sz[u];
        }
    }

    int find(int v, int p, int tsz) { // find a centroid
        for (int u : edges[v]) 
            if (!blocked[u] && u != p && 2*sz[u] > tsz) 
                return find(u, v, tsz);
        return v;
    }

    void dfs_dist(int v, int p, int layer, int d) {
        dist[layer][v] = d;
        for (int u : edges[v]) {
            if (blocked[u] || u == p) continue;
            dfs_dist(u, v, layer, d + 1);
        }
    }

    int solve(int v, int p) {
        // solve the problem for each subtree here xD   
    }

    int decompose(int v, int layer=0, int lst_x = -1) {
        dfs_sz(v, -1);
        int x = find(v, v, sz[v]);
        blocked[x] = true;
        depth[x] = layer;
        parent[x] = lst_x;
        dfs_dist(x, x, layer, 0);

        int res = solve(x, v); // solving for each subtree
        
        for (int u : edges[x]) {
            if (blocked[u]) continue;
            decompose(u, layer + 1, x);
        }
        return res;
    }
};

