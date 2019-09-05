/**
 * Author: Felipe Abella
 * Date: 2015-02-10
 * License: CC0
 * Source: folkore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 *  edges such that the path from any leaf to the root contains at most log(n)
 *  light edges. 
 * Usage:
 *  heavylight_t hl{n}, hl.build()
 */
struct heavylight_t {
    int n;
    vector<vector<int>> adj = vector<vector<int>>(n);
    vector<int> parent = vector<int>(n);
    vector<int> depth = vector<int>(n);
    vector<int> sts = vector<int>(n);
    vector<int> path_of = vector<int>(n);
    vector<int> preorder;
    vector<int> invpreorder = vector<int>(n), endsubtree = vector<int>(n);
    struct path_t {
        int n;
        segtree_t<int> seg(n);
        void init() {
        seg = segtree_t(n);
        }
    };
    vector<path_t> paths = vector<path_t>(n);
    void init(int v, int p, int d) {
        invpreorder[v] = preorder.size();
        preorder.push_back(v);
        parent[v] = p;
        depth[v] = d;
        sts[v] = 1;
        for (int u : adj[v])
            if (u != p) {
                init(u, v, d + 1);
                sts[v] += sts[u];
            }
        endsubtree[v] = preorder.size() - 1;
    }
    void assign_paths(int v, int p, int path_of_v) {
        path_of[v] = path_of_v;
        paths[path_of[v]].n += 1;
        for (int u : adj[v])
            if (u != p)
                assign_paths(u, v, 2 * sts[u] >= sts[v] ? path_of_v : u);
    }
    void build() {
        init(0, -1, 0);
        assign_paths(0, -1, 0);
        for (int v = 0; v < n; ++v)
            if (path_of[v] == v)
                paths[v].init();
    }
    int pos_of(int v) { return depth[v] - depth[path_of[v]]; }
    segtree_t::node_t query(int v) { //TODO: Mudar a seg usada!
        segtree_t::node_t result;
        while (v != -1) {
            result = segtree_t::node_t(paths[path_of[v]].seg.query(0, pos_of(v)),
                                 result);
            v = parent[path_of[v]];
        }
        return result;
    }
};
