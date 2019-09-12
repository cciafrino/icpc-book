/**
 * Author: Chris 
 * Date: 2019
 * License: CC0
 * Source: Adamant tutorial
 * Status: Tested on LCA SPOJ
 * Description: LCA using Heavylight Decomposition.
 * Usage:
 *  unique_ptr<heavylight> HLD;
 *  HLD.reset(new heavylight(edges));
 *  HLD->build(root); HLD->lca(a, b); // [a, b]
 * Time: Build = $O(N)$, Query = $O(\log(N))$
 */

struct heavylight {
    int t;
    vector<vector<int>> edges;
    vector<int> in, parent, h, size;
    heavylight(vector<vector<int>> &e) : in(e.size()), h(e.size()), parent(e.size()), size(e.size()) {edges = e;}
    void build(int v, int p = -1, int f = 1) {
        in[v] = t++; size[v] = 1;
        for (int &u : edges[v]) {
            if (u == p) continue;
            parent[u] = v;
            h[u] = (u == edges[v][0] ? h[v] : u);
            build(u, v, f);
            size[v] += size[u];
            if (size[u] > size[edges[v][0]]) swap(u, edges[v][0]);
        }
        if (p * f == -1) {
            t = 0;
            h[v] = v;
            build(v, -1, 0);
        }
    }
    int lca(int a, int b) {
        if (in[a] < in[b]) swap(a, b);
        return h[a] == h[b] ? b : lca(parent[h[a]], b);
    }
};
