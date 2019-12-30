/**
 * Author: BenQ
* Description: Eulerian undirected/directed path/cycle algorithm. Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 *  empty list if no cycle/path exists. To get edge indices back, also put it->second in s (and then ret).
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */
template<bool directed> 
struct EulerWalk {
    int N, M;
    vector<vector<pair<int,int>>> edges;
    vector<pair<int,int>> circuit;
    vector<int> out, in, deg, seen;
    bool bad;
    EulerWalk(int n) : N(0), M(0), edges(n+1), out(n+1), in(n+1), deg(n+1), bad(0) {} 
    void dfs(int pre, int cur) {
        while (edges[cur].size()) {
            pair<int,int> x = edges[cur].back(); 
            edges[cur].pop_back();
            if (seen[x.second]) continue; // edge is already part of path
            seen[x.second] = 1; dfs(cur,x.first);
        }
        if (circuit.size() && circuit.back().first != cur) bad = 1;
        circuit.push_back({pre,cur}); // generate circuit in reverse order
    }
    void addEdge(int a, int b) {
        if (directed) {
            edges[a].push_back({b,M});
            out[a]++, in[b]++;
        } 
        else {
            edges[a].push_back({b, M});
            edges[b].push_back({a, M});
            deg[a]++, deg[b]++;
        }
        seen.push_back(0); M++;
    }
    vector<int> walk(int n) { // vertices are 1-indexed
        int start = 1; 
        for(int i = 1; i <= n; ++i) 
            if (deg[i] || in[i] || out[i]) start = i;
        for(int i = 1; i <= n; ++i)  {
            if (directed) 
                if (out[i]-in[i] == 1) start = i;
            else if (deg[i]&1) start = i;
        }
        dfs(-1,start);
        if (circuit.size() != M+1 || bad) return {}; // no sol
        vector<int> ret; 
        for(int i = circuit.size()-1; i >= 0; --i) 
            ret.push_back(circuit[i].second);
        return ret;
    }
};