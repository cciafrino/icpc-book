/**
 * Author: Felipe Abella
 * Date: 2019-01-09
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf (do read, it's excellent)
   Accuracy bound from http://www.daemonology.net/papers/fft.pdf
 * Description: fft(a) computes $\hat f(k) = \sum_x a[x] \exp(2\pi i \cdot k x / N)$ for all $k$. Useful for convolution:
   \texttt{conv(a, b) = c}, where $c[x] = \sum a[i]b[x-i]$.
   For convolution of complex numbers or more than two vectors: FFT, multiply
   pointwise, divide by n, reverse(start+1, end), FFT back.
   Rounding is safe if $(\sum a_i^2 + \sum b_i^2)\log_2{N} < 9\cdot10^{14}$
   (in practice $10^{16}$; higher for random inputs).
   Otherwise, use long doubles/NTT/FFTMod.
 * Time: O(N \log N) with $N = |A|+|B|$ ($\tilde 1s$ for $N=2^{22}$)
 * Status: somewhat tested
 */
using doublex = complex<long double>;
struct FFT {
    using i64 = int64_t;
    vector<doublex> fft(vector<doublex> y, bool invert = false) {
        const int N = int(y.size()); assert(N == (N&-N));
        vector<i64> rev(N);
        for (int i = 1; i < N; ++i) {
            rev[i] = (rev[i>>1]>>1) | (i&1 ? N>>1 : 0);
            if (rev[i] < i) swap(y[i], y[rev[i]]);
        }
        vector<doublex> rootni(N/2);
        for (int n = 2; n <= N; n *= 2) {
            const doublex rootn = polar(1.0, (invert ? +1.0 : -1.0) * 2.0*acos(-1.0)/n);
            rootni[0] = 1.0;
            for (int i = 1; i < n/2; ++i) rootni[i] = rootni[i-1] * rootn;
            for (int left = 0; left != N; left += n) {
                const int mid = left + n/2;
                for (int i = 0; i < n/2; ++i) {
                    const doublex temp = rootni[i] * y[mid + i];
                    y[mid + i] = y[left + i] - temp; y[left + i] += temp;
                }
            }
        } if (invert) for (auto &v : y) v /= (doublex)N;
        return move(y);
    }
    uint32_t nextpow2(uint32_t v) { return v ? 1 << __lg(2*v-1) : 1; }
    vector<doublex> convolution(vector<doublex> a, vector<doublex> b) {
        const i64 n = max(int(a.size()) + int(b.size()-1), 0), n2 = nextpow2(n);
        a.resize(n2); b.resize(n2);
        vector<doublex> fa = fft(move(a)), fb = fft(move(b)), &fc = fa;
        for (int i = 0; i < n2; ++i) fc[i] = fc[i] * fb[i];
        vector<doublex> c = fft(move(fc), true);
        c.resize(n);
        return move(c);
    }
};
