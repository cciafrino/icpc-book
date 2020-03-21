/**
 * Author: Chris
 * Date: 2020-03-21
 * License: CC0
 * Description: Finds a minimum edge cover in a bipartite graph.
 *  The size is the same as the number of vertices minus the size of a maximum matching.
 * The mark vector represents who the vertices of set $B$ has an edge to.
 * Usage: vector<int> mark(n+m, -1);
          auto cover = minEdgeCover(g, mark);
 * Status: Tested
 */
#pragma once

#include "MaxBipartiteMatching.h"

vector<pair<int,int>> minEdgeCover(BipartiteMatcher &g, vector<int> &mark) {
    int maxMatching = g.maxMatching();
    vector<pair<int,int>> cover;
    for (int i = 0; i < g.L.size(); ++i) {
        if (g.L[i] >= 0) cover.push_back({i, g.L[i]});
        else if (g.edges[i].size()) cover.push_back({i, g.edges[i][0]});
    }
    for (int i = 0; i < g.R.size(); ++i) 
        if (g.R[i] == -1 && mark[i] >= 0) 
            cover.push_back({mark[i], i});
    return cover;
}