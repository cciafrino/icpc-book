/**
 * Author: Chris
* Description: Data structure for computing lowest common
 * ancestors in a tree (with 0 as root). C should be an adjacency list of the tree,
 * either directed or undirected.
 * Can also find the distance between two nodes.
 */

struct lca_t {
    int logn, preorderpos;
    vector<int> invpreorder, height;
    vector<vector<int>> edges;
    vector<vector<int>> parent;
    lca_t(int n, vector<vector<int>> &adj) : height(n), invpreorder(n) { /// start-hash
        parent = vector<vector<int>>(n, vector<int>(n+1, 0));
        edges = adj;
        while((1 << (logn+1)) <= n) ++logn;
        dfs(0, 0, 0);
        
    } /// end-hash
    void dfs(int v, int p, int h) { /// start-hash
        invpreorder[v] = preorderpos++;
        height[v] = h;
        parent[v][0] = p;
        for (int l = 1; l <= logn; ++l)
            parent[v][l] = parent[parent[v][l-1]][l-1];
        for (int u : edges[v]) {
            if (u == p) continue;
            dfs(u, v, h+1);
        }
    }/// end-hash
    int climb(int v, int dist) { /// start-hash
        for (int l = 0; l <= logn; ++l)
            if (dist & (1<<l)) v = parent[v][l];
        return v;
    }/// end-hash
    int query(int a, int b) { /// start-hash
        if (height[a] < height[b]) swap(a, b);
        a = climb(a, height[a] - height[b]);
        if (a == b) return a;
        for (int l = logn; l >= 0; --l) 
            if (parent[a][l] != parent[b][l]) {
                a = parent[a][l];
                b = parent[b][l];
            }
        return parent[a][0];
    } /// end-hash
    int dist(int a, int b) {
        return height[a] + height[b] - 2 * height[query(a,b)];
    }
    bool is_parent(int p, int v) { /// start-hash
        if (height[p] > height[v]) return false;
        return p == climb(v, height[v] - height[p]);
    }/// end-hash
};
