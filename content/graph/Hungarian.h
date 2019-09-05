/**
 * Author: BenQ
 * Description: finds min cost to complete n jobs w/ m workers 
	* each worker is assigned to at most one job (n <= m)
 * Source: https://github.com/mpfeifer1/Kattis/blob/master/cordonbleu.cpp
 */

int HungarianMatch(const vector<vector<int>> &a) { // cost array, negative values are ok
    int n = a.size()-1, m = a[0].size()-1; // jobs 1..n, workers 1..m
    vector<int> u(n+1), v(m+1), p(m+1); // p[j] -> job picked by worker j
    for(int i = 1; i <= n; ++i) { // find alternating path with job i
        p[0] = i; int j0 = 0;
        vector<int> dist(m+1, MOD), pre(m+1,-1); // dist, previous vertex on shortest path
        vector<bool> done(m+1, false);
        do {
            done[j0] = true;
            int i0 = p[j0], j1; int delta = MOD;
            for(int j = 1; j <= m; ++j) if (!done[j]) {
                auto cur = a[i0][j]-u[i0]-v[j];
                if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
                if (dist[j] < delta) delta = dist[j], j1 = j;
            }
            for(int j = 0; j <= m; ++j) // just dijkstra with potentials
                if (done[j]) u[p[j]] += delta, v[j] -= delta;
                else dist[j] -= delta;
            j0 = j1;
        } while (p[j0]);
        do { // update values on alternating path
            int j1 = pre[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }
    return -v[0]; // min cost
}
