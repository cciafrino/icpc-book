/**
 * Author: Johan Sannemo, Simon Lindholm, Chris
 * Date: 2016-12-15
 * License: CC0
 * Description: Finds a minimum vertex cover in a bipartite graph.
 *  The size is the same as the size of a maximum matching, and
 *  the complement is a maximum independent set.
 * Status: stress-tested
 */
#include "MaxBipartiteMatching.h"
vector<int> cover(BipartiteMatcher& B, int n, int m) {
    int res = B.maxMatching();
    vector<bool> lfound(n, true), seen(m);
    for(int &it : B.R) if (it != -1) lfound[it] = false;
    vector<int> q, cover;
    for(int i = 0; i < n; ++i) if (lfound[i]) q.push_back(i);
    for(int i = 0; i < q.size(); ++i) {
        int v = q[i];
        lfound[v] = true;
        for (int e : B.edges[v]) if (!seen[e] && B.R[e] != -1) {
            seen[e] = true;
            q.push_back(B.R[e]);
        }
    }
    for(int i = 0; i < n; ++i) if (!lfound[i]) cover.push_back(i);
    for(int i = 0; i < m; ++i) if (seen[i]) cover.push_back(n+i);
    assert(cover.size() == res);
    return cover;
}