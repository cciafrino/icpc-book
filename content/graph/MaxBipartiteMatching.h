/**
 * Author: Lucian Bicsi, Chris
 * Date: 
 * License: 
 * Source:
 * Description: Fast Kuhn! Simple maximum cardinality bipartite matching algorithm. 
 * Fast and reliable maximum cardinality matching solver, better than 
 * DFSMatching and sometimes even faster than hopcroftKarp (Crazy heuristic huh). 
 * This implementation has got an $O(n^2)$ worst case on a sparse graph. Shuffling the
 * edges and vertices ordering might fix it. Good Luck.  $R[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched. $L[i]$ will be the match for vertex $i$ on the left side.
 * Time: $O(VE)$ worst case with shuffling I guess
 * Usage: 
 * Status: stress-tested
 */

struct BipartiteMatcher {
    vector<vector<int>> edges;
    vector<int> L, R, seen;
    BipartiteMatcher(int n, int m) : edges(n), L(n, -1), R(m, -1), seen(n) {}
    void addEdge(int a, int b) { edges[a].push_back(b); }  
    void improve() {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < edges.size(); ++i)
            shuffle(edges[i].begin(), edges[i].end(), rng);
    } 
    bool find(int v) {
        if (seen[v]) return false;
        seen[v] = true;
        for (int u : edges[v]) 
            if (R[u] == -1) {
                L[v] = u, R[u] = v;
                return true;
            }
        for (int u : edges[v]) 
            if (find(R[u])) {
                L[v] = u, R[u] = v;
                return true;
            }
        return false;
    }
    int maxMatching() {
        int ok = true;
        while (ok--) {
            fill(seen.begin(), seen.end(), 0);
            for (int i = 0; i < (int)L.size(); ++i)
                if (L[i] == -1) ok |= find(i);
        }
        int ret = 0;
        for (int i = 0; i < L.size(); ++i)
            ret += (L[i] != -1);
        return ret;
    }
};