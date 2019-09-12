/**
 * Author: BenQ
* Description: Eulerian undirected/directed path/cycle algorithm. Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 *  empty list if no cycle/path exists. To get edge indices back, also put it->second in s (and then ret).
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */
template<int SZ, bool directed> 
struct EulerWalk {
    int N, M;
    vector<pair<int,int>> edges[SZ], circuit;
    int out[SZ], in[SZ], deg[SZ];
    vector<bool> used;
    bool bad;
    void clear() {
        for(int i = 1; i <= N; ++i) edges[i].clear();
        circuit.clear(); used.clear();
        for(int i = 1; i <= N; ++i) out[i] = in[i] = deg[i] = 0;
        N = M = bad = 0;
    }
    void dfs(int pre, int cur) {
        while (edges[cur].size()) {
            pair<int,int> x = edges[cur].back(); 
            edges[cur].pop_back();
            if (used[x.second]) continue; // edge is already part of path
            used[x.second] = 1; dfs(cur,x.first);
        }
        if (circuit.size() && circuit.back().first != cur) bad = 1;
        circuit.push_back({pre,cur}); // generate circuit in reverse order
    }

    void addEdge(int a, int b) {
        if (directed) {
            edges[a].push_back({b,M});
            out[a] += 1, in[b] += 1;
        } 
        else {
            edges[a].push_back({b, M});
            edges[b].push_back({a, M});
            deg[a] += 1, deg[b] += 1;
        }
        used.push_back(0); M += 1;
    }
    vector<int> walk(int _N) { // vertices are 1-indexed
        N = _N;
        int start = 1; 
        for(int i = 1; i <= N; ++i) 
            if (deg[i] || in[i] || out[i]) start = i;
        for(int i = 1; i <= N; ++i)  {
            if (directed) {
                if (out[i]-in[i] == 1) start = i;
            } else {
                if (deg[i]&1) start = i;
            }
        }
        dfs(-1,start);
        if (circuit.size() != M+1 || bad) return {}; // no sol
        vector<int> ret; 
        for(int i = circuit.size()-1; i >= 0; i--) 
            ret.push_back(circuit[i].second);
        return ret;
    }
};
