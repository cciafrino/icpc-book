/**
 * Author: Chris
 * Description: Builds dfs tree. Find cut vertices and bridges.
 * Usage: Call solve right after build the graph
 */
struct tree_t {
    int timer, n;
    vector<vector<int>> edges;
    vector<pair<int,int>> bridges;
    vector<int> depth, mindepth, parent, st, cut, children;
    tree_t(int n) : n(n), timer(0), edges(n), parent(n,-1),
        mindepth(n,-1), depth(n,-1), st(n,-1) {}
    void addEdge(int a, int b) { 
        edges[a].push_back(b); edges[b].push_back(a);
    }
    void dfs(int v) {
        st[v] = timer;
        mindepth[v] = depth[v];
        for (int u : edges[v]) {
            if (u == parent[v]) continue;
            if (st[u] == timer) {
                mindepth[v] = min(mindepth[v], depth[u]);
                continue;
            }
            depth[u] = 1 + depth[v];
            parent[u] = v;
            dfs(u);
            mindepth[v] = min(mindepth[v], mindepth[u]);
        }
    }
    vector<pair<int,int>> find_bridges() {
        for (int i = 0; i < n; ++i) 
            if (parent[i] != -1 && mindepth[i] == depth[i]) 
                bridges.push_back({parent[i], i});
        return bridges;
    }
    vector<bool> find_cut() {
        cut.resize(n), children.resize(n);
        for (int i = 0; i < n; ++i) 
            if (parent[i] != -1 && mindepth[i] >= depth[parent[i]]) 
                cut[parent[i]] = 1;
        for (int i = 0; i < n; ++i) 
            if (parent[i] != -1) child[parent[i]]++;
        for (int i = 0; i < n; ++i) 
            if (parent[i] == -1 && child[i] < 2) cut[i] = 0;
        return cut;
    }
    void solve() {
        for (int i = 0; i < n; ++i) 
            if (depth[i] == -1) {
                depth[i] = 0; parent[i] = -1;
                ++timer;
                dfs(i);
            }
    }
};
