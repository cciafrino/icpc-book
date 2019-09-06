/**
 * Author: Chris
 * Date: 2015-02-10
 * License: CC0
 * Source: folkore
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 *  edges such that the path from any leaf to the root contains at most log(n)
 *  light edges. 
 * Status: Not tested
 */


struct heavy_light_t {
    constexpr int N = (int)1e8;
    int t;
    vector<int> parent, size, next, height;
    vector<int> preorder, invpreorder, postorder;
    vector<vector<int>> edges;
    heavy_light_t(int _n) : parent(n), size(n), next(n), height(n),
    in(n), invpreorder(n), postorder(n), edges(n) {}
    void dfs(int v) {
        size[v] = 1;
        for (int u : edges[v]) {
            height[u] = height[v] + 1;
            dfsOrder(u);
            size[v] += size[u];
            if (size[u] > size[edges[v][0]])
                swap(u, edges[v][0]);
        }
    }
    void dfsOrder(int v) {
        preorder[v] = t++;
        invpreorder[preorder[v]] = v;
        for (int u : edges[v]) {
            next[u] = (u == edges[v][0] ? next[v] : u);
            dfsOrder(u);
        }
        postorder[v] = t - 1;
    }
    int lca(int u, int v) {
        while(next[u] != next[v]) {
            if (height[next[u]] < height[next[v]]) swap(u, v);
            u = parent[next[u]];
        }
        if (height[u] > height[v]) swap(u, v);
        return u;
    }
};


