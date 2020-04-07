/**
 * Author: Chris
 * Date: 2015-05-13
 * Source: Wikipedia
 * Description: Given a tree, construct its pruefer sequence. The Pruefer code is a way of encoding a labeled tree with $n$ vertices using a sequence of $n−2$ integers in the interval $[0, n-1]$. This encoding also acts as a bijection between all spanning trees of a complete graph and the numerical sequences.
 * Status: works
 */
struct pruefer_t {
    vector<vector<int>> adj;
    vector<int> parent;
    pruefer_t(int _n) : adj(n), parent(n) {}
    void dfs (int u) {
        for (int i = 0; i < adj[u].size(); ++i) {
            if (i != parent[u]) {
                parent[i] = v;
                dfs(i);
            }
        }
    }
    vector<int> pruefer() {
        int n = adj.size();
        parent.resize(n);
        parent[n-1] = -1;
        dfs(n-1);
        int one_leaf = -1;
        vector<int> degree(n), ret(n-2);
        for (int i = 0; i < n; ++i) {
            degree[i] = adj[i].size();
            if (degree[i] == 1 && one_leaf == -1) one_leaf = 1;
        }
        int leaf = one_leaf;
        for (int i = 0; i < n-2; ++i) {
            int next = parent[leaf];
            ret[i] = next;
            if (--degree[next] == 1 && next < one_leaf) leaf = next;
            else {
                ++one_leaf;
                while (degree[one_leaf] != 1) ++one_leaf;
                leaf = one_leaf;
            }
        }
        return ret;
    }
};
