#include<bits/stdc++.h>
using namespace std;

template<typename T, int N, int M>
struct Matrix : public array<array<T, M>, N> {
    Matrix(T diag = T()) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                (*this)[i][j] = (i == j ? diag : T());
            }
        }
    }
    Matrix(initializer_list<initializer_list<T>> lst) : Matrix() {
        int i = 0, j = 0;
        for (auto& v : lst) {
            for (auto x : v) (*this)[i][j++] = x;
            i++, j = 0;
        }
    }
    template<typename Op> Matrix& compose(const Matrix& rhs, Op&& op) {
        auto& lhs = *this;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                lhs[i][j] = op(lhs[i][j], rhs[i][j]);
        return *this;
    }
    Matrix& operator+=(const Matrix& rhs) { return compose(rhs, std::plus<T>()); }
    Matrix& operator-=(const Matrix& rhs) { return compose(rhs, std::minus<T>()); }
    Matrix operator+(const Matrix& rhs) const { return Matrix(*this) += rhs; }
    Matrix operator-(const Matrix& rhs) const { return Matrix(*this) -= rhs; }
    template<int K> Matrix<T, N, K> operator*(const Matrix<T, M, K>& rhs) const {
        const auto& lhs = *this;
        Matrix<T, N, K> res;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < K; ++j)
                for (int k = 0; k < M; ++k)
                    res[i][j] += lhs[i][k] * rhs[k][j];
        return res;
    }
    Matrix power(int64_t p) {
        Matrix res(1), A = *this;
        while (p) {
            if (p & 1) res = A * res;
            A *= A, p >>= 1;
        }
        return res;
    }
    friend Matrix operator*(const T& alpha, Matrix A) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < M; ++j)
                A[i][j] *= alpha;
        return A;
    }
};

template<typename T, int N>
struct Vector : public Matrix<T, N, 1> {
    using Base = Matrix<T, N, 1>;
    Vector() : Base() { }
    Vector(const Base& v) : Base(v) { }
    Vector(initializer_list<T> lst) : Base() {
        int i = 0;
        for (const auto& x : lst) (*this)[i++] = x;
    }
    T& operator[](int i) { return Base::operator[](i)[0]; }
    const T& operator[](int i) const { return Base::operator[](i)[0]; }
};

template<typename T, int N, int M>
struct Affine {
    Matrix<T, N, M> A;
    Vector<T, N> b;
    Affine(T value = T(0)) : A(value) { }
    Affine(const Matrix<T, N, M>& A, const Vector<T, N>& b) : A(A), b(b) { }
    Affine operator+=(const Affine& rhs) { A += rhs.A, b += rhs.B; }
    Affine operator-=(const Affine& rhs) { A -= rhs.A, b -= rhs.B; }
    Affine operator+(const Affine& rhs) const { return Affine(*this) += rhs; };
    Affine operator-(const Affine& rhs) const { return Affine(*this) -= rhs; };
    T* operator[](int i) { return A[i]; }
    const T* operator[](int i) const { return A[i]; }
    template<int K> Affine<T, N, K> operator*(const Affine<T, M, K>& rhs) const {
        return Affine<T, N, K>(A * rhs.A, A * rhs.b + b);
    }
    Vector<T, N> operator*(const Vector<T, M>& x) const {
        return A * x + b;
    }
};

template<typename T, int N>
T determinant(Matrix<T, N, N> A, int n) {
    T det = T(1);
    for (int x = 0; x < n; ++x) {
        int sel = -1;
        for (int i = x; i < n; ++i) {
            if (A[i][x] != T(0)) {
                sel = i;
                break;
            }
        }
        if (sel == -1) return T(0);
        if (sel != x) {
            swap(A[sel], A[x]);
            det *= T(-1);
        }
        det *= A[x][x];
        for (int i = 0; i < n; ++i) if (i != x) {
            T c = A[i][x] / A[x][x];
            for (int j = x; j < n; ++j) A[i][j] -= c * A[x][j];
        }
    }
    return det;
}
template<typename T, int N, int M>
struct GaussianElimination {
    using DomainType = Vector<T, M>;
    using CodomainType = Vector<T, N>;
    Matrix<T, N, M> A;
    Matrix<T, N, N> E;
    const int n, m;
    int pivot[M], rank = 0, nullity;
    // O(min(n, m)nm)
    GaussianElimination(const Matrix<T, N, M>& A_, int n, int m) : A(A_), E(1), n(n), m(m), nullity(m) {
        fill(begin(pivot), end(pivot), -1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            int sel = -1;
            for (int i = row; i < n; ++i) {
                if (abs(A[i][col]) > abs(A[sel][col])) {
                    sel = i;
                }
            }
            if (sel == -1) continue;
            if (sel != row) {
                swap(A[sel], A[row]);
                swap(E[sel], E[row]);
            }
            for (int i = 0; i < n; ++i) if (i != row) {
                T c = A[i][col] / A[row][col];
                for (int j = col; j < m; ++j) A[i][j] -= c * A[row][j];
                for (int j = 0; j < m; ++j) E[i][j] -= c * E[row][j];
            }
            pivot[col] = row++;
            ++rank, --nullity;
        }
    }
    // O(n^2 + m)
    pair<bool, DomainType> solve(CodomainType b, bool reduced = false) const {
        if (not reduced) b = E * b;
        DomainType x;
        for (int j = 0; j < m; ++j) {
            if (pivot[j] != -1) {
                x[j] = b[pivot[j]] / A[pivot[j]][j];
                b[pivot[j]] = T(0);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (b[i] != T(0)) return {false, x};
        }
        return {true, x};
    }
    // O(nullity * nm)
    vector<DomainType> kernel_basis() const {
        vector<DomainType> basis;
        DomainType e;
        for (int j = 0; j < m; ++j) if (pivot[j] == -1) {
            e[j] = T(1);
            DomainType y = solve(A * e, true).second;
            e[j] = T(0), y[j] = T(-1);
            basis.push_back(y);
        }
        return basis;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    //cin.exceptions(cin.failbit | cin.eofbit | cin.badbit);
    int N, M; cin >> N >> M;

    Matrix<double, 3, 3> A = {{3.0, 0.0, 2}, {2, 0.0, -2}, {0, 1, 1}};

    GaussianElimination gs(A, 3, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            cout << gs.E[i][j] << ' ';
        }
        cout << endl;
    }
}
