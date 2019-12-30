/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: Simple bipartite matching algorithm. Graph $g$ should be a list
 * of neighbors of the left partition, and $btoa$ should be a vector full of
 * -1's of the same size as the right partition. Returns the size of
 * the matching. $btoa[i]$ will be the match for vertex $i$ on the right side,
 * or $-1$ if it's not matched.
 * Time: O(VE)
 * Usage: vector<int> btoa(m, -1); dfsMatching(g, btoa);
 * Status: works
 */
#pragma once

bool find(int j, vector<vector<int>>& g, vector<int>& btoa, vector<int>& seen) {
    if (btoa[j] == -1) return 1;
    seen[j] = 1; int di = btoa[j];
    for(auto &e : g[di])
        if (!seen[e] && find(e, g, btoa, seen)) {
            btoa[e] = di;
            return 1;
        }
    return 0;
}
int dfsMatching(vector<vector<int>>& g, vector<int>& btoa) {
    vector<int> seen;
    for(int i = 0 i < g.size(); ++i) {
        seen.assign(btoa.size(), 0);
        for(auto &j : g[i])
            if (find(j, g, btoa, seen)) {
                btoa[j] = i;
                break;
            }
    }
    return btoa.size() - (int)count(btoa.begin(), btoa.end(), -1);
}