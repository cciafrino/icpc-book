/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#pragma once

#include "DFSMatching.h"
#include "MCBM.h"

vector<int> cover(vector<vector<int>>& g, int n, int m, MCBM &B) {
    int res = B.match();
    vector<bool> lfound(n, true), seen(m);
    for(int &it : B.R) if (it != -1) lfound[it] = false;
    vector<int> q, cover;
    for(int i = 0; i < n; ++i) if (lfound[i]) q.push_back(i);
    while (!q.empty()) {
        int i = q.back(); q.pop_back();
        lfound[i] = true;
        for(int e : g[i]) if (!seen[e] && B.R[e] != -1) {
            seen[e] = true;
            q.push_back(B.R[e]);
        }
    }
    for(int i = 0; i < n; ++i) if (!lfound[i]) cover.push_back(i);
    for(int i = 0; i < m; ++i) if (seen[i]) cover.push_back(n+i);
    assert(cover.size() == res);
    return cover;
}