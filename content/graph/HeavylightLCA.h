/**
 * Author: TFG
 * Date: 2019
 * License: CC0
 * Source: https://github.com/tfg50/Competitive-Programming/blob/master/Biblioteca/Graph/HLD.cpp
 * Status: Tested on LCA SPOJ
 * Description: LCA using Heavylight Decomposition.
 * Usage:
 *  unique_ptr<heavylight> HLD;
 *  HLD.reset(new heavylight(n));
 * Time: dfs = $O(N)$, query = $O(\log(N))$
 */

struct heavylight {
    int t, n;
    vector<vector<int>> edges;
    vector<int> preorder, parent, h, sz;
    vector<int> postorder, nxt, invpreorder;
    heavylight(int _n) : n(_n), preorder(n), h(n), parent(n), sz(n), nxt(n), invpreorder(n), postorder(n) { }
    void addEdge(int u, int v) {
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    void dfs(int v, int p) {
        sz[v] = 1;
        parent[v] = p;
        for (int i = 0; i < (int)edges[v].size(); ++i) {
            int &u = edges[v][i];
            if (u == p) {
                swap(u, edges[v].back());
                edges[v].pop_back(); i--;
            }
            else {
                h[u] = 1 + h[v];
                dfs(u, v);
                sz[v] += sz[u];
                if (sz[u] > sz[edges[v][0]]) swap(edges[v][0], u);
            }
        }
    }
    void hld(int v) {
        preoder[v] = t++;
        invpreorder[preorder[v]] = v;
        for (int u : edges[v]) {
            nxt[u] = (u == edges[v][0] ? nxt[v] : u);
            hld(u);
        }
        postorder[v] = t;
    }
    void make_root(int v) {
        t = 0; parent[v] = v;
        h[v] = 0; dfs(v, v);
        nxt[v] = v; hld(v);
    }
    bool in_subtree(int u, int v) {
        // is v in the same subtree that u?
        return preorder[u] <= preoder[v] && preorder[v] < postorder[u];
    }
    int lca(int u, int v) {
        while(!in_subtree(nxt[u], v)) u = parent[nxt[u]];
        while(!in_subtree(nxt[v], u)) v = parent[nxt[v]];
        return preorder[u] < preorder[v] ? u : v;
    }
    vector<pair<int,int>> getPathtoAncestor(int v, int p) {
        // returns ranges [l, r) that the path has
        vector<pair<int,int>> ret;
        assert(in_subtree(p, v));
        while(nxt[v] != nxt[p]) {
            ret.emplace_back(preorder[nxt[v]], preorder[v] + 1);
            v = parent[nxt[v]];
        } // this includes the ancestor
        ret.emplace_back(preorder[p], preorder[v] + 1);
        return ret;
    }
    
};

