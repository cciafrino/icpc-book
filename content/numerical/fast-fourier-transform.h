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
template<typename T> struct root_of_unity {
    T operator()(int N) const = delete; // not implemented
};
template<typename T>
struct root_of_unity<std::complex<T>> {
    inline static const T PI = std::acos(-1);
    std::complex<T> operator()(int N) const {
        return std::polar<T>(1, 2 * PI / N);
    }
};

template<typename T>
vector<T> fft(std::vector<T> p, bool inverse) { // df3434
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
    root_of_unity<T> rt;
    for (int b = 1; b < N; b <<= 1) {
        T w = rt(b << 1);
        if (inverse) w = T(1) / w;
        for (auto [i, x] = std::pair(0, T(1)); i < N; ++i, x *= w) {
            q[i] = p[i & ~b] + x * p[i | b];
        }
        swap(p, q);
    }
    if (inverse) {
        T inv = T(1) / T(N);
        for (int i = 0; i < N; ++i) p[i] *= inv;
    }
    return p;
}

template<typename T>
vector<T> operator*(vector<T> p, vector<T> q) {
    int N = p.size() + q.size() - 1, M = 1;
    while (M < N) M <<= 1;
    p.resize(M), q.resize(M);
    auto phat = fft(p, false), qhat = fft(q, false);
    for (int i = 0; i < M; ++i) {
        phat[i] *= qhat[i];
    }
    auto r = fft(phat, true);
    r.resize(N);
    return r;
}
