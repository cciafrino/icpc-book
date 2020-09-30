/**
 * Author: Chris
 * Date: 2020
 * License: 
 * Source: Yosupo
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int> A(N, vector<int>(N));
 * Status: tested
 */
template <typename T> struct Matrix : vector<vector<T>> {
    using vector<vector<T>>::vector;
    using vector<vector<T>>::size;
    int h() const { return int(size()); }
    int w() const { return int((*this)[0].size()); }
    Matrix operator*(const Matrix& r) const {
        assert(w() == r.h());
        Matrix res(h(), vector<T>(r.w()));
        for (int i = 0; i < h(); i++) {
            for (int j = 0; j < r.w(); j++) {
                for (int k = 0; k < w(); k++) {
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
        for (int i = 0; i < h(); i++) r[i][i] = T(1);
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
};
