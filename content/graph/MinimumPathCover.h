/**
 * Author: Chris
 * Date: 2020-03-21
 * License: CC0
 * Description: Finds a minimum vertex-disjoint path cover in a dag.
 *  The size is the same as the number of vertices minus the size of a maximum matching.
 * Usage:       
 * Status: Tested
 */
#include "MaxBipartiteMatching.h"
vector<vector<int>> minPathCover(BipartiteMatcher &g) {
    int how_many = g.edges.size() - g.maxMatching();
    vector<vector<int>> paths;
    for (int i = 0; i < g.edges.size(); ++i) 
        if (g.R[i] == -1) {
            vector<int> path = {i};
            int cur = i;
            while (g.L[cur] >= 0) {
                cur = g.L[cur];
                path.push_back(cur);
            }
            paths.push_back(path);
        }
    return paths;
}