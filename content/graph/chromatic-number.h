/**
 * Author: Chris
 * Date: 2020-01-23
 * License: 
 * Source: maroonrk && http://www.wisdom.weizmann.ac.il/~dinuri/courses/11-BoundaryPNP/L01.pdf
 * Description: Compute the chromatic number of a graph. Minimum number of colors needed to paint the graph in a way s.t. if two vertices share an edge, they must have distinct colors.
 * Time: $O(N 2^N)$
 * Status: Tested on AtCoder - Close Group
 */
template<class T> int min_colors(int N, const T& gr) {
    vector<int> adj(N);
    for (int a = 0; a < N; ++a) {
        for (int b = a + 1; b < N; ++b) {
            if (!gr[a][b]) continue;
            adj[a] |= (1 << b);
            adj[b] |= (1 << a);
        }
    }
    static vector<unsigned> dp(1 << N), buf(1 << N), w(1 << N);
    for (int mask = 0; mask < (1 << N); ++mask) {
        bool ok = true;
        for (int i = 0; i < N; ++i) if (mask & 1 << i) {
            if (adj[i] & mask) ok = false;
        }
        if (ok) dp[mask]++;
        buf[mask] = 1;
        w[mask] = __builtin_popcount(mask) % 2 == N % 2 ? 1 : -1;
    }
    for (int i = 0; i < N; ++i) {
        for (int mask = 0; mask < (1 << N); ++mask) if (!(mask & 1 << i)) {
            dp[mask^(1 << i)] += dp[mask];
        }
    }
    for (int colors = 1; colors <= N; ++colors) {
        unsigned S = 0;
        for (int mask = 0; mask < (1 << N); ++mask) {
            S += (buf[mask] *= dp[mask]) * w[mask];
        }
        if (S) return colors;
    }
    assert(false);
}
