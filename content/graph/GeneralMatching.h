/**
 * Author: Koosaga
 * Description: Maximum Matching for general graphs (undirected and non bipartite) using Edmond's Blossom Algorithm.
 * Time: $O(EV^2)$ 
 */

struct blossom_t {
    int t, n; // 1-based indexing!!
    vector<vector<int>> edges;
    vector<int> seen, parent, og, match, aux, Q;
    blossom_t(int _n) : n(_n), edges(n+1), seen(n+1), 
        parent(n+1), og(n+1), match(n+1), aux(n+10), t(0) {}
    void addEdge(int u, int v) {
        edges[u].push_back(v); 
        edges[v].push_back(u);
    }
    void augment(int u, int v) {
        int pv = v, nv; // flip states of edges on u-v path
        do {
            pv = parent[v]; nv = match[pv];
            match[v] = pv; match[pv] = v;
            v = nv;
        } while(u != pv);
    }
    int lca(int v, int w) { // find LCA in O(dist)
        ++t;
        while (1) {
            if (v) {
                if (aux[v] == t) return v; aux[v] = t;
                v = og[parent[match[v]]];
            }
            swap(v, w);
        }
    }
    void blossom(int v, int w, int a) {
        while (og[v] != a) {
            parent[v] = w; w = match[v]; // go other way around cycle
            if(seen[w] == 1) Q.push_back(w), seen[w] = 0;
            og[v] = og[w] = a;      // merge into supernode
            v = parent[w];
        }
    }
    bool bfs(int u) {
        for (int i = 1; i <= n; ++i) seen[i] = -1, og[i] = i;
        Q = vector<int>(); Q.push_back(u); seen[u] = 0;
        for(int i = 0; i < Q.size(); ++i) {
            int v = Q[i]; 
            for(auto &x : edges[v]) {
                if (seen[x] == -1) {
                    parent[x] = v; seen[x] = 1;
                    if (!match[x]) return augment(u, x), true;
                    Q.push_back(match[x]); seen[match[x]] = 0;
                } else if (seen[x] == 0 && og[v] != og[x]) {
                    int a = lca(og[v], og[x]);
                    blossom(x, v, a); blossom(v, x, a);
                }
            }
        }
        return false;
    }
    int solve() {
        int ans = 0; // find random matching (not necessary, 
        vector<int> V(n-1); iota(V.begin(), V.end(), 1);// constant improvement)
        shuffle(V.begin(), V.end(), mt19937(0x94949));
        for(auto &x : V) if(!match[x]) 
            for(auto &y : edges[x]) if (!match[y]) {
                match[x] = y, match[y] = x;
                ++ans; break;
            }
        for (int i = 1; i <= n; ++i) 
            if (!match[i] && bfs(i)) ++ans;
        return ans;
    }
};