/**
 * Author: Chris
 * Date: 2020
 * License: 
 * Source: Yosupo
 * Description: Calculates determinant of a matrix. Destroys the matrix. Tested with modnum and doubles.
 * Status: stress-tested (weakly)
 * Time: $O(N^3)$
 */
#include<../matrix.h>;

// ** use T() if it's not a finite field
template<class T> T calc_det(Matrix<T> a) {
    assert(a.h() == a.w());
    int n = a.h();
    bool flip = false;
    for (int x = 0; x < n; x++) {
        int my = -1;
        for (int y = x; y < n; y++) {
            if (int(a[y][x])) { // **
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
            if (!int(a[y][x])) continue; // **
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
