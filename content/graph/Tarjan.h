/**
 * Author: Chris
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Usage: cnt[i] holds the
 * component index of a node (a component only has edges to
 * components with lower index). ncnt will contain the
 * number of components.
 */
struct tarjan_t { 
    int n, ncnt = 0, time = 0;
    vector<vector<int>> edges;
    vector<int> preorder, cnt, order, stack_t;
    tarjan_t(int n): n(n), edges(n), preorder(n), cnt(n,-1) {}
    int dfs(int u) { 
        int reach = preorder[u] = ++time, v;
        stack_t.push_back(u);
        for (int v : edges[u]) if (cnt[v] == -1) 
            reach = min(reach, preorder[v]?:dfs(v));
        if (reach == preorder[u]) { 
            do {
                v = stack_t.back();
                stack_t.pop_back();
                order.push_back(v);
                cnt[v] = ncnt;
            } while (v != u);
            ++ncnt;
        }
        return preorder[u] = reach;
    }
    void scc() {
        time = ncnt = 0;
        for (int i = 0; i < (int)edges.size(); ++i)
            if (cnt[i] == -1) dfs(i);
    }
};

