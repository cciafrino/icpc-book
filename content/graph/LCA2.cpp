struct lca_t {
    int n, m, u, v, w;
    vector<int> parent, level, dist;
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> anc;
    lca_t(int _n) : n(_n), parent(n), level(n), dist(n), adj(n), anc(n, vector<int>(n)) {}
    void dfs(int u) {
        for (int i = 0; i < adj[u].size(); ++i) {
            int v = adj[u][i].first, w = adj[u][i].second;
            if (v != parent[u]) {
                parent[v] = u;
                level[v] = level[u] + 1;
                dist[v] = dist[u] + w;
                dfs(v);
            }
        }
    }
    void build() {
        parent[0] = level[0] = dist[0] = 0;
        dfs(0);
        for (int i = 0; i < n; ++i) anc[i][0] = parent[i];
        for (int j = 1; 1 << j < n; ++j)
            for (int i = 0; i < n; ++i)
                anc[i][j] = anc[anc[i][j - 1]][j - 1];
    }
    int query(int u, int v) {
        if (level[u] < level[v]) swap(u, v);
        int log;
        for (log = 1; 1 << log <= level[u]; log++);
        log--;
        for (int i = log; i >= 0; --i) {
            if (level[u] - (1 << i) >= level[v]) u = anc[u][i];
        }
        if (u == v) return u;
        for (int i = log; i >= 0; --i)
            if (anc[u][i] != anc[v][i]) {
                u = anc[u][i];
                v = anc[v][i];
            }
        return parent[u];
    }
};

///////

