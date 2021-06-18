/**
 * Author: Chris
 * Date: 
 * License: 
 * Source: 
 * Description: 
 * Status: tested
 * Usage:
 * Time: 
 */
#include"../data-structures/matrix.h"
// TODO: kernel basis
template<class T> vector<T> solve_linear(Matrix<T> a, vector<T> b) {
    int h = a.h(), w = a.w();
    int rank = 0, nullity = w;
    vector<int> idxs;
    for (int x = 0; x < w; ++x) {
        /*  // uncomment if it's not a finite field
            T eps = 1e-5;
            for (int y = rank + 1; y < h; ++y) {
                T d = hypot(a[rank][x], a[y][x]);
                if (abs(d) <= eps) continue;
                T c = a[rank][x] / d, s = a[y][x] / d;
                auto rot = [&](T& u, T& v) {
                    tie(u, v) = make_pair(c * u + s * v, c * v - s * u);
                };
                rot(b[rank], b[y]);
                for (int k = x; k < w; k++) rot(a[rank][k], a[y][k]);
            }
            if (a[rank][x] <= eps) continue;
        */
        int my = -1;
        for (int y = rank; y < h; ++y) {
            if (int(a[y][x])) {
                my = y; break;
            }
        }
        if (my == -1) continue;
        if (rank != my) swap(a[rank], a[my]);
        swap(b[rank], b[my]);
        for (int y = rank + 1; y < h; ++y) {
            if (!int(a[y][x])) continue;
            auto freq = a[y][x] / a[rank][x];
            for (int k = x; k < w; ++k) a[y][x] -= freq * a[rank][k];
            b[y] -= freq * b[rank];
        }
        rank++;
        --nullity;
        idxs.push_back(x);
        if (rank == h) break;
    }
    vector<T> v(w);
    for (int y = rank - 1; y >= 0; y--) {
        int f = idxs[y];
        v[f] = b[y];
        for (int x = f + 1; x < w; x++) {
            v[f] -= a[y][x] * v[x];
        }
        v[f] /= a[y][f];
    }
    return v;
}
