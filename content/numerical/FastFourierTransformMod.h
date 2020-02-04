/**
 * Author: chilli
 * Date: 2019-04-25
 * License: CC0
 * Source: http://neerc.ifmo.ru/trains/toulouse/2017/fft2.pdf
 * Description: Higher precision FFT, can be used for convolutions modulo arbitrary integers
 * as long as $N\log_2N\cdot \text{mod} < 8.6 \cdot 10^{14}$ (in practice $10^{16}$ or higher).
 * Inputs must be in $[0, \text{mod})$.
 * Time: O(N \log N), where $N = |A|+|B|$ (twice as slow as NTT or FFT)
 * Status: somewhat tested
 */
typedef unsigned int uint;
typedef long double ldouble;

template<typename T, typename U, typename B> struct ModularFFT {
    inline T ifmod(U v, T mod) { return v >= (U)mod ? v - mod : v; }
    T pow(T x, U y, T p) {
        T ret = 1, x2p = x;
        while (y) {
            if (y % 2) ret = (B)ret * x2p % p;
            y /= 2; x2p = (B)x2p * x2p % p;
        }
        return ret;
    }
    vector<T> fft(vector<T> y, T mod, T gen, bool invert = false) {
        int N = y.size(); assert(N == (N&-N));
        if (N == 0) return move(y);
        vector<int> rev(N);
        for (int i = 1; i < N; ++i) {
            rev[i] = (rev[i>>1]>>1) | (i&1 ? N>>1 : 0);
            if (rev[i] < i) swap(y[i], y[rev[i]]);
        }
        assert((mod-1)%N == 0);
        T rootN = pow(gen, (mod-1)/N, mod);
        if (invert) rootN = pow(rootN, mod-2, mod);
        vector<T> rootni(N/2);
        for (int n = 2; n <= N; n *= 2) {
            T rootn = pow(rootN, N/n, mod);
            rootni[0] = 1;
            for (int i = 1; i < n/2; ++i) rootni[i] = (B)rootni[i-1] * rootn % mod;
            for (int left = 0; left != N; left += n) {
                int mid = left + n/2;
                for (int i = 0; i < n/2; ++i) {
                    T temp = (B)rootni[i] * y[mid+i] % mod;
                    y[mid+i] = ifmod((U)y[left+i] + mod - temp, mod);
                    y[left+i] = ifmod((U)y[left+i] + temp, mod);
                }
            }
        }
        if (invert) {
            T invN = pow(N, mod-2, mod);
            for (T &v : y) v = (B)v * invN % mod;
        }
        return move(y);
    }
    vector<T> convolution(vector<T> a, vector<T> b, T mod, T gen) {
        int N = a.size()+b.size()-1, N2 = nextpow2(N);
        a.resize(N2); b.resize(N2);
        vector<T> fa = fft(move(a), mod, gen), fb = fft(move(b), mod, gen), &fc = fa;
        for (int i = 0; i < N2; ++i) fc[i] = (B)fc[i] * fb[i] % mod;
        vector<T> c = fft(move(fc), mod, gen, true);
        c.resize(N); return move(c);
    }
    vector<T> self_convolution(vector<T> a, T mod, T gen) {
        int N = 2*a.size()-1, N2 = nextpow2(N);
        a.resize(N2);
        vector<T> fc = fft(move(a), mod, gen);
        for (int i = 0; i < N2; ++i) fc[i] = (B)fc[i] * fc[i] % mod;
        vector<T> c = fft(move(fc), mod, gen, true);
        c.resize(N); return move(c);
    }
    uint nextpow2(uint v) { return v ? 1 << __lg(2*v-1) : 1; }
};

const int mod = 998244353, mod_gen = 3;

vector<int> convolute(const vector<int> &a, const vector<int> &b) {
    if (a.empty() || b.empty()) return {};
    ModularFFT<int, uint, lint> modular_fft;
    return modular_fft.convolution(a, b, mod, mod_gen);
}
 
vector<int> convolute_all(const vector<vector<int>> &polys, int begin,
                          int end) {
    if (end - begin == 0) return {1};
    else if (end - begin == 1) return polys[begin];
    else {
        int mid = begin + (end - begin) / 2;
        return convolute(convolute_all(polys, begin, mid),
                         convolute_all(polys, mid, end));
    }
}

vector<int> convolute_all(const vector<vector<int>> &polys) {
  return convolute_all(polys, 0, (int)polys.size());
}