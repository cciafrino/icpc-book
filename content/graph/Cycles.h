/**
 * Author: Tourist-Chris
 * Description: Cycle Detection (Detects a cycle in a directed or undirected graph.)
 * Time: O(V)
 * Source: https://github.com/dragonslayerx
 */

bool detectCycle(vector<vector<int>> &edges, bool undirected) {
    vector<int> seen(n, 0), parent(n), stack_t;
    for (int i = 0; i < edges.size(); ++i) {
        if (seen[i] == 2) continue;
        stack_t.push_back(i);
        while(!stack_t.empty()) {
            int u = stack_t.back();
            stack_t.pop_back();
            if (seen[u] == 1) seen[u] = 2;
            else {
                stack_t.push_back(u);
                seen[u] = 1;
                for (int w : edges[u]) {
                    if (seen[w] == 0) {
                        parent[w] = u;
                        stack_t.push_back(w);
                    }
                    else if (seen[w] == 1 && (!undirected || w != parent[u])) 
                        return true; 
                }
            }
        }
    }
}

