/**
 * Author: Chris
 * Date: 2020
 * License: 
 * Source: Yosupo
 * Description: Calculates determinant of a matrix. Destroys the matrix. Tested with modnum and doubles.
 * Status: stress-tested (weakly)
 * Time: $O(N^3)$
 */
#include<../Matrix.h>;
template<typename T> T det(Matrix<T> a) { 
    assert(a.h() == a.w());
    int n = a.h();
    bool flip = false;
    for (int x = 0; x < n; x++) {
        int my = -1;
        for (int y = x; y < n; y++) {
            if (T(a[y][x]) != 0) {
                my = y;
                break;
            }
        }
        if (my == -1) return 0;
        if (x != my) {
            swap(a[x], a[my]);
            if ((x - my) & 1) flip = !flip;
        }
        for (int y = x + 1; y < n; y++) {
            if (T(a[y][x]) == 0) continue;
            auto freq = a[y][x] / a[x][x];
            for (int k = x; k < n; k++) a[y][k] -= freq * a[x][k];
        }
    }
    T det = (!flip ? 1 : -1);
    for (int i = 0; i < n; i++) det *= a[i][i];
    return det;
}
