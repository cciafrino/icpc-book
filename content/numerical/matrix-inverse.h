/**
 * Author: Chris
 * Date: 2020
 * Description: 
 * Time: O(n^3)
 * Status: Slightly stress-tested with modnum and doubles
 */
#include"../matrix.h";
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

