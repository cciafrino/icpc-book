/**
 * Author: Chris
 * Date: 2020-03-21
 * License: CC0
 * Description: Finds a minimum vertex-disjoint path cover in a dag.
 *  The size is the same as the number of vertices minus the size of a maximum matching.
 * Usage:       
 * Status: Tested
 */
#include "bipartite-matching.h"
vector<vector<int>> minPathCover(bipartite_matching& g, int N) {
    int how_many = int(g.adj.size()) - g.solve();
    vector<vector<int>> paths;
    for (int i = 0; i < N; ++i) 
        if (g.match[i + N] == -1) {
            vector<int> path = {i};
            int cur = i;
            while (g.match[cur] >= 0) {
                cur = g.match[cur] - N;
                path.push_back(cur);
            }
            paths.push_back(path);
        }
    return paths;
}
