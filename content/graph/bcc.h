/**
 * Author: Chris Ciafrino, LeticiaFCS
 * License: CC0
 * Description: Finds all biconnected components in an undirected graph.
 *  In a biconnected component there are at least two distinct paths 
 *  between any two nodes or the component is a bridge. 
 *  Note that a node can be in several components. $blockcut$ constructs 
 *  the block cut tree of given graph. The first nodes represents the 
 *  blocks, the others represents the articulation points.
 * Time: O(E + V)
 * Status: tested on Yosupo, $blockcut$ tested on Baekjoon - Blockade
 * Usage:
 *  int e_id = 0; vector<pair<int, int>> g(N);
 *  for (auto [a,b] : edges) {
 *    g[a].emplace_back(b, e_id);
 *    g[b].emplace_back(a, e_id++); }
 *  bcc_t b(g); b.solve([\&](const vector<int>\& edges_id) {...});
 */
struct bcc_t{
    using pii = pair<int, int>; // v, e_id
    int n, t;
    vector<vector<pii>> adj;
    vector<int> low, id, stk, is_art;
    bcc_t(const vector<vector<pii>> &g) : n(int(g.size())),
    t(0), adj(g), low(n,-1), id(n,-1), is_art(n) {}
    template<class F> void dfs(int cur, int e_par, F f){
        id[cur] = low[cur] = t++;
        stk.push_back(e_par); int c = 0;
        for (auto [nxt, e_id] : adj[cur]) {
            if (id[nxt] == -1) {
                dfs(nxt, e_id, f);
                low[cur] = min(low[cur], low[nxt]); c++;
                if (low[nxt] < id[cur]) continue;
                is_art[cur] = true;
                auto top = find(stk.rbegin(), stk.rend(), e_id);
                vector<int> cc(stk.rbegin(), next(top));
                f(cc); stk.resize(stk.size()-cc.size());
            }
            else if (e_id != e_par) {
                low[cur] = min(low[cur], id[nxt]);
                if (id[nxt] < id[cur]) stk.push_back(e_id);
            }
        } if(e_par == -1) is_art[cur] = (c > 1) ? true : false;
    }
    template<class F> void solve(F f) {
        stk.reserve(n);
        for(int r = 0; r < n; ++r) if(id[r] == -1) dfs(r,-1,f);
    }
    auto blockcut(const vector<pii> &edges){
        vector<vector<int>> cc; vector<int> cc_id(n);
        solve( [&](const vector<int> &c) {
            set<int> vc;
            for(int e : c){
                auto [a, b] = edges[e];
                cc_id[a] = cc_id[b] = int(cc.size());
                vc.insert(a); vc.insert(b);
            } cc.emplace_back(vc.begin(), vc.end());
        } );
        for(int a = 0; a < n; a++) if(is_art[a]) {
            cc_id[a] = int(cc.size()); cc.push_back({a});
        }
        int bcc_num = int(cc.size());
        vector<vector<int>> tree(bcc_num);
        for(int c = 0; c < bcc_num && 1<int(cc[c].size()); ++c)
            for(int a : cc[c]) if(is_art[a]) {
                tree[c].push_back(cc_id[a]);
                tree[cc_id[a]].push_back(c);
            }
        return make_tuple(cc_id, cc, tree);
    }
};
