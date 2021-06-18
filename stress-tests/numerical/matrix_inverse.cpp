#include<bits/stdc++.h>
using namespace std;
#include "../../content/number-theory/modular-arithmetic.h"
template <typename T> struct Matrix : vector<vector<T>> {
    using vector<vector<T>>::vector;
    using vector<vector<T>>::size;
    int h() const { return int(size()); }
    int w() const { return int((*this)[0].size()); }
    Matrix operator*(const Matrix& r) const {
        assert(w() == r.h());
        Matrix res(h(), vector<T>(r.w()));
        for (int i = 0; i < h(); ++i) {
            for (int j = 0; j < r.w(); ++j) {
                for (int k = 0; k < w(); ++k) {
                    res[i][j] += (*this)[i][k] * r[k][j];
                }
            }
        }
        return res;
    }
    Matrix& operator*=(const Matrix& r) { return *this = *this * r; }
    Matrix pow(int n) const {
        assert(h() == w());
        Matrix x = *this, r(h(), vector<T>(w()));
        for (int i = 0; i < h(); ++i) r[i][i] = T(1);
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};

template<class T> vector<T> solve_linear(Matrix<T> a, vector<T> b) {
    int h = a.h(), w = a.w();
    int rank = 0, nullity = w;
    vector<int> idxs;
    for (int x = 0; x < w; ++x) {
        /* TODO: uncomment if it's not a finite field
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

template<typename T> Matrix<T> inverse(Matrix<T> a) {
    assert(a.h() == a.w());
    int n = a.h();
    Matrix<T> b(n, vector<T>(n));
    for (int i = 0; i < n; ++i) b[i][i] = 1;
    for (int x = 0; x < n; ++x) {
        int my = -1;
        for (int y = x; y < n; ++y) {
            if (T(a[y][x]) != 0) {
                my = y;
                break;
            }
        }
        if (my == -1) return {};
        if (x != my) {
            swap(a[x], a[my]);
            swap(b[x], b[my]);
        }
        auto freq = a[x][x];
        for (int j = 0; j < n; ++j) {
            a[x][j] /= freq;
            b[x][j] /= freq;
        }
        for (int y = 0; y < n; ++y) {
            if (x == y) continue;
            if (T(a[y][x]) == 0) continue;
            freq = a[y][x];
            for (int k = 0; k < n; k++) a[y][k] -= freq * a[x][k];
            for (int k = 0; k < n; k++) b[y][k] -= freq * b[x][k];
        }
    }
    return b;
}

template<class T> T calc_det(Matrix<T> a) {
    assert(a.h() == a.w());
    int n = a.h();
    bool flip = false;
    for (int x = 0; x < n; x++) {
        int my = -1;
        for (int y = x; y < n; y++) {
            if (int(a[y][x])) {
                my = y;
                break;
            }
        }
        if (my == -1) return 0;
        if (x != my) {
            swap(a[x], a[my]);
            if ((x - my) % 2) flip = !flip;
        }
        for (int y = x + 1; y < n; y++) {
            if (!int(a[y][x])) continue;
            auto freq = a[y][x] / a[x][x];
            for (int k = x; k < n; k++) a[y][k] -= freq * a[x][k];
        }
    }
    T det = (!flip ? 1 : -1);
    for (int i = 0; i < n; i++) {
        det *= a[i][i];
    }
    return det;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
    using num = modnum<998244353>;

    Matrix<num> A = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    auto res = calc_det(A);
    //auto res2 = inverse(A);
    //for (int i = 0; i < 3; ++i) {
        //for (int j = 0; j < 3; ++j) {
            //cout << res2[i][j] << ' ';
        //}
        //cout << endl;
    //}
    //
    cout << res << endl;
}
