/**
 * Author: Célio Passos
 * Date: 2022
 * License: 
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. N must be a power of 2.
   Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 */
inline int nxt_pow2(int s) { return 1 << (s > 1 ? 32 - __builtin_clz(s-1) : 0); }
template<typename dbl> struct cplx {
    dbl x, y;
    cplx(dbl x_ = 0, dbl y_ = 0) : x(x_), y(y_) { }
    friend cplx operator+(cplx a, cplx b) { return cplx(a.x + b.x, a.y + b.y); }
    friend cplx operator-(cplx a, cplx b) { return cplx(a.x - b.x, a.y - b.y); }
    friend cplx operator*(cplx a, cplx b) { return cplx(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
    friend cplx conj(cplx a) { return cplx(a.x, -a.y); }
    friend cplx inv(cplx a) { dbl n = (a.x*a.x+a.y*a.y); return cplx(a.x/n,-a.y/n); }
};

template<typename T>
struct root_of_unity {};

template<typename dbl> struct root_of_unity<cplx<dbl>> {
    static cplx<dbl> f(int k) {
        static const dbl PI = acos(-1);
        dbl a = 2*PI/k;
        return cplx<dbl>(cos(a),sin(a));
    }
};

constexpr int MOD = 998244353;
template<> struct root_of_unity<modnum<MOD>> {
    static constexpr modnum<MOD> g = modnum<MOD>(3);
    static modnum<MOD> f(int k) {
        assert((MOD-1)%k == 0);
        return g.pow((MOD-1)/k);
    }
};

template<typename T>
vector<T> fft(vector<T> p, bool inverse) { // df3434
    int N = p.size();
    vector<T> q(N);
    for (int i = 0; i < N; ++i) {
        int rev = 0;
        for (int b = 1; b < N; b <<= 1) {
            rev = (rev << 1) | !!(i & b);
        }
        q[rev] = p[i];
    }
    swap(p, q);
    for (int b = 1; b < N; b <<= 1) {
        T w = root_of_unity<T>::f(2*b);
        if (inverse) w = T(1) * inv(T(w));
        for (auto [i, x] = std::pair(0, T(1)); i < N; ++i, x = x * w) {
            q[i] = p[i & ~b] + x * p[i | b];
        }
        swap(p, q);
    }
    if (inverse) {
        auto v = T(N), iv = inv(v);
        T inv = T(1) * iv;
        for (int i = 0; i < N; ++i) p[i] = p[i] * inv;
    }
    return p;
}

constexpr int threshold = 64;
template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    int N = p.size(), M = q.size();
    int K = N + M - 1, S = nxt_pow2(K);
    vector<T> res(K);
    if (min(N, M) <= threshold) {
        for (int a = 0; a < N; ++a) 
            for (int b = 0; b < M; ++b) 
                res[a + b] = res[a + b] + p[a] * q[b];
    } else {
        p.resize(S), q.resize(S);
        auto phat = fft(std::move(p), false);
        auto qhat = fft(std::move(q), false);
        for (int i = 0; i < S; ++i) {
            phat[i] = phat[i] * qhat[i];
        }
        res = fft(std::move(phat), true);
        res.resize(K);
    }
    return res;
}
