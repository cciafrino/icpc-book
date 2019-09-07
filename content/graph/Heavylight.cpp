/**
 * Author: BenQ
 * Date: 2015-02-10
 * License: CC0
 * Source: folkore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 *  edges such that the path from any leaf to the root contains at most log(n)
 *  light edges. 
 * Status: Not tested
 */

template<int SZ, bool VALUES_IN_EDGES> 
struct heavylight_t { 
    int N; vector<int> edges[SZ];
    int par[SZ], sz[SZ], depth[SZ];
    int root[SZ], pos[SZ];
    LazySegTree<lint> tree{SZ};
    void addEdge(int a, int b) { edges[a].push_back(b), edges[b].push_back(a); }
    void dfs_sz(int v = 1) {
        if (par[v]) edges[v].erase(find(edges[v].begin(), edges[v].end(),par[v]));
        sz[v] = 1;
        for(auto &u : edges[v]) {
            par[u] = v; depth[u] = depth[v]+1;
            dfs_sz(u); sz[v] += sz[u];
            if (sz[u] > sz[edges[v][0]]) swap(u, edges[v][0]);
        }
    }
    int t = 0;
    void dfs_hld(int v = 1) {
        pos[v] = t++;
        for(auto &u : edges[v]) {
            root[u] = (u == edges[v][0] ? root[v] : u);
            dfs_hld(u);
        }
    }
    void init(int _N) {
        N = _N; par[1] = depth[1] = 0; root[1] = 1; 
        dfs_sz(); dfs_hld();
    }
    template <class BinaryOperation>
    void processPath(int u, int v, BinaryOperation op) {
        for (; root[u] != root[v]; v = par[root[v]]) {
            if (depth[root[u]] > depth[root[v]]) swap(u, v);
            op(pos[root[v]], pos[v]);
        }
        if (depth[u] > depth[v]) swap(u, v);
        op(pos[u]+VALUES_IN_EDGES, pos[v]); 
    }
    void modifyPath(int u, int v, int val) { // add val to vertices/edges along path
        processPath(u, v, [this, &val](int l, int r) { tree.update(l, r, val); });
    }
    
    void modifySubtree(int v, int val) { // add val to vertices/edges in subtree
        tree.update(pos[v]+VALUES_IN_EDGES,pos[v]+sz[v]-1,val);
    }
    lint queryPath(int u, int v) { // query sum of path
        ll res = 0; processPath(u, v, [this, &res](int l, int r) { res += tree.query(l, r); });
        return res;
    }
};
