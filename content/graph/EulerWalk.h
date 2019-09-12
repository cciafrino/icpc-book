/**
 * Author: BenQ
* Description: Eulerian undirected/directed path/cycle algorithm. Returns a list of nodes in the Eulerian path/cycle with src at both start and end, or
 *  empty list if no cycle/path exists. To get edge indices back, also put it->second in s (and then ret).
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */

template<int SZ, bool directed> struct Euler {
    int N, M = 0;
    vector<pair<int,int>> adj[SZ];
    vector<pair<int,int>>::iterator its[SZ];
    vector<bool> used;
    void addEdge(int a, int b) {
        if (directed) adj[a].push_back({b,M});
        else adj[a].push_back({b,M}), adj[b].push_back({a,M});
        used.push_back(0); M += 1;
    }
    vector<pair<int,int>> solve(int _N, int src = 1) {
        N = _N; 
        for(int i = 1; i <= N; ++i) its[i] = begin(adj[i]);
        vector<pair<pair<int,int>, int>> ret, s = {{{src,-1},-1}};
        while (!s.empty()) {
            int x = s.back().first.first;
            auto &it = its[x], end = adj[x].end();
            while (it != end && used[it->s]) it ++;
            if (it == end) { 
                if (ret.size() && ret.back().first.second != s.back().first.first) return {}; // path isn't valid
                ret.push_back(s.back()), s.pop_back(); 
            } else { s.push_back({{it->first,x},it->second}); used[it->second] = 1; }
        }
        if (ret.size() != M+1) return {}; // No eulerian cycles/paths.
        // else, non-cycle if ret.front() != ret.back()
        vector<pair<int,int>> ans; 
        for(auto &t : ret) ans.push_back({t.first.first,t.second});
        reverse(ans.begin(), ans.end()); return ans;
    }
};
