/**
 * Author: BenQ
 * Description: Given array of (possibly negative) costs to complete 
    * each of $N$ jobs with each of $M$ workers $(N\le M)$, finds min cost to 
    * complete all jobs such that each worker is assigned to at most one job.
    * Basically just Dijkstra with potentials.
 * Source: 
 * Status: Tested
 * Time: $O(N^2 M)$
 */

int Hungarian(const vector<vector<int>>& a) { 
    int n = a.size()-1, m = a[0].size()-1; // jobs 1..n, workers 1..m
    vector<int> u(n+1), v(m+1); // potentials
    vector<int> p(m+1); // p[j] := job picked by worker j
    for(int i = 1; i <= n; ++i) { // find alternating path with job i
        p[0] = i; int j0 = 0; // add "dummy" worker 0
        vector<int> mindist(m+1, INT_MAX), pre(m+1, -1); 
        vector<bool> done(m+1, false);
        do { // dijkstra
            done[j0] = true; // fix mindist[j0], update dists from j0
            int i0 = p[j0], j1; int delta = INT_MAX;
            for(int j = 1; j <= m; ++j) if (!done[j]) { 
                int cur = a[i0][j]-u[i0]-v[j]; 
                if (mindist[j] > cur) {
                    mindist[j] = cur;
                    pre[j] = j0;
                }
                if (delta > mindist[j]) {
                    delta = mindist[j];
                    j1 = j;
                }
            }
            for(int j = 0; j <= m; ++j) { // subtract constant from all edges going 
                // from done to not done vertices, lowers all 
                // remaining dists by constant
                if (done[j]) u[p[j]] += delta, v[j] -= delta; 
                else mindist[j] -= delta; 
            }
            j0 = j1;
        } while (p[j0]); // Potentials adjusted so all edge weights 
        // are non-negative. Perfect matching has zero weight and
        // costs of augmenting paths do not change.
        while (j0) { // update alternating path
            int j1 = pre[j0];
            p[j0] = p[j1]; j0 = j1;
        } 
    }
    return -v[0];
}
