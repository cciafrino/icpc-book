/**
 * Author: Yui Hosaka
 * Date: 2021
 * License: CC0
 * Source: libra
 * Description: radix 3 FFT, can be used for convolutions modulo arbitrary integers
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: stress-tested
 */
#include "../number-theory/modular-arithmetic.h"

// M: prime, G: primitive root, 2^K | M - 1
template<unsigned M_, unsigned G_, int K_ > struct FFT {
    static_assert(2U <= M_, "Fft: 2 <= M must hold.");
    static_assert(M_ < 1U << 30, "Fft: M < 2^30 must hold.");
    static_assert(1 <= K_, "Fft: 1 <= K must hold.");
    static_assert(K_ < 30, "Fft: K < 30 must hold.");
    static_assert(!((M_ - 1U) & ((1U << K_) - 1U)), "Fft: 2^K | M - 1 must hold.");
    static constexpr unsigned M = M_;
    static constexpr unsigned M2 = 2U * M_;
    static constexpr unsigned G = G_;
    static constexpr int K = K_;
    modnum<M> FFT_ROOTS[K + 1], INV_FFT_ROOTS[K + 1];
    modnum<M> FFT_RATIOS[K], INV_FFT_RATIOS[K];
    constexpr FFT() {
        const modnum<M> g(G);
        for (int k = 0; k <= K; ++k) {
            FFT_ROOTS[k] = g.pow((M - 1U) >> k);
            INV_FFT_ROOTS[k] = FFT_ROOTS[k].inv();
        }
        for (int k = 0; k <= K - 2; ++k) {
            FFT_RATIOS[k] = -g.pow(3U * ((M - 1U) >> (k + 2)));
            INV_FFT_RATIOS[k] = FFT_RATIOS[k].inv();
        } assert(FFT_ROOTS[1] == M - 1U);
    }
    // as[rev(i)] <- \sum_j \zeta^(ij) as[j]
    void fft(modnum<M>* as, int n) const {
        assert(!(n & (n - 1)));
        assert(1 <= n);
        assert(n <= 1 << K);
        int m = n;
        if (m >>= 1) {
            for (int i = 0; i < m; ++i) {
                const unsigned x = as[i + m].x; // < M
                as[i + m].x = as[i].x + M - x; // < 2 M
                as[i].x += x; // < 2 M
            }
        }
        if (m >>= 1) {
            modnum<M> prod = 1U;
            for (int h = 0, i0 = 0; i0 < n; i0 += (m << 1)) {
                for (int i = i0; i < i0 + m; ++i) {
                    const unsigned x = (prod * as[i + m]).x; // < M
                    as[i + m].x = as[i].x + M - x; // < 3 M
                    as[i].x += x; // < 3 M
                }
                prod *= FFT_RATIOS[__builtin_ctz(++h)];
            }
        }
        for (; m;) {
            if (m >>= 1) {
                modnum<M> prod = 1U;
                for (int h = 0, i0 = 0; i0 < n; i0 += (m << 1)) {
                    for (int i = i0; i < i0 + m; ++i) {
                        const unsigned x = (prod * as[i + m]).x; // < M
                        as[i + m].x = as[i].x + M - x; // < 4 M
                        as[i].x += x; // < 4 M
                    }
                    prod *= FFT_RATIOS[__builtin_ctz(++h)];
                }
            }
            if (m >>= 1) {
                modnum<M> prod = 1U;
                for (int h = 0, i0 = 0; i0 < n; i0 += (m << 1)) {
                    for (int i = i0; i < i0 + m; ++i) {
                        const unsigned x = (prod * as[i + m]).x; // < M
                        as[i].x = (as[i].x >= M2) ? (as[i].x - M2) : as[i].x; // < 2 M
                        as[i + m].x = as[i].x + M - x; // < 3 M
                        as[i].x += x; // < 3 M
                    }
                    prod *= FFT_RATIOS[__builtin_ctz(++h)];
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            as[i].x = (as[i].x >= M2) ? (as[i].x - M2) : as[i].x; // < 2 M
            as[i].x = (as[i].x >= M) ? (as[i].x - M) : as[i].x; // < M
        }
    }
    // as[i] <- (1/n) \sum_j \zeta^(-ij) as[rev(j)]
    void inverse_fft(modnum<M> * as, int n) const {
        assert(!(n & (n - 1)));
        assert(1 <= n);
        assert(n <= 1 << K);
        int m = 1;
        if (m < n >> 1) {
            modnum<M> prod = 1U;
            for (int h = 0, i0 = 0; i0 < n; i0 += (m << 1)) {
                for (int i = i0; i < i0 + m; ++i) {
                    const unsigned long long y = as[i].x + M - as[i + m].x; // < 2 M
                    as[i].x += as[i + m].x; // < 2 M
                    as[i + m].x = (prod.x * y) % M; // < M
                }
                prod *= INV_FFT_RATIOS[__builtin_ctz(++h)];
            }
            m <<= 1;
        }
        for (; m < n >> 1; m <<= 1) {
            modnum<M> prod = 1U;
            for (int h = 0, i0 = 0; i0 < n; i0 += (m << 1)) {
                for (int i = i0; i < i0 + (m >> 1); ++i) {
                    const unsigned long long y = as[i].x + M2 - as[i + m].x; // < 4 M
                    as[i].x += as[i + m].x; // < 4 M
                    as[i].x = (as[i].x >= M2) ? (as[i].x - M2) : as[i].x; // < 2 M
                    as[i + m].x = (prod.x * y) % M; // < M
                }
                for (int i = i0 + (m >> 1); i < i0 + m; ++i) {
                    const unsigned long long y = as[i].x + M - as[i + m].x; // < 2 M
                    as[i].x += as[i + m].x; // < 2 M
                    as[i + m].x = (prod.x * y) % M; // < M
                }
                prod *= INV_FFT_RATIOS[__builtin_ctz(++h)];
            }
        }
        if (m < n) {
            for (int i = 0; i < m; ++i) {
                const unsigned y = as[i].x + M2 - as[i + m].x; // < 4 M
                as[i].x += as[i + m].x; // < 4 M
                as[i + m].x = y; // < 4 M
            }
        }
        const modnum<M> invN = modnum<M>(n).inv();
        for (int i = 0; i < n; ++i) as[i] *= invN;
    }
    void fft(vector<modnum<M>>& as) const { fft(as.data(), size(as)); }
    void inverse_fft(vector<modnum<M>>& as) const { inverse_fft(as.data(), size(as)); }
    vector<modnum<M>> convolve(vector<modnum<M>> as, vector<modnum<M>> bs) const {
        if (empty(as) || empty(bs)) return {};
        const int len = size(as) + size(bs) - 1;
        int n = 1; for (; n < len; n <<= 1) {}
        as.resize(n); fft(as);
        bs.resize(n); fft(bs);
        for (int i = 0; i < n; ++i) as[i] *= bs[i];
        inverse_fft(as); as.resize(len); return move(as);
    }
    vector<modnum<M>> square(vector<modnum<M>> as) const {
        if (empty(as)) return {};
        const int len = size(as) + size(as) - 1;
        int n = 1;
        for (; n < len; n <<= 1) {}
        as.resize(n); fft(as);
        for (int i = 0; i < n; ++i) as[i] *= as[i];
        inverse_fft(as); as.resize(len); return move(as);
    }
};

const FFT<998244353, 3, 22> fft_data;
