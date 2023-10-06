/**
 * Author: Chris Ciafrino
 * License: CC0
 * Description: Finds all strongly connected components in a directed graph.
 * Time: O(E + V)
 * Status: tested on Yosupo
 * Usage: scc_t s(g); s.solve([\&](const vector<int>\& cc) {...}); 
 * visits all components in reverse topological order.
 */
struct scc_t {
    int n, t, scc_num;
    vector<vector<int>> adj;
    vector<int> low, id, stk, in_stk, cc_id;
    scc_t(const vector<vector<int>>& g) : n(int(g.size())), t(0), scc_num(0),
    adj(g), low(n,-1), id(n,-1), in_stk(n, false), cc_id(n) {}
    template<class F> void dfs(int cur, F f) {
        id[cur] = low[cur] = t++;
        stk.push_back(cur); in_stk[cur] = true;
        for (int nxt : adj[cur])
            if (id[nxt] == -1)
                dfs(nxt, f);low[cur] = min(low[cur], low[nxt]);
            else if (in_stk[nxt])
                low[cur] = min(low[cur], id[nxt]);
        if (low[cur] == id[cur]) {
            vector<int> cc; cc.reserve(stk.size());
            while (true) {
                int v = stk.back(); stk.pop_back();
                in_stk[v] = false;
                cc.push_back(v); cc_id[v] = scc_num;
                if (v == cur) break;
            } f(cc); scc_num++;
        }
    }
    template<class F> void solve(F f) {
        stk.reserve(n);
        for (int r = 0; r < n; ++r) if (id[r] == -1) dfs(r, f);
    }
};
